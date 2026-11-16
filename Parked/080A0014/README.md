# 0x080A0014 - near miss: byte-identical only through a single-use do-while macro (574 bytes)

Target: complete `[0x080A0014, 0x080A0252)`, 574 bytes, 272 instructions. Default flags, no new data symbols.

| file | result |
| --- | --- |
| `080A0014.c` (natural form of 2026-11-15) | NOT MATCHING: 578-byte symbol, 221/271 instructions, 547/578 bytes; the real difference is confined to 0x080A0134-0x080A0170, the rest is branch offsets shifted by 4 bytes |
| `080A0014-macro.c` (2026-11-16, kit fcdf2d45) | `MATCH - byte identical`, 272/272 instructions, 574/574 bytes (elf-symbol-thumb-frame-calls-v1), plausible --strict clean |

Not shipped: a helper or statement macro ships only with shared text (the same text reproduces a second function) or
as a verbatim copy of a real ROM function. `HEIGHT_DIFFERENCE` is neither, and what it contributes is a once-loop
(`do { } while (0)`), the open policy question on loops that run once.

## The natural form (`080A0014.c`)

Fixed against the older parked source: `range` declared s16 (not u32) and used without (s16) casts - the mask load (ldr r3, =0xFF3F; adds r0, r3; ands r7, r0) and the scratch registers of the first distance case now match.

Remaining: ROM keeps the height limit in r4, the first height in r5 (lsls/lsrs #24 into r5) and the absolute difference in r0; the candidate has limit r5, first height r4 (adds r4, r0; lsls; lsrs), difference r4. Cause (allocator dumps): the first height is a block-local pseudo, so local-alloc gives it r4 before the limit is placed; the ROM needs it in global-alloc ranked between the limit and `properties`, which with two references needs a live length <= 8, i.e. a third reference that later disappears.

Diagnostic only, NOT acceptable: the dead statement `if (from_height < 0) from_height = 0;` (value is a zero-extended u8) after the first func_0801CC18 call gives MATCH 272/272. It is dead code that exists only to steer allocation.

The twin 0x080A0254 has the same block shape (limit r4, first height r5, difference r0), and written as this form it has the same r4/r5 swap; the original idiom is shared.

Ruled out: inline abs(f() - f()), explicit if (d < 0) d = -d, copy then -=, static inline helpers with s32 or u8 parameters; s32/u8/u16/s16 height locals with u8/s8/s16/u16 limit (all leave the first height local). Forms that make it global but emit wrong code: to_height - from_height in the negative arm or a double-evaluating ABS (second subs instead of rsbs); negating under from_height < to_height (cmp on the heights). Reuse of one variable for the func_0801CC7C result and the first height (ranks below properties, r5/r6 swap); an s32 holding (s8)to_y reused (needs a func_0809D79C(s32, s32) prototype that contradicts the matched definition). `if (from_height < 0) return 0;` puts the first height in r6.

## The macro form (`080A0014-macro.c`)

`080A0014-macro.c` prints MATCH 574/574 (272/272) with: s16 height_limit
(as the twin 0x080A0254); the first height reused for the result (`height = f(from); height = abs(height - f(to));`,
live across blocks so local-alloc no longer gives it r4); and those two statements inside a single-use
`#define HEIGHT_DIFFERENCE(out, ...) do { ... } while (0)`; prototypes from the matched definitions (func_0809FEF0 returns
u32; func_0812E1A8 and func_080B7C50 take a u8 last argument). The macro works through loop depth: the do-while's loop
notes double the first height's reference count in the allocator's priority (0.200 -> 0.800), above `properties`
(0.217). Best natural form (the first two changes only): 265/272, the first height and `properties` swap r5/r6. Macro
with an s32 limit: 266/272; macro around the plain form: 582 bytes. A source for the twin 0x080A0254 with the first two
changes alone is byte-identical (530/530) and needs no macro; only this function, with its reused `properties`, does.
Nothing shows the original had this macro (src/0800C224.c's `UNLINK_NODE` is a different text). Also ruled out: limit
types u8/s8/u16/s16/u32 with the reuse (r5/r6 swap); range masks ~0xC0, ~0xC0u, (u16)~0xC0; splitting `properties` (spills; the ROM keeps it in r6); zero-initialising
the height outside the if (582); difference and abs in place on the first height (270/272).

kit issue: shubshub/fftadecomp-kit#191 (policy question on loops that provably run once, including `do { } while (0)`)
