# 0x0814511C bounded matching attempt

Accepted native lease: sol-511C, request6529083902, broker batch52.
Actual native function span and indexed extent: [0x0814511C,0x0814513C),32 bytes.

Actual matched caller08145358 declares void(AudioState *,u16 interval).
Matched player layouts08145990 and08146120 confirm the signature word at0x34.
The target compares that signature with0x68736D53, writes interval to halfword0x26,
then halfword0x24, then0x100 to halfword0x28. Unknown field meanings remain unknown.

Three grounded forms were checked with the default native command:
1. Signature inequality with early return, then three separate stores.
2. Signature equality guarding the same three stores.
3. Equality guard with field24 = field26 = interval, then field28 =0x100.

All three forms were plausible ordinary mismatches, exit1, and emitted the same
36-byte complete ELF function. The target is32 bytes. Generated code adds
push{lr}/pop{r0}, puts interval inr3 rather than targetr1, and loads signature
intor1 rather than targetr3. The native report records5/15 instructions and25/36
comparison bytes. Its36-byte ROM comparison extends4 bytes into the next indexed
function; it is not a32-byte complete-target match. The exact32-byte body and
all compiled bytes are separately bound in the author receipt.

No unsupported-model refusal occurred. No fourth form, compiler workaround,
shared input change, or successful proof replay was attempted. This is a bounded
source/compiler mismatch, not a claim that all natural C forms are impossible.

Final exact source and native report are preserved here as0814511C.c andmatch.md.
All three pre-native source/all9header snapshots, runtime/compiler/tool/map/body
pins, native logs and exit receipts are retained under
state/matching-0814511C-author/. Parent owns lease release and integration.
