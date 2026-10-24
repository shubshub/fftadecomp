# 080DFB0C — timed two-command sequence (NONMATCH)

One natural C candidate, one agbcc compilation, no source revisions or retries.
Fixed compiler `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2` produces a complete
424-byte Thumb symbol with 202 reached instructions. The actual ROM function is
`[080DFB0C,080DFCAC)`: 416 bytes, 198 instructions. This is not a match and earns
no matched-function or matched-byte credit. The source passes plausibility.

## Exact difference

Within the true 416-byte target, 216 byte positions agree and 200 differ; the
compiled function has eight additional bytes. A byte LCS finds 377 shared bytes,
which is an alignment diagnostic, not a positional identity measurement. The
canonical report's 377/424 metric uses a compiler-sized ROM window containing
eight bytes of the next function; that window does not redefine ownership.

The masked-value operand order differs at DFBAE/DFBB0, the command switch has a
different decision tree, and each default-duration ternary uses an additional
register selection/copy sequence instead of the ROM's conditional assignment.
Subsequent branches/calls are relocated accordingly. The middle literal 0xFFF
remains at DFBD0; the compiled trailing 0x101 literal is DFCB0 rather than DFCA8.
No changes were attempted to chase these compiler differences. They do not prove
that a natural exact recovery is impossible.

## Recovered contract and limits

Constructor DFD8C registers callback DFB0D through scheduler 08005B6C with a
16-byte payload. Dispatcher 08005C04 supplies three full pointers; the recovered
function returns u32 zero and does not use its task argument. Payload fields are
count+0, cursor+1, channel+2, tick+4, delay+6, flags+8, events pointer+12. Event
stride is eight: u16 tick, two byte channel overrides, two halfword commands.
Phase zero intentionally leaves cursor and tick untouched: external initialization
is unproved. Matching an event increments the stored cursor by one, not by the
scanned position; post-call field reloads and two-command ordering are retained.

The five typed direct callees are 08141520(u16), 08141570(u32,u32),
080DFE74(u8,u16), 080DFE28(u8,u16), and 0814164C(u16); their ignored returns are
represented as void. The 08141570 declaration agrees with published 08123770.
Five R_ARM_THM_CALL relocations resolve to unique indexed Thumb targets; the
linked ELF has no relocations. Both target and compiled CFGs pass the ordinary
direct-call ABI-summary profile. This is not transitive callee equivalence;
downstream 08145388 is a ROM-observed published Parked nonmatch. No native or
emulator equivalence tests were run after this byte nonmatch.

The approved private metadata correction is end DFCA8→DFCAC, size 412→416,
instruction count 206→198, and ffta.sym size 0x14→0x1A0. An existing interior
functions.txt row at DFBCA remains unchanged and requires separate inventory
review; it lies in the second halfword of BL DFBC8.

## Provenance

Source SHA256: `51c0d5582791cfe7e7bf028e37b56baad602180976d8ad08864bbdced44d3b91`.
Source plus all nine unchanged headers:
`bfc9379e5fc316935782335154892dfe550047cd50f60648c46feb47765ce900`.
Evidence: `/home/user/.codex-work/ffta-ulw/080DFB0C-author-next`.
The immutable candidate, canonical report/log, same-run ELF hex/symbol/relocation
capture, exact input bindings, metadata proposal, validation and chronology are
retained there. Source chmod0444 preceded compilation, but precompile JSON
serialization failed before a timestamp/hash record was saved. No such record
is fabricated. The canonical report binds the unchanged compilation inputs.
The capture wrapper discarded match.main's return and exited zero; the canonical
NONMATCH code path returns one. Wrapper success is not match success.
