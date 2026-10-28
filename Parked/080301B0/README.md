# 080301B0 — unmatched natural C

Target: `0x080301B0..0x08030200`, complete 80-byte symbol, 38 reachable instructions. The retained candidate also emits a complete 80-byte symbol with 38 instructions and the four-byte global-address literal. No target truncation or compiler flag changes were used.

The fixed native matcher exited 1: `bytes DIFFER`, `source plausible`, `NOT MATCHING - bytes differ`. Its aligned diff score is 24/38 instructions and 65/80 bytes; this is the native alignment metric, not a claim of same-offset equality. The complete ELF symbol has a closed leaf CFG and no relocations.

The function searches 16 resource slots at the object reached through `g_state_03002810` and its pointer at offset 4. Slots begin at offset 0x24. It replaces the first null slot, zero packed 10-bit ID, or matching ID and returns its index; otherwise it returns -1.

Remaining difference: target keeps the resource argument in r4, index in r6, slot address in r3, and the packed-ID mask in r5. The candidate instead uses r6, r5, r4, and r3 respectively; both use r7 for the global address. The target shifts the index before adding the slot-array offset, while the candidate adds 0x24 before shifting the index. Branch destinations, literal location, loop bounds, packed-ID byte reads, and the complete function extent agree.

Bounded natural forms included direct indexed array access, a cached child object, cached slot/current pointers, split pointer-base arithmetic, an explicit byte offset, for/do-while/explicit loop exits, and a signed halfword counter. Direct indexing introduced a second byte-offset induction variable and an 86-byte symbol; the halfword counter introduced narrowing and a 98-byte symbol. Split array-base and slot-pointer locals produced this retained 80-byte form, but the allocation and address-order gap remained. No asm, volatile, pragmas, dead code, or compiler steering was added.

Retained source SHA-256: `cd41dfbd03fdb0c103e22d3b9ea5c9ace0d95b51cb5234e413574e56cd235185`.
Last native report SHA-256 before removing the unmatched active report: `c0f9a6996b1be366cfa33d7a2893306f6bed099b643c52acfe66932328ad2009`.

This candidate was tested in the private v82 mapping snapshot. Main source/report were cleared before publication; this private Parked pair carries no exact-match credit.
