# 0813F140 — unused byte loads before full-byte bitfield writes

The complete indexed target is 0x0813F140..0x0813F19C: 92 bytes and 41
reachable instructions. The tested natural candidate emits one function,
84 bytes and 37 instructions, with agbcc `-mthumb-interwork -O2`.

The native matcher exits 1 at the complete-symbol extent gate:
`compiled symbol is shorter than the indexed span: 84 < 92`. The gate does
not reach plausibility evaluation for this candidate; no native plausibility
verdict or match credit is claimed.

The incoming arguments are a transition-state pointer, two bytes, and two
halfwords. The fifth argument is read at incoming stack offset zero, which
is `[sp, #12]` after saving r4, r5, and lr. A zero duration disables the
transition; a nonzero duration stores endpoints, clears elapsed time, and
enables it after updating the control fields.

The control object at g_control_flags_03000940 has byte-sized fields at
offsets 0x4A and 0x4E. The candidate models each as an unsigned 8-bit bitfield
within a halfword alongside an unknown neighboring 8-bit field. This
reproduces their exact byte offsets, truncating stores, and address order.

The complete generated assembly follows the target operation sequence except
for these four omitted loads and the resulting branch/literal displacements:

- Zero-duration branch: target 0x0813F162 loads `[r2]` into r1 before storing
  r3 to that byte; target 0x0813F168 loads `[r0]` into r1 before storing r5.
- Nonzero-duration branch: target 0x0813F184 and 0x0813F18A repeat those same
  loads before stores.

Each loaded value is overwritten or unused before the function returns. The
fixed compiler removes these reads for the full-width byte bitfield writes,
accounting for exactly four instructions and eight bytes. This is the
established unused-load-before-whole-byte-store pattern, not a native CFG
eligibility failure. One natural bitfield attempt was tested and preserved;
no artificial read expressions, volatile qualifiers, compiler changes, or
assembly were introduced to retain the unused operations.
