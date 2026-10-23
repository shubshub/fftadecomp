# 08009A24 — Parked first natural recovery

## Outcome

PARKED only. The first natural source was frozen before compilation and was not changed. Fixed agbcc `-mthumb-interwork -O2` produces a complete 104-byte, 41-instruction function; the complete ROM body is 108 bytes and 43 instructions. Diagnostic typed linking finds 57 equal overlapping byte positions and 47 unequal positions, starting at `+0x06`, with four additional ROM bytes absent from the candidate. This is a genuine byte mismatch, not merely a verifier limitation.

The published `c3baef2` toolkit also rejects the canonical unsigned-quotient call combined with data relocations:

```text
division evidence excludes literal, switch and thunk combinations
```

`official.log` and `no-write.log` preserve that result. No official MATCH or NONMATCH report is produced because verification stops before comparison. The separately labeled diagnostic link does not weaken, replace, or bypass the official gate. It retains the original undefined `__udivsi3` symbol and both addressed `func_08009A14` calls; no addressed runtime alias or helper model is substituted.

## Complete ownership

The target owns `[08009A24,08009A90)`: 92 executable bytes containing 43 reachable instructions, then four literal words. There is no target internal alignment or external padding in that interval. The final return is `BX r1` at `08009A7E`.

| Literal address | Value | Observed role |
| --- | --- | --- |
| `08009A80` | `02000000` | RAM base |
| `08009A84` | `00002192` | halfword selector offset |
| `08009A88` | `089C1484` | packed relative-offset data base |
| `08009A8C` | `00003C2A` | byte value offset |

The old endpoint `08009A84` omits three consumed words. `metadata.patch` proposes only endpoint `08009A84 → 08009A90` and instruction count `48 → 43` in JSON/text, preserving mode, discovery kind, and next entry `08009A90`. No other entry overlaps the corrected extent. `data.patch` separately proposes only the `g_table_089C1484` address binding, without implying its allocation size or type is proved. Both patches were applied only to the temporary fixture, never to the baseline or production.

Raw Capstone closed-CFG traversal and actual-address Binary Ninja mapped-view analysis agree on every target instruction boundary. `CLASSIFIED.txt` accounts for every byte of the target and the three bounded runtime dependencies. The candidate has 88 code bytes, one internal four-byte literal at `08009A38`, and three trailing words at `08009A80..08009A8C`; no internal or external alignment bytes are hidden. `CANDIDATE-CLASSIFIED.txt` records its complete CFG and literals. Its `.text` and sole function symbol are both 104 bytes.

## Recovered operation and types

The argument is narrowed to `u16`. For values above 239, the routine selects entry 170; otherwise it loads the halfword at `02002192` and passes that index to `func_08009A14`. The returned entry's byte at offset two chooses a relative word offset in the block rooted at `089C1484`. Usually the result is that base plus the selected offset.

For an input at most 239 and entry byte 61, the routine reads the byte at `02003C2A`, decrements it only when nonzero, divides the resulting unsigned value by ten, narrows the quotient to a byte, and uses it to choose another relative offset from the first selected block. The result is again relative to the original `089C1484` base. The quotient is in `0..25`; this arithmetic fact does not establish table allocation capacity.

The helper declaration and four-byte record view match the frozen `08009A14` reconstruction: `const Entry08009A14 *(u16)`, with byte fields `field_00`, `field_01`, `field_02`, and `unknown_03`. The combined compatible check and ten target-compiler assertions pass; deliberately incompatible helper-argument and caller-return declarations fail. The return is expressed as `const u8 *` because the target returns an address and performs no subsequent dereference. This does not prove the unique original return type or recover downstream payload formats.

The packed-data word casts express the observed aligned 32-bit loads. The source's byte-array declaration is not proof of a compatible declared/effective type for every word subobject. The RAM halfword cast at C line 26 has the same unresolved requirement: declaring the surrounding storage as a byte array does not establish a suitably typed live `u16` object at that address. Strict ISO C effective-type/alias closure remains unresolved for both the ROM `u32` casts and the RAM `u16` cast; numerical alignment, compiler acceptance, and passing machine tests alone do not resolve it. This is an explicitly partial Parked storage view, not a whole-program type-safe reconstruction. Any later grounded type repair requires separate review, not byte-matching source iteration.

## Actual runtime and verification limits

- The original ELF has one complete function and six relocations: three Thumb calls, one zero-addend table-object relocation, and two RAM-object relocations, one with addend `0x2192`. Diagnostic linking uses typed absolute definitions, leaves all nonrelocation bytes unchanged, and adds no veneers, allocated data, unresolved relocations, or extra text.
- Actual ROM `08009A14` executes in every test. Its complete span is 16 bytes, including two internal zero bytes and its table literal; the old baseline's short helper row is retained in the fixture and is not treated as its full ownership proof.
- Actual ROM `08142AB0` executes on special cases. The exact 120-byte runtime and two-byte zero-path dependency match the toolkit's checked identities and the local `libgcc/lib1thumb.asm` unsigned-division structure. This is quotient, not remainder. The nonzero constant divisor is ten. The zero-divisor dependency is statically classified but never executed; no defined-C zero-division behavior is asserted.
- One hundred executions cover 25 fixtures, both complete bodies, and ARM/Thumb caller return states. Twenty-four fixtures use original ROM table contents; one explicitly synthetic fixture changes only entry 170's type byte to 61 to check the outer input guard. Four fixtures supply noncanonical upper argument bits and are machine-only truncation checks, not valid narrow-argument ABI claims.
- Every ROM caller instruction (43/43), candidate caller instruction (41/41), and lookup instruction (5/5) executes. Unsigned quotient coverage is 52/59; the unexecuted general large-divisor/zero-path instructions are not inferred tested. No helper or callback is modeled, and no callback executes.
- The oracle checks selected helper arguments and results, ordered data and literal reads, initialized consumed RAM, no unwritten/dead stack reads, exact stack writes, complete EWRAM/IWRAM including guards, `r4`–`r11`, SP, and ARM/Thumb return state. Caller stack use is 16 bytes; the actual quotient helper adds four bytes. Ten deliberate semantic/read-initialization defects are rejected.

The consumed RAM halfword must be initialized on the ordinary-input path; the byte is required only on the special path. Actual tests do not establish original RAM object lifetimes, all table lengths, all possible selector backing, offset arithmetic within a single C object, arbitrary aliasing, concurrent mutation, or universal source equivalence. The loaded ROM words and selected destinations are readable numeric machine locations in the tested fixtures, not proof of their nominal allocation boundaries. This slice does not analyze external state writers, all callers, adjacent functions, or whole-game reachability.

## Reproduction

The named scripts, logs, patches, JSON files, manifests, and reproduction commands in this README refer to the separately retained local `08009A24-author` and `08009A24-review` evidence bundles. They are not included in the two-file `Parked/08009A24/` publication. Reproduction requires the pinned toolkit snapshot, baseline, helper source, all nine captured headers, approved compiler, and approved ROM.

Use a separately owned sibling copy of the local author evidence bundle before running the scripts: they write results relative to their own location. They use immutable `game-next-8a98500` and create and remove only an owned disk-backed fixture; no ROM or compiled binaries are retained.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 audit.py
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 probe.py
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp python3 runtime.py
```

`audit.json`, `build.json`, and `runtime-results.json` retain exact identities, inputs, layouts, relocations, differences, and finite test traces. `manifest.json` and `SHA256SUMS` pin the final author evidence. Integration, metadata approval, and independent review remain separate coordinator gates. No match credit is requested.
