# 08117320: byte-identical; the looped `func_08005B6C` site keeps the descriptor address in R4

Target: `[0x08117320, 0x081175D2)`, 690 bytes. A phase callback, `u32 f(owner, event, state)`, with a nine-case switch on `event->phase` (0, 1, 0x100..0x106). It has two scheduler sites, each with a 28-byte stack descriptor:

- `0x0811740A`, phase 0x100: `func_08005B6C(func_08116F98, 0x34, &intro, owner)`;
- `0x081174B2`, phase 0x102: `func_08005B6C(func_081171CC, 0x1C, &child, owner)` in a `u8` loop over `i < state->count`, where `state->count` is the `u8` result of `func_080D8858`.

Phase 0x106 has a second counted loop, over four entries.

## Byte identity

`08117320.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 690 bytes, and every byte outside a relocation field equals the ROM (the object's `.text` has two more bytes, the assembler's alignment fill after the symbol);
- the 24 `R_ARM_THM_CALL` and 5 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_08116F98` and `func_081171CC` as Thumb addresses).

`match.py` on kit main does not reach its own byte comparison (below). A scratch copy of the kit in which the looped-site check also lets through a register outside `match.CALLER_CLOBBERED` whose frame offset equals the R2 descriptor's, with nothing else changed, reports `MATCH - byte identical` for this file under `conditional-scheduler-three-per-path-live-alias-v1`. `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/08117320/08117320.c src/08117320.c
# config/data_symbols.json: add the three symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x08117320
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x08117320
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

The function has 308 reachable instructions, more than the 256 the two `requires a complete bounded instruction graph` selectors allow.

## Cause

```
08117494  add  r4, sp, #0x28      @ &child, before the loop header at 0x08117496
08117496  strh r6, [r4, #0x14]    @ child.index
081174AE  adds r2, r4, #0         @ &child for the call
081174B2  bl   0x08005B6C
```

The descriptor fields are stored through R4, which holds the descriptor address across the call. The kit's own alias state at `0x081174B2` is R2 and R4, both at entry SP - 56. The rule refuses any alias other than R2 at a looped scheduler site (`tools/conditional_local_buffer_profile.py:324`).

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A506C": "0x083A506C"`):

`data_083A506C`, `data_083A50C0`, `data_083A50D4`.

## Source notes

- Phase 0x104 falls through into phase 0x105 after its `event->phase++`, as a phase of the matched `src/080F2FFC.c` does.
- `odd` is `int`; `u32` gives the same bytes. With `u8` the function is 690 bytes of which 16 differ.

kit issue: (to be filed)
