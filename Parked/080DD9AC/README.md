# 0x080DD9AC — PARKED, not byte-identical

Recovered C: `080DD9AC.c`, SHA-256 `08da60502517122dd4afa43c4a3edad90692a03415c68fde3ae4146007379c59`.

Only this README and `080DD9AC.c` are intended for integration under `Parked/080DD9AC/`. All other evidence remains in `/home/user/.codex-work/ffta-ulw/080DD9AC-author-substantial/`; no successful match or shared `src/` integration is claimed.

## Recovered behavior

This is a task callback with scheduler ABI `u32(void *task, void *descriptor, void *payload)`, returning zero on every path and not otherwise reading `task`.

- State 0 copies descriptor object `+4`, sequence `+8`, count `+0x14` narrowed to `u8`, and signed delay `+0x16` into the twelve-byte ARM payload. It does **not** initialize the payload index at `+6`.
- State 1 and unknown states do nothing. At `0x100`, delay `-1` waits on a completion predicate; other nonzero delays decrement and defer the action until a later callback. Zero or successful polling executes the current eight-byte sequence record.
- Record kind zero selects `080DE12C`; other kinds select `080DE168`. Signed variant `-1` substitutes object byte `+0x1F`, then the actual argument is sign-extended. Records also supply u16 action and option fields.
- After the action, sequence pointer and index are reloaded before reading the record's next signed delay. The byte index increments with wrap; equality with byte count increments the descriptor state.
- State `0x101` uses the same delay/predicate rules, then sets state 2.

## Exact remaining difference

One natural candidate was frozen before compiling. It is plausible and emits a complete 230-byte Thumb function with 111 instructions, no local stack frame and no literal pool. Both ROM and candidate have exactly the same branch destinations and four direct BL sites/targets. They are still **not byte-identical**: 200 byte positions agree and 30 differ. The canonical report's 202/230 sequence-similarity figure is not the positional equality count.

The ROM keeps payload in `r4`, object in `r5`; the compiler keeps payload in `r5`, object in `r4`, and retains incoming `r2` for payload operations on call-free paths. The compiler also loads the first record's sequence base after shifting its index, rather than before, and reverses the equivalent add operands. These register and scheduling differences explain the remaining bytes; no semantic discrepancy was identified. Two assembler alignment bytes follow the symbol and are excluded from all 230-byte claims.

There was no second semantic candidate, declaration/call reordering, flag search, alternative spelling campaign, register steering, inline assembly, volatile, pragma, or warning suppression. Exactly two agbcc compilations occurred: canonical check, then unchanged-source ELF audit, both using `-mthumb-interwork -O2`. The retained failed report is `/home/user/.codex-work/ffta-ulw/080DD9AC-author-substantial/Parked/080DD9AC/match-report.md`; exact differing offsets and full decoded bodies are in `/home/user/.codex-work/ffta-ulw/080DD9AC-author-substantial/verification.json`.

## Evidence and limits

The actual constructor `080DE0E0` loads Thumb callback pointer `080DD9AD` from literal `080DE108` at `080DE0F4`, sets payload size 12, and calls matched scheduler `08005B6C` at `080DE0FC`. The scheduler's existing source supplies the three-pointer/u32 callback signature. Constructor compilation and the scheduler's complete lifecycle are not claimed proven here.

The three outgoing callees were decoded directly. `080DE1F0` returns the low byte of its dependency result. `080DE12C` forwards u16 action and a sign-extended low-byte variant; this caller supports the local `s8` declaration, but the original public signedness is not independently recovered. `080DE168` forwards u16 action, u16 option and s8 variant in the downstream ordering also supported by existing `08124710.c` declarations. ABI summaries do not prove callee implementations or termination.

Seven focused native ASan/UBSan groups pass: initialization/count narrowing/index preservation, inert states, predicate low-byte handling, countdown and negative delays, both action variants, post-call sequence/index/state mutation, byte-index wrap and final completion. Destination canaries and unconditional zero returns are checked. Native mocks test callback semantics, not the live task scheduler or action implementations; ARM layout comes from the ROM/ELF offsets, not native pointer size.

External code must initialize the index and provide valid object/sequence storage for the current index. The callback does not guard zero count, count mismatch, invalid pointers, or exhausted sequence storage, and no new guards/defaults were invented. The separate `metadata.patch` in the retained author bundle proposes only the ROM-derived symbol-size correction 12 → 230; it is not part of the C-plus-README payload and gives no match credit.
