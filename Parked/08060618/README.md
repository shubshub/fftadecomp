# 08060618

Bounded natural C attempt retained after a native proof-model refusal.

Target: complete Thumb [0x08060618, 0x08060828), 528 bytes, 228 reached instructions.
Accepted reservation: sol-0618, claim 6532714988. The coordinator owns release.

Two distinct natural source forms were tested with the existing command:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree --owner-runtime-profile named-data-buffer-v1 0x08060618
```

The first form compiled to exactly 528 bytes with 12 differing bytes. One
explicitly authorized compiler-only diagnostic retained its complete ELF,
assembly, symbol bytes, commands and difference list. The actual differences
were the observed flags subobject offset (0x88 versus 0x84) and the location of
halfword narrowing around the first state-field update.

The retained second form corrects the unknown layout gap after the rounded
cursor struct and expresses the actual state halfword assignment, test and
decrement directly. It preserves the real initialized automatic byte, actual
60468 signature, defining helper argument widths, signed row conversions,
pointed-state reloads and call/store order.

Attempt 2 passed the native complete unique span and whole-ROM-byte identity
guard, then exited 1 during buffer proof. The exact final error chain is:

```
buffer callee 0x08141570:
  buffer callee 0x081458AC:
    buffer callee 0x08144D94:
      buffer callee 0x08144D84:
        non-leaf indirect control flow requires linked CFG verification
```

The actual 60468 output-pointer alias can remain in IP, an ABI scratch register.
The current buffer engine tracks that alias into subsequent audio calls; its
ordinary dependency inspection cannot close the encountered indirect transfer.
This does not establish an extra formal audio argument or a callback contract.
No source/profile/helper workaround, third form, second diagnostic or successful
proof replay was attempted after this precise model refusal.

No MATCH report was emitted, and source plausibility admission was not reached.
No native match credit is claimed. The final native process removes its temporary
ELF; only the separately authorized first-form diagnostic ELF is retained.

Evidence is frozen under:
/home/user/Desktop/FFTA-handover-2026-10-30/state/matching-08060618-author/

The ordinary one-object ignored-result interface for 0805F69C remains ABI
conditional. Its real 80-byte ROM code/pool context and legacy 76-byte index
discrepancy remain recorded; no helper boundary repair, original return-type
certainty, transitive helper semantic proof or mapping change is claimed.
