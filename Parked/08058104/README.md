# 08058104

The complete target is 166 bytes / 74 reachable instructions. The recovered
function copies a five-halfword row block through `data_02003CB0`, chooses the
source/destination half according to direction 0x80 or 0x40, and calls
`func_08057E98(state, value, first, second)`.

The preserved natural candidate passes the standalone plausibility check.
The final default native matcher with agbcc `-mthumb-interwork -O2` exits 1:
`compiled symbol is shorter than the indexed span: 156 < 166`. The matcher
stops at that extent check and produces no native comparison report or match
credit.

Compiler assembly from the equivalent initial 156-byte candidate exposed the
remaining allocation gap: the target allocates a 12-byte frame and saves all
three byte parameters to stack slots as well as high registers; the candidate
uses an 8-byte frame and two parameter spill slots, retaining the third byte
in a low register on the first branch. The scratch pointer, row-count temporary,
and resulting address moves also occupy different registers. The candidate's
copy/update operations and direction cases follow the complete saved body.

Bounded natural attempts covered if/else with and without an early return,
independent early-return conditionals, a switch, signed/unsigned word and
halfword row counts, byte versus halfword buffer addressing, explicit byte
counts, and converting the count to bytes within each branch. The switch
shortened to 140 bytes; the other tested forms remained 156 bytes. No alternate
compiler flags or steering constructs were used. This is a bounded source gap
at the fixed flags, not a permanent impossibility claim.

The complete captured target remains in the address-private scratch directory.
The unmatched source and any generated report are absent from the private
root's `src/` and `docs/match/` directories.
