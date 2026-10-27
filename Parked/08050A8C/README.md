# 08050A8C — unresolved register allocation

Target: `[0x08050A8C, 0x08050AF2)`, 102 bytes, 46 reachable instructions.
The retained complete natural C candidate emits a 102-byte ELF symbol with
fixed agbcc `-mthumb-interwork -O2`.

The final native matcher invocation exited 1 and reported:

```
extent    102 bytes (complete ELF symbol; direct Thumb BL with ordinary ARM ABI call summaries; no relocations)
bytes   DIFFER
source  plausible
verdict NOT MATCHING - bytes differ
41/46 instructions identical (96/102 bytes)
```

The final line is the native aligned diff score. Direct comparison of the
102-byte target and compiled hex strings in the same native log gives
94/102 equal bytes at identical offsets. Neither measure is exact equality;
no match credit is claimed.

The complete behavior is recovered: reset the embedded state at offset 0x7C;
when mode is zero, set the embedded sequence at offset 0x68 from the unsigned
byte argument; otherwise, pass that byte as signed to 0x080505BC, then call
0x08017884 for the object at offset 0x48 with the promoted object value and
third argument one. Finally call 0x08050B9C with the sequence's current byte
at offset 0x11 and mode zero.

The remaining five instruction differences arise from saved-register roles
and one argument setup order. The candidate keeps the object value in sb
and the sequence pointer in r8; the target uses r8 and sb. At the zero-mode
call, the candidate sets r0 before r1, while the target sets r1 before r0.
The named reset-state pointer reproduces the target's address setup before
the first call. This is a bounded unresolved compiler mismatch, not a proof
of unmatchability.

Natural direct and cached member-access forms were tested. A direct final
member access changed address generation and increased the diff. Restoring
the sequence pointer and using the established word-sized step parameter of
0x08017884 gave the retained complete, native-plausible candidate. An explicit
promoted step local did not eliminate the remaining register-role difference.

The complete captured target and final native log remain in the sibling
address scratch directory as `target-disassembly.md` and `match-current.log`.
The unmatched active source and report were removed. No shared metadata,
headers, toolkit, main-game files, or other addresses were changed.
