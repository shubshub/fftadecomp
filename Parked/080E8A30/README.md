# 080E8A30: one preserved nonmatching candidate

**NONMATCH; zero match credit.** This is the unchanged first natural candidate,
compiled once with literal `$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2` through
the canonical matcher. Actual main return, SystemExit and process status are
all 1. The canonical source label is **plausible**, with no findings or waiver;
a genuine `NOT MATCHING - bytes differ` report was produced. No source/type/
flag/order retry, second compile/link or native campaign occurred.

| Extent | Bytes | Reached instructions | Code / literal / alignment |
| --- | ---: | ---: | --- |
| Owned ROM [080E8A30,080E8B24) | 244 | 107 | 228 / 16 / 0 |
| Complete candidate symbol | 264 | 115 | 244 / 16 / 4 |

Within the actual 244-byte target, **7 bytes agree at the same offset and 237
differ**; none are absent. The candidate has **20 excess bytes**. First mismatch
is offset 2, address080E8A32. Both candidate `.text` and function symbol are
264 bytes; there is no external section filler or additional helper function.
The canonical diagnostic compares a 264-byte ROM window, including 20 bytes
from the next entry E8B24. Those bytes are not owned by this target. Its
190/264 aligned-byte score and 55/108 sampled-instruction comparison are not
positional ownership metrics or CFG instruction counts; the linear display
also decodes pool words as instructions. No successor-byte credit is claimed.

Observed differences include an extra r8 save/restore and additional pointer
register copies, different register allocation, branch/pool placement and
internal alignment. The compiler folds the record-child flag expression into
12/20, while the ROM chooses 8/16 then ORs4. These are descriptive differences,
not justification for changing the frozen expression. The preserved source
is not proven equivalent on all inputs, and one failed candidate does not
establish that natural C recovery is impossible.

The semantic recovery retains the compatible fullword-zero callback with three
full pointers. Its reached registration requests a 32-byte payload. Phase0
copies the selector/wrapper and invokes effectful DD748 with optional third
coordinate output NULL. Phase100 tests DD580's low byte, conditionally creates
the coordinate and unpolled record children, always creates the wrapper child,
then reloads/increments phase. Phase101 and phase102 poll separate stored
children. Selector/wrapper/phase reloads follow prior effectful calls. No guard
or initialization is added for the coordinate slot when creation was skipped;
its later validity is an external precondition. Storage at payload+0x10 and
numeric ROM record pointers do not prove callee write extent, object bounds,
allocation success, descriptor retention or lifetime. No named data is invented.

The complete original 1288-byte ELF has seven R_ARM_THM_CALL relocations to
DD748, DD580, D6098, DFD8C, DCFE4, D6134 and DBA5C. The actual canonical linked
3644-byte ELF resolves all seven to typed Thumb function symbols, with no
residual relocations or undefined symbols. Full raw ELF hex, all parsed
sections/symbols/relocations, compiler assembly and preprocessed source are
retained in the private evidence bundle, not as binary files in this payload.
Caller structural verification assumes ordinary returning callee ABIs; it
does not recursively certify scheduler, allocator or callback behavior.

Evidence bundle:
`/home/user/.codex-work/ffta-ulw/080E8A30-author-next`.
The source (including full target-byte comment) was frozen mode0444 at
2026-10-24T14:54:54.510985+00:00, before the sole compile started at
2026-10-24T14:55:10.575174+00:00. `freeze.json`, `compile-start.json`,
`elf-capture.json`, `canonical.log`, `verification.json` and
`isolatedroot/docs/match/080E8A30.md` retain chronology and results.

Source SHA256, identical to the frozen original and this Parked copy:
`9b104536cf5ebc697448d12eff87062858a45057763ac50df2510e4ab57e2143`.
Source plus nine-header fingerprint:
`95a308197641630c954e9b8129bf39537e5d8d861202a75a5ae69aee1e1f5a17`.
Canonical report SHA256:
`a29951b3998854626cf44d3d6e7933dfa5b85829bf681c2c22e862bdae97ebc2`.
The report binds private mapping57f1cf5f and actual toolkit306ceafb inputs;
later shared mapping drift would not make it current evidence. No metadata
change is proposed. Ready integration is only this C/README pair, not a new
matched source or report. Root owns independent preservation review and release.
