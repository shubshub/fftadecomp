# 081179B4: unresolved display-byte writes

Target: complete `[0x081179B4, 0x08117B9A)`, **486 bytes / 211 reachable instructions**, with unchanged indexed endpoints. This candidate is **not a match** and belongs outside `src/`.

## Native result

Fixed compiler: `agbcc -mthumb-interwork -O2`. With this candidate at `src/081179B4.c`, the prescribed command was:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x081179B4
```

Native exit **1**: `compiled symbol is shorter than the indexed span: 454 < 486`. The native command stops before generating a match report. No match credit or completed plausibility verdict is claimed.

A private diagnostic using the same native compiler and typed linker produces a **454-byte complete symbol / 197 reachable instructions**. Direct same-offset comparison finds **46 equal bytes / 486 target bytes**, with **408 differing present bytes plus 32 absent bytes**. These counts are not sequence-alignment scores.

## Precise remaining differences

The natural candidate omits eleven target byte loads immediately preceding full-byte writes to the display state at `0x03000940`:

| Target load address | Global byte offset |
| --- | --- |
| `0x08117A0C` | `+0x42` |
| `0x08117A14` | `+0x43` |
| `0x08117A26` | `+0x44` |
| `0x08117A2E` | `+0x3B` |
| `0x08117A34` | `+0x3A` |
| `0x08117A3A` | `+0x3F` |
| `0x08117A46` | `+0x3D` |
| `0x08117A4E` | `+0x3C` |
| `0x08117A56` | `+0x41` |
| `0x08117A5C` | `+0x40` |
| `0x08117B34` | `+0x4A` |

The field writes and values remain in the target order, but omitting these loads also changes pointer-register allocation and reduces pointer setup by two instructions overall. The shorter body permits the phase-`101` dispatch to use a short conditional branch, saving another instruction. Both internal pools lose their target two-byte alignment gap. These account for the complete 32-byte size deficit: 28 instruction bytes plus four alignment bytes.

Phase `100` begins at candidate `0x081179E4`, two bytes before target `0x081179E6`. The interpolation initialization begins at candidate `0x08117A56`, 26 bytes before target `0x08117A70`. Phase `101` begins at candidate `0x08117AC0`, 28 bytes before target `0x08117ADC`. Phase `102` begins at candidate `0x08117B40`, 32 bytes before target `0x08117B60`; its task cleanup and return have the same operation sequence with shifted branch/call encodings. The first literal pool is at candidate `0x08117AB4` versus target `0x08117AD0`; the second is at candidate `0x08117B38` versus target `0x08117B58`.

## Recovered behavior and attempts

Phases `0` and `1` do nothing. Phase `100` loads resource `data_088F46CC`, configures two window masks, clears their coordinates, enables both windows, initializes two interpolations from 0 to 64 with durations 60 and 54, sets a six-frame delay, creates two window tasks and a child task, and advances the phase. Phase `101` updates the first interpolation immediately and the second after the delay, then clears the blend byte and control masks when both complete. Phase `102` polls both window tasks and the child task before setting phase 2. Field names describe inferred display-register roles; original declarations and callee contracts remain unknown.

Natural unsigned full-width eight-bit fields, signed eight-bit fields, ordinary byte fields, and `u16`/`u32` bitfield bases were examined with fixed flags. Those forms remove the target's unused reads. A packed aggregate retains unwanted bytewise accesses to the halfword header and changes phase-update sharing; that candidate was 482 bytes and still omitted the eleven target loads. Small isolated layout probes covered packed fields, aggregate alignment, and adjacent subfields; none recovered the target access pattern. The parked candidate keeps aligned halfword control accesses, the ordinary byte at `+3E`, and a signed eight-bit bottom-coordinate field at `+40`.

No alternate flags, assembly, pragmas, volatile qualifiers, inert executable statements, helper calls, endpoint changes, or shared mapping edits were used. The same unresolved family is documented at `Parked/081104DC/README.md`. Raw diagnostics remain in the private task directory. No unmatched active source or match report remains; the coordinator owns reservation release and integration.
