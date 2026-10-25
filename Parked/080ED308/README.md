# 080ED308: signed-offset byte-pair buffer fill

**Not matched.** The complete target is `[080ED308,080ED3B8)`, 176 bytes,
including its four-byte literal at `080ED3B4`. The retained candidate compiles
to a complete 160-byte symbol using the fixed `agbcc -mthumb-interwork -O2`
recipe. No unverified source remains under `src/`.

## Recovered behavior and limits

The one-pointer, void-compatible helper obtains a writable buffer through
`080D9B08(payload->handle)`, with the handle at payload offset `0x1D8`.
The signed 32-bit offset at `0x150` controls a positive prefix of `(0,16)`
pairs. The prefix index wraps at eight bits and is compared against the
reloaded signed offset; no output-index guard was added. For a negative
offset, the table index starts at its negation narrowed to eight bits.

If the table index is at most 30, the first pair is copied without checking
the output index. Continuation requires the updated output index at most
159 and the updated table index at most 30. The tail fills `(16,16)` through
index 159, then calls `080D9B98` with the reloaded handle. The table symbol
is an unsized byte array mapped by the coordinator to `083992B8`; the
observed 62 bytes do not establish the original allocation size.

The retained C preserves those stores, loop widths, guards, and calls. It
does **not** reproduce the target's destination reads before its stores.
No discarded read was inserted into the C solely to reproduce those bytes.

## Exact remaining code-generation differences

The target has 172 code bytes, 84 reached instructions, no alignment gap,
and a four-byte literal pool. The retained candidate has 154 code bytes,
75 reached instructions, two alignment bytes, and a four-byte literal pool.
Its literal is at `080ED3A4` rather than `080ED3B4`.

The nine-instruction code-size difference consists of:

- Six target destination `ldrb` instructions absent from the candidate:
  `080ED32C`, `080ED330` in the prefix; `080ED366`, `080ED36E` in the table
  copy; and `080ED38E`, `080ED392` in the tail.
- Target `080ED35C` / `080ED35E` form and retain `table + 1` in `ip`.
  The candidate retains only the table base.
- Target `080ED36A` adds the byte offset to that second base. The candidate
  reuses its first element address and loads the second byte at address +1.

The resulting register allocation also differs: candidate output pointer
`r2`, output index `r3`, table index `r4`, payload `r5`, table base `r6`;
target output pointer `r3`, output index `r4`, table index `r5`, payload
`r7`, table base `r6`, second base `ip`. Thus the candidate saves only
`r4-r6` rather than `r4-r7`, and its branch, literal-load, and final BL
encodings differ with the shorter body. These are not a claim that the
unmatched function is impossible to recover.

## Attempts ruled out in this session

All attempts used the fixed flags; no alternate compiler flags were tried.

- Two full-width eight-bit bitfields with `u8` or `u16` backing did not
  produce the destination reads. The initial unpacked byte-bitfield layout
  also acquired a four-byte stride in this compiler, contrary to the target.
- Packed `u32`-backed eight-bit fields gave the correct two-byte stride but
  ordinary byte stores, still omitting the reads. These early loop/type
  candidates compiled to 164-byte symbols and were superseded.
- A packed scalar `u16`, and a packed full-width 16-bit bitfield, compiled
  to 170 bytes. Both combined the table bytes with shifts/OR before storing,
  unlike the target's separate byte operations, and still omitted the reads.
- A flat byte-table `for` loop with an internal output-limit break compiled
  to 196 bytes: it peeled the first iteration, duplicated the table-copy
  block, and emitted separate numeric table/base+1 literals. The raw ROM
  pointer also triggered the `rom-address` plausibility finding.
- The retained unsized named table plus guarded `do`/`while` removes that
  peeling, duplicate block, raw-pointer finding, and middle pool. It gives
  the target's loop guard order but remains 16 complete bytes short.

No narrower bitfield layout was inferred merely from the table values.
No assembly, pragmas, volatility, dead code, dummy destination reads,
additional guards, initialization, helper functions, or shared-header edits
were introduced.

## Verification evidence

The final canonical command from the game repository was:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' \
python ../fftadecomp-kit/tools/match.py --root . 0x080ED308
```

It exited 1 with `compiled symbol is shorter than the indexed span: 160 < 176`.
The standalone check of this source with `plausible.py --addr 0x080ED308`
exited 0. A fresh diagnostic compilation using the unchanged matcher's
`compile_object`, `link_calls`, `verify_leaf_instructions`, and
`verify_data_literals` also passed the ordinary CFG/direct-call and typed
data-literal checks, without changing the indexed target extent. Those
checks do not establish byte equality.

Source SHA256:
`b12fba80a8cce4487c775a307533c8a9e4015f093c44b88784ee400a172fd3d5`.
Linked 160-byte candidate SHA256:
`3770a56a394edfe76c1b8905308184bd4a746170d670df5fc5aa7f4dd4c8c17e`.
Session diagnostic text, candidate bytes/disassembly, and canonical failure
log are retained under
`/home/user/.codex-work/ffta-ulw/audio-following-v8-matching/080ED308/`.

The complete target and bounded ABI/table evidence remain in the sealed
`audio-following-region-inventory-v8-completion` bundle. The coordinator
owns lease release and integration. No Git, reservation, status, global
plausibility sweep, shared map, or shared header action was performed by
this matching worker.
