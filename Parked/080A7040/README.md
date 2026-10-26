# 080A7040 — Parked

Target: 248 bytes / 118 reachable instructions.

The retained complete candidate reaches the native byte and plausibility gates. The default matcher exits 1: source plausible, compiled extent 248 bytes, 83/116 compiled instructions and 193/248 bytes identical. No exact-match credit is claimed.

The C models the registry and record layouts, filters ineligible entries and records, obtains a positive signed score, and updates one of thirteen output slots. Separate flag guards and the full-width score local preserve the target's flag checks and signed-score normalization.

The remaining gap is slot-search control flow and register allocation. The retained compiler output strength-reduces the indexed slot search into a pointer walk, spills the output base, retains the record index in a high register, and places the successful write block differently. The target uses indexed slot addresses, retains the output base in a high register, spills the record index, and prepares its record-lookup alias before filtering the entry.

Bounded attempts covered combined and separate flag guards, score-width boundaries, indexed and pointer expressions, for/while searches, updater return forms, and a direct nested slot loop. Direct/indexed alternatives reached 246 bytes and stopped at the extent guard; the retained 248-byte form has the best complete native comparison. No forbidden steering was used.

Detailed native output and the differing report remain in private address scratch, outside the matching root.
