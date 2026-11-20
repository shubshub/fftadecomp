# 0x0800B568 - node list update of module 0x0800: bytes identical, refused (stack aliases live across func_0800AF04, and `volatile` on the SDK CpuFastFill temporary) (1528 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`void func_0800B568(void)` walks the two records of `g_records_02009000`. For each record with a node list it decides
whether the record's buffer must be cleared and, if so, fills it through the BIOS (`func_08141868`, `svc #0xc`,
CpuFastSet) from a word on the stack; then it steps every live node (`update_offset` for nodes whose frame entries
carry an offset, flag 8, `update_plain` otherwise), frees the nodes that finished (`free_node`, an inlined copy of
`func_0800C224`), and queues the buffer's copy to its destination: one transfer (`func_08000ADC`), or 2 or 4 screen
copies of 32 rows (`func_08000C08`) for a map 0x4000 or 0xC000 bytes long. It ends each record with
`func_0800B0AC(i)`.

## The index

The index row `0800B568 0800BB60 1528 716 return` is right: 716 instructions and 13 literal words in seven pools, and
the last pool ends at the indexed end. No index change is needed.

## Byte identity

`0800B568.c` (SHA-256 `0a48b978d25b3e14a381994a31d0d846044a08e78d4204d066958922f44fe8a6`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x0800B568 with every callee and data
symbol bound to its ROM address (26 relocations resolved). The 1528 linked bytes equal the ROM span
`[0x0800B568, 0x0800BB60)`. `match.py` refuses before its own byte comparison, and `plausible.py --strict` refuses
the source (both below).

## Data symbols

Two symbols are needed; neither is in `config/data_symbols.json`. A whole-ROM scan finds each address as aligned
literal words only inside this function:

| Symbol | Literal words | Object |
|---|---|---|
| `data_02009050` | 0x0800BAC8, 0x0800BB58 | `u8`, the index of the next queued transfer (incremented and wrapped at 8 by `next_transfer`); it follows `g_records_02009000` (two 0x28-byte records end at 0x02009050) |
| `data_02009058` | 0x0800BACC, 0x0800BB5C | `Transfer[8]`, 0x1C bytes each; 8 * 0x1C = 0xE0 ends at the existing `data_02009138` |

The literal 0x02009024 at 0x0800BA84 is `g_records_02009000` plus 0x24 folded by the inliner (the existing
`data_02009024` name holds the same address); it needs no new symbol.

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x0800B568` with this source copied to `src/0800B568.c` and
the symbols above added. None matched.

| Selector | Refusal |
|---|---|
| default | `buffer callee 0x0800AF04: local stack pointer escapes through a return register` |
| `--owner-runtime-profile bounded-buffer-bios-fast-fill-source-v1` | `CpuFastSet fill requires only its actual direct wrapper calls` |
| `--owner-runtime-profile bounded-buffer-discarded-return-scratch-v1` | `buffer callee 0x08007170: buffer callee 0x08006FCC: buffer callee 0x08006E28: buffer callee 0x08006C88: named-data buffer dependency budget exceeded` |
| `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `buffer callee 0x0800AF04: mixed CpuFastSet requires its exact bound root call` |
| `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-source-v1` | the same |
| `--owner-runtime-profile bounded-buffer-runtime-summaries-v1` | `buffer callee 0x0800AF04: local stack pointer escapes through a return register` |

`plausible.py --strict src/0800B568.c include` (exit 1):

```
  0800B568.c:273: ERROR: volatile
      volatile: it suppresses reordering, which is the classic way to force a byte match (real I/O code is the only legitimate use - justify it)
```

The source has one `volatile`: `volatile u32 tmp = record->fill;` on line 345 (the finding's line number does not
point at it; line 273 is an ordinary statement).

## Cause

1. **Stack aliases live across `func_0800AF04`.** The two calls to `func_0800AF04` (0x0800B7C8 and 0x0800BA06, in the
   inlined `update_offset` and `update_plain`) are made while addresses of the owner's own locals are held in
   registers. The buffer proof therefore walks `func_0800AF04`, and the walk refuses at its return: the refusal is
   raised in the argument check of that call (`match.py` `check_call` -> `check_arguments` -> `_check_arguments`,
   traceback taken under `bounded-buffer-runtime-summaries-v1`). `func_0800AF04` is matched on main
   (`src/0800AF04.c`) under `bounded-buffer-discarded-return-scratch-v1`, the selector that admits its own stack
   address left in a scratch register at its return; under that selector the owner instead exceeds the named-data
   buffer dependency budget through the allocator chain `func_08007170` -> ... -> `func_08006C88`.
2. **The CpuFastSet fill** (0x0800B5C4-0x0800B5DA) is the SDK's `CpuFastFill(value, dest, size)`:
   `str r0, [sp, #0xc]` stores the record's fill word to the stack, `add r0, sp, #0xc` passes its address, and the
   control word is `size / 4 | 0x01000000` (source fixed). The fill selectors refuse it beside the `func_0800AF04`
   walk (`CpuFastSet fill requires only its actual direct wrapper calls`, `mixed CpuFastSet requires its exact bound
   root call`).
3. **The plausibility gate refuses the SDK macro's temporary.** The source spells out the SDK's `CpuFastFill`
   expansion (lines 339-348): the value goes into a temporary declared `volatile u32 tmp`, and the temporary's address
   is passed to CpuFastSet with the fixed-source bit. The SDK declares the temporary volatile because its only reader
   is the BIOS, through the pointer. In this compile the qualifier also decides the slot: agbcc places the volatile at
   its declaration, sp+0x0C below the inlined helpers' frames (`str r0, [sp, #0xc]`, `add r0, sp, #0xc` in
   0x0800B5C4-0x0800B5DA); with a plain `u32 tmp` the word is still stored before the call, but at sp+0x1C, and the
   function compiles to 1564 bytes instead of 1528.
   `plausible.py` refuses every `volatile` outside its exemptions, so the gate refuses the SDK form today. This is the
   case of kit#164, which asks for the SDK fill temporaries (`CpuFill16`'s `vu16 tmp`, and the `volatile u32`
   CpuFill32 form) to be allowed as evidence-backed volatile locals; `CpuFastFill`'s `vu32 tmp` is the same idiom
   through CpuFastSet. Two more parked sources not yet published (0x080E13A8, 0x080E1A38) use the same fill.

## A possible original bug (not established)

The node update tests `node->flags | 0x200` where `&` may have been meant: the ROM ORs 0x200 into the flags and
compares the result with zero (`movs; lsls #2; adds; orrs; [lsls #16;] cmp #0; beq`, the shift at the last three, at
0x0800B6DA-0x0800B6E4, 0x0800B76C-0x0800B778, 0x0800B934-0x0800B940 and 0x0800B9AE-0x0800B9BA), so the test never fails. 0x200 is a flag
the node constructors set (`node->flags |= 0x200` in `src/0800B2A4.c`, `node->flags = 0x201` in `src/0800B394.c`). Whether the always-true test changes anything in play is
**not established**: it was not run in an emulator, and the nodes that would behave differently were not traced in
the game. There is no reproduction case, and this entry is not a bug case. The source writes the test as the ROM has
it, with a comment; it carries no `BUGFIX` arm.

## Source notes

Each alternative below was compiled with only that change:

1. **`update_offset` and `update_plain` as `static inline` functions with their own locals.** The ROM shows two
   bodies whose eight output halfwords share sp+0x10..0x1F while each keeps its own offset slot (sp+0x20,
   sp+0x24). Neither has an out-of-line copy in the ROM; a reviewer should judge them under the inline-helper policy.
2. **`free_node` is the text of `func_0800C224` (`src/0800C224.c`) plus `node = 0;` after the free.** The ROM gives
   the parameter a register of its own (`adds r4, r6, #0` at 0x0800BA2C, passed on at 0x0800BA5C). Without the
   assignment the function is 1524 bytes.
3. **`next_transfer`** (`data_02009050` wrapped at 8, then `&data_02009058[...]`) appears twice in the ROM
   (0x0800BA9A-0x0800BAB6 and 0x0800BAF8-0x0800BB14, with different registers), as `static inline`.
4. **`s16 entry`** in both helpers (cast to `u16 *` at the call, as `src/0800AF04.c` takes it): `u16 entry` gives
   1524 bytes.
5. **`else if` in the redraw test**: two independent `if`s give 1532 bytes.
6. **Nested `if (node->status == 1) { if (node->flags & 0x80) ... }`**: the `&&` form is 1528 bytes but differs.

kit issues: shubshub/fftadecomp-kit#164 (the SDK fill macro's volatile temporary, refused by the plausibility gate).
The verifier refusals (a stack alias live across a walked callee that leaves a stack address at its return; the
fill selectors beside that walk) have no issue yet; related kit#199 (the same refusal text at a root return).
