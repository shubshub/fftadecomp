# 08036D44 — unresolved natural C

Target: complete `[0x08036D44, 0x0803701C)`, 728 bytes and 305 reachable instructions. The candidate recovers the six-slot rendering loop, cached-position path, normal and advanced rendering calls, and current/previous nibble update.

The final native matcher invocation used the fixed agbcc `-mthumb-interwork -O2` toolchain and approved ROM. It exited 1 with `compiled symbol is shorter than the indexed span: 716 < 728`. This is a complete compiled function, 12 bytes short; the early span gate produced no native match report, byte/instruction agreement count, or plausibility verdict. No match is claimed.

Inspected 716-byte output still differed in the normal renderer argument setup and cached-position address allocation. The target establishes the mode-one value in IP before the advanced-flag branch (0x08036E16–0x08036E18), transfers it to the stack at 0x08036E52, and explicitly zero-extends the normal delay byte at 0x08036E56–0x08036E58. The candidate instead materialized mode one at the call and directly stored the known delay value. The cached-position path used offset arithmetic in place of the target's separate 0x7E2 literal load at 0x08036DC6. These lifetime/address choices also changed register assignments and literal-pool placement.

Tested natural forms: an independent sprite counter with byte delay (700 bytes); a per-iteration sprite local and wider delay (704 bytes); direct narrowed `i + 13` call arguments, explicit no-render kind zero, and signed kind local (716 bytes); explicit normal delay if/else (716 bytes). The final retained form uses byte mode/delay parameters for the normal renderer, consistent with a matched neighboring caller, and a wider local delay; it also remains 716 bytes. No compiler flags were changed and no assembly, volatile, inert code, or steering was introduced.

Only the complete source is preserved here. The unmatched source/report entries were removed. The captured full target remains in the private address scratch directory.
