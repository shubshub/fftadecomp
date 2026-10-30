# 080D5CC0: native buffer extent refusal

The complete indexed Thumb target is [0x080D5CC0, 0x080D5DD2), 274 bytes
and 134 reached instructions. The authored natural wrapper uses the actual
defining ten-argument 08011348 ABI, actual 08011138 byte setter, two u16 output
locals for 0801E6F0, and the packed header layout evidenced by 080D5E80.

The only native invocation was the default matcher with explicit isolated root:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x080D5CC0
```

It exited 1 on 2026-10-30 UTC with:

```
compile failed:
buffer caller requires an exact complete mapped span
```

The matcher reaches this gate after compilation and buffer-call verification,
when the compiled caller length differs from its complete mapped extent. Its
output does not disclose the compiled symbol length, so no exact shortfall or
byte-equivalence claim is made. No native match report was generated. This is
not evidence that every source form or the target's buffer calls are unsupported.

The accepted task explicitly required stopping at a native-model refusal.
There was one natural source form, one native invocation, no retry or diagnostic
compilation, and no profile, ABI, frame, helper, header or mapping alteration.
The exact authored source is retained here and in the task's attempt1.c.
Current-machine compiler/tool, all nine header, three map, full target ROM and
raw/composite source pins were frozen before the native invocation in:

`state/matching-080D5CC0-author/attempt1-pre-run.json`

Native output, exit receipt and the final frozen receipt are in that same
owned task directory. The active source was moved here only after the refusal.
