# 08002D84

The preserved complete natural candidate converts ASCII lowercase letters to
uppercase and leaves every other byte unchanged. With fixed agbcc
`-mthumb-interwork -O2`, its final fresh native check returned exit 1:
complete 32-byte ELF symbol, closed leaf CFG, no relocations, plausible source,
but 20/32 bytes and 7/16 instructions identical. The indexed target is exactly
32 bytes / 16 reachable instructions. No match credit is claimed.

The ROM preserves the original byte in R1 and a separate result in R2. Its
range check subtracts 0x61 from the normalized byte, then narrows that offset
before comparing with 25. The candidate folds the subtraction into the
already shifted incoming byte using `(0x9F << 24)`, keeps the result in R1,
and narrows the changed byte before the common return. These differences
remain despite identical ASCII conversion behavior.

Tested forms: direct range guard with a byte result (preserved); a promoted
signed-word result (28-byte extent refusal); an explicit byte lowercase offset
with that promoted result (28-byte extent refusal); a genuine naturally
inlined lowercase classifier (36-byte complete plausible nonmatch, with extra
Boolean materialization); and a word input narrowed to a byte inside the
routine with a promoted result (28-byte extent refusal). Overlong native
comparison included four bytes from the following ROM function and is not a
32-byte target comparison. The original complete candidate was restored and
freshly checked before freezing. No further variants were tested.

The final native output and source-bound report are preserved in the private
address scratch as last-native-result.txt and last-native-report.md. The
unmatched active source/report and temporary compiler diagnostics were removed.
