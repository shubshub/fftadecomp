# 0x080018A0 | affine sprite renderer

The US ROM function occupies 796 bytes in `[0x080018A0, 0x08001BBC)`. Its 367 reachable Thumb instructions occupy 738 bytes, with 56 bytes of literals and two bytes of alignment. The return is at `0x08001B90`. The SHA-256 of the full span is `d2faf191b334f119a02ea3e146d67431580db260c64c8a78b02424e31a791418`.

The renderer reads a signed part count and six-byte sprite records. It obtains one affine matrix slot, clips each part against the 240 × 160 display and appends visible parts to the selected 128-entry OAM shadow bank. It preserves the fourth halfword in each destination entry. For left-edge clipping, the original uses the sprite's height. In double-size mode it centers X using half the width and Y using half the height. The prototype follows the narrow argument widths in callers `0x080216F8` and `0x0808F1F4`. Five older caller declarations use full ABI words for byte-sized options.

At `0x08001922` the renderer calls `0x08141894`, the Thumb BIOS wrapper for `swi 0x0F` (ObjAffineSet). The input starts at SP+8 and the destination at SP+16. The count is one and the destination stride is two bytes. The four output halfwords are copied to SP+0 for the matrix allocator call at `0x08001948`. The literal for `0x08149510` points to 16 signed halfword width/height pairs indexed by the sprite's shape and size. The private data manifest maps the ELF object `data_08149510` to this address.

## Native comparison

The ordinary C compiles and links to 740 bytes with agbcc `-mthumb-interwork -O2` at the original address. It first differs at `0x080018AA`, where it reserves 52 stack bytes and the ROM reserves 60. 127 bytes agree at their original offsets. Its linked SHA-256 is `4132f78ee336fe9b7783d63b905946899156eaf877cbd308670d9f2bd768ec0a`.

The ROM reads its local matrix destination halfwords before replacing them at `0x0800192A`, `0x08001932`, `0x0800193A` and `0x08001942`. It also reads OAM destination fields before replacing them at `0x08001A7E`, `0x08001A8A`, `0x08001A96` and `0x08001AE6`. The ordinary C omits those discarded loads. The opposite-bank VBlank transfer provides independent evidence for hardware access to shadow OAM. The local matrix copy remains private until the synchronous allocator call. A diagnostic with qualified OAM fields and qualified local matrix fields produces 796 bytes, of which 253 agree at their original offsets. Its first difference is `0x080018F2`. The parked source uses ordinary field assignments.

The default native verifier at toolkit commit `f0c07c2d70f0` stops at the BIOS call with `buffer callee 0x08141894: non-leaf calls and interrupts require linked CFG verification`. The existing sprite-node verifier checks this renderer below the caller at `0x080216F8`. Admission of the renderer itself would also require exact compiled bytes.

## Behavioral check

104 deterministic differential cases executed the compiled renderer and original ROM under ARM emulation. The BIOS stub returned the same deterministic matrix in both executions. Each pair agreed on the BIOS input values, count and stride, the input passed to the native matrix allocator, both OAM banks, bank counts, matrix slot storage and restoration of the stack pointer. The cases include both banks, a full bank, clipping boundaries, double-size parts, negative and zero part counts, occupied matrix slots and extreme X coordinates. These comparisons cover the tested game state. They do not establish BIOS arithmetic, native memory access order or a byte match.
