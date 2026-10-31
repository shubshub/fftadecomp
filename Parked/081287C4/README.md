# 081287C4

The one natural C candidate did not match. The accepted claim was 6538553997,
label sol-87C4. The original default native command used agbcc
`-mthumb-interwork -O2` and exited 1 after 0.316696456 seconds:

```
compile failed:
buffer caller requires an exact complete mapped span
```

The native command did not produce a complete report or compiled body. One
explicitly authorized compiler-only diagnostic compiled the unchanged source
through the existing native compile_object and typed link_calls mechanisms.
It exited 0 after 0.061960699 seconds. No proof API or MATCH replay ran.

The complete emitted ELF function is 210 bytes, while the complete target is
212 bytes, [0x081287C4,0x08128898). The compiled symbol ends at 0x08128896.
The genuine four-byte local allocation and two halfword helper outputs remain
present. The compiler orders the helper arguments as SP+2 into r1, then SP into
r0; the target sets r0 first. At 0x0812882E the compiled second halfword read is
`movs r2,#2; ldrsh r0,[r0,r2]`. The target uses
`adds r0,#2; movs r2,#0; ldrsh r0,[r0,r2]`, two bytes longer. Subsequent code
and direct-call sites move two bytes earlier. This is a concrete compiler
extent/instruction mismatch, not evidence of an unsupported buffer model.

The exact fixed-offset byte comparison has 104 equal positions in the 210-byte
common extent and 108 differing or missing positions over the 212-byte union.
Those counts are positional comparisons, not an alignment-based diff score.
No semantic correction was established. Pointer-expression, declaration,
register, lifetime, padding, or spelling changes solely to influence output
were not attempted. This bounded result does not claim that matching is
impossible.

Accounting: one C form, one normal native attempt, one unchanged-source
compiler-only diagnostic, zero native retries and successful replays. The C
here is byte-identical to the original attempted source. No shared files or
other target sources changed. All 115 tool, nine header, five native-binary,
and six map pins stayed unchanged; the nine isolated header copies and current
machine runtime were also checked. No new ROM root/helper reads occurred.

Retained evidence is under
`state/matching-081287C4-author/`: original stdout/stderr and native timing,
source/composite input pins, the saved 212-byte target, exact linked ELF and
210-byte body, full disassembly, positional differences, instruction diff,
all diagnostic commands, and the final receipt. Native report absent.
