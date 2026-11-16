# 080F6060: byte-identical; 44 call sites against the 40 call-site budget of the three-per-path scheduler selectors

Target: `[0x080F6060, 0x080F648E)`, 1,070 bytes. A phase callback, `u32 f(context, command, state)`, with an eleven-case switch on `command->state` (0, 1, 0x100..0x108), written in the form of the matched `src/080FC13C.c`. Phase 0x105 fills a 28-byte stack descriptor and calls `func_08005B6C(func_080F5F7C, 0x24, &descriptor, context)` at `0x080F63C4`. That is the only scheduler site. The function has no loop.

As the kit counts them: 435 reachable instructions, 44 call sites (the scheduler site and 43 others), 28 ordinary call targets.

## Byte identity

`080F6060.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 1,070 bytes, and every byte outside a relocation field equals the ROM (the object's `.text` has two more bytes, the assembler's alignment fill after the symbol);
- the 44 `R_ARM_THM_CALL` and 19 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_080F5F7C` as a Thumb address).

`match.py` on kit main does not reach its own byte comparison (below). A scratch copy of the kit with the two call-site budgets changed from 40 to 48, and nothing else, reports `MATCH - byte identical` for this file under both three-per-path selectors. `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/080F6060/080F6060.c src/080F6060.c
# config/data_symbols.json: add the eleven symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x080F6060
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x080F6060
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`. Selector names written `-...` share the `conditional-scheduler` prefix.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-three-per-path-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `scheduler loop composition exceeds the explicit call-site or target bounds` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |

The two three-per-path selectors allow 32 ordinary targets and 40 call sites (`tools/scheduler_branch_profile.py:48`, `tools/scheduler_loop_composition_profile.py:88`); `-three-per-path-live-alias-v1` also allows 512 instructions and eight scheduler sites, `-three-per-path-calls-v1` four scheduler sites. This function is inside every one of those except the call sites: 44 against 40.

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_0839B664": "0x0839B664"`):

`data_0839B664`, `data_0839B6C4`, `data_0839B6DC`, `data_0839B754`, `data_0839B780`, `data_0839B794`, `data_0839B798`, `data_0839B7A0`, `data_0839B7A8`, `data_088EF44C`, `data_0894D91C`.

kit issue: shubshub/fftadecomp-kit#197
