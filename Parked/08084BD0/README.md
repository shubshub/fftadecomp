# 08084BD0 bounded matching attempt

Verdict: Parked after one original native failure and one authorized unchanged-source compiler-only diagnostic. No MATCH or plausibility verdict was reached.

The indexed target is the complete 200-byte interval [0x08084BD0,0x08084C98), with 95 reached Thumb instructions and the numeric literal 0x001FFFFF. The first source uses the observed byte at object offset 0x15 as the cached column count. It retains the ignored incoming R0 slot and the object pointer in R1, the actual u16-returning 08017B50 declaration, the signed two-argument 08142950 interface, and the three-argument CpuSet wrapper interface.

Original command, exactly once:

```text
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree --addressed-signed-runtime-profile addressed-signed-runtime-v1 0x08084BD0
```

The original command exited 1 at the combined emitted-span/ownership guard, reporting `inert spins require an exact unique nonoverlapping Thumb span`. It produced no report or preserved emitted body. This error does not establish an unsupported profile or an impossibility result.

The single separately authorized compiler-only diagnostic retained the unchanged first source and the native default cpp/agbcc/as/link pipeline with the real three helper bindings. Its ten commands all exited 0. The emitted ELF function and complete linked .text are 192 bytes, [0x08084BD0,0x08084C90), versus the 200-byte target. The emitted function saves/restores R8 and R9, whereas the target saves/restores R8, R9 and R10. The saved complete disassemblies and equal-offset byte comparison record the remaining instruction/register/layout differences. No equivalence claim is made, and no source correction or code-generation steering was attempted.

Raw first-source SHA256: 02a861cd58cd16a7867a2b5152d15f2f0103b0d764f5a7727942fbf06acc1887.

Source/header composite SHA256: 11b98f9d969b23cc1006e85f2938cd4d5e0fc029f50cf4a2bab82f6c0d4c2aac.

Target body SHA256: 75522ec8a01361efd43df1ce765c83d07eb4f77dea7e7c504d31cba8df8c3331.

Diagnostic emitted body SHA256: d087c28995e0589d746530ad27343c64919807eec8726f0376ebe5ee0e32e496.

Evidence: `/home/user/Desktop/FFTA-handover-2026-10-30/state/matching-08084BD0-author/`. It contains the original source snapshot, original stdout/stderr/exit/timing, before/after current-machine input captures, compiler-only commands and outputs, complete ELF/object/assembly/body, exact target and emitted bytes, diagnostic receipt, and final receipt.

Accounting: one source form, one original native run (exit 1), one unchanged-source compiler-only diagnostic (ten successful commands), zero native retries, zero new ROM/helper reads, zero MATCH credit. The active source was moved here unchanged; the active native report was absent. This bounded attempt is frozen.
