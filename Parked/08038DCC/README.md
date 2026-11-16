# 0x08038DCC - seven-row text tile draw: bytes identical, refused because two VRAM addresses are plain numbers (256 bytes)

Attempt 2026-11-13, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x08038DCC with every
callee bound to its ROM address, the source gives all 256 bytes of [0x08038DCC, 0x08038ECC). Index row correct; no
data symbols needed.

For each of seven rows the function writes the row's tile numbers, clears the row's text tiles in VRAM with a
CpuFastSet fill (func_08141868, control 0x010000E0) and draws the row text with func_08015110. It is the same row loop
as 0x08038ECC over another tile block.

Refusals:
- default: `buffer callee 0x08141868: non-leaf calls and interrupts require linked CFG verification`
- `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-source-v1`: `owner address literals require exact
  typed object/function coverage`

Cause: two literal-pool words hold VRAM tile addresses as plain numbers, 0x06009960 (pool word at 0x08038EB4) and
0x060099E0 (at 0x08038EC0), each plus i * 0x380, with no relocation. The owner admission rule
(tools/owner_admission_profile.py:858-873) requires a typed object or function binding for every reached word in
[0x02000000, 0x09000000) apart from switch words and BIOS scalar controls. Naming the two addresses as
data_06009960 / data_060099E0 changes the register allocation (235/256 bytes equal).

Kit gap: a numeric hardware-address word class for the owner and addressed BIOS-fill profiles (see 0x08038ECC). In a
copy of the kit with only that classification changed, match.py reports MATCH - byte identical under the selector
above. Same gap: 0x08038ECC, 0x0808BAD0 and 0x0802B5A8.
