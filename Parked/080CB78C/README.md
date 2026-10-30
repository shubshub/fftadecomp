# 080CB78C: plausible, not matching

The final candidate has the correct complete 52-byte extent, and the native matcher reports source plausible. It is not byte identical: 15/22 instructions and 45/52 bytes match. The native command exited 1.

```sh
python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080CB78C
```

Defining callee sources establish u8 func_080C817C(void *) and u32 func_080C92F0(void *, u32). Existing neighboring sources establish object index byte +4, table g_table_085273D8 with 14-byte rows, and byte member +0xB. The false predicate branch correctly returns the low u8 of func_080C92F0(data,9).

Only the table branch differs in the final source. The target loads the object index into r1, computes index*14 in r0, loads the named table base into r1, adds into r0, and loads the byte from [r0,#0xB]. The candidate loads the index into r0, computes index*14 in r1, loads the table base into r0, adds into r1, and loads the byte from [r1,#0xB]. The control flow, helper calls, narrowing, literal address, epilogue, and complete symbol length match.

Tried representations:

1. Ordinary full record struct: 48 bytes. Diagnostic assembly exposed the compiler default 16-byte struct stride, which is incorrect for this table.
2. Packed full 14-byte record: 56 bytes, plausible, not matching. The compiler folded the +0xB field offset into the table base rather than using the target byte-load displacement.
3. Existing [][14] byte-row declaration with direct [0xB] access: the same 56-byte output as the packed form.
4. Existing [][14] byte-row declaration with a prefix member view, matching the pattern in 080CB714.c and 080CB868.c: 52 bytes, plausible, register allocation differs as described above. This is candidate.c and native-report.md.

Earlier forms, failure logs, and this machine source-bound receipt are retained under state/matching-080CB78C-author/ at the handover root. No assembly, volatile, pragmas, dead operations, arbitrary register steering, misdeclared callee return widths, or toolkit/profile changes were introduced. The candidate is parked for an evidence-backed continuation rather than an unsupported source perturbation.
