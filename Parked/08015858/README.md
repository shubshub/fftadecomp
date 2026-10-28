# 08015858: unresolved tilemap setup code generation

Complete target: `[0x08015858, 0x08015C90)`, **1080 bytes / 501 reachable instructions**, unchanged indexed endpoints. The recovered C is plausible but **not byte-identical**. This is an unresolved match, not a claim of unmatchability.

The final native matcher invocation used `agbcc -mthumb-interwork -O2` and the approved ROM directly. It exited **1**, accepted the complete **1080-byte ELF symbol** and ordinary caller/frame/data profile, and reported **480/501 aligned instructions / 1050/1080 aligned bytes**. Direct same-offset comparison has **56 differing bytes across 30 halfwords**.

Remaining differences are limited to:

- `0801589E..080158B2`: the initial map pointer, paired-row stride calculation and copies are scheduled differently. The candidate computes the two equivalent stride scales separately; the target computes one scale and copies it.
- `080159DA..080159FA`: the first reverse label loop loads its tile constant and counter before the geometry calculations that the target places first. Register allocation also differs in this setup.
- `08015A1A..08015A1E` and `08015AC0..08015AC4`: each later reverse label loop loads the tile constant before its counter; the target reverses those two loads.

All remaining bytes are identical at their original addresses, including the final **460 bytes** from `08015AC4` through the epilogue.

Natural direct loops, signed and unsigned geometry/label locals, pointer/index grouping, and legitimate inline loop helpers were tried with fixed flags. None resolved the setup differences. No assembly, volatile, pragmas, altered endpoints, dead operations or compiler-flag changes were used. There is no missing runtime helper or metadata rejection.

The candidate was verified in the private thin root with copied maps/indexes and a symlink to the approved headers. The final native report is `/home/user/.codex-work/ffta-ulw/audio-following-v73-matching/08015858/native-match.md`; the command below expects this exact source temporarily at private `src/08015858.c`:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x08015858
```

Main `src/08015858.c` and its active report remain absent. Root owns lease release.
