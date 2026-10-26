# 080A8DB8

Complete natural candidate for the 82-byte / 41-instruction animation timer
and script-frame advance function. Fixed agbcc `-mthumb-interwork -O2`.
The final native matcher exited 1: complete ELF extent 82 bytes, source
plausible, closed leaf CFG, no relocations, NOT MATCHING. Its aligned diff
reports 40/41 identical instructions and 80/82 identical bytes.

The remaining gap is the count-byte load order at 0x080A8DD0..0x080A8DD6.
The target loads the low byte into r1, then the high byte into r0 and shifts
r0 by eight. The candidate loads and shifts the high byte before loading
the low byte. The OR, signed index comparison, frame selection, index and
timer stores, and return sequence otherwise match.

Tested forms: a typed header (agbcc aligns its entry member to four, whereas
the format starts entries at byte two); explicit byte-buffer header decoding
with low-first and high-first OR expressions; staged signed count decoding;
and staged unsigned-halfword count decoding. The staged forms retain the
low-first loads but put the OR and comparison value in r1 instead of the
target's r0. This preserved high-first expression is the closest complete
plausible tested candidate. No compiler flags or unsupported source devices
were used. The final native report is retained in the private address scratch.
