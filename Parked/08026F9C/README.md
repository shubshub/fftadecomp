# 0x08026F9C - resource-list menu builder: near miss, 295/304 bytes; byte-identical only with a once-through loop (304 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function walks a menu list from `first` to `last`.
It adds each entry of type 1 or 4 that passes `func_080CD560(unit, i)` and `func_080CCD50(id, 0x15)`, storing
`i` in `context->indices[count]`. For an added entry it reads the entry's resource record (stride 28 in
`data_0855187C`). If `func_080CDB3C(unit)` is set and `func_080CCD50(id, 0x14)` is not, the entry is disabled,
and a non-zero cost raises the list severity to at least 3 (to 4 if the cost is over 99). Otherwise a non-zero
cost raises the severity the same way, and the entry is disabled when the unit's points (+0x1C) are below the
cost. The list width becomes the widest name text (`func_080161BC` over `g_table_085567F0[resource->name]`).
At the end, a non-zero severity sets the menu state to 9, and `count` is stored in the list. It is the
two-check form of the merged ten-check builder `src/08026D44.c`, and its typedefs and prototypes are
character-identical to that file. The index row `08026F9C 080270CC 304 138 return` is right: 138 reachable
instructions (5 `bl`), code to 0x080270C4, literal words at 0x08027044, 0x08027048, 0x080270C4 and 0x080270C8.
The named data (`data_0200F438`, `data_0855187C`, `g_table_085567F0`) is all in `config/data_symbols.json` on
main.

## Byte identity

`08026F9C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08026F9C with every callee and data symbol bound
to its ROM address (5 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The symbol and `.text` are exactly 304 bytes. ROM
span SHA-256 `012289eb5b36ac88c49c06df64d3fe53c3a05caf96ff74f1877470b7335f1442`, linked symbol SHA-256
`63cccfaf61d885b994cb4f4aa93b69b4d13e89b77128bf51ae7b3f23758dc68e`: 9 bytes differ.

`match.py --root . --no-write 0x08026F9C` reports `verdict NOT MATCHING - bytes differ` and `129/138
instructions identical (295/304 bytes)`. `plausible.py --strict` exits 0.

All nine differing instructions come from one register swap. The ROM keeps the list entry in r6 (`adds r6,
r0, r1` at 0x08026FC2) and the resource record in r5 (`adds r5, r0, r1` at 0x08026FFA), and this build swaps
them. The other seven are the loads through them: 0x08026FC4 (type), 0x08026FE4, 0x08026FF0 and 0x0802701A
(id), 0x08027026 and 0x0802704C (cost) and 0x08027084 (name). Each differs in one byte. The calls, branches,
literal pools and every other instruction are identical.

## The byte-identical variant and the rule that holds it

The bytes are identical when the enable decision is wrapped in a once-through loop. The two arms become
`if`s that each end in `break`, with a final `break` (this is the variant's text after
`context->indices[count] = i;`):

```c
            while (1) {
                if (func_080CDB3C(data_0200F438->unit) && !func_080CCD50(entry->id, 0x14)) {
                    if (resource->cost) { /* the severity update, as above */ }
                    context->enabled[count] = 0;
                    break;
                }
                if (resource->cost) {
                    /* the severity update and the points test, as above */
                    break;
                }
                break;
            }
```

Copied to `src/08026F9C.c`, that variant gives `verdict MATCH - byte identical` and `138/138 instructions
identical (304/304 bytes)` from `match.py --root . --no-write 0x08026F9C`. The hand link equals the ROM span
(SHA-256 `012289eb5b36ac88c49c06df64d3fe53c3a05caf96ff74f1877470b7335f1442`), and `plausible.py --strict`
exits 0. Wrapping the published `if` / `else if` unchanged in `while (1) { ...; break; }` or `for (;;) { ...;
break; }` is also byte-identical (MATCH 138/138, `plausible.py --strict` exit 0).

It is not published. AGENTS.md ("Evidence first: what is a fake") lets a once-through loop ship only as the
body of a statement macro that the ROM shows expanded more than once. It lists "a once-through loop written
bare in a function body" under "Does not ship". This ROM shows no loop around the decision. The only backward
branch is the outer loop's (`ble 0x08026FBE` at 0x080270A2). The decision 0x0802700A-0x0802707C is
straight-line, and no exit test is rolled to the end of the block. The block's only effect is on allocation
(below). `plausible.py --strict` does not look at once-through `while (1)` / `for (;;)` blocks, so its clean
run says nothing about this one.

The evidence that does exist for a loop belongs to other functions. Merged `src/08026D44.c` keeps the second
half of its first check (`func_080CCD50(id, 0x1F)`) at the end of its block (0x08026F36, branching back to
0x08026DC8), which agbcc does when it closes a loop statement. Parked 0x08027918 shows the same roll with the
0x14 check (0x08027A98). Those loops hold different statements: 08026D44's opens with a `func_080C95A8(0xD)`
check this function does not have and runs on through ten arms, and its cost goes through `func_080258C4`,
while this function reads the table byte directly (0x08027026). No statement macro can carry this block
verbatim into those bodies. Whether that sibling evidence is enough is the open question in kit issue #191.

## Cause

Global allocation hands out registers in priority order, and each reference counts with its loop depth. In
the natural form the entry pointer comes first and takes r5. Inside the once-through block, the four source
references to `resource->cost` sit one loop level deeper. The resource pointer then outranks the entry pointer,
takes r5, and the ROM's order comes out. This is the effect described for the parked 0x08010DD0, where a
once-through loop changed only loop-depth weighting. In this attempt, moving the entry filter or the locked
check into inline predicates still left the entry pointer ahead.

## Source notes

- The cost is copied to a `u32` local after the non-zero test, as the ROM copies it (`ldrb r0, [r5, #4]; cmp
  r0, #0; beq; adds r1, r0, #0` at 0x08027026-0x0802702C).
- Offsets were checked against the immediates: entries stride 8, `id` +4 (`ldrh`), `type` +6 (`ldrb`); list
  `first`/`last`/`width`/`severity`/`count` +4/+5/+7/+8/+9; resource stride 28, `name` +0 (`ldrh`), `cost`
  +4 (`ldrb`); menu +0x80, `state` +0xD, `indices` +0x94, `enabled` +0x98; unit +0x18, `points` +0x1C
  (`ldrh`).
- The severity update (`severity < 3` -> 3, `cost > 99` -> 4) is the same block twice in the ROM
  (0x0802702E-0x0802703E, 0x08027054-0x08027064). The sibling 0x080270CC, which passes the cost through
  `func_080258C4`, matches with that block written as the statement macro `RAISE_SEVERITY` in
  `do { } while (0)` form (`src/080270CC.c`); here the same macro does not help (Ruled out).

## Ruled out

- The `RAISE_SEVERITY` macro of `src/080270CC.c` for both severity updates, with the `u32` cost local as its
  argument: the same 9 bytes differ (295/304). With `resource->cost` as the argument: 308 bytes.
- The previous parked copy (main) compiles to the same 304 bytes as this source (same linked SHA-256). This
  source only re-types it with the merged `src/08026D44.c` text.
- Measured in this attempt, from the byte-identical variant: `for (;;)` with the inner `break`s gives a
  300-byte symbol (`compiled symbol is shorter than the indexed span: 300 < 304`; `plausible.py --strict`
  exit 0). `do { } while (0)` with the inner `break`s gives 300 bytes, and `plausible.py --strict` exits 1
  with a `dead-code` finding.
- From the earlier attempts (kit fcdf2d45), not re-run: a nested `if` / `else`, a `goto` chain and a `static
  inline` predicate with early returns all give 129/138 with the same swap. Also tried without a loop, with
  the same swap or worse: early `continue` filters, function-scope locals, declaration orders, typed and byte
  views of both records, a cached descriptor-array base, `u32`/`s32`/`u8` cost and counters, and 36 prototype
  combinations. With the loop, its extent is pinned: also holding `context->indices[count] = i` gives
  133/138, and also holding `count++` gives 128/138. For the cost local, a snapshot before the test gives 300
  bytes, no local 115/137 and a `u8 cost` 122/137.
- `do { if ... else if ... } while (0)` around the published arms is byte-identical (hand link equal to the
  ROM span), but `plausible.py --strict` reports a `dead-code` finding, and `match.py` gives `verdict HAND-ASM
  REQUIRED BUT NOT ALLOWED - byte identical, yet 0x08026F9C is not on the hand-asm allow list` (measured in
  this attempt).

kit issue: shubshub/fftadecomp-kit#191 (policy question; the published natural form is not byte-identical)
