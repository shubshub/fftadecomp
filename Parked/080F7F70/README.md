# 080F7F70: byte-identical; no selector admits a stack-indexed ROM table copy together with a looped `func_08005B6C` call

Target: `[0x080F7F70, 0x080F830C)`, 924 bytes. A phase callback, `u32 f(task, descriptor, payload)`, with an eight-case switch on `descriptor->phase` (0, 1, 0x100..0x105). Phase 0x101:

- copies the five-byte ROM table at `0x08149D5C` (`00 28 1E 14 0A`) to the stack with `func_081443FC`;
- stores the `u8` result of `func_080D8924` in `payload->count` (the byte at `payload + 8`) and reads `delays[payload->count]`;
- in a `u8` loop over `i < payload->count`, fills a 28-byte stack descriptor and calls `func_08005B6C(func_080F7EC0, 0x20, &child, task)` at `0x080F815C`, adding 10 to the delay each time.

## Byte identity

`080F7F70.c` writes the table copy as a call, `func_081443FC(delays, data_08149D5C, sizeof(delays));`. It was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 924 bytes, and every byte outside a relocation field equals the ROM;
- the 33 `R_ARM_THM_CALL` and 14 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_080F7EC0` as a Thumb address).

The literal at `0x080F8188` is the only aligned word in the ROM with the table's address. `match.py` does not reach its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/080F7F70/080F7F70.c src/080F7F70.c
# config/data_symbols.json: add the nine symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x080F7F70
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x080F7F70
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`. Selector names written `-...` share the `conditional-scheduler` prefix.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `named-data-buffer-stack-index-v2`, `named-data-buffer-stack-index-v1` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-three-per-path-calls-v1` | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |

The stack-index walk follows `&child` into the scheduler: `0x08005B6C` calls `0x08005954`, which calls the callback through `_call_via_r3` at `0x08142250`, and the walk stops there. The live-alias scheduler selector stops at the table copy, where the address of `delays` is passed to `func_081443FC`. The function has 387 reachable instructions, 33 call sites and 28 ordinary call targets; the two `requires a complete bounded instruction graph` selectors allow 256 instructions.

### With the table copy written as an initialiser

`u8 delays[5] = {0, 40, 30, 20, 10};` in a block of the case gives the same 924 bytes; the compiler then emits the table as `.rodata` and calls `memcpy`. The default run and `conditional-scheduler-three-per-path-live-alias-v1` then refuse with `unexpected nonempty allocated section`; `named-data-buffer-stack-index-v2` and `named-data-buffer-rom-table-copy-v1` refuse as above.

## The index

```
080F8138  ldrb r1, [r4, #8]      @ payload->count, stored at 0x080F8136 from func_080D8924's result
080F813A  adds r0, r5, r1
080F813C  ldrb r6, [r0]          @ delays[payload->count]
```

The table has five bytes, so a stack-index profile needs a premise for the load at `0x080F813C`: the byte read at `0x080F8138` is at most 4 (bound 5). That is not proven. `func_080D8924` is not matched on main and its result has not been traced.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_08149D5C": "0x08149D5C"`):

`data_08149D5C`, `data_0839BE74`, `data_0839BE7C`, `data_0839BEB0`, `data_0839BEB8`, `data_0839BEBC`, `data_0839BED0`, `data_0839BED4`, `data_0894A370`.

## Source notes

- The file declares its own `extern u16 g_control_flags_03000940;`, as 90 sources on main do, instead of including `control_flags.h`. With the header and `.display` the bytes are the same and `plausible.py --strict` still exits 0, but a selector run then stops before its profile (checked with `named-data-buffer-stack-index-v2` and `conditional-scheduler-three-per-path-live-alias-v1`). It stops at the allowlisted volatile semantic check: `more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled)`.
- The flag update of phase 0x101 goes through a `u16` temporary, the spelling of the matched `src/08108D9C.c` and `src/081072B0.c`. Written as `g_control_flags_03000940 |= func_080035A8(2);` the function is 922 bytes.
- `parity` in phase 0x104 is `u32`. With `u8`, as the matched `src/080FFEC0.c` has it, the function is 924 bytes of which 14 differ.

kit issue: (to be filed)
