# 0803616C — unresolved compiler mismatch

Target: `[0x0803616C, 0x08036282)`, 278 bytes, 129 reachable instructions.
The retained complete C candidate compiles to 272 bytes with fixed agbcc
`-mthumb-interwork -O2`. The last native matcher invocation exited 1 with:

```
compiled symbol is shorter than the indexed span: 272 < 278
```

The extent gate stopped before byte comparison and native plausibility checks.
No exact-match or native-plausibility credit is claimed.

The source recovers the complete coordinate lookup and adjustment behavior:
scan 30 records of 20 bytes; scale each record's byte coordinates by eight;
check the rectangle from x−4 through x+20 and y−8 through y+16; reject disabled
entries 8 and 27 using enable bits 0 and 1; increment the dwell byte at state
field 0xF3C up to 30 when centered; otherwise, when dwell is zero, move each
signed coordinate one unit toward the center. Return the one-based entry ID
on a hit, or zero for no hit or a disabled entry.

Three natural source forms were tested. The initial scalar-enable form with
`i + 1` returned a 258-byte symbol. Explicit global-address locals with a
separate one-based ID produced 272 bytes. The retained direct-state access
and named enable-array pointer form also produced 272 bytes.

The remaining code-generation differences include the enable-byte accesses
and register/load schedule. The target independently reloads the enable byte
for both feature-bit tests and saves three high registers. The candidate
caches that byte across the tests and saves two high registers. The target
also loads the state-pointer address before the enable address and one-based
ID; the candidate orders these loads differently. These observations explain
the remaining recovery work; they do not establish unmatchability.

The complete captured target and last native output remain in the sibling
address scratch directory as `target-disassembly.md` and `match-current.log`.
The unmatched active source and report have been removed. No shared metadata,
headers, toolkit, or main-game files were changed.
