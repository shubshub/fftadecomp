# 08002524 — bounded natural C attempt

Target: complete `[0x08002524, 0x08002710)`, 492 bytes and 238 reachable
instructions. The retained candidate emits one complete 492-byte Thumb FUNC
with 238 instructions and the same 40-byte local frame.

This is an iterative partition sort followed by insertion sort. Its incoming
arguments are workspace, array base, signed element width, signed element
count, and a comparator in the fifth argument slot. Workspace holds two
12-entry index stacks at offsets 0 and 0x30, then element scratch at 0x60.
Copy calls use the real `data_0836D4BC` callback table. Comparisons and copies
emit the canonical `_call_via_r2`/`_call_via_r3` helpers.

Fixed compiler: agbcc `-mthumb-interwork -O2`. The retained source's native
matcher result with `--function-address-profile canonical-thunks-v1` was
exit 1: `inert-spin complete body differs from ROM`. Complete extent agrees,
but the early exact-body gate rejects the bytes; native plausibility and
downstream verification were not reached. This is not a match.

A separate diagnostic comparison of the assembled candidate, resolving only
its six canonical helper calls and one named-data literal, found 482/492
identical bytes. All differences are in these five instructions:

| ROM address | Target | Candidate |
| --- | --- | --- |
| 080025A2 | `mov r5, r8` | `subs r5, r7, #1` |
| 080025A4 | `adds r5, #1` | `mov r6, r8` |
| 080025A6 | `subs r6, r7, #1` | `adds r6, #1` |
| 080025C0 | `mov r8, r5` | `adds r7, r5, #0` |
| 080025C2 | `adds r7, r6, #0` | `mov r8, r6` |

The residual is the scheduling and allocation of the next lower/upper scan
indices across the byte-swap loop. The remaining complete emitted body agrees
with the target, including the partition comparisons, stack push/pop paths,
insertion loop, literal location and callback relocations. The diagnostic
comparison does not replace any native acceptance gate.

Tested natural forms:

- Nested partition/stack loops with a post-decrement byte count: extra loop
  induction state and an unsupported high-register call-helper relocation.
- One combined partition/stack loop, explicit byte countdown to -1, separate
  insertion index lifetime: recovered the target frame and control flow.
  Separating declarations from initialization recovered the complete extent.
- Both independent scan-index increment orders after the swap: the retained
  decrement-then-increment form has the five-instruction difference above;
  the opposite order also keeps the next-index register allocation reversed.
- Post-increment/decrement in the two swap-pointer expressions: native extent
  gate rejected the different emitted body.

No assembly, volatile accesses, compiler flag changes, forced inlining, fake
aliases or register constraints were used. Unmatched active source/report
were removed; this pair is the bounded retained result.
