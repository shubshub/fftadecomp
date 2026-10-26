# 0801360C — parked

Target: complete [0x0801360C, 0x08013728), 284 bytes / 126 reachable instructions.
The retained natural candidate compiled to a complete 280-byte symbol using fixed agbcc `-mthumb-interwork -O2`. Native matching exited 1 with `compiled symbol is shorter than the indexed span: 280 < 284`, before a full diff or plausibility verdict. No byte-identical match is claimed.

Recovered behavior includes glyph width lookup, aligned and partial eight-pixel block loops, cursor/output advancement, and final edge-state operations. In the retained form the previous partial-block shift occupies r9 and the updated pixel offset occupies r7. The target keeps the starting shift in r7, the updated offset in r9, and copies it into r7 at the common tail. The first loop guard and remaining-width arithmetic consequently have different register assignments and instruction order.

Tested forms: an initial while loop with a separate total (286 bytes, native source plausible); guarded do loops with signed shift arithmetic (290 bytes, plausible); the retained running-offset form with a branch-local starting shift (280 bytes); and a separate u16 total (294 bytes, plausible, adds narrowing). The last trial was discarded and the previously tested 280-byte form was restored without further matcher calls. None used changed flags, assembly, volatile access, synthetic operations, or optimization directives. Matching stopped after the bounded natural reconstruction.
