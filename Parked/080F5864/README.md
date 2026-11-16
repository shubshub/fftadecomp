# 080F5864: byte-identical; the looped `func_08005B6C` site keeps the descriptor address in R6

Target: `[0x080F5864, 0x080F5BE2)`, 894 bytes. A phase callback, `u32 f(task, descriptor, state)`, with an eleven-case switch on `descriptor->phase` (0, 1, 0x100..0x108). Phase 0x104 stores the `u8` result of `func_080D8858` in `state->count` and, in a `u8` loop over `i < state->count`, fills a 28-byte stack descriptor and calls `func_08005B6C(func_080F5710, 0x1C, &child, task)` at `0x080F5ABA`. That is the only scheduler site. Phase 0x108 has a second counted loop, over four entries.

## Byte identity

`080F5864.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 894 bytes, and every byte outside a relocation field equals the ROM (the object's `.text` has two more bytes, the assembler's alignment fill after the symbol);
- the 27 `R_ARM_THM_CALL` and 10 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_080F5710` as a Thumb address).

`match.py` on kit main does not reach its own byte comparison (below). A scratch copy of the kit in which the looped-site check also lets through a register outside `match.CALLER_CLOBBERED` whose frame offset equals the R2 descriptor's, with nothing else changed, reports `MATCH - byte identical` for this file under `conditional-scheduler-three-per-path-live-alias-v1`. `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/080F5864/080F5864.c src/080F5864.c
# config/data_symbols.json: add the eight symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x080F5864
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x080F5864
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`. Selector names written `-...` share the `conditional-scheduler` prefix.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `looped scheduler calls exclude every local alias other than the R2 descriptor` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-calls-v1`, `-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1` | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-branch-descriptor-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |

The function has 384 reachable instructions, more than the 256 the two `requires a complete bounded instruction graph` selectors allow.

## Cause

```
080F5A9C  add  r6, sp, #0x14      @ &child, before the loop header at 0x080F5A9E
080F5A9E  strh r5, [r6, #0x14]    @ child.mode
080F5AB6  add  r2, sp, #0x14      @ &child again, for the call
080F5ABA  bl   0x08005B6C
```

The halfword fields of the descriptor are stored through R6, which holds the descriptor address across the call. The kit's own alias state at `0x080F5ABA` is R2 and R6, both at entry SP - 56. The rule refuses any alias other than R2 at a looped scheduler site (`tools/conditional_local_buffer_profile.py:324`).

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_0839B418": "0x0839B418"`):

`data_0839B418`, `data_0839B454`, `data_0839B46C`, `data_0839B49C`, `data_0839B4B0`, `data_0839B4B4`, `data_0839B4B8`, `data_0839B4C0`.

## Source notes

- `parity` in phase 0x107 is `u32`. With `u8`, as the matched `src/080FFEC0.c` has it, the function is 894 bytes of which 16 differ.
- The child descriptor's field names follow the matched `src/080F5710.c`.

kit issue: shubshub/fftadecomp-kit#198
