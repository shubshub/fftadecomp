# 0x080E9BDC - BG2 affine zoom effect phase callback: bytes identical, refused (BgAffineSet with a payload-resident source and a local destination, and named data beside the buffer walk) (588 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main edc8e8f321. `u32 func_080E9BDC(void *task, Descriptor080E9BDC *descriptor, Payload080E9BDC *payload)` is a phased BG2 affine zoom. `func_080E9E28` starts it through `func_08005B6C` with a 0x50-byte payload (function word `0x080E9BDD` at `0x080E9FDC`, loaded at `0x080E9F90`); no `bl` reaches it. Phase 0x100 wraps the target object in a VRAM loader task (`func_080DC1E8`, `0x0600F9C0` to `0x06005800`) and reads its position into the payload (`func_080DBDC8(object, &payload->x, &payload->y)`); 0x101 waits for the loader, sets the BG2 control word and enables BG2, fills the payload's `BgAffineSrc` (texture centre 0x1000/0x3000, or 0x2C00 when `func_080DD6E0` returns 0x51; scale 0x100) and calls BgAffineSet; 0x102 resets the scales and continues only if `func_080DD580(wrapper)`; 0x103 steps two interpolated scales through the keyframe table `data_08398830` or `data_08398858` (by `payload->selector`) and calls BgAffineSet again every frame.

Each BgAffineSet call reads the source from the payload and writes a local 16-byte `BgAffineDst`, which then goes to `func_080032F8`:

```
080E9DF8  adds r0, r5, #0
080E9DFA  adds r0, #0x38              @ &payload->affine (not a local)
080E9DFC  add  r4, sp, #0x1c          @ dst
080E9DFE  adds r1, r4, #0
080E9E00  movs r2, #1
080E9E02  bl   0x08141864             @ BgAffineSet (svc 0x0E)
080E9E06  adds r0, r4, #0
080E9E08  movs r1, #2
080E9E0A  bl   0x080032F8
```

(phase 0x101 makes the same pair of calls with `dst` at `sp + 0xC`, `0x080E9D1A`).

## The index

The index row `080E9BDC 080E9E28 588 294 return` is right about the extent, but its instruction column is the halfword count (bytes/2), as is `config/functions.json`'s (294): the reachable CFG has 253 instructions (the kit's `analyze.refine_function` at 18dcc516 closes it over the indexed extent). Not corrected here: no draft needs it. The selectors that check the count against the CFG refuse on it (`restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-acyclic-v1` and 2 more: `complete-owner text reachable instruction count differs`).

## Byte identity

`080E9BDC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`, `arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080E9BDC, with every callee and data symbol bound to its ROM address (23 `R_ARM_THM_CALL`, 4 `R_ARM_ABS32`). The 588-byte symbol equals the ROM span `[0x080E9BDC, 0x080E9E28)`: SHA-256 `84bd710e8a762bb037f166157601f1b57d17ae98b55a1ccd5da49beca007d3f0` for both. `.text` is exactly 588 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Data symbols

Not in `config/data_symbols.json` on main; each was added with its address as the value (`"data_08398830": "0x08398830"`) for the runs below: `data_08398830`, `data_08398858`.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080E9BDC.c` and the data symbols above: the default run and all 213 selector values. None matched. The default run prints the refusal after `compile failed:`, a selector run as `error (ValueError): <text>`.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-v1`, and 22 other selector values | `buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG verification` |
| `bounded-buffer-bios-bg-affine-set-v1`, `bounded-buffer-bios-bg-affine-set-transparent-leaf-scratch-v1`, `bounded-buffer-bios-bg-affine-set-discarded-scratch-v1` (3) | `BgAffineSet requires exactly a local source and a local destination` |
| `bounded-buffer-bios-fill-source-v1`, and 2 other selector values | `verdict NOT VERIFIED - the selector was not run` |

The other 184 selector values give 64 other refusals, none of them a match; the most frequent are `addressed runtime ELF requires actual addressed calls and no unresolved symbols` (29), `private float requires unique undefined pinned helper symbols` (15), `addressed signed runtimes exclude data and irregular relocations` (13).

## Cause

The local `dst` reaches the BgAffineSet wrapper `0x08141864`. The default run and the plain buffer selectors walk into the wrapper and stop at its `svc` (`buffer callee 0x08141864: non-leaf calls and interrupts require linked CFG verification`), the BIOS-wrapper summary asked for on kit #192. The three BgAffineSet selectors summarise the call but only for a local source and a local destination (`BgAffineSet requires exactly a local source and a local destination`); here the source is the payload's `affine` member. The three BIOS-fill selectors stop at the allowlisted volatile semantic check on the VRAM literal (`verdict NOT VERIFIED - the selector was not run`, finding `allowlisted volatile semantic check: owner literal requires genuine named object proof at 0600F9C0`). The function also has named data (the two keyframe tables). In the prototypes measured for the issues below (not re-run here), it matches with the BIOS summary inside the buffer walk together with named data beside the buffer proof on the plain path, and with neither alone; the root call-site placement of the BIOS summary does not cover it, because BgAffineSet is not a memory fill.

## Source notes

- The keyframe step is an inline helper used twice, once per table, and the ROM has both expansions: written as one call with the table chosen by `?:`, the function is 584 bytes (16 halfwords differ). Its shape was found by trying spellings, as the earlier notes say; the repetition itself is in the ROM.
- `func_08003A80` is declared returning `u16`, which is the return type of the matched `src/08003A80.c`; the earlier note that its definition returns `u32` no longer holds.
- The source includes `control_flags.h`; the display update is a member store into `g_control_flags_03000940`.

kit issue: shubshub/fftadecomp-kit#236; shubshub/fftadecomp-kit#192 (comment)
