# 0x0804CBB4 - menu state machine of the 0x0201F544 module: bytes identical, refused (same-function long BL jumps in a switch function) (2552 bytes)

Attempt 2026-11-20, kit b141ba59, decomp main 82b7baab5e.
`u8 func_0804CBB4(void)` is the per-frame state machine of the 0x0201F544 menu module. It reads the state number at
`data_0201F544->current` (+0x08) and dispatches through a 27-entry jump table at 0x0804CBDC (states 0..26). The module
keeps a small stack of state numbers, `count` (+0x0A) and `commands[8]` (+0x0C). Most cases either save the current
state and switch to a new one, or resume the last saved state. Every `break` leads to `func_0804E1B8(0); return 0;`;
state 26 calls `func_0804E990()` and returns 1. The caller, `func_0804CAE4`, tests the result as a u8 (`lsls #24`).

The function uses the named data symbols `data_0201F544`, `g_state_020020D0`, `data_03002710`, `data_030008B0` and
`data_03000990`, all already mapped, and three function literals, all indexed entries: `func_0804E9F0`,
`func_0804CABC` and `func_0804CAD0`. The frame holds only the six outgoing stack arguments of `func_0801174C`.

## The index

The index row is `0804CBB4 0804D5AC 2552 1276 return`. The extent is right: the start is word aligned, and the
prologue `push {r4, r5, r6, lr}; sub sp, #0x18` pairs with the epilogue `add sp, #0x18; pop {r4, r5, r6}; pop {r1};
bx r1` at 0x0804D5A4. The instruction column is the halfword count (bytes/2): the kit's `analyze.refine_function`
closes the CFG with 1005 reachable instructions, and only with both its same-owner long-branch and
one-object-word-switch opt-ins. Not corrected here: no draft needs it.

## Byte identity

`0804CBB4.c` (SHA-256 `7e26401ce71d064d642b15e26ff5bab4cd78dcefe6e431196c32596e0db0a0c2`) was compiled with the
fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`)
and linked by hand at 0x0804CBB4, with every callee, function literal and data symbol bound to its ROM address
(103 `R_ARM_THM_CALL`, 70 `R_ARM_ABS32`). The 2552-byte symbol equals the ROM span `[0x0804CBB4, 0x0804D5AC)`:
SHA-256 `ecd5f81d1e422765ffb0f39ef9ba83db4d47c45f32a9da6bff80f724e797b2f1` for both. `.text` is exactly 2552 bytes.
The object has 116 `bl` instructions: 103 relocated calls to named functions, and the 13 same-function long BL
jumps below (agbcc's `@far jump`), which the assembler resolves without a relocation. `match.py` refuses
before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

None needed.

## Refusals

Kit b141ba59, `match.py --root . --no-write` with this source copied to `src/0804CBB4.c`. None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `switch evidence excludes object, callback and runtime-thunk bindings` | `match.py:1148` |
| `--switch-data-profile u16-scalars-functions-frame-v2` | `call is not a validated external direct Thumb BL` | `match.py:4828`, `verify_leaf_instructions`, at `0x0804CBC4 bl #0x804d59c` |
| `--switch-data-profile u16-scalars-functions-frame-v1` | `call is not a validated external direct Thumb BL` | `match.py:4828`, at the same instruction |
| `--owner-runtime-profile restoring-owner-runtime-v1` | `owner profile requires actual compiler UDIV and indirect thunk calls` | `owner_admission_profile.py:1362` |
| `--owner-runtime-profile restoring-owner-switch-cycles-function-words-v1` | `aligned owner requires actual external two-byte Thumb alignment` | `owner_admission_profile.py:1197` |
| `--owner-runtime-profile numeric-data-switch-source-v1` | `numeric switch requires ordinary calls, zero-addend data and local table words` | `owner_admission_profile.py:1314` |

The selector that fits is `u16-scalars-functions-frame-v2`: the pool is dispatch-identified, with the
`data_0201F544` word interposed before the table pointer at 0x0804CBD4/0x0804CBD8; every other literal is a typed
object or a function word; and the frame holds six write-only outgoing words. It refuses only because of the long
BLs; the refusing instruction, read from the refusing frame, is 0x0804CBC4, the guard's default jump.

## Cause: 13 same-function long BL jumps

agbcc emits a `bl` for an unconditional jump that a narrow `b` cannot reach (about +/-2 KB), marked `@far jump` in its
assembly. That `bl` overwrites LR, which the prologue has already saved.

| Site | Target | What the target is |
|---|---|---|
| 0x0804CBC4 | 0x0804D59C | switch guard default, to the shared exit `func_0804E1B8(0); return 0` |
| 0x0804CC4E | 0x0804D5A4 | `return 1` of state 26, to the epilogue |
| 0x0804CC7C | 0x0804D59A | cross-jumped `strh r0, [r2, #8]` (set the state), then the exit |
| 0x0804CCA4 | 0x0804D59C | shared exit |
| 0x0804CCCA | 0x0804D59C | shared exit |
| 0x0804CCE8 | 0x0804D59C | shared exit |
| 0x0804CCF4 | 0x0804D586 | shared `POP_STATE` tail, then the exit |
| 0x0804CD06 | 0x0804D59C | shared exit |
| 0x0804CD1A | 0x0804D59C | shared exit |
| 0x0804CD2E | 0x0804D59C | shared exit |
| 0x0804CD6C | 0x0804D59A | cross-jumped state store |
| 0x0804CDBA | 0x0804D59A | cross-jumped state store |
| 0x0804CDD2 | 0x0804D59C | shared exit |

The other `bl`s inside the span are ordinary external calls, including `func_0804D5AC` (at the function's end
address) and `func_0804D5F4`.

**Which selectors already admit them.** In `verify_leaf_instructions` (`match.py:4809-4815`) a call-group
instruction becomes a local branch only when `double_context is not None` or
`addressed_signed_runtime.local_branches(context)` is true. `local_branches` (`addressed_signed_runtime_profile.py:280`)
is true only for the thunk selectors `addressed-signed-runtime-thunks-v1`, `addressed-signed-runtime-thunks-data-v1`
and `compiler-signed-runtime-thunks-data-v1`. Those re-prove the edges with `local_long_branch_profile.prove_frame`
and record them as `local_long_branches` (kit README: "These two selectors also admit agbcc's same-owner long `bl`
jumps"). The switch recogniser already understands the guard form (`match.py:2505-2516`: "agbcc uses a local BL when
the shared default block is beyond a narrow branch"), but, as its comment says, shape recognition grants no call
permission, and none of the switch-data selectors grants it later. `restoring-owner-runtime-v1` names "local BL
control, guarded switches" in its control-flow string, but it requires compiler UDIV and indirect thunk calls
(`owner_admission_profile.py:1362`), so it does not apply.

**A possible fix.** Let the u16-scalars switch selectors, at least the `-frame` and `-functions-frame` variants,
treat same-owner long BL edges as the thunk selectors do: recognise them with `local_long_branch_profile.target`,
walk them as plain edges with no ABI call summary and LR overwritten, re-prove the restoring frame with the same
`prove_frame` proof, and record them as `local_long_branches` in the manifest. The frame proof stays as
`u16-scalars-frame-v1` describes it; the recogniser should accept only an unconditional `bl` to a non-entry boundary
inside the owner, and every return must still restore LR from the saved frame.

**A minimal reproducer.** This compiles with agbcc `-mthumb-interwork -O2` to a guarded jump table whose default jump
and several case exits are emitted as `bl .L3 @far jump` and `bl .L11 @far jump`. It is not a ROM function, so it was
not run through the selectors; a kit test would use it as a synthetic owner.

```c
extern void f(int);
extern unsigned short *g;
#define F4 f(1); f(2); f(3); f(4);
#define F16 F4 F4 F4 F4
#define F64 F16 F16 F16 F16
#define F256 F64 F64 F64 F64
int t(void)
{
    switch (*g) {
    case 0: f(0); break;
    case 1: f(1); break;
    case 2: f(2); return 1;
    case 3: f(3); break;
    case 4: F256 F256 break;
    }
    f(7);
    return 0;
}
```

No Parked entry on main had this refusal; 0x08054E14, published alongside, has the same gap.

## Source notes

Case order in the source follows the ROM layout: 26, 0, 1, 3, 4, 2, 5..25 (agbcc has no block reordering pass).

1. **`PUSH_STATE()` / `POP_STATE()` macros.** `PUSH_STATE()` is `commands[count++] = current`; `POP_STATE()` is
   `current = commands[--count]`. The ROM repeats these blocks about 40 times; a typical push is
   0x0804CD40..0x0804CD56, and the POP tail is 0x0804D586..0x0804D59A. The sibling `src/0804D6B0.c` spells each push
   with its constant (`current = 26; commands[count++] = 26;`); that spelling, compiled at all 30 set-and-push sites,
   is also byte-identical, so this is a style choice. The macros were chosen because one push-current macro covers
   every shape in the ROM: set then push (the failure paths); push then set (case 11 at 0x0804CFFE..0x0804D048, case
   16 at 0x0804D2DE..0x0804D2F6); pop then push (cases 12, 13, 17); and the stack reset (cases 15, 19). Period code
   used statement macros for repeated blocks.
2. **The stack reset in cases 15 and 19** (0x0804D1E8..0x0804D1FA, and the same bytes at 0x0804D402..0x0804D414).
   Source: `count = 0; current = 2; PUSH; current = 3; PUSH; current = 24; PUSH; current = 25;`. The ROM keeps only
   five stores, in this order: `commands[0] = 2`, `commands[1] = 3`, `count = 3`, `commands[2] = 24`,
   `current = 25`. `movs r2, #24` sits before the count store, the position of the deleted `current = 24`
   statement: flow's dead-store elimination removes the intermediate stores, because every address in this path is a
   constant offset from one base. Alternatives compiled: explicit stores in natural order (`commands[0..2]`, then
   `count = 3`, then `current = 25`) leave 10 halfwords different, first at 0x0804D1EE; explicit stores in ROM store
   order leave 6, first at 0x0804D1F2, because `movs #24` moves into r0 right before its own store. The push sequence
   is the only form tried that matches; there is a comment at the site.
3. **`POP_STATE(); PUSH_STATE(); current = 25;`** in cases 12, 13 and 17 (0x0804D0A6..0x0804D0C4; case 17 branches
   into it at 0x0804D346; case 13 is at 0x0804D126..0x0804D148). Every store is in the ROM: the count is decremented
   and stored, the popped state is stored, the old count is stored back, the state is pushed again, then 25 is
   stored. This is ROM-shown code, not a construct added to steer the compiler; there is a comment at the site.
4. **Case 11's two arms of `if (selection->count != 0)`**: `{ PUSH_STATE(); current = 13; } else { PUSH_STATE();
   current = 12; }`. The ROM has both push copies (0x0804CFFE..0x0804D014 and 0x0804D030..0x0804D046); only the
   final `strh r0, [r2, #8]` at 0x0804D048 is cross-jumped. The arms differ (13 against 12), so this is not inert
   control flow; folding the arms into a conditional state value would leave one push copy.
5. **`func_0804E3BC(second, 1)` after the if/else** in cases 12, 17 and 19. The ROM reloads the global pointer at that
   join (0x0804D44A, `ldr r0, =data_0201F544`). Case 13 is straight-line: it keeps the pointer in r2 (0x0804D14A) and
   enters the call at 0x0804D450.
6. **Case 11 tests `selection->count` twice.** The ROM re-reads `ldrh [r4, #2]` at 0x0804CF98 and again at
   0x0804CFF8. `u8 index` holds the 0/4 value in r6 across the calls; it is the third argument of `func_0801174C`.
7. **`extern s32 func_0804E1B8(u8 unused)`.** The matched definition takes no argument, but the only caller in the
   ROM, at 0x0804D59C, passes 0 (`movs r0, #0` before the call). Commented at the declaration.
8. **`func_0804E9D0` is declared `u32`.** Case 11 casts the result to the selection record (`ldrb [r4]`,
   `ldrh [r4, #2]`); case 16 ORs the same value into `field_04` as an integer (0x0804D28C..0x0804D298).
9. **`s16 result` is reused across cases 5, 7, 11, 16 and 20.** Each case sign-extends with `asrs r1, r0, #16`, then
   compares with 0 and with -1.
10. **The `u8` return type**: `func_0804CAE4` tests the result with `lsls #24`.
11. **Field names.** +0x00 is `delay` (set to 4 or 16 and counted down in cases 4 and 25); `func_0804CAE4` calls this
    field `mode` and +0x08 `timer`, so new names avoid the clash. +0x01 `enabled` and +0x02 `mode` follow
    `func_0804D6B0`, as do `current`, `count` and `commands`. +0x1C / +0x20 / +0x24 `first` / `second` / `third`
    follow `func_0804D5AC` and `func_0804D658`. +0x28 `window` follows the `func_0801174C` callers. The
    `g_state_020020D0` view uses `unknown_00`, `field_04`, `field_0c` and `unknown_12`; `field_04` and `field_0c`
    follow the Record type in `ffta.h`.
12. **The declaration order** of the locals (`result`, `selection`, `index`) was never varied, so whether the match
    depends on it is untested.
13. **No original-game bug is reproduced**, so no bug case is needed.

kit issue to be filed: same-function long BL in switch selectors
