# 08141984: timer selection and callback installation

The complete indexed ROM body is [0x08141984, 0x081419BE): 58 bytes and
21 reachable Thumb instructions, including four referenced literal words.
An unsigned-byte timer index above 3 returns 1. Otherwise the function stores
the index at 0x03005E40, stores 0x04000100 + index * 4 at 0x03005E44,
writes the genuine Thumb callback 0x0814195C to the output pointer, and
returns 0. The callback literal is a function address, not data.

The retained natural C expresses that behavior with named data symbols,
a typed callback, and a halfword timer-register array. Hardware volatility
qualifies only the hardware register object and pointed-to register type;
the RAM index and RAM pointer object are not volatile. No volatile access
is added to force a reload.

The fixed agbcc -mthumb-interwork -O2 compiler emits a complete 58-byte,
21-instruction symbol with the ROM's branch and middle literal-pool layout.
The remaining difference is register allocation: compiler output keeps the
callback output pointer in r3, loads the global pointer destination into r2,
and loads the timer-register base into r1. ROM uses r2, r1, and r3 for those
three values respectively. The affected pointer-copy, literal-load,
address-addition and store instructions differ accordingly.

Final native matching exits 1 with:
    compile failed: function-address caller differs from the ROM
This is the typed function-address proof's exact-caller gate, before source
plausibility and the normal instruction-diff report. No native plausibility
or successful callback proof is claimed. This is not an exact match.

The initial valid-case conditional placed the failure return and literal
pool differently and was rejected for a nonexact mapped span. An explicit
invalid-index guard recovered the correct complete extent and pool layout.
Both a four-byte timer-register structure and the retained halfword-register
array produced the same remaining register allocation. No assembly,
forced inlining, compiler-option changes or artificial liveness was used.

Final native log:
/home/user/.codex-work/ffta-ulw/audio-following-v449-matching/08141984/match-current.log.
The retained compiler diagnostic is candidate.s in that address scratch.
Active unmatched C and report were removed; no match credit is proposed.
