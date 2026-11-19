# 0x0812130C - effect script player: bytes identical, refused (a switch pool with one interposed object word beside stack buffers, and the volatile check's path bound) (1530 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`u32 func_0812130C(void *context, Request0812130C *request, State0812130C *state)` is a script player with phases 0,
0x100, 0x101 and 0x102 (the outer switch compiles to a compare tree). Phase 0 copies the request's group and fills
`state->objects[0..count)`. Phase 0x100 counts down `delay`, then runs record `data_083A7A34[state->step]` (16 bytes:
u8 op at +0, u16 id at +2, u8 delay at +4, u32 words at +8 and +0xC) through a 22-entry jump table on `op` (cases
0-11 and 13-21; 12 and anything above 21 fall to the tail). The tail sets the phase to 0x102 when the record finished
the script, and otherwise advances it unless the record holds the step. Phase 0x101 waits for `func_080D8B4C` and the
script task, loads the next delay and moves to the next record (`cmp #0x4A` at 0x081218D4 ends after record 74). The
source includes `ffta.h`, `control_flags.h` and `effect_registry.h`.

Nothing in the ROM refers to it: a byte search found no word 0x0812130D at any alignment, and the review in
`docs/match/0810533C.md` rules out the word 0x0812130C and any BL or branch to it.

## The index

The index row is `0812130C 08121906 1530 765 return`. The extent is right: the start is word aligned, the prologue
`push {r4-r7, lr}; push {r8-sl}; sub sp, #0x1c` matches the epilogue at 0x081218F4..0x08121904, the last pool word is
0x081218E0, and the next function starts at 0x08121908 after two padding bytes. The instruction column is the
halfword count (bytes/2): the kit's `analyze.refine_function` closes the CFG with 628 reachable instructions, and only
with its `one_object_word_switch` (or `one_numeric_word_switch`) opt-in; it then reports one
`bounded-guarded-word-switch-v1` with bound 21 and `interposed_words: 1`. Without an opt-in it stops at
`unresolved jump at 0x081213E0` after 159 instructions, and `two_constant_word_switch` does not help. Not corrected
here: no draft needs it.

## Byte identity

`0812130C.c` (SHA-256 `8cf4799154896d4415f9f51bc4d964bd0a36464930ea38248bd3411be0dcb992`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0812130C, with every callee and data symbol bound to its ROM address (66 `R_ARM_THM_CALL`,
31 `R_ARM_ABS32`, including the table pointer and the 22 table words). The 1530-byte symbol equals the ROM span
`[0x0812130C, 0x08121906)`: SHA-256 `bb664cdc2652fd837a4a4a2dcf4e6bbcb611c70f9ce3d22d6286abb2a9602400` for both.
`.text` is 1532 bytes: the symbol plus two bytes of alignment padding. `match.py` refuses before its own byte
comparison (below). `plausible.py --strict` exits 0; the volatile refusal comes from `match.py`'s own semantic check.

## Data symbols

One is needed: `data_083A7A34` = `0x083A7A34`, the const table of 16-byte script records. Its pool words are
0x081213E4 and 0x081218E0 (`data_083A7A34`) and 0x0812164C (`data_083A7A34+8`, the hoisted base of
`data_083A7A34[step].first` in the opcode-11 loop). The other objects are already named: `data_03000000` (input
state, `pressed` at +2), `g_control_flags_03000940` through `control_flags.h` (`display` only) and `data_03003860`.
Without the symbol the default run refuses first with `data target must be an undefined mapped object`.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0812130C.c` and the data symbol added.
None matched.

Default, and `--switch-data-profile u16-scalars-frame-v1`:

```
compile failed:
stack aliases cannot cross calls in caller-clobbered registers
```

(the default walk refuses at the call `bl 0x080DBD5C` at 0x081216F6, `match.py:5006`).

`--owner-runtime-profile bounded-buffer-root-guarded-switch-v1` (the profile of sibling 08120724):

```
source    IMPLAUSIBLE
verdict NOT VERIFIED - the selector was not run

plausibility findings:
  allowlisted volatile semantic check: real compile of func_0812130C: more than 32 unknown branch conditions on one path (loops with unknown exit conditions are not modelled); relational loop induction (kit#137): real compile of func_0812130C: a frame store in a loop outside the slots it stores at [sp, #imm] at `<back edge of loop 1 at instruction 325>`
```

The shapes behind them:

- **The switch pool.** `cmp r0, #0x15; bls; b default` at 0x081213D2, then the five-op dispatch at
  0x081213D8..0x081213E0. One reached object word, `data_083A7A34` at 0x081213E4, sits between `mov pc, r0` and the
  table-pointer literal at 0x081213E8; the 22-word table follows at 0x081213EC.
- **The stack buffers.** A fixed frame (`sub sp, #0x1c`, spill slot at sp+0x18) passes stack addresses to ordinary
  callees: &x, &y (sp, sp+2) to `func_0801E6F0` at 0x081214A2, and &x, &y, &z to `func_080DBD5C` at 0x08121686
  (sp+0xA/0xC/0xE) and 0x081216F6 (sp+0x10/0x12/0x14). The switch-data frame path has no buffer proof, so it refuses
  these.
- **The volatile check.** The source reaches the allowlisted volatile object through `control_flags.h`, although it
  uses only the non-volatile `display` member (`&= ~func_080035A8(n)` at 0x08121810..0x08121822 and
  `|= func_080035A8(n)` at 0x08121868..0x0812187A). The check therefore runs before any selector, and it cannot bound
  this function: too many branch conditions on one path. Its kit #137 retry refuses the u8 counter loops that store
  through a register alias of the frame (`strb r0, [r4]` with r4 = sp+4 at 0x0812157A; the same at 0x081215D8 and
  0x0812163C). This finding is selector independent.

### Header diagnostic (not the parked source)

To see which refusal comes after the volatile check, a diagnostic copy replaces `#include "control_flags.h"` with a
local `extern struct { u16 display; } g_control_flags_03000940;`. That copy is still byte-identical (the same
SHA-256 by the hand link above). On it:

| Selector | Refusal |
|---|---|
| `--owner-runtime-profile bounded-buffer-root-guarded-switch-v1` | `structural inventory is not closed` (`owner_graph_profile.graph`, called from `owner_admission_profile.verify`): the owner refinement passes no layout opt-in, so the jump at 0x081213E0 stays unresolved |
| default | `stack aliases cannot cross calls in caller-clobbered registers` |
| `--switch-data-profile u16-scalars-functions-frame-v2` | `u16 switch-data requires a mapped local switch without other runtimes; function literals require and are required by a function-literal selector` |

A second diagnostic copy (not re-run for this entry) used the plain `extern u16 g_control_flags_03000940;` spelling,
as 90 merged sources do, including sibling 0811C50C. It is not byte-identical: it loads the 0x03000940 literal before
the `func_080035A8` calls instead of after them, and `match.py` reported `switch caller differs from the ROM`
(default) and `inert-spin complete body differs from ROM` (root-guarded-switch). So the struct-member spelling is the
one the ROM shows.

## Source notes

Every item below is load-bearing unless it says otherwise; for each one the plainer form was compiled and did not
match.

### 1. `static inline void select_range(u8 target, u8 count, u8 *first, u8 *end)`, opcodes 9, 10 and 11

```c
static inline void select_range(u8 target, u8 count, u8 *first, u8 *end)
{
    u8 start;

    if (target == 1)
        start = 0;
    else if (target == 2)
        start = 0;
    else if (target == 3)
        start = 1;
    else
        start = 0;
    *first = start;
    *end = start + count;
}
/* each of cases 9, 10, 11: */
{
    u8 index, end;

    select_range(data_083A7A34[state->step].second, state->count, &index, &end);
    for (; index < end; index++)
        func_080DE390(state->objects[index]);   /* 10: func_080DBEB4(.., 0); 11: func_080DE10C(.., record.first) */
}
```

#### For the reviewer

**ROM evidence.**

- **Three repeated blocks and no out-of-line copy.** The selection block appears at 0x0812152E..0x08121558,
  0x08121588..0x081215B4 and 0x081215E6..0x08121610. The copies are identical apart from frame offsets and the loop's
  callee. A ROM-wide byte search for the chain `cmp r0, #1; beq; cmp r0, #2; beq; cmp r0, #3; bne` finds these three
  sites and no others, so no function of this shape exists out of line.
- **Per-case stack bytes.** Each case's index/end pair lives in its own frame bytes: sp+4/5, sp+6/7 and sp+8/9. No
  call takes their addresses. The selection stores through `add r2, sp, #4` / sp+5 in r2/r3 (0x0812153A..0x0812153E);
  the loop reloads both through separate copies (`adds r6, r2, #0; adds r5, r3, #0` at 0x08121542) and keeps them in
  memory across the callee.
- **u8 parameter loads.** The record's u32 word at +0xC is read with `ldrb` (0x08121536, 0x08121590, 0x081215EE),
  the narrowing of an argument to a u8 parameter. `state->count` is loaded (0x08121538) before the tests, as an
  evaluated argument is.

**Alternatives compiled, with results.**

- **Inline selection with `*&index = start; *&end = start + count;` and `if (k == 1 || k == 2) ... else if (k == 3)`**
  (reduced test): no match. The `||` became a range test (`subs #1; cmp #1; bls`), the stores go through
  `mov r0, sp`, and the first loop test uses `end` from a register instead of reloading it.
- **Inline `switch (k) { case 1: ...; case 2: ...; case 3: ...; }` with addressed locals** (reduced test): no match.
  It produced a balanced compare tree (`cmp #2; beq; cmp #2; ble; cmp #3`), and `end` stayed in a register.
- **A `do { } while (0)` statement macro taking `&index, &end`** (full function): no match. The record word is
  compared as a word (`ldr`, not `ldrb`), `count` is loaded after the tests, the stores are re-addressed
  (`add r1, sp, #4` after the chain), and the PRE copies are missing.
- **The inline helper with pointer parameters** (reduced test, then the full function): byte-identical. Three
  spellings of its body give the same bytes: `u8 start = 0;` plus arms assigning 0, 0, 1; empty arms for targets 1
  and 2; and the all-paths-assigned form above, which is the parked one because it has no redundant initialiser.
- **Plain block-scope `u8 index, end;` with no address taken:** not compiled. Non-addressable u8 scalars get
  registers, so the per-case frame bytes could not appear.

**The question.** A helper ships when it performs a real domain operation the ROM shows, and is refused when it only
moves registers. Here the helper computes a selection, the start and end of the group objects a record addresses,
which the ROM performs three times with its own frame storage per call site. In every compiled alternative that does
not pass the pair's addresses into a function boundary, the ROM's argument-shaped loads and per-case frame bytes do
not come out. On the other side: no period evidence is recorded for `static inline` helpers, the helper has no
out-of-line counterpart and no merged sibling sharing its text, and the selection rule it encodes (targets 1 and 2
give 0, target 3 gives 1) has no clear meaning (see note 2). Does this helper qualify as a real operation the ROM
shows, or as a device?

### 2. Targets 1 and 2 assign the same start as the else arm

The ROM keeps both tests: `cmp r0, #1; beq` at 0x08121546 and `cmp r0, #2; beq` at 0x0812154A, both jumping to the
join at 0x08121554 with r1 = 0, which was set at 0x08121540 before the chain. Empty arms and initialiser-plus-arms
compile to the same bytes (note 1). A `switch` gives a balanced tree that starts with `cmp #2`, not the ROM's linear
chain. The arms are single statements in an if/else-if chain whose final else differs, so this is not the
`if (c) X; else X;` shape of kit #201.

Semantics: target 3 produces the range [1, count+1), so it reads `objects[count]`, which phase 0 never fills.
Records 71 and 72 (opcodes 10 and 11) use target 3. This may be an original bug, but the function is unreferenced in
the ROM, so it cannot trigger. No `BUG` comment or bug case was written; that decision is the reviewer's.

### 3. `op` is a local, assigned before `first` and `second`

The ROM loads `op` into ip at 0x081213BA, before the +8 and +0xC loads at 0x081213C4 and 0x081213CC.
`switch (data_083A7A34[state->step].op)` moves the load after them (compiled: no match). The statement order is the
ROM's.

### 4. Case 13: `s8 direction = func_080DBC88(state->objects[0]);` then `func_080DBC90(state->objects[1], direction);`

The ROM loads objects[1] after the inner call (0x08121662). The nested spelling
`func_080DBC90(state->objects[1], func_080DBC88(state->objects[0]))` loads objects[1] into r4 before the call
(compiled: no match). The source carries a one-line comment citing 0x08121662.

### 5. Cases 14 and 15 reuse one `Object0812130C *object` across two or three `func_080DD350` results

The ROM has `adds r1, r0, #0; movs r0, #K; strh r0, [r1, #0x34]` at 0x081216A4, 0x081216B0, 0x08121742, 0x0812174E and
0x0812175A. The one-line spelling `func_080DD350(x)->unknown_34 = K;`, used by cases 13 and 16 here and by sibling
`src/0811C50C.c`, gives `movs r1, #K; strh r1, [r0, #0x34]` (compiled in cases 14 and 15: no match). A local assigned
once gives the same as the one-liner. The reused local has several deaths, so global-alloc places it and local-alloc
gives the constant r0. A temporary reused across consecutive objects is ordinary code.

### 6. Case bodies re-read the record instead of using `first` and `second`

The ROM re-reads it at four places: case 0 compares the +0xC word at 0x08121444..0x0812144C rather than reusing r6;
case 1 passes the +0xC word at 0x0812147C..0x08121484; case 3 passes byte +2 at 0x081214C6..0x081214CA; case 11 reads
+8 as a u16 in every iteration through `data_083A7A34+8` (0x0812161E, 0x0812162C..0x08121632). So the source names
the record field at those sites. The locals stay where the ROM uses r5 and r6: cases 0, 2, 3, 4, 5 and 8.

### 7. `func_080DBD70` is declared here with s16 x, y and z

The call sites sign-extend: `ldrsh` at 0x0812168E..0x08121696, and `lsls #16; asrs #16` for `y + 0x40` at 0x08121704
and 0x0812171E. `src/080DBD70.c` defines u16 parameters; the caller's type follows its own extension.

### 8. `extern u16 data_03003860;`

It has a single `strh` of 0 at 0x08121830. Siblings declare it as `u16[]` (08120724, 08112AEC) or `u16[][16]`.

### 9. Case 2: `s16 x, y` are passed by address

They are read with `ldrsh` at 0x081214BA and 0x081214BE for `func_080D8B28(s16, s16)`, matching the four other
sources that declare it that way.

No dependence on declaration order was found; permutations were not tested beyond the items above.

kit issue to be filed: owner guarded-switch selectors and interposed pool words
kit issue: shubshub/fftadecomp-kit#137 (the volatile check's path bound)
