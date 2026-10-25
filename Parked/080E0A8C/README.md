# 080E0A8C, one natural candidate, nonmatch

This is the unchanged first plausible C recovery, preserved with zero match credit. One canonical agbcc invocation used the default literal `$HOME/agbcc/gcc/agbcc` and `-mthumb-interwork -O2`. There were no source/type/order/flag retries, native campaign, inline assembly, volatile, bitfield guesses or inserted dead reads.

## Exact result and ownership

The independently qualified target is [080E0A8C,080E0C88), 508 bytes: 208 reached instructions / 470 code bytes, 36 literal bytes and two zero alignment bytes. The candidate owns 510 ELF function bytes: 211 reached instructions / 476 code bytes, 32 literal bytes and two zero alignment bytes. Its ELF `.text` is 512 bytes; the final `c046` is outside the function and receives no ownership credit.

Only 71/508 target bytes agree at the same position; 437 owned-target positions differ, and the candidate has two further bytes beyond the target endpoint. Only 17/208 complete target instructions agree at the same address. The canonical diagnostic instead compares a compiler-sized 510-byte ROM window, including external `00b5` at E0C88 in the following unindexed prologue-shaped window. Its `389/510 bytes` is an LCS-aligned metric, and `110/190 instructions` samples ROM at compiler instruction positions. Neither is positional equality, a complete target instruction count, or authorization to extend the target. The candidate is not byte-identical.

Canonical `main()` returned 1, its `SystemExit` code was 1, and the process exited 1. A source-plausible **NOT MATCHING - bytes differ** report was produced under the frozen private map; this is historical diagnostic evidence, not a current integrated match report. Typed linking resolves all 27 `R_ARM_THM_CALL` sites to 22 indexed Thumb targets without residual relocations. ABI call summaries do not certify complete or recursively equivalent callee implementations.

## Recovered contract and remaining delta

The local contract is `u32(void *unused, void *state, void *work)`, with state halfword phases 0/0x100/0x101/0x102 and zero return. State zero selects or fills a buffer; later phases enqueue requests, create a handle, optionally configure shadow state and two signed-word interpolators, then wait, release, restore and finish. Phase, handle and mode reloads across external side effects and short-circuit completion order are retained.

No incoming context was witnessed in the bounded inventory. The work prefix describes observed offsets through +0x127, not a proved allocation size; the external write starting +0xA has a separate buffer-size/validity requirement. Unmatched dependencies remain ROM-observed compatible contracts rather than matched or recursively verified C. Original nominal types and several public return widths remain uncertain.

The target has seven discarded shadow-byte loads and an OR-zero without a proved original aggregate/bitfield declaration. The ordinary byte-field candidate omits these operations. It also emits a different register-save/live-value arrangement, additional return-width normalization, changed literal placement and a folded 0300393E address in place of the target's 03003860 base plus offset. These are observed output differences, not instructions for a spelling/type/register search. This single attempt does not establish impossibility, and no output-directed rewrite was attempted.

## Provenance

- Candidate SHA256: `f51e7d9da9993b9ba3d7bf885889495d0a1aaa907df182752078d4fafcaf0e2e`.
- Source plus nine-header fingerprint: `bbb32b8dfc87497ae97b542642f0f8a4818440c65f29eab7c7a4e60312ad5265`.
- Full evidence bundle: `/home/user/.codex-work/ffta-ulw/080E0A8C-author-next`.
- `freeze.json` and `compile-start.json` establish precompile source/input freeze. `elf-capture.json` retains complete raw original and linked ELF as text, including all sections/symbols/relocations. `verification.json` contains complete owned-body partitions, disassembly and every positional difference.
- Canonical report SHA256: `b5b4daa665ea7d7f6e7a55c911e0ac8cedd8e508ae21516e4f6b7917e044f431`.
- Private map SHA256: `c4c506ce8780f810357ae5825ce1ba356759b27c8718719694542e32220c2cf8`; only this target's count 254->208 and legacy symbol size 0x12->0x1FC were corrected. Root separately owns the reviewed combined metadata integration.

The ROM was read from the existing approved copy, never duplicated. The canonical temporary build directory is empty and no generated binaries or bytecode remain. The source is an exact copy of the frozen candidate, including its original target-byte comment.
