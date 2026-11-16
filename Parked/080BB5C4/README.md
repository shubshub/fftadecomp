# 0x080BB5C4 - near miss: byte-identical only through a single-use inline helper (488 bytes)

Target: complete `[0x080BB5C4, 0x080BB7AC)`, 488 bytes, 223 instructions, default flags, no data symbols. Enters group
objects in a ranked list.

`080BB5C4.c` prints `MATCH - byte identical` (223/223 instructions, 488/488 bytes) and `plausible.py --strict` exits
0, through one `static inline` helper, `child_rank`. Not shipped: a helper ships only with shared text (the same text
reproduces a second function) or as a verbatim copy of a real ROM function, and `child_rank` is neither (below).
Nothing else in the source is in doubt.

## What the function does

Returns at once when `g_state_02000000.mode` (0x2190) is 1. With `skip_first` it remembers the first group's object as excluded; without it, when `func_081352CC(collection, 0, override_mode ? 1 : 0)` is non-zero, the first group's object is entered in the list with rank `max(existing rank, 1)`. Then, for every group whose object is non-null, is not the excluded one and fails `func_080C8280`, the greatest per-child value (0, 1, or 10 when the group's u16 at 0x10 is 0xB8) is taken; a non-zero result is entered, replacing a smaller existing rank. Last, 12 is stored to the list's u16 at 0x78 when bit 7 of the global byte at 0x2FC0 is set.

## The blocking helper: `child_rank`

```c
static inline u8 child_rank(GroupInfo *info, Child *child)
{
    if (info->object == 0 || info->object == child->object ||
        !func_080A8858(child, 3))
        return 0;
    if (info->action == 0xB8)
        return 10;
    return 1;
}
```

What it reproduces: at 0x080BB706-0x080BB714 the ROM keeps three separate arms, `movs r0,#0; b` / `movs r0,#0xa; b` / `movs r0,#1`, joining at `cmp r0, r7; ble`. agbcc's first jump pass rewrites `if (c) x = 10; else x = 1;` into `x = 1; if (c) x = 10;` (jump.c, "Simplify if (...) x = a; else x = b"), which is one instruction shorter, whenever `x` is an ordinary register that the test does not read. Every plain spelling therefore loses the third arm (484 bytes). The rewrite is skipped only when the destination is not a plain pseudo (an inlined function whose return type is narrower than `int`) or when `x` is itself the compared value.

What it lacks:
* (a) No out-of-line counterpart. A ROM-wide scan finds `ldrh rX,[rY,#0x10]` followed by `cmp rX,#0xB8` only at 0x080BB70A, and `movs r0,#0xa; b; movs r0,#1` only at 0x080BB710. Of the 21 call sites of `func_080A8858` none sits in a small function that returns 0/1/10.
* (b) No second expansion. The only functions that call the group accessors together are 080BB5C4, 08134B88 and 081352CC (both unmatched; 081352CC is parked); their child loops have other bodies and neither tests 0xB8.
* (c) No acceptable helper-free form (table below). The single helper-free spelling that matches reuses one local for the action id and then the rank (`value = child_info->action; if (value == 0xB8) value = 10; else value = 1;`), one scratch local reused for two unrelated values, which exists only to steer the compiler.
* The return type is fixed by output shape only. `u8`, `u16`, `s8` and `s16` all match; `s32`, `u32` and `int` give 484 bytes. The ROM has no extension instruction on the value (each arm is a constant). `u8` was kept because the value ends in the `u8` field at entry+4 (`strb r6,[r1,#4]`, compared unsigned against `ldrb r0,[r1,#4]`); that is consistency, not proof. The value is not summed in this function: it is max-reduced into a signed `best` (`cmp r0,r7; ble`) and copied to the unsigned `rank`. The sum happens later in 080BB7AC (u16 at object data + 0xD6 plus the entry's rank byte, capped at 10).

Nothing more can come from this ROM, since the scans above are ROM-wide: it would take another build of the same code that keeps the helper out of line.

## Two helpers of an earlier version, now written in place

* `group_rank(group)`: not needed. The child loop written in the function body matches with function-scope locals. It needs its own info pointer (`child_info`), because the ROM calls `func_080A880C(group)` a second time at 0x080BB6D6 and keeps that result in r4 while the first stays in sb; reusing `info` gives 480 bytes and dropping the second call gives 472. No out-of-line counterpart and no second expansion exist (same scan as above).
* `find_entry(list, object)`: not needed. The lookup is now written in place as a loop that leaves by `goto` past `entry = 0` (merged precedent for `goto found`: src/0801E710.c, src/080C1920.c). That is the only helper-free shape that gives the ROM's hit path (`beq` straight to `cmp r1,#0`) and miss path (`movs r1,#0` falling into the same test). No out-of-line counterpart exists: a scan of the code for a compare-and-advance loop over 8-byte entries finds only the two in this function, and the other functions that use this list's count at 0x6E (080BB7AC, 080BC810) do no lookup by object. The loop body is expanded twice, at 0x080BB642 and 0x080BB72C, both inside this function and nowhere else.
  Two things in the in-place form are load-bearing and are allocator effects only:
  * each lookup needs its own `object` local (block-scoped here). One function-scope `object` shared by both swaps r4/r5: 478/488 bytes, 213/223 instructions.
  * the child loop needs a different index variable (`k`) from the lookups (`j`). One shared index: 439/488 bytes, 164/219 instructions.
  The `object` local itself is in the ROM: `ldr r5,[r0]` loads it before the count test, and the later store reloads `info->object` through sb instead of using r5.

## Alternatives compiled

Rank spellings without `child_rank`, with the child loop in the function body. Rows that give an instruction figure for a 484- or 480-byte build were compiled on the parked source; the remaining rows were compiled with `find_entry` still in place. match.py stops at the extent gate for builds shorter than the span, so those instruction figures are from a diff of the compiler output against the matching build.

| rank written as | result |
|---|---|
| nested `if / else if / else` into `s32 value` | 484 bytes, 217 of 223 instructions |
| the same into a `u8 value` (three arms) | 484 bytes, 217 of 223 |
| `s8` or `s16 value` | 488 bytes, 480/488 identical, 218/223 |
| `u16` or `u32 value` | 484 bytes |
| inner `switch (action) { case 0xB8: ... default: ... }` | 484 bytes, 217 of 223 |
| one conditional expression | 484 bytes, 216 of 223 |
| early `continue` for the zero case | 480 bytes, 215 of 223 |
| `value = 0;` first, then the guarded 10/1 (if/else or `?:`) | 484 bytes |
| `value = 1;` then `if (action == 0xB8) value = 10;` | 484 bytes |
| `!= 0xB8` arm first | 484 bytes |
| `goto done` after each arm | 484 bytes |
| `u16 action` local, then the test | 484 bytes |
| `(u8)` casts on the three constants | 484 bytes |
| redundant `info->object != 0 &&` in the 0xB8 test | 492 bytes, 470/492, 200/225 |
| action id and rank in one reused local | MATCH 488/488 - rejected as a contrivance |

`child_rank` return type: `u8`, `u16`, `s8`, `s16` MATCH; `s32`, `u32`, `int` 484 bytes.

Lookup spellings (with the other two helpers still in place, to isolate the lookup):

| lookup written as | result |
|---|---|
| `goto` past `entry = 0`, per-site `object` local | MATCH 488/488 |
| the same, comparing `info->object` in the loop (no local) | 488 bytes, 459/488, 165/214 |
| the same, one function-scope `object` for both sites | 488 bytes, 478/488, 213/223 |
| `entry = 0;` first, then `break` on a hit | 520 bytes, 397/520, 128/231 |
| `break`, then `entry = j < count ? &entries[j] : 0` | 532 bytes, 430/532, 154/237 |
| `break`, then `entry = &entries[j]; if (j == count) entry = 0;` | 520 bytes, 416/520, 143/231 |
| pointer walk with `break` and a post-loop index test | 504 bytes, 415/504, 144/224 |
| pointer walk with `goto` | 484 bytes |
| `for (;;)` with the bound test inside | 476 bytes |
| `while (j < count && entry == 0)` | 496 bytes, 415/496, 142/221 |
| end-pointer loop | 500 bytes, 370/500, 120/224 |
| `do { } while (0)` around a `break` loop | 520 bytes and `IMPLAUSIBLE` |

Other forms:

| form | result |
|---|---|
| three helpers (`find_entry`, `group_rank`, `child_rank`) | MATCH 488/488 |
| `find_entry` + `child_rank`, child loop in the body | MATCH 488/488 |
| `child_rank` only (the parked source) | MATCH 488/488 |
| `value > best` written through a `u32 value` | 487/488, 222/223 |
| `u32 best` | 487/488, 222/223 |
| testing `best == 0` before `rank = best` | 484/488, 221/223 |
| calling `child_rank` twice instead of a `value` local | 544 bytes |
| earlier parked candidate (no helpers, post-loop index test) | 387/488, 144/218 |

## Other load-bearing choices, checked

* Declaration order: only `total` before `excluded` matters. The ROM keeps `total` at sp+4 and `excluded` at sp+8; declaring `excluded` first swaps the slots (483/488, 218/223) in every order tried (four orders), and both orders tried with `total` first match, including a plain scalars-then-pointers order.
* `info = func_080A880C(group); excluded = info->object;` is two statements: the ROM loads through r0 into r1 (`ldr r1,[r0]`). One expression gives `ldr r0,[r0]` (486/488, 221/223); nesting the two calls gives 484 bytes. The same `info =` statement is used at the three other call sites.
* `enabled`: the result of the two `func_081352CC` calls is merged into a local and then tested (`lsls; lsrs; cmp`). `if (override_mode ? f(.., 1) : f(.., 0))` gives 496 bytes; passing `override_mode ? 1 : 0` or `override_mode != 0` gives 476. `u8` and `s32` both match for the local.
* `func_080A8830` is declared returning `s32`: the ROM uses the result without extension (`mov r8, r0` at 0x080BB6D2). Declared `u8` it gives 492 bytes.

## Layout and prototypes

* `RankedObject`: object +0 (`ldr`/`str`), rank +4 (`ldrb`/`strb`), stride 8 (`lsrs #0x15`, `adds #8`). `RankedList`: count +0x6E (`ldrb`/`strb`), u16 +0x78 (`strh`). `entries[13]` fills 0x68 bytes exactly, and 080BB7AC keeps a pointer at +0x68.
* `GroupInfo`: object +0, u16 +0x10. `func_080A880C` returns its argument (src/080A880C.c), so this is the head of the group record.
* Global state: u8 +0x2190 (`mode`, as src/0812F3CC.c), u8 +0x2FC0 (`movs #0xBF; lsls #6`).
* Callers 080BC810, 080BC878 and 080BC8E8 all declare `void (void *, void *, u8, u8)`; the entry narrows r2 and r3 to `u8` and no caller uses a result.
* `func_081352CC` narrows r2 to `u8` and never reads r1; the caller extends its result as `u8`.
