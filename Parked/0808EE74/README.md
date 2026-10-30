# 0808EE74 bounded matching attempt

Native accepted claim 6534943825, label sol-EE74. One natural source was checked once with the default native command. It compiled to a complete 60-byte symbol against the complete 64-byte target. Native exit 1: `compiled symbol is shorter than the indexed span: 60 < 64`. The native check stopped before report and plausibility generation. No MATCH credit.

One explicitly authorized compiler-only diagnostic retained the unchanged first source and exact default host cpp13, agbcc, assembler/linker commands and current mapped symbols. Diagnostic evidence is under `state/matching-0808EE74-author/compiler-diagnostic/` in the handover root.

The compiler emits a signed loop comparison against immediate 41 with `ble` and saves r4-r6. The target holds bound 42 in r7, compares against r7 with `blt`, and saves r4-r7. Literal placement/order and call displacements also differ. The observed operation, helper interfaces, call order, byte source reads and destination stride agree. No independently grounded operation correction was identified. Adding a bound local or changing declarations solely to force the target register allocation would be prohibited steering, so no second source form or native replay was attempted.

The actual helper contracts remain `void func_080CB9E0(void *, u32)` and the compatible caller interface `void func_0814186C(const void *, void *, u32)`, under conditional ordinary returning ARM ABI only. No helper numeric or transfer semantics are claimed.

Frozen source and result/native receipts are retained. Only this lane's failed active source was moved here; no generated native report existed. Parent owns native release and integration decisions.
