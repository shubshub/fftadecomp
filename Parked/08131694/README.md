# 08131694 signed-remainder operand proof refusal

Accepted held claim6528414058, sol-1694. Two distinct natural C forms were checked with the unchanged normal default native command. Form1 emitted a108-byte symbol against the112-byte target. Parent classified its combined span/ROM error as ordinary mismatch and authorized exactly one compiler-only diagnostic of that unchanged first source. The diagnostic preserves exact commands,108Bsymbol,bytes,assembly and comparison, without proof APIs or matching credit.

Form2 represents the observed narrowed remainder as an s16 local before widening to the factor, and preserves the observed factor-times-value order in the final multiplication. Its normal native invocation exited1 with:

```
compile failed:
signed remainder requires proven signed16 r0 and nonzero r1
```

This operand refusal is reached only after modsi3_profile.verify_context checks exact mapped span and complete caller-ROM equality. Passing that earlier guard is evidence of byte agreement in the native pipeline, but no successful native verdict, plausibility report, or matching credit is claimed. No report was created.

The target obtains r1=257 through the PC-relative LDR at081316B2 from the integer literal081316D4. The existing modsi3_profile.prove_operands implementation propagates signed16 and nonzero facts through immediate MOV, register copies, zero-add copies, ASR16 and qualifying zero-comparison edges. It does not propagate a nonzero fact from a PC-relative LDR. The preceding LSLS16/ASRS16 establishes the dividend, while the literal-loaded divisor lacks a modeled nonzero fact. This is a precise default proof limitation, not a source-level permission to change the divisor or emitted instructions.

The final exact source and native failure are preserved here, all before-run source/all9header contents/currentruntime/compiler/tool/3map/full112Btarget pins and both runs in state/matching-08131694-author/. No third source form, second diagnostic, successful replay, ABI/profile/gate/toolkit/shared-input change was performed. Active source and report are absent. Parent owns release and any future proof-capability decision.
