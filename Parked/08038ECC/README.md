# 0x08038ECC - seven-row list panel draw: bytes identical, refused because two VRAM addresses are plain numbers (756 bytes)

Attempt 2026-11-14, kit fcdf2d45. Compiled with agbcc -mthumb-interwork -O2 and linked by hand at 0x08038ECC with every
callee and data symbol bound to its ROM address, the source gives all 756 bytes of [0x08038ECC, 0x080391C0). Index row
correct.

For each of seven rows the function redraws the row frame from one of four tile-map tables, writes the row's tile
numbers, clears the row's text tiles in VRAM with a CpuFastSet fill (func_08141868, control 0x010000E0) and draws the
row text with func_08015110.

Needs four data symbols (not in config/data_symbols.json): data_08391D44, data_08391D6C, data_08391D94 and
data_08391DBC, the frame tables indexed by a row's flags byte.

Refusals, with the four symbols added:
- default: `buffer callee 0x08141868: non-leaf calls and interrupts require linked CFG verification`
- `--owner-runtime-profile bounded-buffer-bios-mixed-fast-fill-source-v1`: `owner address literals require exact
  typed object/function coverage`

Cause: two literal-pool words hold VRAM tile addresses as plain numbers, 0x0600B1E0 (pool word at 0x080390A0) and
0x0600B260 (at 0x080390AC), each plus i * 0x380, with no relocation. The owner admission rule
(tools/owner_admission_profile.py:858-873) treats every reached word in [0x02000000, 0x09000000) as an address that
needs a typed object or function binding; only switch words and, for the BIOS selectors, scalar control words are
exempt. Naming the two addresses as data symbols does not match: a symbol is a relocation and a constant is not, so
the register allocation changes (749/756 bytes equal with data_0600B1E0 / data_0600B260). The original source used
numbers there.

Kit gap: a numeric hardware-address word class for the owner and addressed BIOS-fill profiles, as
tools/unsigned_thunk_profile.py already records reached untyped I/O, palette, VRAM and OAM words while still
requiring typed provenance for RAM and ROM words. In a copy of the kit with only that classification changed
(untyped words in [0x04000000, 0x08000000) left numeric), match.py reports MATCH - byte identical under the selector
above. 0x08038DCC, 0x0808BAD0 and 0x0802B5A8 have the same gap (kit #192 proposes this route for three of them).
