# 081086D0: byte-identical; no selector admits a stack-indexed ROM table copy together with a looped `func_08005B6C` call

Target: `[0x081086D0, 0x08108A74)`, 932 bytes. A phase callback, `u32 f(task, descriptor, state)`, with an eight-case switch on `descriptor->phase` (0, 1, 0x100..0x105). Phase 0x101:

- copies the five-byte ROM table at `0x08149EDC` (`00 28 1E 14 0A`) to the stack;
- stores the `u8` result of `func_080D8924` in `state->count` (the byte at `state + 8`) and reads `delays[state->count]`;
- in a `u8` loop over `i < state->count`, fills a 28-byte stack descriptor and calls `func_08005B6C(func_08108630, 0x10, &child, task)` at `0x081088CA`, adding 10 to the delay each time.

## Byte identity

`081086D0.c` writes the table copy as an initialiser, `u8 delays[5] = {0, 40, 30, 20, 10};`. It was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 932 bytes, and every byte outside a relocation field equals the ROM;
- the 34 `R_ARM_THM_CALL` and 14 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_08108630` as a Thumb address);
- `memcpy`, which the compiler calls for the initialiser, resolves to `0x081443FC`, and the 5 bytes of `.rodata` resolve to `0x08149EDC`, where the ROM holds the same bytes. The literal at `0x08108908` is the only aligned word in the ROM with that address.

`match.py` does not reach its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/081086D0/081086D0.c src/081086D0.c
# config/data_symbols.json: add the nine symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x081086D0
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x081086D0
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`. Selector names written `-...` share the `conditional-scheduler` prefix.

| Selector | Refusal |
|---|---|
| default | `unexpected nonempty allocated section` |
| `named-data-buffer-stack-index-v2`, `named-data-buffer-stack-index-v1` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-rom-table-copy-v1` | `unsupported stack-alias use or escape` |
| `conditional-scheduler-three-per-path-live-alias-v1`, `-three-per-path-calls-v1`, `-sequential-live-alias-counted-loops-v1`, `-u16-counted-loop-v1`, `-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `unexpected nonempty allocated section` |

The stack-index walk follows `&child` into the scheduler: `0x08005B6C` calls `0x08005954`, which calls the callback through `_call_via_r3` at `0x08142250`, and the walk stops there. The scheduler selectors stop at the `.rodata` the initialiser produces.

### With the table copy written as a call

Replacing the initialiser by `u8 delays[5];` and `func_081443FC(delays, data_08149EDC, sizeof(delays));` as the first statement of the case gives the same 932 bytes (it also needs `data_08149EDC`). The three `named-data-buffer-*` refusals stay as above. The others become:

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `buffer callee 0x081443FC: unsupported buffer pointer use or escape` |
| `conditional-scheduler-three-per-path-calls-v1` | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |

The function has 393 reachable instructions, more than the 256 the two `requires a complete bounded instruction graph` selectors allow.

## The index

```
081088A2  ldrb r1, [r4, #8]      @ state->count, stored at 0x081088A0 from func_080D8924's result
081088A4  adds r0, r5, r1
081088A6  ldrb r7, [r0]          @ delays[state->count]
```

The table has five bytes, so a stack-index profile needs a premise for the load at `0x081088A6`: the byte read at `0x081088A2` is at most 4 (bound 5). That is not proven. `func_080D8924` is not matched on main and its result has not been traced.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A1038": "0x083A1038"`):

`data_083A1038`, `data_083A1050`, `data_083A1058`, `data_083A1070`, `data_083A1094`, `data_083A10AC`, `data_083A10C0`, `data_083A10C4`, `data_0894A26C`.

## Source notes

- The file declares its own `extern u16 g_control_flags_03000940;`, as 90 sources on main do, instead of including `control_flags.h`. With the header and `.display` the bytes are the same and `plausible.py --strict` still exits 0, but a selector run then stops before its profile (checked with `named-data-buffer-stack-index-v2` and `conditional-scheduler-three-per-path-live-alias-v1`). It stops at the allowlisted volatile semantic check, which says of the compiler's `bl memcpy`: `the callee has no prototype with a fixed argument list, so its arguments cannot be compared`.
- The flag update of phase 0x101 goes through a `u16` temporary, the spelling of the matched `src/08108D9C.c` and `src/081072B0.c`. Written as `g_control_flags_03000940 |= func_080035A8(2);` the function is 930 bytes.
- `child` is declared before `delays`. The other order gives 936 bytes.

kit issue: shubshub/fftadecomp-kit#200
