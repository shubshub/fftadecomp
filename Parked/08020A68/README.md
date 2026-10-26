# 08020A68

Recovered four-record animation update, target `[0x08020A68, 0x08020B9E)`.
The fixed native `agbcc -mthumb-interwork -O2` matcher verifies the complete
310-byte symbol as a plausible closed leaf CFG with no relocations, but exits 1:
**302/310 bytes and 146/152 instructions identical**.

The remaining difference is flags handling. The candidate reloads the flags
halfword into r3 after selecting the frame data, before decrementing the timer.
The target retains the first flags load in r1 and copies it to r3 only when the
timer reaches zero. The two loop-flag tests also use different AND destinations
and comparisons. The other body instructions, record indexing, loop registers,
byte decoding, data pointer updates, literal pool and complete extent agree.

Natural forms tried: combined cases, individual cases and if/else handling of
kinds 0 and 1; byte, halfword and promoted count/flag locals; typed state versus
byte-offset record addressing; direct versus staged byte decoding; early flags
snapshots, later flags reads, positive guards and a narrow reverse flag. Some
compile to 290, 292, 300 or 306 bytes; signed narrow flags produce 320 bytes.
The preserved 310-byte form is the closest tested candidate. No alternate flags,
assembly, volatile accesses, pragmas or artificial code were used. This records
a bounded matching attempt, not a permanent impossibility result.
