# 0x08123474 - near miss: byte-identical only with two value-neutral (u8) casts (64 bytes)

Retry of Parked/08123474 on 2026-11-16, kit fcdf2d45, default profile. Not shipped: the match depends on casts that change no value and exist only to steer the compiler.

The source here prints `MATCH - byte identical` (64/64 bytes, 31/31 instructions, elf-symbol-thumb-frame-calls-v1) and passes
plausible.py. Index row 08123474 081234B4 64 is correct (push {r4,r5,r6,lr} / pop {r4,r5,r6}; pop {r1}; bx r1, no pool).

It is the parked C with three changes: the endpoints are `s16 start/end = script[N]`; the early test is
`if ((u8)start == (u8)end) return 0x110;`; the high nibble is `(u8)start >> 4` (same for `end`); the low nibble stays `start & 0xF`.

Why it is parked:
1. The `(u8)` casts change no value (start and end only ever hold one byte). They exist only because they produce the bytes: the cast in
   the test puts `lsls r2, r1, #24` before the `beq`, and the second block reuses that shifted value, which is how the high nibble becomes
   `lsrs #28`. Removing either cast gives the parked 60-byte output with no early `lsl`. The low nibble must come from the uncast variable.
2. Nothing evidences `s16` for the endpoints: int/u32/u16/s32 give the same instructions with the script pointer in r3 instead of r5, and
   u8 loses the `lsl` entirely.

Ruled out (about 22 compiles): a local union of a raw u8 and x:4/y:4 bitfields (and/orr into a garbage register); a union with u32
bitfields (high nibble back to lsr #4); a command struct with bitfields read through a pointer (ldr of a whole word); a static inline
helper with u8 parameters, given byte or s16 arguments; every variant with casts in only one of the two places; a nested if instead of
the early return (extra register copies). Declaration order does not matter; `/ 16` compiles the same as `>> 4`.

No natural spelling found that gives the early `lsl #24`. Neighbour 0x0812352C reads a nibble pair from one script
byte as two s8 locals; that form does not reproduce this function's early test.
