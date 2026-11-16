# 0x0802B5A8 - OBJ tile load and fill: bytes identical, refused because two VRAM addresses are plain numbers (136 bytes)

Attempt 2026-11-13, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x0802B5A8 with every
callee and data symbol bound to its ROM address, the source gives all 136 bytes of [0x0802B5A8, 0x0802B630). Index row
correct.

Given a transfer-record array, the function queues two 0x400-byte copies of data_083BD9F4 to 0x06013900 through
func_08000ADC; without one it copies the tiles at once with CpuFastSet (func_08141868, 0x200 words). Either way it then
fills 0x06014100 with 0x66666666 by CpuSet (func_0814186C, control 0x05000100).

Needs one data symbol (not in config/data_symbols.json): data_083BD9F4, the source tiles.

Refusals, with the symbol added:
- default: `buffer callee 0x0814186C: non-leaf calls and interrupts require linked CFG verification`
- `--addressed-runtime-profile addressed-native-bios-fill-buffer-data-v1`: `addressed data requires exact typed
  coverage of reached address words`
- `--owner-runtime-profile bounded-buffer-bios-fill-source-v1`: `owner address literals require exact typed
  object/function coverage`

Cause: the VRAM addresses 0x06013900 and 0x06014100 are plain numbers in the literal pool, with no relocation. Both
selectors require typed coverage of every reached address word. Naming them as data symbols changes the register
allocation (a symbol is a relocation, a constant is not; the compiled symbol becomes 144 bytes), so the original
source used numbers. 0x05000100 (pool words at 0x0802B5FC and 0x0802B62C) is a CpuSet control word (fill, 32-bit,
0x100 units), not a palette address; the BIOS selectors already classify it as a scalar control.

Kit gap: a numeric hardware-address word class for the owner and addressed BIOS-fill profiles (see 0x08038ECC). In a
copy of the kit with only that classification changed, match.py reports MATCH - byte identical. Same gap: 0x08038ECC,
0x08038DCC and 0x0808BAD0.
