# 0810BEA0: byte-identical; no selector admits a stack-indexed ROM table copy together with a looped `func_08005B6C` call

Target: `[0x0810BEA0, 0x0810C244)`, 932 bytes. A phase callback, `u32 f(task, descriptor, payload)`, with an eight-case switch on `descriptor->phase` (0, 1, 0x100..0x105). Phase 0x101:

- copies the three-byte ROM table at `0x08149F20` (`06 00 0C`) to the stack;
- passes the addresses of local `s16` values to `func_080DBDC8` and, twice, to `func_080DBDA0`;
- in a `u8` loop over 0..2, fills a 28-byte stack descriptor with `delay = delays[i]` and calls `func_08005B6C(func_0810BB70, 0xCC, &child, task)` at `0x0810C05C`.

Phase 0x103 has a second counted loop, with no call in it.

## Byte identity

`0810BEA0.c` writes the table copy as an initialiser, `u8 delays[3] = {6, 0, 12};`. It was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 932 bytes, and every byte outside a relocation field equals the ROM;
- the 32 `R_ARM_THM_CALL` and 10 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_0810BB70` as a Thumb address);
- `memcpy` resolves to `0x081443FC`, and the 3 bytes of `.rodata` resolve to `0x08149F20`, where the ROM holds the same bytes. The literal at `0x0810C080` is the only aligned word in the ROM with that address.

`match.py` does not reach its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/0810BEA0/0810BEA0.c src/0810BEA0.c
# config/data_symbols.json: add the eight symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x0810BEA0
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x0810BEA0
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`. Selector names written `-...` share the `conditional-scheduler` prefix.

| Selector | Refusal |
|---|---|
| default | `unexpected nonempty allocated section` |
| `named-data-buffer-stack-index-v2` | `buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `named-data-buffer-stack-index-v1`, `named-data-buffer-rom-table-copy-v1` | `buffer callee 0x080DBDC8: unsupported buffer pointer use or escape` |
| `conditional-scheduler-three-per-path-live-alias-v1`, `-three-per-path-calls-v1`, `-sequential-live-alias-counted-loops-v1`, `-u16-counted-loop-v1`, `-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `unexpected nonempty allocated section` |

The `-stack-index-v2` walk follows `&child` into the scheduler: `0x08005B6C` calls `0x08005954`, which calls the callback through `_call_via_r3` at `0x08142250`, and the walk stops there. The scheduler selectors stop at the `.rodata` the initialiser produces.

### With the table copy written as a call

Replacing the initialiser by `u8 delays[3];` and `func_081443FC(delays, data_08149F20, sizeof(delays));` as the first statement of the case gives the same 932 bytes (it also needs `data_08149F20`). The three `named-data-buffer-*` refusals stay as above. The others become:

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `counted loop increments a different or caller-clobbered counter` |
| `conditional-scheduler-three-per-path-calls-v1` | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |

The counted-loop rule wants the counter in R4-R7. The scheduler loop keeps its counter in R4; the phase 0x103 loop keeps it in R1 (`adds r0, r1, #1` at `0x0810C112`). The function has 404 reachable instructions, more than the 256 the two `requires a complete bounded instruction graph` selectors allow.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A2218": "0x083A2218"`):

`data_083A2218`, `data_083A2260`, `data_083A2290`, `data_083A22C0`, `data_083A22C4`, `data_083A22C8`, `data_083A22D0`, `data_083A22D8`.

## Source notes

- One function-scope `u8 i` in place of the two block-scoped ones gives 932 bytes of which 10 differ, all in the phase 0x103 loop.
- The `extern void *memcpy(...)` declaration does not change the bytes. The matched `src/0810533C.c` has the same line.
- `payload->countdown = 10` is stored on every iteration of the scheduler loop; moved after the loop, 14 bytes differ.
- The callback `func_0810BB70` is not matched on main.

kit issue: (to be filed)
