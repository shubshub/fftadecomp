# 0809D58C

Recovered the complete reset and child-state update. The function clears the
halfword pair at +0xDC/+0xDE and counter at +0x1A, copies +0x1E to +0x1C,
invokes 0809836C with child +0x00, identifier 11, signed byte +0x27 and mode
zero, maps modes 0/1 to 1 and 2/3 to 3, then invokes 0809A530 and 0809A570.

The fixed native matcher (`agbcc -mthumb-interwork -O2`) exits 1: the source
is plausible, but compiles to 94 bytes / 44 instructions against the indexed
92-byte / 43-instruction target. The preserved local coordinate-array view
matches the initial +0xDC base and the +2/0 store offsets. It then emits one
extra `movs r0, #0` before storing the +0x1A counter. The ROM reuses the zero
already in r0. The following instruction sequence otherwise agrees; its
branch/call offsets shift by two bytes. This is not a byte match.

Natural forms tried: separate x/y fields; a nested position pair; a direct
coordinate array; signed and unsigned halfword-array pointers; chained and
separate pair clears; and a chained pair-plus-counter clear. Direct field
and array views instead retain an extra two-byte address adjustment. Local
array pointers retain the extra zero load described above. All used the
same fixed flags. No assembly, volatile, pragmas, custom flags, or steering
constructs were used. This bounded attempt does not establish impossibility.

Native evidence is retained in the private address scratch as
`best-native-report.md` and `last-native-output.txt`. Its 89/94-byte diff
includes two bytes after the indexed target because the candidate is longer;
that diagnostic does not represent match credit.
