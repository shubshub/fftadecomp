# 080846B0 — bounded native mismatch

Complete target: `[0x080846B0, 0x08084A98)`, 1000 bytes and 406 reachable instructions. The retained C implements the full delay, confirmation, secondary-action, cancellation, cursor-movement and page-scrolling paths using the observed 0xCC-byte window records.

The final native matcher invocation exited 1. It accepted the complete 1012-byte ELF symbol, direct Thumb calls with ordinary ARM ABI call summaries, typed linking and source plausibility, then reported `NOT MATCHING - bytes differ`. Its comparison summary is `268/401 instructions identical (843/1012 bytes)`. This is a mismatch, with no match credit.

The remaining differences are concrete compiler output differences:

- After the first selection lookup, the candidate loads the entry-array pointer before preparing the destination item address. The target prepares the destination first and keeps the entry address in a different register.
- The secondary-action path retains the 0x2D50 literal in a temporary register and derives the menu address by subtracting 0x50. The target overwrites that temporary with the context pointer and separately materializes 0x2D00.
- The down-page path assigns the page size and scroll offset to different registers and derives 0x2D1A from an existing address constant. The target loads 0x2D1A independently. The candidate has a separate sound/update tail for this path, while the target joins it with the up-page sound/update tail.
- The up-page path retains the precomputed window stride across the sound call. The target reuses that register for the window base and recomputes the stride after the call. Subsequent literal-pool placements and branch displacements differ as a result.

Natural iterations covered byte versus wider cursor locals, explicit signed cursor conversion, scoped versus shared movement locals, cached entry/context pointers, and byte versus integer page-size locals. All matcher calls used the fixed `-mthumb-interwork -O2` flags. A separate signed-selection overlay was discarded; the retained source has one selection-record type and an explicit signed integer cursor conversion.

The current complete candidate and final mismatch log are retained. The unmatched source and report were removed from `src/` and `docs/match/`. No function-boundary or metadata changes were made. This bounded result does not establish unmatchability.

Native replay command, after temporarily restoring this C to the address source path:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v158-matching/matching-root 0x080846B0
```

Final log: `/home/user/.codex-work/ffta-ulw/audio-following-v158-matching/080846B0/match-current.log`.
