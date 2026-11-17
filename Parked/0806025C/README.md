# 0x0806025C - menu list setup: bytes identical, refused (an object-word switch with data, function words, loops and a frame, and no alignment pad) (408 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function draws a menu window
(`func_08016210(renderer, resource, 0x1C0 + rect->tile, rect->rows)`), then switches on `mode - 2` (six cases) to
register a row callback with `func_08017AC4`: `func_08060100` for modes 3 and 7 (mode 7 first runs
`func_080175E0(list, 1, 4)` and falls into case 3), `func_080601B4` for 5, `func_080601A4` for 6, and only
`func_080175E0` for 2. It then sets the list's selection from `data_0200F44C->configs[mode]`, counts the rows with
`func_08017B50`, draws each with `func_080601D0`, marks rows with `func_08017AF4` (in mode 5, the last two records'
rows when their flag is set), and installs `func_08017E80` as the draw callback and `func_08017F04` as the cursor
callback when the list does not fit (`func_08015D58(renderer, draw, secondary)`, with the local `secondary` held in
the 4-byte frame). It is a sibling of the matched `0x0804F948`: the same menu set-up, largely the same callees and the
same callback words.

What it combines:

- a six-entry word switch on `mode - 2` (guard `subs r0, #2; cmp r0, #5; bhi` at 0x080602B2); the dispatch
  `mov pc, r0` at 0x080602C0 is followed by a pad halfword, then one object word (`data_0200F44C` at 0x080602C4,
  loaded at 0x08060282), and only then the table pointer (0x080602C8, table at 0x080602CC);
- named data, `data_0200F44C`, in two literal words;
- five function-address literals: `func_08060100`, `func_080601B4`, `func_080601A4`, `func_08017F04`,
  `func_08017E80`;
- two counted loops (0x0806032C-0x0806033E, 0x0806034E-0x0806037E);
- a 4-byte frame for the local callback pointer, stored at 0x08060280 and 0x080603A6 and reloaded at 0x080603C0 as
  R2 of `func_08015D58`;
- no external pad: the function ends on a pool word at 0x080603F0, 408 is a multiple of four, and `.text` is exactly
  the symbol. `0x0804F948` is 410 bytes and has the pad.

## The index

Two index changes come with this entry, both decomp-side:

- `func_080601A4` is a 14-byte callback that was not indexed: `push {lr}; adds r0, r1, #0; movs r1, #0;
  bl func_08060154; pop {r1}; bx r1` at `[0x080601A4, 0x080601B2)`, 6 instructions, followed by a zero halfword
  before `0x080601B4`. Its only reference is the function word `0x080601A5` at 0x0806030C. It is added as
  `080601A4 080601B2 14 6 thumb` in `symbols/functions.txt` and a `thumb-callback-literal` entry in
  `config/functions.json`, as `080D9C48` is. Without the `config/functions.json` entry the function word is refused
  as unknown (`function address is unknown, ambiguous, misaligned, or not Thumb ROM code`).
- `0806025C` was indexed with 204 instructions in both files, half its byte count. The CFG closed through the
  object-word switch has 160 instructions (the kit's own refinement with its one-object-word switch option agrees);
  both files now say 160. The owner selectors read the count in `symbols/functions.txt`, and the switch inventory
  also requires the one in `config/functions.json`.

## Byte identity

`0806025C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0806025C, with callees, data and function words bound
to their ROM addresses (13 `R_ARM_THM_CALL`, 14 `R_ARM_ABS32`). All 408 bytes, jump table and pools included, equal
the ROM span `[0x0806025C, 0x080603F4)`: SHA-256
`9d342f1e4d3dd6ce3fd0797f46eb223c43bc718019ab3b61eafc04684df6848a` for both. `.text` is exactly 408 bytes. `match.py`
refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This revision renames the types after the siblings (`Config`, `Record`, `List` with the `Struct08017AC4` core from
`include/ffta.h`, `Rect`) and spells out the mode-7 fall-through. The earlier copy in this directory gives the same
bytes and the same SHA-256.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0806025C.c` and the two index changes
above: the default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `--switch-data-profile u16-scalars-v1`, `-v2`, `-frame-v1`, `typed-outgoing-six-words-v1` | `switch evidence excludes object, callback and runtime-thunk bindings` |
| `restoring-owner-switch-cycles-function-words-v1`, `restoring-owner-switch-aligned-v1` and 10 other aligned-tail owners (12) | `aligned owner requires actual external two-byte Thumb alignment` |
| `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1`, `restoring-owner-ignored-leaf-alias-v1`, `local-rom-halfword-table-v1` | `complete-owner text reachable instruction count differs` |
| `named-data-buffer-v1`, `bounded-buffer-guarded-switch-v1`, `bounded-buffer-root-guarded-switch-v1`, `watched-switch-preservation-v1` and 85 other owner selectors (89) | `structural inventory is not closed` |
| `--switch-data-profile u16-scalars-functions-frame-v1`, `-v2` | `outgoing-argument frame access must store an owned aligned word` (the frame word is a local, not an outgoing argument) |
| `--switch-data-profile u16-scalars-functions-v1`, `-v2` | `switch evidence excludes fixed frames and runtime call thunks` |
| `--switch-data-profile switch-thunks-v1`, `switch-thunks-frame-v1` | `switch thunks require canonical _call_via aliases without function words` |
| `--function-address-profile canonical-thunks-interposed-pool-v1` | `function thunks require canonical calls` |
| `ordinary-multiple-switch-source-v1` | `data target must be an undefined mapped object` |
| `numeric-data-switch-source-v1` | `numeric switch requires ordinary calls, zero-addend data and local table words` |

The other 88 selector values stop on requirements this function does not meet (a runtime, float helpers, a BIOS
wrapper, the -O0 toolchain; the 42 addressed-runtime selectors on the data and function words).

## Cause

The matched sibling `0x0804F948` verifies under `restoring-owner-switch-cycles-function-words-v1`, which admits a
loop, a switch and typed function words. That selector refuses this function on the missing alignment pad first.
In a scratch copy of the kit, the changes below were applied one at a time to that selector to find the next
refusal (a probe, not a proposed patch, reported with the kit #74 comment and not re-run for this README; line
numbers at 18dcc516):

1. accepting a `.text` exactly as long as the symbol besides symbol + 2 (`tools/owner_admission_profile.py:1045-1046`)
   gives `complete-owner text reachable instruction count differs`: the owner refinement stops at the unresolved
   dispatch with 143 instructions;
2. refining with the one-object-word switch option (`tools/owner_admission_profile.py:445`, `:451`, `:991`, `:993`)
   closes the CFG at 160; next, `aligned switch owner excludes data and function-pointer literals`;
3. admitting typed data bindings (`:474-475`, `:956-957`) gives `structural inventory is not closed`, from the
   scalar switch inventory;
4. which refines without the option and requires zero interposed words (`tools/framed_switch_inventory.py:73-78`).

With all four and both index changes the probe gives `verdict MATCH - byte identical`, for this source and the
earlier copy. So the function needs the pad made optional for this selector and the composition kit #74 already asks
for (the object-word switch with named data).

## Source notes

- `object->mode` is read twice, for the config index and for the switch; `config` is computed before the switch,
  in the ROM's order.
- Mode 7 runs `func_080175E0(list, 1, 4)` and falls into mode 3's registration: the call at 0x080602EA continues into
  0x080602EE.
- The function words are passed as `(u32)func_08060100` because `include/ffta.h` declares
  `func_08017AC4(Struct08017AC4 *, u32, u32)`.
- The declaration order of `renderer`, `list`, `cursor` and `rect` is load-bearing (frame and register choice), and
  the record index is spelled `data_0200F44C->count - 2 + i`, as the matched `src/0805F824.c` writes it.

## Ruled out

Nothing beyond the source above is recorded; the renaming in this revision does not change the bytes.

kit issue: shubshub/fftadecomp-kit#74 (comment for 0806025C: the pad, the object-word switch and the named data)
