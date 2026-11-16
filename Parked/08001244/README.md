# 0x08001244 - near miss: matches only in the context of its original file (120 bytes, 114/120 alone)

Retry of Parked/08001244 on 2026-11-16, kit fcdf2d45, default flags. NOT MATCHING alone: 40/46 instructions, 114/120 bytes.
Extent [0x08001244, 0x080012BC), 46 instructions, word aligned, push {r4-r7, lr} / pop; the 7-word pool ends at
0x080012BC. Not -O0 (no mov r7, sp).

The six differing instructions are one register swap: the ROM keeps the address of data_03002F58 in r6 and of
data_03003168 in r5; the single-file compile has them the other way round. Everything else - extent, loops, store order,
literal pool - is identical.

Why (checked against agbcc's gcse.c, hash_expr_1): those two pseudos are created by GCSE and are equally ranked, so the
lower-numbered one gets r5. GCSE numbers them in hash-bucket order of the constant-pool labels `.LCn` (bucket = the
label string's hash mod a table size of max_cuid/2|1, 25 here). Compiled alone the labels are LC0-LC4 and data_03002F58
(LC0, bucket 11) always precedes data_03003168 (LC4, bucket 15); the ROM needs the opposite. Shifting the label counter
by k with a throwaway preceding function (test only): k = 9-12, 16-19, 26-29, 36-39 reproduce the ROM exactly, every other
k in 0..40 does not, and a bucket model predicts all 41 results. Compiling src/0800105C.c + src/08001194.c + this C as
one file (conflicting duplicate declarations renamed only) puts this function's labels at LC29-LC33 and its code bytes
0x08001244-0x0800129F equal the ROM, the two constant pool words match, and only the five relocated symbol words differ
in the unlinked object (both siblings likewise differ from the ROM only at relocated words).

So the target is this exact source compiled in a file that had already used 29 constant labels. A one-file match would
need contrivances (extra functions or inline helpers that only consume labels), which are not allowed. The fix is in the
tooling: verify a function in the context of its neighbouring functions in the same translation unit, or accept a
constant-label offset; neither exists on kit main fcdf2d45.

Ruled out: swapped helper parameter order (45 instructions); the local-alias style of 08001ED0/08002108 (38/46, 27/45,
116 bytes); 0800105C's declarations (table size stays 25); other single-file spellings (label order is fixed by
evaluation order; changing the table size needs 76-79/88-91 or < 36 GCSE instructions).

Source: `static inline HideEntries(u64 *entry, s32 count)`, character for character the helper of merged
src/08001194.c, called twice, and a chained count reset.

kit issue: shubshub/fftadecomp-kit#189 (position in the translation unit)
