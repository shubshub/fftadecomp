# 0804BD4C — Parked

The retained natural C compiles to a complete 96-byte symbol with the fixed
`agbcc -mthumb-interwork -O2` toolchain. The indexed target is
`[0x0804BD4C, 0x0804BDB0)`, 100 bytes and 47 reachable instructions. Native
matching returned exit 1: `compiled symbol is shorter than the indexed span:
96 < 100`. That early rejection does not issue a source-plausibility verdict
or an instruction-comparison report for this retained candidate. No match
credit is claimed.

The recovered function returns a pair of signed 16-bit coordinates through
the structure-return ABI. It checks a byte index against a sequence count,
supports reverse indexing, reads two signed bytes from the selected sequence,
and returns a zero pair for an invalid index. Table entries are eight bytes:
a count byte at +0 and a coordinate pointer at +4.

The remaining gap is count/offset lifetime, reversed-index arithmetic, and
register allocation. In the retained form the count loads directly into r2;
the target loads r0 then copies it to r2. The candidate computes
`count - 1 - index`, while the target forms `index + 1` before subtraction.
The candidate saves the return address argument in r5 and the index in r6;
the target uses r6 and r5 respectively. The signed coordinate extraction,
halfword packing, zero-result path, and structure-return behavior are
recovered.

Tested natural forms included separate count and byte-offset variables,
u8/u16/u32 local count types, staged reversed-index arithmetic, reusing the
count as the offset, and a common index-to-byte conversion after choosing
the direction. Separate-variable forms produced 94-byte symbols; the
retained reused-offset form produced 96 bytes. Moving the multiplication
after the direction branch produced a complete 100-byte symbol and passed
native source plausibility, but introduced an additional 16-bit truncation
and different register allocation (native aligned comparison 72/100 bytes,
25/48 decoded entries; the indexed target has 47 reachable instructions).
That form was not retained. No assembly, volatile accesses, pragmas, or
forced allocation devices were introduced.
