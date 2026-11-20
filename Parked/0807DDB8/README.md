# 0x0807DDB8 - menu mode dispatcher with a four-byte initialiser: bytes identical, refused (a `.rodata` initialiser beside one interposed switch-pool word) (1292 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`void func_0807DDB8(void *unused, u8 *state)` is a task callback of the 0x0807 menu module. It keeps a local
`u8 modes[4] = {1, 2, 3, 5}`, indexed by the `choice` byte at +0xC1F, and dispatches on `*state`
through a guarded 19-entry jump table: case 0 resets the choice and draws five text rows, case 4 redraws them, case 7
handles the confirm and cancel input (`func_08084DA0`, and `func_08141540` with 0x9B, 0x68 or 0x64), cases 8 to 11 and 16 step the
mode, the record and the two callbacks `func_0807C7E8`/`func_0807D240`, and case 17 hands over to state 18.

## The index

The index row `0807DDB8 0807E2C4 1292 646 return` has the right extent: `push {r4-r7, lr}; sub sp, #0xc` pairs with
the epilogue, and the last literal pool ends at the indexed end. Its instruction column (646) is the span in
halfwords, 1292 / 2, which `refine.py` writes when it corrects a span (this row was corrected from 14 bytes in
72002af5520); it counts the table and the literal pools. `analyze.refine_function` closes the graph with 434
reachable instructions, and only with the one-object-word switch layout (below). The buffer selectors do not check
this column, so the row is harmless as it is, and no index row is changed here.

## Byte identity

`0807DDB8.c` (SHA-256 `d51494cd94e51cb86a89396dbe448ee0c479f75cea14e5b267849fe5b06fe984`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x0807DDB8 with every callee and data
symbol bound to its ROM address (85 relocations resolved). The 1292 linked `.text` bytes equal the ROM span
`[0x0807DDB8, 0x0807E2C4)`, SHA-256 `39c58ce76006ca30892f21c210989410eb202c9beb42c62e0ba6247296582da6`. The object also
has one allocated `.rodata` section, the initialiser of `modes`, and its four bytes `01 02 03 05` equal the ROM at
0x081499C0, the address the literal at 0x0807DDDC loads for the copy. `match.py` refuses before its own byte
comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Three symbols are needed; none is in `config/data_symbols.json`. Each address was found as an aligned literal word
by scanning the whole ROM, and every such word is inside this function:

| Symbol | Object | Literal words |
|---|---|---|
| `data_0200F237` | `u8` | 0x0807DF10, 0x0807DFA4, 0x0807E070, 0x0807E0A8, 0x0807E154, 0x0807E1BC, 0x0807E288, 0x0807E2AC |
| `data_0200F238` | `u8` | 0x0807DF0C, 0x0807DFA0, 0x0807E06C, 0x0807E0A4, 0x0807E2A8 |
| `data_0200F239` | `u8` | 0x0807DEF8, 0x0807E284 |

The initialiser's address 0x081499C0 appears as an aligned word only at 0x0807DDDC.

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x0807DDB8` with this source copied to `src/0807DDB8.c` and
the symbols above added. None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `unexpected nonempty allocated section` | (no traceback taken) |
| `--owner-runtime-profile named-data-buffer-stack-index-v1` | `structural inventory is not closed` | `owner_graph_profile.py:26`, from `owner_admission_profile.verify` (`:512`) |
| `--owner-runtime-profile named-data-buffer-stack-index-v2` | the same | the same |
| `--owner-runtime-profile named-data-buffer-rom-table-copy-v1` | the same | the same |
| `--owner-runtime-profile bios-word-switch-local-buffers-v1` | `unexpected nonempty allocated section` | `match.allocated_text_only` (`match.py:637`), from `owner_admission_profile.original_bindings` (`:1276`) |
| `--switch-data-profile u16-scalars-functions-frame-v2` | `unexpected nonempty allocated section` | (no traceback taken) |

## Cause

1. **One interposed word before the jump table.** The dispatch is `lsls r0, r0, #2; ldr r1, [pc, #0xc];
   adds r0, r0, r1; ldr r0, [r0]; mov pc, r0` (0x0807DDD0-0x0807DDD8), after the guard `cmp r0, #0x12; bls`
   (0x0807DDCA). The pool word at 0x0807DDDC is the initialiser's address 0x081499C0, read by the copy set-up at
   0x0807DDBE (`ldr r1, [pc, #0x1c]`, then `bl 0x081443FC` at 0x0807DDC4); the table pointer follows at 0x0807DDE0
   and the 19-word table at 0x0807DDE4. `analyze.refine_function` on the ROM bytes returns `cfg_closed: False`,
   `unresolved jump at 0x0807DDD8`, with 20 instructions, by default, and `cfg_closed: True` with 434 instructions,
   one switch and one interposed word, with `one_object_word_switch=True`.
2. **No selector composes that layout with a `.rodata` initialiser.** `owner_admission_profile.verify` passes
   `one_object_word_switch` to `owner_graph_profile.graph` only for `bios-word-switch-local-buffers-v1`
   (`owner_admission_profile.py:512-513`), and that selector rejects the allocated `.rodata` section. The selectors
   that bind a compiler initialiser to ROM bytes (`named-data-buffer-rom-table-copy-v1` and the two stack-index
   selectors, `rom_table_copy_profile.SELECTORS`) refine the owner without the opt-in, so their graph does not close.
3. Beyond that point the walk was never reached: the two function literals, the 0xC-byte frame and the variable
   index `modes[choice]` (`add r0, sp, r0` at 0x0807DE60). A stack-index selector would also need a reviewed
   `config/stack_index_premises.json` entry bounding the `choice` byte to the table's four entries.

## Source notes

1. **The empty `case 18`.** The guard's bound is 18 (`cmp r0, #0x12` at 0x0807DDCA) and the table has 19 words,
   the last one the common exit 0x0807E2BC. Without the label the function is 1288 bytes.
2. **`func_08084DA0` declared to return `int`.** Its merged definition (`src/08084DA0.c`) returns `u8`, but this
   caller compares the result at 0x0807DF70 (`cmp r0, #0xff`) with no narrowing after the call at 0x0807DF6C. With
   the `u8` prototype the function is 1296 bytes. A reviewer should decide whether a stale `int` prototype is the
   likely original.
3. **`func_0807D96C` declared to return `int`** (unmatched). The address of `data_0200F239` is loaded at 0x0807DE58,
   ahead of the arguments and the call at 0x0807DE74, and the result is narrowed by the assignment. With a `u8`
   prototype the output differs (same size, 23 differing lines).
4. **`data_03002818->mode = 1;` inside the test of `mode == 1`** stores the value just tested: `cmp r1, #1; bne;
   strb r1, [r0]` at 0x0807E1D8-0x0807E1DC.
5. **`s8 x`** in the entry record: the ROM reads it with `ldrsb` at 0x0807E168 and 0x0807E192; `src/0807DC24.c`
   only stores to it.
6. **`extern void *memcpy(...)`** is declared, with a comment, for the compiler's initialiser copy at 0x0807DDC4.
   It is not load-bearing: without the line the bytes are identical and `plausible.py --strict` still exits 0. A
   reviewer may drop it.
7. The mode byte at +0x1131 is named `mode` here; `src/0807E2C4.c` calls the same byte `enabled`.

No original bug is reproduced.

kit issue: shubshub/fftadecomp-kit#414 (a buffer owner's own jump table with interposed pool words: only
`bios-word-switch-local-buffers-v1` opts into a one-object-word pool, and here that selector cannot take the
`.rodata` initialiser the other buffer selectors bind).
