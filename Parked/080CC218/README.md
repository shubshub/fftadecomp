# 080CC218: plausible reconstruction, not byte-identical

The accepted claim was 6484518076. The target is the complete Thumb owner
[0x080CC218, 0x080CC2B4): 156 bytes and 60 reachable instructions.

The recovered function takes a u16 identifier and returns a byte-sized scaled
amount. Identifiers above 0xAA use four-byte records at data_0839475C after
subtracting 0xAB. Their first byte is scaled by four, eight when the first state
type is nine, or two when only the second state type is nine. Other identifiers
select sixteen-byte records at g_table_08528F34, subtracting 0x55 above that
threshold. Their first byte is scaled by two, four for a first-type match, or
left unscaled for a second-type match. The record type is byte 0x0E; the two
state types are at root offsets 0x2E5E and 0x2E5F. Scaled results wrap to u8.
All three external names use existing prepared data bindings.

## Native result and precise remaining difference

The fixed agbcc -mthumb-interwork -O2 build passes plausibility and the native
closed-leaf CFG check. It emits a complete 156-byte ELF symbol with 62 reachable
instructions, but native match.py exits 1 because the linked bytes differ.
There is no successful report or match credit.

The target shares its byte-conversion instruction at 0x080CC28C across the two
special-record override branches and the ordinary-record first-type branch.
The candidate instead repeats the lsrs #24 conversion in the special branches
and branches directly to the final return block. The target's ordinary-table
record address and initial amount occupy r2 and r4; the candidate retains that
record address in r0 and the amount in r2, with different state-offset register
choices and load scheduling. On the final unscaled branch the target reloads
the first record byte, while the candidate reuses its prior loaded byte with a
register move. These differences alter instructions, branch destinations and
literal references despite the equal total symbol size.

## Bounded natural approaches tested

Byte and promoted integer temporaries, direct repeated table accesses and
record pointers, ordinary conditional index normalization, and early returns
were tested. The variants produced complete symbols between 152 and 164 bytes;
none matched. The retained source keeps the full recovered behavior, genuine
record layouts, u8 result semantics and explicit promoted type comparison.
No flags, assembly, pragmas, artificial reads, volatile RAM, register bindings,
helper functions or fabricated data aliases were used.

The original unmodified compiler ET_REL and generated assembly for this exact
source are preserved in the sibling 080CC218 delivery directory. The failed
native report and complete native log are diagnostic artifacts there. Active
unmatched source and report files were removed. A future attempt must still
prove every original ELF byte, plausibility and fresh report replay.
