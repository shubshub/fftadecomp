# 08126FCC: one-form native extent mismatch

The complete target is `[0x08126FCC,0x08127124)`, 344 bytes and 148 reached
instructions, including 12 literal bytes and four zero alignment bytes.
The index correction was applied by the parent before this accepted attempt.

One natural source form was compiled under the fixed agbcc
`-mthumb-interwork -O2` configuration, actual host cpp13 and the explicit
`--function-address-profile canonical-thunks-v1` selector. The original native
command exited 1 with this exact error:

```
compile failed:
inert spins require an exact unique nonoverlapping Thumb span
```

No native match report or plausibility verdict was produced. This result is
an ordinary emitted-extent mismatch, not evidence that the selector is
unsupported. The once-authorized unchanged-source compiler-only diagnostic
emitted one complete FUNC of 320 bytes in both original and linked ELF,
24 bytes shorter than the indexed target. No proof/admission API or match
report was run or created by that diagnostic.

The diagnostic exposes a genuine layout failure in this candidate: agbcc
places the `options` union fields at payload offsets 0x10 and 0x11 and reads
the packed halfword at 0x10, whereas the actual target uses offsets 0x0E,
0x0F and halfword 0x0E. The candidate therefore does not reproduce the
observed payload layout. The target also explicitly sign-extends the wrapped
byte total before subtracting shared endpoints; the emitted candidate lacks
that sign-extension sequence. These differences are preserved, not treated
as an established source or ABI equivalence.

The first fixed-offset differing instruction is at 0x08126FDC: candidate
`beq 0x081270AA`, target `beq 0x081270B8`. Later differences include case-block
order, branch targets, the remaining-count loop condition, the call shared
by the two setting branches, and literal-pool placement. Across the maximum
344-byte extent, 308 fixed offsets differ, including 24 missing tail bytes;
this is not an aligned-instruction identity score. The generated assembly,
original and linked ELF, complete emitted and target bytes, and every byte
difference remain in the private diagnostic packet.

The source retains the genuine typed callback through the compiler R2 thunk,
full u32 accessor result, full s32 predicate with an observed low-byte test,
real pointer/word carriers and four u16 settings with two scalar outgoing
words. Callback behavior and returning ARM ABI remain conditional; no memory
allocation, readability, callback effect, numeric or transitive-equivalence
premise was added. No assembly, pragma, volatile access, dead code, forced
frame/register, fabricated bound or alternative source form was used.

The exact failed source is preserved here unchanged. Counts: one source
form, one original native attempt, one unchanged-source compiler-only
diagnostic, zero retries, zero successful replays and zero MATCH credit.
A genuine observed-layout correction is a prerequisite for any future
source work; it was not authorized or attempted in this bounded run.

Private evidence:
`state/matching-08126FCC-author/final-receipt.json` at the handover root.
