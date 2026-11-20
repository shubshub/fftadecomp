# 0x080FA76C - two-kind effect callback with affine sprites: bytes identical, refused (non-leaf scratch call after func_080032F8, and the scheduler thunk chain) (1420 bytes)

Attempt 2026-11-20, kit 3afe589f4, decomp main 81362adaf07.
`u32 func_080FA76C(void *owner, Descriptor080FA76C *desc, State080FA76C *state)` is a scene callback in the family of
`080F1948`. Phase 0 picks one of two kinds (kind 1 when the descriptor's kind is 0xB8) and starts a loader; phases
0x100-0x103 wait for it, build the scene, place a particle and two effect tasks, turn on display layer 2 in
`g_control_flags_03000940.display` and write the first affine transform; phases 0x104-0x109 step a fade
(`func_080E064C`/`func_080E0690`) and rewrite the transform each frame; phases 0x10A-0x10B spawn the closing effect,
wait for every task to finish, turn the layer off and set the state to 2.

## The index

The index row `080FA76C 080FACF8 1420 597 return` is right: `push {r4-r7, lr}` plus r8 and `sub sp, #0x38` pair with
the matching epilogue, and the last literal word, 0x080FACF4, ends at the indexed end. No index change is needed.

## Byte identity

`080FA76C.c` (SHA-256 `e056350925a6ee919736d5c8ec1060d5c6bdc2aa2306ed278b9d0fa5e75b050f`) was compiled as
`match.py` compiles it (fixed flags, `-mthumb-interwork -O2`) and linked at 0x080FA76C with every callee and data
symbol bound to its ROM address (74 relocations resolved). The 1420 linked bytes equal the ROM span
`[0x080FA76C, 0x080FACF8)`, SHA-256 `5c7d815500b9508e28ef4ceeebecfb82e0fd6023f6e7e6c6501361776130f113`.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Fifteen symbols are needed; none is in `config/data_symbols.json`. Each address was found as an aligned literal word
by scanning the whole ROM, and every such word is inside this function:

| Symbol | Literal words | Object (as the function uses it) |
|---|---|---|
| `data_0839C964` | 0x080FA83C | two pointers, by kind (0x0839C8EC, 0x0839C928): the loader script |
| `data_0839C96C` | 0x080FA838 | `u8[2]` = 05 05: the loader count, by kind |
| `data_0839C970` | 0x080FAC80 | 0x30 bytes up to 0x0839C9A0: the closing particle's descriptor |
| `data_0839C9D0` | 0x080FA92C | two pointers, by kind (0x0839C9A0, 0x0839C9B8): particle descriptors |
| `data_0839C9D8` | 0x080FA930 | two pointers, by kind (0x0894A6D8, 0x0894A75C): effect task scripts |
| `data_0839C9E0` | 0x080FA9F4 | two pointers, by kind (0x088F0600, 0x088F0624): background sources |
| `data_0839C9E8` | 0x080FA9F8 | `u16[2]` = 0x00ED 0x00ED, by kind |
| `data_0839C9EC` | 0x080FAA8C, 0x080FAB00 | `s16[16]` (0x0100 ... 0x3000, 0): a scale table |
| `data_0839CA0C` | 0x080FAC84 | two 20-byte records, by kind (`kind * 20`), ending at 0x0839CA34 |
| `data_0839CA34` | 0x080FA898 | 4 bytes, `01 03 00 44`: the scene descriptor |
| `data_0839CA38` | 0x080FA934 | 8 bytes, `00 00 02 00 7f 01 00 00`: an event script |
| `data_0839CA40` | 0x080FAC88 | 8 bytes, `00 00 01 00 8b 00 00 00`: an event script |
| `data_0839CA48` | 0x080FAA00, 0x080FAA90, 0x080FAB04, 0x080FABA8, 0x080FAC18 | `u8[2]` = 08 10: texture x, by kind |
| `data_0839CA4A` | 0x080FAA04, 0x080FAA94, 0x080FAB08, 0x080FABAC, 0x080FAC1C | `u8[2]` = 18 18: texture y, by kind (0x0839CA4C is a pointer, the next object) |
| `data_0894D9E4` | 0x080FAA08 | the descriptor passed to `func_080D3E9C` |

The five literal pairs for `data_0839CA48`/`data_0839CA4A` belong to the five copies of the affine block (below).

## Refusals

Kit 3afe589f4 (every refusal line below was rerun there), `match.py --root . --no-write [selector] 0x080FA76C` with this source copied to `src/080FA76C.c` and
the symbols above added. None matched.

| Selector | Refusal |
|---|---|
| default | `buffer callee 0x080D3E9C: buffer callee 0x08005B6C: buffer callee 0x08005954: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `--owner-runtime-profile bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1` | `buffer callee 0x080032F8: stack aliases cannot cross calls in caller-clobbered registers` |
| `--owner-runtime-profile bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` | `buffer callee 0x080032F8: consumer observes discarded return scratch before a killing write` |
| `--owner-runtime-profile bounded-buffer-bios-bg-affine-set-v1` | `buffer callee 0x080D3E9C: BgAffineSet profile requires its exact bound root call` |

## Cause

1. **The default path's** buffer proof follows the call to `func_080D3E9C` into the
   scheduler `func_08005B6C`, `func_08005954` and the callback thunk `func_08142250`, whose indirect call the walk
   cannot follow without linked CFG verification. This is the scheduler-thunk refusal of kit#200 and kit#238.
2. **The BgAffineSet selectors** are the family the sibling `080F1948` verifies under
   (`bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1`). In phase 0x103, `func_080032F8(&dst, 2)`
   returns at 0x080FA9E2 and the next three instructions are `ldr r0, =0x0894D9E4; adds r1, r7, #0;
   bl func_080D3E9C` (0x080FA9E6). `func_080032F8` leaves the caller's `&dst` in R3 (`adds r3, r0, #0` at
   0x080032FA), and R3 reaches that call with no killing write. The transparent-leaf rule then checks the call
   (`check_scratch_call` -> `incoming_scratch_overwrite_profile.authenticate_ordinary`) by verifying
   `func_080D3E9C` alone as a leaf, and that refuses at `match.py:5096`: `func_080D3E9C` passes its own descriptor
   address in R2 across its scheduler call (`mov r2, sp; bl func_08005B6C` at 0x080D3EB0). The refusal surfaces
   through the buffer proof's argument check of the call to `func_080032F8`, hence the `buffer callee 0x080032F8:`
   prefix. In `080F1948` the call after `func_080032F8` is the leaf `func_080E0690`.

## Source notes

1. **`static inline set_affine_080FA76C(kind, x, y, scale_y)`.** The ROM carries the block five times, at
   0x080FA9A8, 0x080FAA22, 0x080FAA98, 0x080FAB3C and 0x080FABBA, with the same instructions and different registers.
   The copy at 0x080FAA22 reads kind, x, y and the vertical scale once, in that order, ahead of the first store to the
   source block (0x080FAA22-0x080FAA36), and the copies share one source block at sp+0x14 and one result at sp+0x28. The horizontal scale 0x100 and the zero
   angle are constants in every copy: the ROM materialises 0x100 at its store (`adds r1, r0, #0; movs r0, #0x80;
   lsls r0, r0, #1; strh r0, [r1, #0xc]` from 0x080FAA54), which a constant in the body gives and an argument does not.
   `func_080D6E30` (`src/080D6E30.c`) is the out-of-line relative that takes them as arguments. A plain statement macro
   with the same body gives 1416 bytes, so the inline helper is what the ROM shows. A reviewer should judge the helper under the inline-helper policy: it leaves
   five ROM copies and no out-of-line copy.
2. **The layer-on block in phase 0x103** (`u32 mask = func_080035A8(2); u16 flags = ...display; flags |= mask;
   ...display = flags;`) is the text of the merged siblings `080F1948`, `080E21BC` and `0810DE24`. Written as
   `display |= func_080035A8(2);` the function differs (two differences, at 0x080FA9A4: `orrs r0, r1; strh r0`
   instead of the ROM's `orrs r1, r0; strh r1`).
3. **Phase 0x10B** turns the layer off with `display &= ~func_080035A8(2);`, as the siblings do.

No original bug is reproduced.

kit issues: shubshub/fftadecomp-kit#200 and #238 (the scheduler thunk chain under the default path). The
BgAffineSet selectors' refusal (a non-leaf call that receives the scratch R3 of `func_080032F8`) has no issue yet.
