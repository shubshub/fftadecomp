# 080DB8AC matching attempt

Target: 0x080DB8AC..0x080DB942, 150 complete bytes: 146 code bytes,
69 reachable instructions and a four-byte literal at 0x080DB900.
This is an unsuccessful C candidate, not a byte-identical match.

The retained natural-array candidate compiles and links to 154 bytes with
-mthumb-interwork -O2. Its source SHA256 is
90775d0df5503cc3921a2929caa9cbb75e551bd08155024980a0d3200f1c4bdd.
Compiled SHA256:
9c66b06bd7d5e704a85b076a84c86ae9cbbb2f18c780c72c84f51bb84484f2fc.
Target SHA256:
7dbca96280def563eba1a5d80e09bbce19f397c680804e214845f958e57defa0.

The candidate has the intended local arrays at SP+8/+10, SP+12/+14/+16,
and SP+20 through SP+26. The target retains rectangle and second-output
pointers in r4/r5 across the first helper call, with state in r7 and the ROM
pointer in r6. The candidate instead saves r4/r5 only, computes the rectangle
address after the call, and rematerializes array addresses. Its early-return
branch and literal-pool placement also differ. Its four call sites are
0x080DB8C8, 0x080DB8F4, 0x080DB918 and 0x080DB92C; target sites are
0x080DB8CA, 0x080DB8F2, 0x080DB91C and 0x080DB932 respectively.

Three natural source layouts were tried: separate scalar outputs plus a
rectangle array (154 bytes), natural output/rectangle arrays (154 bytes,
retained here), and grouped small structs with an explicit else branch
(198 bytes, including wordwise field-update expansion). None is byte exact.
No compiler flags beyond the repository default were tried. No asm, pragmas,
volatile, dead code, artificial padding or new dependencies were used.

The canonical matching command also refuses before reporting the byte diff:

    buffer callee 0x080D8604: buffer callee 0x0801BB94: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification

This is an admission prerequisite, separate from the remaining C byte
mismatch. No native match report was generated. No toolkit, mapping, shared
header, reservation or publication changes were made by this lane. Full
attempt logs and byte-comparison receipts are retained in the handover state
under state/matching-080DB8AC-author/. The accepted lease was lane sol-B8AC,
claim 6519956443; the primary agent owns its release.
