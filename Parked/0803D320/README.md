# 0803D320: bounded natural candidate, not matched

Target: [0x0803D320, 0x0803D3DC), complete 188 bytes / 83 reachable instructions.
Accepted claim 6459545863; release and integration remain coordinator-owned.

The function initializes the menu header and inline entries at offset 0x230,
scans source records 0..30 at stride 12 with the observed byte at offset 0xB3,
and appends each nonzero record. The returned count is also stored at offset 0.
Each 20-byte output entry records the count, zero state, text pointer selected
from g_table_08526680[index + 0x2CE], the halfword identifier indexed by index+1,
and the source record byte/index. All external data names are existing native
bindings. Unknown fields remain explicitly unknown; no shared types changed.

Fixed agbcc -mthumb-interwork -O2, default native matcher, fresh final exit 1.
Complete candidate ELF is 188 bytes; source plausibility passes.
The native aligned-diff formatter reports 76/83 common instructions and
178/188 common bytes. A strict same-offset comparison has 176/188 equal bytes:
12 differing bytes across eight instruction addresses. The complete literal pool
and initializer/record-loop operations agree. The residual is table-address
load scheduling and register assignment: target uses sb for the text table,
r8 for the identifiers and ip for zero, with table bases loaded before moving
the destination pointer. The candidate uses sb for text, ip for identifiers
and r8 for zero, and moves the destination earlier. At 0x0803D38E the target
moves ip to r7 while the candidate moves r8; at 0x0803D396 the target adds r8
while the candidate adds ip. There are no count or extent adjustments.

Three natural forms were tried, without compiler flag changes: the retained
explicit text-value local (188B, 76/83 instructions identical); explicit local
table views (176B, rejected by the complete extent gate); direct text assignment
(188B, 72/83 identical). The best original form was restored and freshly tested.
No artificial lifetime/register constraints or additional variant sweep was used.

The original unmodified compiler relocatable ELF and fresh refusal log/report
are preserved in sibling 0803D320 scratch outside matching-root. Active unmatched
source/report were removed. Fresh successful report replay does not apply to
this refused candidate. Zero match credit.
