# 0800DECC — address-add operand-order mismatch

Target: 0800DECC..0800DFB0, 228 bytes / 112 instructions.

The retained natural candidate scans packed halfword coordinate pairs for
minimum and maximum signed y values, writes the minimum vertex index,
selects two other vertices through the mapped wrapping helper, and tests
the resulting signed cross product.

The final actual native matcher invocation with the fixed compiler flags
exits 1 with a complete 228-byte symbol and plausible source. It reports
111/112 instructions and 226/228 bytes identical. The sole mismatch is the
operand order of a commutative address addition at 0800DF6A. The candidate
adds the point-array base before the scaled vertex offset; the target uses
the reverse operand order. The destination register and all other emitted
instructions match. This does not constitute a byte-identical match.

Bounded natural formulations covered the scan index width, signed versus
packed halfword storage, flat versus structured coordinate pairs, cached
scan values, explicit orientation returns, and direct indexing versus a
selected-vertex pointer. The direct-indexing alternative shortened the
symbol to 220 bytes; the retained structured packed-halfword formulation
preserves the complete span and closest instruction match.

No assembly, volatile qualifier, pragma, changed compiler flag, fake data
binding, redundant operation, or specialized matcher profile was used.
The existing ordinary direct-call mechanism accepted both mapped helper
calls. This is an ordinary C code-generation mismatch, not a missing tool
or helper capability. The generated native diff is retained privately
outside the repository; only C and this diagnosis are parked here.
