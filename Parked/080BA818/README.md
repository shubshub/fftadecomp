# 080BA818: recovered, not byte matching

Complete target: `0x080BA818..0x080BA878`, 96 bytes and 47 reachable Thumb instructions.

The preserved complete natural C candidate passes native source plausibility and compiles to a complete 96-byte ELF symbol with fixed agbcc `-mthumb-interwork -O2`. Native matching exits 1 because bytes differ. The aligned diff score is 46/47 instructions and 94/96 bytes; actual same-offset byte equality is 86/96 bytes.

The sole instruction-order difference is `adds r5, r0, #0`: the candidate emits this list-pointer copy immediately after the push, before the four coordinate-narrowing shifts; the target emits it immediately after those shifts. All subsequent instructions, registers, offsets, branches, and the linked call match exactly.

Recovered behavior scans thirteen 12-byte entries for an inactive node, initializes its active flag and byte coordinates, obtains its map value, and appends it to the linked list. The source preserves the target's absence of an allocation-failure check and its conditional next-pointer initialization.

Bounded natural forms tried: a coherent inline free-node search with an entry-pointer local (90-byte output); direct indexed array access in that helper (the preserved 96-byte output); a search integrated into the main function with a break and nullable result (102-byte output); and wide coordinate parameters narrowed to byte locals (the same 96-byte output and remaining copy-order difference). No asm, volatile, pragmas, dead code, or compiler steering was used. These attempts do not establish permanent impossibility at the fixed flags.

The source-bound native report is preserved privately as `080BA818/best-report.md`, beside the complete target capture. Unmatched active source/report were removed. No match credit is claimed.
