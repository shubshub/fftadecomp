# 08043468 bounded matching attempt

Accepted lease: 6534014795, sol-3468. Parent owns release and integration.

The single natural C candidate implements the retained complete 1236-byte owner,
its state switch, observed layouts, and 15 qualified helper interfaces. The
normal default native check returned exit 1: NOT MATCHING - bytes differ, with
source plausibility accepted and elf-symbol-thumb-frame-data-v1 verification.
The emitted complete symbol is 1264 bytes, 28 bytes longer than the real owner.
The first byte difference is offset 0x10, address 0x08043478. The native report
compares a ROM window of emitted length, so its final 28 ROM bytes belong beyond
the frozen owner and receive no match or boundary credit.

The source has the target frame save set and 60-byte fixed outgoing frame.
Differences begin with retaining the global address versus the slot offset in
saved registers, followed by repeated global-address loads, automatic height
calculation placement and literal placement. No independent operation correction
was established. Remaining forms were not spent on declarations, register
allocation, type changes or spelling intended solely to steer code generation.

Accounting: one authored candidate, one native invocation, zero MATCH, zero
successful replays, zero standalone compiler diagnostics, no shared input edits.
The native compiler workspace was cleaned by the existing native runner. The
exact C, native report, output, complete target and emitted bytes, current input
pins and machine receipts remain in state/matching-08043468-author/.

Command after sourcing the handover enter.sh:

python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x08043468

Helper contracts retain their conditional ordinary ARM ABI limitation. The
compatible word-carrier declarations do not assert original formal signedness,
callee numeric results, game purpose, alias purity or transitive termination.
