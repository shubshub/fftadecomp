# 0809C8C8

Recovered the complete four-direction movement update. Signed halfword x/y
coordinates occupy +0x0E/+0x10, flags +0x1C, and direction +0x1D. Bit 0
selects the return phase; bit 1 marks completion. The candidate preserves
outward thresholds of +12/-12, signed step updates, zero clamping, direction
clearing, and the asymmetric flag writes present in the native body.

The fixed native matcher (`agbcc -mthumb-interwork -O2`) exits 1: source is
plausible, but the complete candidate is 292 bytes / 146 instructions against
the indexed target's 288 bytes / 144 instructions. The remaining difference
is control-flow sharing: the ROM shares the positive/negative outward x
stores at 0x0809C946 and outward y stores at 0x0809C9BC, and places the shared
successful return at 0x0809C948. The candidate retains separate outward
stores and places the shared successful return near its end. Resulting
branch offsets and total extent differ; this is not a byte match.

Natural forms tried: a switch with common successful return after breaks
(278 bytes, rejected as shorter than the indexed body); per-case successful
returns with a final zero return (292 bytes, preserved here); and early
successful returns after outward updates, both in all four cases and only
in the negative directions (310 bytes). All used the same fixed flags.
No assembly, volatile, pragmas, custom flags, or compiler-steering constructs
were used. This bounded attempt does not establish permanent impossibility.

Native evidence is retained in the private address scratch as
`best-native-report.md` and `last-native-output.txt`. The native report's
260/292-byte comparison includes four bytes following the indexed target,
because the compiled candidate is four bytes longer; it is not match credit.
