# 0805DE30 bounded matching attempt

Accepted lease: sol-DE30, claim6537005661. One grounded natural C form and one default native attempt were performed in the isolated worktree. Primary source was untouched.

The native check returned exit1 with plausible source and a complete356-byte ELF symbol. 148/154 instructions and350/356 bytes are identical. Six register-encoding bytes differ in [0805DF52,0805DF60), the extraction of the observed10-bit value from SlotFlags bytes0/1 and its u16 count store. Both versions load the same bytes, mask with3, shift8, OR, and store the same value. No source-level semantic bug was identified.

Actual defining helper void func_0805DDC8(u16) and the existing four-byte MenuEntry/state layout were retained. The global pointer and field reloads, slot exchange, helper call, literal pools, complete extent and return all match in this first candidate. No second spelling, register/type/loop steering, asm, pragma, volatile, dead code or fabricated padding was attempted.

The full native output already contains both complete bodies, so no compiler-only diagnostic was needed or run. No native replay was performed. The exact source is retained here unchanged; failed native report and command/source/header/map/tool/runtime receipts are in state/matching-0805DE30-author/. Parent owns reservation release and any future publication.

Target: [0805DE30,0805DF94),356bytes,154reached Thumb instructions,310code+44pool+2alignment. Default command used:

python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x0805DE30
