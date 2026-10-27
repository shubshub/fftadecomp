# 08010D2C

Complete target: [0x08010D2C, 0x08010DCE), 162 bytes and 81 reachable instructions.

Recovered behavior: resolve a resource pointer from row/column metadata. Flag
0x40 reverses the column with a -1 fallback; flag 0x4000 selects 16-bit row
offsets and two-byte entries instead of 32-bit offsets and four-byte entries.
The selected entry supplies an index; flag 0x2000 selects a 16-bit resource
offset table instead of a 32-bit table. The resolved pointer is stored at +0x18.

The retained complete candidate was tested with fixed agbcc
-mthumb-interwork -O2 and the canonical native matcher. Native exit 1:
162-byte complete ELF symbol, closed leaf CFG, no relocations; source plausible,
bytes differ. The diff reports 57/81 aligned instructions and 134/162 aligned
bytes; these are alignment scores, not same-offset byte equality or match credit.

Remaining differences: the candidate retains column narrowing and a copy of the
flags near the initial field reads, assigning the saved columns/column/flags to
different registers. The target keeps the initial column directly and extends
it only in the reverse calculation. Around the -1 comparison the candidate
loads the row before the signed conversion and constant materialization. In the
compact-entry path it folds the two-byte header into the final indexed byte
load; the target adds the header separately after computing the column offset.
The candidate joins entry values directly in r2; the target assembles in r0
and then copies the common result to r2. Both versions have the same total size,
so those local differences balance without proving equality.

Tried ordinary unsigned and signed field/local forms, natural named signed
arithmetic intermediates, and semantic inline helpers for reverse-column and
entry lookup. The unsigned form compiled to 152 bytes and was refused at the
extent gate; helper/intermediate forms emitted 164 or 166 bytes. No compiler
flags, assembly, volatile accesses or forced-inline attributes were used. The
retained signed direct form has the best tested full-extent result. Matching
remains unresolved; no unmatchability claim is made.

Native log:
/home/user/.codex-work/ffta-ulw/audio-following-v352-matching/08010D2C/match-current.log.
