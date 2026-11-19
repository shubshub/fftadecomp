# 0x0809836C - action sprite set-up for an object: bytes identical, refused (six jump tables with loops, named data and a read/write frame) (1600 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`void func_0809836C(Object0809836C *object, u16 action, s8 direction, u16 item)` starts an action animation on an
object (a negative `direction` keeps the object's own). A first switch on the action releases the object's two
sprite handles, sets its animation through `func_080975DC` and updates its flags. Every other action takes the
default path: the item's category (`func_080CA7A4(item, 3)`) is mapped to a type, a second action switch and three
per-action type switches pick the animation, sprite, palette and offset, and the extra sprites are created and
configured in a one-sprite or a two-sprite handle loop. It inlines four sibling functions of the same source file:
`func_0809A09C`, `func_0809A298`, `func_0809A398` and `func_0809A570`.

## The index

The index row `0809836C 080989AC 1600 627 return` is right: the start is word aligned and the last pool word
(0x080989A8 = 0x08394350) is inside the span. The kit's `analyze.refine_function` closes the CFG with 627 reachable
instructions.

## Byte identity

`0809836C.c` (SHA-256 `77a9714f589c34a7e4126ebd47da959d2945f7b191573f478dd5df18a6e7905c`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0809836C, with every callee and data symbol bound to its ROM address (37 `R_ARM_THM_CALL`,
66 `R_ARM_ABS32`, including the six jump tables and their pool words). The 1600-byte symbol equals the ROM span
`[0x0809836C, 0x080989AC)`: SHA-256 `6b31f2ed6c91907995ec198ff91a0bd33dbdd8ffbc3e30b1da6f26f29960f074` for both.
`.text` is exactly 1600 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict`
exits 0.

## Data symbols

One is needed: `"data_08394350": "0x08394350"`, next to the existing `data_08394352`.

- ROM contents: `data_08394350` = `{0x08, 0x10}` and `data_08394352` = `{0x10, 0x10}`, adjacent and not overlapping.
- The ROM has two separate pool words. 0x0809891C = 0x08394352 is read by the one-sprite loop: `subs r3, r5, #1`,
  then the base is added, then `ldrb` (0x080988C8-0x080988D0), that is `data_08394352[i - 1]`, as in the merged
  `src/08097704.c`. 0x080989A8 = 0x08394350 is read by the two-sprite loop: `adds r2, r5, r2`, then `ldrb`
  (0x08098950-0x08098954), that is `data_08394350[i]`.
- If both loops indexed one array, `[i + 1]` would fold to a 0x08394351 pool word with no `subs`; the ROM has neither.
- Without the symbol, the default run refuses first with `data target must be an undefined mapped object`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0809836C.c` and the data symbol added.
None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `switch words must describe an adjacent table and forward local cases` | `match.py:2411` in `switch_layout`, reached through `selected_switch_layout` (`match.py:2185`) |
| `--owner-runtime-profile ordinary-multiple-switch-source-v1` | `data target must be an undefined mapped object` | `match.py:886` in `call_bindings`, called from `multiple_switch_owner_prerequisite.py:123` (through `multiple_switch_native_profile.py:31`) |
| `--switch-data-profile u16-scalars-frame-v1` | `switch words must describe an adjacent table and forward local cases` | as default |
| `--switch-data-profile u16-scalars-functions-frame-v2` | `switch words must describe an adjacent table and forward local cases` | as default |
| `--owner-runtime-profile canonical-integer-scalar-data-source-v1` | `six-word integer source requires canonical integer calls and zero-addend named objects` | |

## Cause

The function combines four things that no single selector admits together:

- **Six jump tables**, all with forward cases: the action switch (table at 0x080983B8), the item-category mapping
  (0x080986F0), the second action switch (0x08098774), and three per-action type switches (0x080987BC, 0x080987FC,
  0x0809883C).
- **Six loops**: the release loops (each first-switch case), the flag loops (the inlined `func_0809A570` copies), and
  the one-sprite and two-sprite handle loops.
- **A 0x18-byte frame that is both written and read.** Two locals are spilled to `[sp, #0xc]` and `[sp, #0x10]` and
  read back, at 0x08098936 and 0x08098956/0x0809895A; outgoing argument words 5-7 sit at `[sp]`-`[sp, #8]`.
- **Two named data pool words**: `data_08394350` and `data_08394352`.

How each candidate fails:

- **The default path** treats every local switch relocation as one table: the pointer word followed by adjacent
  entries. With six tables the sorted relocation offsets are not one contiguous range, so `switch_layout` rejects
  them.
- **`ordinary-multiple-switch-source-v1`** partitions up to eight tables, but its prerequisite passes no data map, so
  any named data word is refused (the refusal above); it also rejects local CFG cycles
  (`multiple-switch prerequisite excludes local CFG cycles`) and any instruction with an SP operand other than push,
  pop and stack adjustment (`multiple-switch excludes wide/block operations and stack address materialization`).
  This function would hit all three.
- **The framed switch-data selectors** (`u16-scalars-frame-v1`, `u16-scalars-functions-frame-v1` / `-v2`,
  `switch-thunks-frame-v1`) allow one table and a write-only outgoing-argument frame; a read of the frame is refused.

A kit fix would need a multi-switch owner that also admits bounded loops, typed named data words and a spill frame
that is both read and written, alongside the outgoing argument words. The C should not be changed to fit the
verifier.

## Source notes

### 1. `func_0809A298` is inlined in cases 0-5 and the default path

`func_0809A298` is a real ROM function in the same source file, `func_080975DC(object, value, adjustment, 1)`
(`src/0809A298.c`). The merged `src/0809A2D8.c` already inlines it as `inlined_0809A298`, and the text here is the
same. Case 11 passes `automatic = 0`, so it calls `func_080975DC` directly.

It is load-bearing. With direct `func_080975DC(..., 1)` calls:

- **The case paths:** GCSE hoists two values into a new pseudo each at the start of every case: `direction << 24`
  (pseudo 396: 15 refs, live 150, priority 3000) and `object + 0x4C` (pseudo 397: 16 refs, live 206, priority 3106).
  The compiler places `object + 0x4C` first, so it gets r7 and the shifted direction gets r8. The ROM has the
  reverse: `lsls r7, r0, #24` at 0x080983F0 and `mov r8, r1` at 0x080983F6.
- **The default path:** the call at 0x080988AC loads r0 before r2, where the ROM has `adds r2, r7, #0` at 0x080988AC
  ahead of `adds r0, r6, #0` at 0x080988AE. With the inline, the direction is bound to the helper's s8 parameter
  before the call is set up, and the call's own re-extension reduces to a copy that the compiler places ahead of the
  r0 load: the ROM order.

### 2. `func_0809A570` is inlined with u16 parameters

The inlined copy here takes `(Object0809836C *flags, u16 clear, u16 set)` and passes `clear` and `set` straight to
`func_08021DE4`. The ROM loads these constants afresh at every call, also inside the loop: for example
`movs r1, #0x80; lsls r1, r1, #1; movs r2, #2` at 0x08098426-0x0809842A and again at 0x0809843A-0x0809843E, and
`movs r2, #0x81; lsls r2, r2, #1` at 0x080984F2 and 0x08098506.

The merged `src/0809A570.c` takes `void *object, u32 clear, u32 set` and copies them into locals
`u16 clearBits = clear; u16 setBits = set;`. Inlined with that spelling, each mask becomes a pseudo set once to a
constant, and the masks are held in r7 and sb across the loop (`movs r7, #0x80; lsls r7, r7, #1; ... adds r1, r7,
#0`), which the ROM does not show.

Other spellings of the out-of-line function, compiled on their own:

| Out-of-line spelling of 0809A570 | Matches 0x0809A570? |
|---|---|
| `(ObjectFlags *flags, u16 clear, u16 set)`, no locals | identical (BLs compared unlinked) |
| `(void *object, u16 clear, u16 set)` with a local `ObjectFlags *flags = object;` | no: the parameter narrowing comes before the object copy |
| `(void *object, u32 clear, u32 set)`, passed straight through | no |

#### For the reviewer

Shared text with a merged sibling is evidence only if the sibling's matching text is not edited to create it, and
the inlined copy here is not text-identical to the merged `src/0809A570.c`. Making them match would mean respelling
`src/0809A570.c`:

- change the signature from `void func_0809A570(void *object, u32 clear, u32 set)` to
  `void func_0809A570(ObjectFlags *flags, u16 clear, u16 set)`;
- delete the three locals `ObjectFlags *flags = object;`, `u16 clearBits = clear;` and `u16 setBits = set;`;
- pass `clear` and `set` in place of `clearBits` and `setBits` in the two `func_08021DE4` calls;
- keep the loop, the `ObjectFlags` type and the `func_08021DE4` declaration.

That respelling compiles to the same 58 out-of-line bytes at 0x0809A570
(`f0b5071c09040e0c1204150c786c311c2a1c...0134012cf1ddf0bc01bc0047`), checked with a standalone agbcc compile of the
respelled text with BLs compared unlinked; it was not re-run through `match.py`. Whether to edit the merged sibling,
or to ship this copy with text that differs from it, is a decision for whoever ships it.

### 3. The other inlined copies

- `inlined_0809A09C`: the sibling text of `src/0809A09C.c` (release both handles, then clear them). It appears once
  per first-switch case, for example at 0x080983F8-0x08098416.
- `inlined_0809A398`: the sibling text of `src/0809A398.c` (category 0x1D/0x20/0x48/0x49 gives 4), at 0x080984C0. The
  ROM has no out-of-line callers of `func_0809A398` at all.
- `inlined_0809A570`: see note 2.

Each is a real ROM function in the same source file, and the out-of-line copies are emitted after this function, as
the compiler emits deferred inline functions. Each helper carries an `/* An inlined copy of ... */` comment giving its
ROM site.

### 4. `s32 animation`

Load-bearing. Declared `u16`, the `adds r1, r4, #0` moves from 0x080988A4 (ahead of the direction's `lsls`/`asrs`) to
after `adds r0, r6, #0`. In the ROM that move into r1 is all that is left of a narrowing to the u16 parameter, bound
at the inline argument before the direction, so the variable is wider than u16. It is only ever assigned constants
and is also added to the direction (`adds r7, r4, r7` at 0x080988C0), so `s32` is the natural type. There is a
comment at the declaration.

### 5. The zero assignments come after the direction fix-up

`palette = 0; sprite = 0; offset = 0; animation = 0;` are statements after
`if (direction < 0) direction = object->direction;`. The ROM tests and fixes the direction first
(0x0809838A-0x08098390), then stores the four zeros (0x08098392-0x080983A0: sb, `[sp, #0xc]`, `[sp, #0x10]`, r4).
Initialisers on the declarations put the zeros ahead of the test; writing them after the `if` is ordinary statement
order.

### 6. Declaration order

`palette, sprite, offset` is load-bearing: swapping it to `offset, sprite, palette` changes the code from 0x08098398.
It matches the order of the zero stores. The order of `category, type, count, i` is not load-bearing; the reversed
order is identical.

### 7. ROM-shown constructs, each commented at the site

- **Case 10 falls through into case 0.** `func_08098130` at 0x080983E8 runs into the case 0/9 code at 0x080983EE.
- **Cases 16 and 17 repeat their body.** Each sets type 1, offset 0x10 and sprite 0x7E, then sprite 0x7C if the item
  is 0x2D; only the animation differs (0x94, 0x98). The ROM keeps one copy, entered at 0x08098892, because the
  compiler merges identical tails: the same as the duplicated store in the merged `src/08148914.c`, which the ROM
  keeps once after cross-jumping.
- **Type 4 gives animation 0x70 in cases 6, 7 and 8.** Each of the three type switches writes it in its own
  `case 4:`, and the compiler shares one block at 0x08098858 (case 8's type-3/type-4 block).
- **`count` lives in a register.** It is `movs r0, #3; mov r8, r0` at 0x080988BA, and 2, or 1 when flag 2 is set, at
  0x08098920-0x0809892E; both loops compare `cmp r5, r8`. This mirrors `end_row = 3` in the merged `src/08097704.c`.
- **Two palette tests that never fire.** In the one-sprite loop, `if (action == 13) palette = 1; if (action == 12)
  palette = 2;` (0x080988F0-0x08098902) can never fire, because actions 12 and 13 always set type 1. The ROM keeps
  both tests. This is unreachable logic with no behavioural effect, so it is not a bug and needs no bug case.
- **`object->handles[i]` is read again** for the `func_08021E64` call in the two-sprite loop: `ldr r0, [r4]` at
  0x08098986, after `func_08021C08` has clobbered r1. The source names the field there, not the local `handle`.

### 8. Types and names

- The struct offsets come from the instructions: `unit` +0x00 (with `category` at unit+0x04); `palette` +0x1E,
  `direction` +0x1F; `flags` +0x30, `sprite` +0x34, `animation` +0x36; `renderer` +0x40, `display` +0x44,
  `handles[2]` +0x4C. The names follow `src/080975DC.c`, `src/08097704.c`, `src/08097A04.c`, `src/0809A09C.c` and
  `src/0809A570.c`; members without evidence are `unknown_*`.
- `palette` and `sprite` are `s32`: both take `func_080CA7A4`'s `s32` result without narrowing, and `palette` is
  narrowed at each `func_08021E64` call.
- The prototypes follow the merged callees: `func_08021618` (`src/08021618.c`), `func_08021DE4`, `func_08021C08`,
  `func_08021E64`, `func_08021E28`, `func_08021E68`, `func_08021BD4`, `func_080CA7A4` and `func_080975DC`.

kit issue: shubshub/fftadecomp-kit#74 (switches combined with named data; here six tables, loops and a read/write frame)
