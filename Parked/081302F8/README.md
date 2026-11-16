# 0x081302F8 - near miss: byte-identical only through a single-use helper with an unevidenced parameter type (82 bytes)

Target: complete `[0x081302F8, 0x0813034A)`, 82 bytes, 38 instructions, default flags, no data symbols. If the unit's byte at 0xFD (named `movement`, as src/0809995C.c names the same offset) is 5 it returns 0; otherwise it returns func_0813034C(unit, height(x, y) - height(other_x, other_y)) with heights from func_0801CC18.

`081302F8.c` prints `MATCH - byte identical` (38/38 instructions, 82/82 bytes) and `plausible.py --strict` exits 0, but only because the inline helper `height_difference` declares its four coordinates `s16`. Not shipped: a helper ships only with shared text (the same text reproduces a second function) or as a verbatim copy of a real ROM function, and `height_difference` is neither; its parameter type is also chosen for codegen:

- The coordinates are u8 on both sides of the helper: this function narrows all four at entry (`lsls/lsrs #24`), and func_0801CC18's definition (src/0801CC18.c) takes `u8 column, u8 row`. With u8 parameters the helper is 80 bytes - the same code as having no helper at all. s16, u16, s32, u32 and int all match; s8 does not. Five interchangeable types matching and the only evidenced one failing means the type is chosen for codegen.
- What the type changes is only register allocation. u8 forms narrow x and y into r4/r1 and need one move (r4 -> r0) before the first call, and swap the saved registers of the second pair (r6/r5). The ROM narrows x and y in place (r1/r2), moves both (r0 = r1, r1 = r2), and keeps the second pair in r5/r6: the u8 -> s16 -> u8 round trip makes extra pseudos, and the tie goes to the earlier parameter. No instruction converts anything; the ROM has the same entry narrowings in parameter order in every spelling, because they are this function's own u8 parameters.
- No ROM function corresponds to the helper. Scanning every indexed function for BLs to 0801CC18 finds no out-of-line lookup-and-subtract; small callers (0809D79C, 080BA818, 080D8B7C, 080D8D18, 08131BE0) call it once. 081302F8 itself has no BL callers and no pointer to it exists in the ROM. Merged sources that compare or subtract two heights do it in place: src/0812E1A8.c (`u8 from_height = ...; s32 height_delta = func_0801CC18(to_x, to_y) - from_height;`), src/0801CF10.c (`func_0801CC18(x, y) == func_0801CC18(neighbor_x, neighbor_y)`). src/0809C6B8.c's `height_at(s8, s8)` is a four-use bounds-checked lookup, not this.
- The s16 argument came from src/080D8BD8.c's get_world_coordinates, where the coordinates really are s16: the ROM sign-extends them from s8 fields. 081302F8 has no s16 values.
- Compared with src/080A0854.c's accepted single-use `travel_distance` (merged in PR #165): there the inline's parameters have the same s16 type as the outer function's, so the helper does not change any types, and the evidence was the number of extensions. Every in-place spelling extends the coordinates again at each use and is 8 to 26 bytes longer. Here a helper that does not change types (u8) gives exactly the in-place code. The 2-byte difference is one register move, and the s16 helper gets it only by introducing a type conversion that neither the caller's nor the callee's types call for. Cf. Parked/08082924, a one-line wrapper with no ROM counterpart that exists only to shape codegen.

Tried (all plausible --strict exit 0 unless noted):
| form | result |
| helper, u8 parameters (previous Parked source) | 80 < 82, extent gate |
| helper, s16 / u16 / s32 / u32 / int parameters | MATCH (all five) |
| helper, s8 parameters | not a match: adds u8->s8->u8 re-narrowings of the second pair; verifier refuses ("recursive or intra-function calls are unsupported") |
| helper s16 or int parameters, body `return f(x,y) - f(ox,oy);` (no u8 locals) | 77/82, 35/37 (first result narrowed late) |
| helper u8 parameters, s32 locals | 80 < 82 |
| no helper: `return f(unit, f(x,y) - f(ox,oy));` | 80 < 82 |
| no helper: u8 first/second locals | 80 < 82 |
| no helper: 0812E1A8 idiom (u8 first; s32 difference = first - f(ox,oy)) | 80 < 82 |
| no helper: u8 height; f(unit, height - f(ox,oy)) | 80 < 82 |
| no helper: s16 difference local | 80 < 82 |
| no helper: s32 first/second locals | 80 < 82 |
| no helper: `if (mode != 5) return ...; return 0;` | 80 < 82 |
| no helper: ternary return | 80 < 82 |
| no helper: s16 result local assigned in if/else | 61/84, 22/35 |
| no helper: s32 copies of the four parameters at declaration | 77/82, 35/37 (dead copies anyway) |
| macro HEIGHT_DIFFERENCE(x, y, ox, oy) | 80 < 82 |
| func_0801CC18 declared (), (s16,s16), (int,int), (u32,u32) with direct expression | 80 < 82 (all four) |
Also ruled out: u32 parameters narrowed into u8 locals, a K&R definition, and a u8 wrapper; plain s32 copies after the guard match but are dead copies.

To ship this, evidence would be needed that the coordinates pass through a wider type: a matched caller passing s16/int coordinates to a shared helper, or a ROM out-of-line copy.
