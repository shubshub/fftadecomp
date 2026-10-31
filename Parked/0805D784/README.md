# 0805D784 bounded matching attempt

Accepted lease 6537625979, lane sol-D784. One natural C form and one original default native attempt were authorized. The source retains actual defining helper contracts, including the ten-slot 0801174C compatible ABI with a u16 third argument.

Native comparison exited 1 with a plausible, complete 408-byte ELF symbol: 404/408 bytes and 159/163 instructions identical. The exact full target and compiled body are retained under state/matching-0805D784-author/ with stdout, stderr, input inventory and exit receipt.

Differences:
- 0x0805D86E: ROM `cmp r0, #1`; compiled `cmp r0, #0`.
- 0x0805D870: ROM `blt #0x805d906`; compiled `beq #0x805d906`.
- 0x0805D874: ROM `bgt #0x805d880`; compiled `bhi #0x805d880`.
- 0x0805D882: ROM `bgt #0x805d906`; compiled `bhi #0x805d906`.

The u8 mode local produces unsigned comparisons where the ROM has promoted signed comparisons. This is an ordinary exact-byte mismatch. No unsupported-model conclusion, helper ABI change, or semantic defect is claimed. No second form or native retry was authorized. No compiler-only diagnostic was needed because native output supplied the complete emitted body. Original source, report and inputs remain frozen; no matching credit is claimed.

Native command:
`python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x0805D784`
