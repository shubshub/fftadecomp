# 0803FAA4 bounded ordinary byte mismatch

Status: Parked, zero MATCH credit. One grounded natural source form and one default-profile native attempt were run under accepted claim 6533346176 (sol-FAA4). Native exit code was 1, with explicit NOT MATCHING - bytes differ. No compiler-only diagnostic, second source form, or successful replay was run.

The complete Thumb target is [0x0803FAA4, 0x0803FB50), 172 bytes. The native attempt accepted the complete source extent, frame/data admission and source plausibility. Both complete target and emitted body are 172 bytes. Direct fixed-offset comparison has 109 equal byte positions and 63 differing positions. The native aligned-sequence scores are 167/172 bytes and 72/76 instructions; these scores do not represent fixed-offset byte identity.

The target loads the genuine constant-one scalar helper argument into r5 before the argument setup and later stores r5 at outgoing SP+24. This source emits the constant into r0 immediately before the outgoing store, moving a two-byte instruction across the setup and changing two PC-relative displacements. The original native report, complete emitted bytes, full target bytes and fixed-offset differences are preserved without alteration.

No distinct grounded operation correction was established. A declaration or constant introduced solely to force early loading/register allocation would violate the assignment's code-steering restriction. The allowance of up to three grounded forms was not treated as a requirement to manufacture additional forms. This result does not claim an unsupported profile, impossible match, historical formal-type certainty, numeric equivalence of callees, or a transitive helper proof.

The source preserves the defining twelve-formal 08017424 contract, the bounded compatible void(pointer,u8) 08016C90 view, the observed twelve-byte aggregate copy, genuine fifth incoming word, and mapped data identities. Ordinary helper return/preservation, readable source/global memory and a readable allocated incoming word remain conditional caller ABI premises. No local buffer pointer is passed to either helper.

0803FAA4.c and 0803FAA4.md are the exact original source and generated NOT MATCHING report pair. This report is not a MATCH receipt. Supporting immutable attempt records and the final source-bound receipt are in state/matching-0803FAA4-author/. The parent owns reservation release and any integration. No PRIMARY or shared input was edited.
