# 0x080A7040 - near miss: byte-identical only through a single-use inline helper (248 bytes)

Target: complete `[0x080A7040, 0x080A7138)`, 248 bytes, 118 instructions. Default flags, no data symbols, no
relocations. Retried 2026-11-16 with kit fcdf2d45.

| file | result |
| --- | --- |
| `080A7040-no-helper.c` (the helper body written out) | NOT MATCHING, 117/118 instructions, 246/248 bytes, plausible --strict clean |
| `080A7040.c` (`static inline void record_adjustment(ValueEntry *, Object *, u16)`) | `MATCH - byte identical`, 118/118, 248/248, plausible --strict clean |

Not shipped: a helper ships only with shared text (the same text reproduces a second function) or as a verbatim copy
of a real ROM function, and `record_adjustment` is neither.
- No out-of-line counterpart: a ROM-wide encoding scan for `ldrh rX, [rB, #4]` followed by an unsigned branch, with
  `strh [rB, #4]`, `str [rB]`, `ldr [rB]` and `cmp #0xc/#0xd` within 24 halfwords, finds only 0x080A7114 (this
  function); a looser scan adds 080261D8 and 08114F1C, neither of which is a slot update.
- No second expansion: the caller src/080A7138.c only walks the array linearly; the sibling src/080A6F20.c and the
  neighbours 080A7218..080A7FE8 have no slot loop; func_0812E5B4 has this single call site.

## The one-instruction difference
Before the 13-slot loop:

    ROM:      lsls r0,r0,#16 ; ldr r3,[r5] ; lsrs r4,r0,#16 ; movs r2,#0
    compiled: lsls r0,r0,#16 ; lsrs r4,r0,#16 ; ldr r3,[r5] ; movs r2,#0

The ROM starts the u16 narrowing, loads the object, and only then binds the narrowed value. In the RTL of the helper
form the u16 argument is zero-extended into a temporary, the object is loaded into its parameter register, then the
temporary is copied into the u16 parameter and combine sinks the `lsrs` into that copy. Written out, the conversion
is followed at once by the copy into `adjustment`. There is no Thumb scheduling pass to reorder them. Only a later
binding gives the ROM order: an inline parameter, or a spare temporary (`u16 value = chance; ... u16 adjustment =
value;`, also MATCH 248/248), and the temporary exists only to delay the `lsrs`.

## Evidence for the rest of the source
- Loop (ROM 080A70F4-080A7118): `movs r2,#0; b test`; the store block `str r3,[r1]; strh r4,[r1,#4]; b exit` at the
  loop top; `adds r2,#1`; test `cmp r2,#0xc; bgt exit`; `ldr r0,[r1]; cmp r0,#0; beq check; cmp r0,r3; bne continue`;
  check `ldrh r0,[r1,#4]; cmp r0,r4; blo store`. The loop leaves at the first empty or same-reference slot and stores
  only when slot.adjustment < adjustment (unsigned). The conditional `break` gives this layout; `if (<) { store }
  break;` in any spelling becomes a pointer walk with an 8-byte frame (240 bytes).
- `state` / `info`: the ROM has the copy (`adds r5,r6,r0; adds r7,r5,#0`, 080A7066-080A7068) and uses both registers;
  one pointer variable gives 90/122. `SelectionState` embeds `SelectionInfo info` as its first member and
  `info = &state->info;`; the sibling's `(SelectionInfo *)state` cast also matches.
- Types: `ValueEntry` is the caller's record (pointer at 0, u16 at 4, u16 unknown at 6; 13 of them fill the 0x68-byte
  block the caller allocates); `Object` is the sibling's name for the one-pointer handle. Offsets from the ROM:
  collection count 0x26BD, state stride 0x2C4, state count 0x2C0, entry stride 0x2C from +0x20, status +9 (ldrb),
  type +0x10 (ldrh, 0x109), flags +0xC (ldrh), slot stride 8, 13 slots (`cmp #0xc; bgt`).
- Parameters: the caller passes its 0x8C-byte result block in r0 at both call sites (080A7164, 080A7174) and this
  function overwrites r0 at 080A7052 without reading it; the second is the caller's own argument; the third the
  13-entry block.
- Separate guards are what the ROM tests: `status == 11 || status == 12` in one statement folds to a range test
  (252 bytes); `!(flags & 0x80) || (flags & 0x40)` folds to `(flags & 0xC0) != 0x80` (240 bytes).
- `s32 chance` from an `s16` callee: the ROM re-extends r0 after the call, tests it signed, then narrows it again for
  the u16 parameter; `s16 chance` folds the second narrowing away (244 bytes). src/0812E5B4.c defines the callee
  returning `s32` but also matches as `s16`, and this is its only call site; with an `s32` callee only
  `chance = (s16)func_0812E5B4(...)` matches.

## Alternatives compiled
n/118 and bytes are match.py results; n/122 counts 118 instructions plus 4 literal halfwords from a direct compile.
| form | result |
| --- | --- |
| `u16 adjustment = chance; Object *reference = info->object;` (block or function scope, any order) | 117/118, 246/248 |
| `Object *reference` first, then `u16 adjustment` | 112/118, 241/248 (order and r3/r4 swapped) |
| no locals | 86/117, 205/248 |
| reference local only, `(u16)chance` in the loop | 99/118, 227/248 |
| reference from `state->info` / `state->object` | 94/119, 213/250 |
| reference hoisted to the outer loop | 81/117, 219/250 |
| slot pointer local; pointer walk; while; do/while; positive nested | 240-248 bytes, 79-120/122 |
| index `u32` / `u8` / `s16` | 120/122; 106/122 (252 bytes); 93/122 (256 bytes) |
| `chance & 0xFFFF`; narrowed before the sign test; object in the for-init; nested `if (chance > 0)` | 121/122; 102/122 (244 bytes); 121/122; 121/122 |
| local `ValueEntry candidate` (field or struct copy) | 268-272 bytes |
| 240 permutations of scope, declaration and assignment order, u16/u32, s32/s16 chance, info/state | best 121/122 |
| 480 permutations of callee return type, call cast, chance type, test spelling, locals, narrowing site | best 121/122 |
| `u16 value = chance; ... u16 adjustment = value;` (spare temporary) | MATCH 248/248 - rejected, steering temporary |
| helper parameters (reference, adjustment, entries) | MATCH |
| helper (entries, adjustment, reference); `SelectionInfo *` parameter with the load inside | 121/122 each |
| helper with an `s32` parameter narrowed inside / `s16` / `s32` or `u32` parameter / not inline | 116/122 / 104/122 / 244 bytes / 264 bytes |
| inside the helper: guard with `continue` or positive guard | MATCH |
| inside the helper: `if (<) { store } break;`, `return` for `break`, while | 240 bytes |
| inside the helper: slot pointer / search then store | 103/122 / 260 bytes |

## Notes on other files
- src/080A7138.c declares `func_080A7040(ValueResult *, const void *, ValueEntry *)`; the second parameter is the
  `SelectionCollection *` of src/080A6F20.c, and its `UnitReference` is the `Object` handle here (names only).
- src/080A6F20.c also matches (286/286) with the embedded `SelectionInfo info` member in place of its cast.
