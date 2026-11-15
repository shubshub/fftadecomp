# 081204A8: byte-identical; the looped `func_08005B6C` site keeps the descriptor address in R7

Target: `[0x081204A8, 0x08120722)`, 634 bytes. A phase callback, `u32 f(parent, script, payload)`. It returns 0 at once when `payload->flags & 0x8000` is set; otherwise it runs an eight-case switch on `script->state` (0, 1, 0x100..0x105). It has three scheduler sites, each with a 28-byte stack descriptor:

- `0x08120584`, phase 0x101: `func_08005B6C(func_0811F95C, 0x103C, &loader, parent)`;
- `0x081205E2`, phase 0x102: `func_08005B6C(func_0811FFD8, 0x44, &child, parent)`;
- `0x0812061A`, phase 0x102: `func_08005B6C(func_08120398, 0x18, &child, parent)` in a `u8` loop over 0..3.

## Byte identity

`081204A8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and the object was compared with the ROM span:

- the function symbol is 634 bytes, and every byte outside a relocation field equals the ROM (the object's `.text` has two more bytes, the assembler's alignment fill after the symbol);
- the 19 `R_ARM_THM_CALL` and 11 `R_ARM_ABS32` relocations, read back from the ROM bytes, give one address per symbol, and it is the address in the symbol's name (`func_0811F95C`, `func_0811FFD8` and `func_08120398` as Thumb addresses).

`match.py` on kit main does not reach its own byte comparison (below). A scratch copy of the kit in which the looped-site check also lets through a register outside `match.CALLER_CLOBBERED` whose frame offset equals the R2 descriptor's, with nothing else changed, reports `MATCH - byte identical` for this file under `conditional-scheduler-three-per-path-live-alias-v1`. `plausible.py --strict` exits 0.

## Refusals

Kit `fcdf2d45`, decomp `main` at `85906dfe` (and `8baf0d65`) with this directory added, from the decomp root:

```sh
cp Parked/081204A8/081204A8.c src/081204A8.c
# config/data_symbols.json: add the five symbols listed under "Data symbols"
python ../fftadecomp-kit/tools/match.py --root . --no-write 0x081204A8
python ../fftadecomp-kit/tools/match.py --root . --no-write --owner-runtime-profile <selector> 0x081204A8
```

Every run exits 1. The default run prints the text below after `compile failed:`. A selector run prints it as `error (ValueError): <text> (set FFTA_TRACEBACK=1 for a traceback)`. Selector names written `-...` share the `conditional-scheduler` prefix.

| Selector | Refusal |
|---|---|
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `conditional-scheduler-three-per-path-live-alias-v1` | `looped scheduler calls exclude every local alias other than the R2 descriptor` |
| `conditional-scheduler-sequential-live-alias-counted-loops-v1` | `scheduler loop composition requires a complete bounded instruction graph` |
| `conditional-scheduler-u16-counted-loop-v1` | `counted scheduler loop requires a complete bounded instruction graph` |
| `conditional-scheduler-three-per-path-calls-v1` | `predicate composition excludes CFG cycles` |
| `conditional-scheduler-twenty-four-target-branches-v1`, `-twenty-four-target-following-calls-v1`, `-live-local-alias-calls-v1`, `-branch-descriptor-calls-v1` | `scheduler branches exceed the explicit call-site or target bounds` |

The function has 264 reachable instructions, more than the 256 the two `requires a complete bounded instruction graph` selectors allow.

## Cause

```
081205F0  adds r7, r4, #0         @ &child, before the loop header at 0x081205F2
081205F4  strh r0, [r7, #0x14]    @ child.category
08120616  adds r2, r7, #0         @ &child for the call
0812061A  bl   0x08005B6C
```

The descriptor fields are stored through R7, which holds the descriptor address across the call. The kit's own alias state at `0x0812061A` is R2 and R7, both at entry SP - 60. The rule refuses any alias other than R2 at a looped scheduler site (`tools/conditional_local_buffer_profile.py:324`).

## Data symbols

Not in `config/data_symbols.json` on main; each is added with its address as the value (`"data_083A7498": "0x083A7498"`):

`data_083A7498`, `data_083A7A0C`, `data_083A7A20`, `data_088F3D90`, `data_0894DF44`.

## Source notes

- The callbacks `func_0811F95C` and `func_0811FFD8` are not matched on main; `func_08120398` is.

kit issue: (to be filed)
