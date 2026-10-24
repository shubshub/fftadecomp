# 080DE918: one natural-C candidate, not matching

This is a preserved first candidate, not a matched source or a claim that the
function is unmatchable. No source revision or compiler-spelling search occurred.

The approved ROM function owns `[0x080DE918, 0x080DE9DE)`: 198 bytes and 87
reached instructions, including three four-byte literal words and two bytes
of internal alignment. The two bytes at 0x080DE9DE are outside the function;
the next indexed function starts at 0x080DE9E0. The complete target is in the
source comment.

## Exact result

One canonical matcher attempt with `/home/user/agbcc/gcc/agbcc
-mthumb-interwork -O2` exits 1:

```text
compiled symbol is shorter than the indexed span: 190 < 198
```

The compiled complete function has 190 bytes and 83 reached instructions.
Its `.text` is 192 bytes: the final `c046` alignment is outside the sized
symbol and is not counted. Typed linking resolves all five ordinary Thumb
calls with no remaining relocations; the framed CFG passes. A separate
source/header plausibility check reports zero findings. The canonical matcher
exits before report creation, so no canonical match report exists.

Against the true 198-byte target, raw same-offset comparison gives 126 equal
bytes, 64 unequal bytes among the 190 compiled bytes, and eight missing target
bytes. The separate LCS-aligned diagnostic is 176/198 equal bytes; it is not
byte-exact match credit.

The ROM materializes `action ? action : 0` through four additional instructions
at 0x080DE99E..0x080DE9A6 before testing it again. The natural direct conditional
does not emit those eight bytes. The action load uses r0 rather than r1;
later instructions/pools shift by eight bytes, with corresponding branches and
BL encodings changing. The first literal at 0x080DE984 is unchanged; the two
0x113 words move from 0x080DE9B4/0x080DE9C0 to 0x080DE9AC/0x080DE9B8.
No actual wrapper explaining the extra normalization was established. No helper,
redundant normalization, assembly, flag change or padding was introduced to
force that shape. A later attempt requires genuine new source/ROM evidence,
not a spelling retry.

## Recovered contract and limits

Matched dispatcher 08005C04 calls the callback with full task, descriptor and
task+0x18 payload pointers and a u32 result. Constructor 080DF92C registers
080DE919 through 08005B6C with a 0x10-byte payload; it supplies object+4,
u16 delay+0x14 and low-eight-bit action stored as a halfword at +0x16.
The callback preserves that three-pointer public signature and returns zero.
Local structure views express only witnessed offsets and unknown fields.

The state machine initializes the payload at phase 0, does nothing at phase 1
or unhandled phases, decrements the wrapped u16 delay at phase 0x100, optionally
creates a child, and enters phase 0x101 with an eight-tick timer. Timer expiry
dispatches action unless it is 0xFF; cleanup happens only on a later invocation
that enters with timer zero. Child creation forwards the full original task
pointer as the fifth stack argument. No native/runtime semantic campaign was
run after the nonmatch; this is a locally supported reconstruction, not a
whole-game behavioral proof.

Frozen source SHA-256:
`9c11486352ce05282b0872b8b14ddbfbb5b73c82b5be2b1d1f776270e5b59862`.
Source plus all nine unchanged headers:
`7df9a010623a9b140d6a6b45d4f050c76fd3e179281a4501c5b9f894c6bd66e7`.

Local evidence bundle:
`/home/user/.codex-work/ffta-ulw/080DE918-author-next`.
It contains the precompile freeze chronology, canonical log, observed original
and linked ELF records, exact difference offsets/disassembly, input bindings,
and zero-finding plausibility result. The ready source is byte-identical to
the frozen candidate. No game source, metadata or claim state was changed.
