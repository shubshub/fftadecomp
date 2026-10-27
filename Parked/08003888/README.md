# 08003888 — bounded natural-C attempt

Target: complete [0x08003888, 0x080038C8), 64 bytes and 22 reachable instructions.
Compiler: agbcc -mthumb-interwork -O2. Native profile: canonical-thunks-v1.
No match credit and no native plausibility verdict.

The recovered function initializes the two-node buffer through the genuine ROM
callback table, sets the node count to 1 and selects its first node, initializes
that current node, then sets its ID to 11. The node layout and globals agree with
matched 0800395C and 0800397C. Both callback calls use the typed pointer-and-size
signature already established for g_callbacks_0836D4B8.

Three natural forms were tested: a const-qualified external callback table,
the ordinary unqualified table declaration preserved here, and a semantic
current-node initialization helper. The const form cached the callback value;
the unqualified form correctly reloads it for both canonical _call_via_r2 calls.
The helper did not obtain an exact match.

The preserved simple candidate compiles to the complete 64-byte symbol with
22 instructions. Its remaining difference is the position of the address load
for data_030034B8. Target 0800389A loads r5 before the count store; the candidate
loads r5 at 0800389E, after that store. The surrounding target sequence is
ldr r1; ldr r5; mov r0,#1; strb r0,[r1]; str r4,[r5]. The candidate sequence is
ldr r1; mov r0,#1; strb r0,[r1]; ldr r5; str r4,[r5]. All other recovered
operations, callback argument sizes, node-field offset and literal identities
agree. This is a compiler scheduling gap, not an asserted byte match.

Each native invocation exited 1 with:

    compile failed: inert-spin complete body differs from ROM

That gate stops before native source plausibility is reported. No verifier,
flags, metadata or shared headers were changed. Unmatched active source/report
were removed; only this complete recovered C and diagnosis remain Parked.
