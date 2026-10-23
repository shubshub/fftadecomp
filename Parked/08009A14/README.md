# 08009A14 — Parked first natural recovery

The evidence filenames referenced below belong to the frozen local author bundle, not to files shipped in this Parked directory.

## Outcome

PARKED, not a byte-exact match. Only the first natural C form was compiled; the source was frozen immediately after the first official result and was not iterated. The approved `c3baef2` toolkit, fixed agbcc `-mthumb-interwork -O2`, and all nine captured headers produce a plausible complete 16-byte symbol with five instructions. The ROM also owns 16 bytes and five instructions, but their scheduling differs:

- ROM: `LSLS; LDR literal; LSRS; ADD; BX`.
- C: `LSLS; LSRS; LDR literal; ADD; BX`.
- The official display is **14/16 bytes and 4/5 instructions**, using sequence alignment. It is **not positional agreement**. Exactly four byte offsets, `+2`, `+3`, `+4`, and `+5`, differ: positional agreement is **12/16 bytes**, with three of five instructions at identical addresses. The literal-load displacement changes with its instruction position.
- Both complete bodies include the same two zero alignment bytes at `+10` and the same four-byte table literal at `+12`.

`NONMATCH.md` retains the genuine official nonmatching report. No MATCH report or active-source promotion is supplied. This is a compiler scheduling difference, not an unsupported-profile failure; no verifier workaround, source steering, alternative flags, or source search was used.

## Complete ownership and metadata proposal

The complete target span is `[08009A14,08009A24)`: ten code bytes, two internal unreachable zero-alignment bytes, and a four-byte PC-relative literal. The ROM `LDR` at `08009A16` resolves to `08009A20`, whose word is `08A19970`. The next indexed entry begins at `08009A24`; no mapped function overlaps the proposed extension. Capstone closed-CFG decoding and Binary Ninja instruction-length decoding agree on all five instructions.

`metadata-proposal.patch` is evidence only. It changes the existing JSON/text endpoint from `08009A1E` to `08009A24`, text size from 10 to 16, and adds the data binding `g_table_08A19970 = 0x08A19970`. Instruction count remains five, discovery kind remains `call`, and mode remains Thumb. All unrelated mapping entries are unchanged. Nothing was applied to the immutable baseline or production. The late ROM address is data, not authorization to recover late code.

The official matcher also compares the complete 16-byte ELF symbol when the text index is temporarily restored to its old ten-byte endpoint; `short-index-full-symbol.log` records this behavior. It does not truncate to a misleading matching prefix. This check is not described as an extent-rejection test.

## Grounded interface and limits

The target computes `0x08A19970 + 4 * (incoming_r0 & 0xFFFF)`, returning that address in `r0`. A `u16` parameter expresses the low-halfword narrowing. The return is a pointer to an unsized external array of four-byte records, not a loaded word. Focused original caller contexts support byte fields at offsets 0, 1, and 2:

- Calls at `08009A30` and `08009A3E` converge on a byte read at returned pointer `+2`; the first passes constant `0xAA`, the second a loaded halfword.
- Calls at `08009AB2` and `08009C70` are followed by byte reads at `+2` and `+0`, respectively.
- The indexed prologue at `0812237C` reaches call `08122384` directly after narrowing its argument, then reads bytes `+0` and `+1` from the returned pointer.

`CALLERS.txt` and `build.json` preserve the bounded decoded windows and hashes. The initial main-code BL-encoding scan supplied these five candidates; it is not a whole-ROM CFG, exhaustive caller inventory, or startup-reachability proof. The focused paths from two indexed prologues establish real call/use context without recovering adjacent C.

The fourth record byte remains `unknown_03`; no meaning is invented. Ten target-compiler assertions establish the scalar/pointer sizes, four-byte record size, four-byte record alignment under agbcc, and byte offsets 0 through 3. A separate layout probe records that agbcc aligns this byte-member structure to four bytes. The table base and stride satisfy that alignment.

This is a compatible read-only record view, not proof of the unique original nominal type, complete table length, or a global guarantee that every `u16` is a valid index. Defined C pointer arithmetic requires a live compatible array with the selected index within its elements or one-past; any caller dereference requires an actual element. Merely landing numerically inside the ROM does not establish object bounds. No bounds guard exists in this leaf. The `const` view reflects ROM-backed access and does not claim that all possible callers have been inspected.

## Fresh verification

- Original ELF: exactly one complete 16-byte function in 16-byte allocated `.text`; one original `R_ARM_ABS32` at `+12` to the undefined table symbol, zero addend. Official typed linking supplies an absolute `STT_OBJECT` at `08A19970`; the linked ELF remains 16 bytes, with no calls, unresolved relocations, extra allocated sections, or veneers.
- Fresh official verification and `--no-write` both return exit 1 with the same plausible NONMATCH. Strict `report_matches` rejects the authentic NONMATCH and a verdict-only forged MATCH. Removing the table binding fails with `data target must be an undefined mapped object`; the saved report is not changed by negative checks.
- Eighteen fresh ROM/candidate runtime pairs, 36 executions, cover fourteen canonical halfword values and four explicitly machine-only high-register inputs. All five instructions execute in every case. The independent oracle checks the arithmetic result, one exact literal read, no stores or stack use, complete synthetic EWRAM/IWRAM preservation, `r4`–`r11` and SP/LR preservation, and ARM/Thumb return state. Two valid word-aligned SP residues are used.
- The table itself is deliberately unmapped in the emulator because this leaf does not dereference it. These runs validate machine pointer arithmetic, not unproven table backing. Four raw inputs with high bits set test truncation only; they are not promoted to valid C ABI or object-lifetime claims.
- Four machine mutations are rejected: wrong input narrowing, wrong stride, subtraction instead of base addition, and wrong table literal. No helper, callback, allocator, hardware, or caller execution is modeled or run.
- All source, nine headers, ROM, base maps, complete approved toolkit, and toolchain input hashes remain stable. Generated ELF/object/preprocessed/assembly files and temporary fixtures are removed. Retained evidence is text only.

## Reproduction and identities

Copy the retained local author evidence bundle, not this Parked directory, to a separately owned sibling below `/home/user/.codex-work/ffta-ulw/` before reproduction. `check.py` writes only relative to its own directory and regenerates an isolated temporary fixture from the immutable inputs; it does not modify the baseline or toolkit.

```sh
env -u FFTA_ROM TMPDIR=/home/user/tmp PYTHONDONTWRITEBYTECODE=1 \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

- Baseline: `game-next-8a98500`; toolkit: `function-address-thunk-candidate-v3`, published as `c3baef2`.
- Source: `9ee05b96be6312fb4ec7657281515151f1305f00defcafe1cebf6ad9d4f5ffe9`.
- Complete ROM body: `2a771e44553d183a4f3bf961309d9363e724943b0ab617e1fa3f2b8a7c05ecc7`.
- Complete linked candidate body: `e8e929eeaeca9995a60c970f8674827e940767c782344005bd69896e886c3f97`.
- Genuine NONMATCH report: `3e7eb050b189049cc5754ca223834d58c9e146914bbd56f7277a3e47698d85a3`.
- Proposed metadata patch: `9880af4efa0081d5f42bbaecbc783e202adf1376b8c9e3a3bb92ad14601489fc`.

`build.json`, `runtime-results.json`, `input-pins.json`, and `SHA256SUMS` provide the complete reproducible evidence. Independent review and any production metadata/parking integration remain the coordinator's responsibility.
