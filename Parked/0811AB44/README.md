# 0811AB44: unresolved display-byte accesses

Target: complete `[0x0811AB44, 0x0811ACF2)`, **430 bytes / 189 reachable instructions**, unchanged indexed endpoints. This candidate is **not a match** and must remain outside `src/`.

Fixed compiler: `agbcc -mthumb-interwork -O2`. One natural C candidate was checked with the exact native command:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python ../fftadecomp-kit/tools/match.py --root . 0x0811AB44
```

Native exit **1**: `compiled symbol is shorter than the indexed span: 406 < 430`. The command stops at the size check and emits no match report or plausibility verdict. No match credit or callee-contract proof is claimed.

The target reads display-state bytes before full-byte stores at:

| Target address | Global offset | Stored value |
| --- | --- | --- |
| `0811AB78` | `03000940 + 42` | `1F` |
| `0811AB82` | `03000940 + 43` | `3F` |
| `0811AB8C` | `03000940 + 44` | `1F` |
| `0811AB94` | `03000940 + 3B` | `00` |
| `0811AB9A` | `03000940 + 3A` | `00` |
| `0811ABA0` | `03000940 + 3F` | `00` |
| `0811ABAC` | `03000940 + 3D` | `00` |
| `0811ABB4` | `03000940 + 3C` | `00` |
| `0811ABBC` | `03000940 + 41` | `00` |
| `0811ABC4` | `03000940 + 40` | `FF` |
| `0811AC9C` | `03000940 + 4A` | `00` |

The recovered candidate uses ordinary byte fields, a signed byte at `+40`, aligned halfword flags, two twelve-byte interpolation records, a six-frame delay, and three polled task/window handles. Positioning calls use `(120, 64, current)`; phases are `100`, `101`, and `102` with idle cases `0` and `1`.

The 24-byte size deficit reproduces the known blocker in `Parked/081175D4/README.md` and `Parked/081104DC/README.md`. No instruction-level candidate comparison was performed after the native size rejection, so the precise distribution of those missing bytes is not asserted here. No further variants, alternate flags, assembly, volatile, pragmas, inert code, endpoint changes, or steering workarounds were attempted. Original declarations, object extents, and helper contracts remain unknown.

The single attempted source is preserved as `0811AB44.c`. Full target disassembly, native output, and handoff hashes are in the private task directory `/home/user/.codex-work/ffta-ulw/audio-following-v47-matching/0811AB44/`.
