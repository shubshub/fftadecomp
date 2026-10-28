# 0800052C — bounded natural C attempt

Target: `[0x0800052C, 0x0800058C)`, 96 bytes, 24 reachable Thumb instructions. The complete recovered function initializes three callback tables with their corresponding callback/state arrays and capacities 4, 1 and 3, then installs the actual typed Thumb callback 08003660 into slot zero of the third table. Callback types follow the dispatcher ABI: byte index and pointer to state byte. The callback is never represented as addressed data or an integer cast.

Native matcher exit: 1. Actual refusal: `function-address caller differs from the ROM`. This occurs during typed function-address caller validation before source plausibility; there is no native plausibility or exact-match claim and no match credit.

The fixed compiler emits one complete 96-byte ELF function symbol, confirmed with arm-none-eabi-readelf after assembling its output. Its code contains 24 instructions and ten referenced literal words. The ROM starts with `push {r7, lr}; mov r7, sp`, reloads the third table pointer for both final calls, and ends with `pop {r7}; pop {r0}; bx r0`. The compiled natural implementation instead starts with `push {r4, lr}`, retains the third table pointer in r4 across the calls, copies that pointer into r0, and restores r4 at return. The table/callback setup behavior and full symbol size are recovered, but instruction bytes and load scheduling differ.

The direct natural implementation was tested without introducing stack objects or other work absent from the ROM semantics. Matching the explicit frame-pointer setup would require further genuine source/type evidence; no frame flags, assembly, artificial volatile access, forced inlining or inert code were added to manufacture it.

Compiler: agbcc `-mthumb-interwork -O2`.
Native command, from the private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x0800052C
```

Final native output: `/home/user/.codex-work/ffta-ulw/audio-following-v464-matching/0800052C/match-current.log`.
Compiler diagnostic assembly: `/home/user/.codex-work/ffta-ulw/audio-following-v464-matching/0800052C/candidate.s`.
Full target: `/home/user/.codex-work/ffta-ulw/audio-following-v464-matching/0800052C/target-disassembly.md`.
