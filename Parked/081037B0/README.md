# 0x081037B0 - phased arrow and segment animation task: bytes identical, refused (a local's address stored into a scheduler descriptor, initialiser copies, forwarded stack arguments) (1634 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`u32 func_081037B0(void *task, Descriptor *d, Payload *p)` is a scene callback in module 0x0810. Phase 0 starts an
opening loader (`func_080E03F8`, mode 5, or 0 when the descriptor's flag is set); phase 0x100 builds the scene;
phase 0x101 places five points along the line from the actor towards a facing-dependent target and offsets them by a
sine/cosine step; phase 0x102 spawns three arrow tasks through the scheduler `func_08005B6C` (`func_081031AC`) with a
stack descriptor; phase 0x103 waits for them, draws two facing-dependent sprites and moves the camera; phases
0x104-0x105 draw two more sprites; phase 0x106 spawns four segment tasks (`func_08103510`), one per pair of points;
phases 0x107-0x108 release the segments one after another; phases 0x109-0x10A spawn the closing record and event.

## The index

The index row `081037B0 08103E12 1634 703 return` is right; the span ends with its last literal pool. No index change
is needed.

## Byte identity

`081037B0.c` (SHA-256 `02334782ac610323e0ae6f2f1835e4fb8486c266e0c13eed4cb168135a7dbbab`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`, `BUGFIX` not defined) and linked at 0x081037B0 with
every callee and data symbol bound to its ROM address (70 relocations resolved). The 1634 linked bytes equal the ROM
span `[0x081037B0, 0x08103E12)`, SHA-256 `91412276eab4847194741d60506e675f1cbc3e986fb5255cb65daf83572dc57a`. The
object's `.rodata` (the seven array initialisers, 52 bytes) equals the ROM bytes at `[0x08149DFC, 0x08149E30)`,
SHA-256 `641243f96b11ed66607101d19441587d843247ff164375a74896f04241bfd9ee`. `match.py` refuses before its own byte
comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Six symbols are needed; none is in `config/data_symbols.json`. Each address is exactly one aligned literal word in
the whole ROM, inside this function. The extents are the distance to the next referenced address and are not
otherwise proven. `data_08502A10` and `data_089492DC`, which the source also uses, are already mapped. The seven
tables at 0x08149DFC-0x08149E30 are array initialisers in the source's `.rodata`, not symbols.

| Symbol | Literal word | Use | Bytes |
|---|---|---|---|
| `data_0839F1E8` | 0x08103918 | records for `func_080E03F8` (the opening loader) | 60, to 0x0839F224 |
| `data_0839F224` | 0x08103DAC | two 24-byte records for `func_080D6098` | 48, to 0x0839F254 |
| `data_0839F254` | 0x08103DB4 | a record for `func_080DCFE4` | 20, to 0x0839F268 |
| `data_0839F268` | 0x08103970 | a table for `func_080DDF68` | 12, to 0x0839F274 |
| `data_0839F274` | 0x08103DB8 | an event record for `func_080DFD8C`, count 1 | 8, to 0x0839F27C |
| `data_0839F27C` | 0x08103BA0 | event records for `func_080DFD8C`, count 2 | 16, to the existing `data_0839F28C` |

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x081037B0` with this source copied to `src/081037B0.c` and
the symbols above added. None matched.

| Selector | Refusal | Raised at |
|---|---|---|
| default | `unexpected nonempty allocated section` | the initialisers' `.rodata` |
| `--owner-runtime-profile named-data-buffer-stack-index-v2` (closest) | `stack aliases cannot be stored or spilled` | `tools/match.py:3079` (`stack_alias_store`) from `verify_leaf_instructions` (`tools/match.py:5278`), at the store `str r0, [r1, #4]` at 0x08103A2C |
| `--owner-runtime-profile named-data-buffer-stack-index-v1` | `buffer callee 0x080DBDA0: unsupported buffer pointer use or escape` | the walk of `func_080DBDA0` |
| `--owner-runtime-profile named-data-buffer-rom-table-copy-v1` | the same as stack-index-v1 | the same |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v2` | `unexpected nonempty allocated section` | the initialisers' `.rodata` |
| `--owner-runtime-profile conditional-scheduler-call-site-summaries-v1` | the same | the same |

## Cause

1. **A local's address stored through a descriptor alias.** In phase 0x102, `add r1, sp, #0x2c; add r0, sp, #0x84;
   str r0, [r1, #4]` (0x08103A28-0x08103A2C) stores the address of the local `position` into the stack descriptor's
   +4 word before the scheduler calls in the loop (`bl func_08005B6C` at 0x08103A5C). This is the store the
   stack-index-v2 walk refuses (the refusing instruction was identified by instrumenting `stack_alias_store`). The
   kit tracks such a payload pointer store only under the payload-descriptor profiles (kit#85, closed), and no
   selector combines that with what else this function needs (kit#200):
   - seven compiler `memcpy` copies of `.rodata` initialisers (`bl func_081443FC` at 0x08103802, 0x0810380E,
     0x081039F8, 0x08103A8E, 0x08103A9A, 0x08103AA8 and 0x08103AB8);
   - three calls to `func_080DBDA0` that forward `&x, &y, &z` as stack arguments (0x08103836, 0x08103A0A,
     0x08103AEA), which only stack-index-v2 admits (kit#238);
   - variable stack-array indices (below);
   - two scheduler sites inside loops (0x08103A5C and 0x08103C72).
2. **Six stack-index sites take the actor's facing as the index**: `(u8)func_080DBC88(p->object)`, scale 2, at
   0x08103854/0x08103860 (`x_offsets`/`y_offsets`, phase 0x101), 0x08103B04/0x08103B12 (`sprite_x`/`sprite_y`) and
   0x08103B62/0x08103B70 (`target_x`/`target_y`, phase 0x103). The arrays have four entries; the premise that the
   facing value is 0..3 is not established, so even a selector that admits the shape would need that premise.
   `delays[i]` at 0x08103A4E is bounded by its loop (`cmp r4, #2; bls` at 0x08103A6C).

## A possible original bug (not established)

Phase 0x108 (0x08103CCA-0x08103CEA) tests `p->segment_status[p->index] <= 1` and
`p->segment_status[p->index - 1] == 3` with no bound on `p->index`, then stores 2 and increments the index. The
status array has four entries and is followed by `p->ready` (+0x10; the array is at +0x0C, `adds r2, #0xc` at
0x08103CCE), so an index of 4 would read and could write `p->ready`. The index does reach 4 inside this phase: the phase
advances only once the index exceeds 3 (0x08103CF6-0x08103CFC) and `func_080D5F24(p->sprites, 2)` returns nonzero
(0x08103D04-0x08103D0C). Whether the phase then runs again with the index at 4, i.e. whether
`func_080D5F24(p->sprites, 2)` still returns 0 on that frame, and whether a write of 2 to `p->ready` has any effect,
is **not established**: it was not run in an emulator, and the animation data that decides when the sprites finish
was not decoded. There is no reproduction case, and this entry is not a bug case.

The source marks the spot with a conditional `BUG` comment ("possible, not reproduced") and an `#ifdef BUGFIX` arm that adds `p->index < 4 &&`. The
byte-identical build is the default one (`BUGFIX` undefined); with `BUGFIX` defined the function is 1642 bytes.

## Source notes

1. **`flags = 4` held in a local before the `func_080DCFE4` call** (phase 0x109). The ROM loads 4 first
   (`movs r2, #4` at 0x08103D7A, before `ldr r0, [r6, #0x64]` at 0x08103D7C). A literal argument instead differs
   (three differing lines).
2. **`dx = (s16)func_08007A4C(angle); dx *= 40; dx >>= 8;`** (and the same for `dy`). The ROM keeps the three steps
   (`asrs r5, r0, #16; lsls r0, r5, #2; adds r0, r0, r5; lsls r5, r0, #3; asrs r5, r5, #8` at
   0x0810399C-0x081039A4). The one-expression form `(s16)func_08007A4C(angle) * 40 >> 8` gives 1630 bytes. Three
   assignments are unusual; a reviewer should judge them.
3. **The `(s16)` cast on `func_08007A4C` only**: its definition (`src/08007A4C.c`) returns `s32`; `func_08007A60`
   (`src/08007A60.c`) returns `s16`.
4. **Block-scoped initialised arrays and descriptors per phase.** The frame shows agbcc reusing the array slots
   (sp+0x14 and sp+0x1C across phases 0x101-0x103), the two address-taken descriptors at sp+0x2C and sp+0x68, and
   `position` at sp+0x84.
5. **`Point points[5]`**, with the target as `points[4]`: phase 0x106 passes `&points[index + 1]` for index 0..3.
6. Payload and descriptor layouts are offset views with `unknown_*` members; the member names are guesses from use.

kit issues: shubshub/fftadecomp-kit#200 (a stack-index owner that also calls the scheduler; the default path's
`unexpected nonempty allocated section`), #238 (forwarded stack arguments through `func_080DBDA0`), and #85 (closed:
the payload pointer store, tracked only under the payload-descriptor profiles). No issue covers the facing premise.
