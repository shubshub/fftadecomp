# 080CD1FC

## Outcome

The natural candidate is not byte-identical. With agbcc
`-mthumb-interwork -O2`, its complete symbol is 200 bytes and 96 instructions,
covering the target `[0x080CD1FC, 0x080CD2C4)`. The final word is the
`g_table_08520080` literal. The framed direct-call/data verifier accepts the
candidate structure and the plausibility check passes.

The only difference is instruction ordering:

| Address | ROM | Candidate |
| --- | --- | --- |
| `0x080CD276` | `adds r1, #2` | `mov ip, r0` |
| `0x080CD278` | `mov ip, r0` | `adds r1, #2` |

Those four bytes differ positionally; the other 196 bytes are identical.
The matcher's sequence-alignment summary reports 95/96 instructions and
198/200 bytes identical. This is a local code-generation difference, not
evidence that the function cannot be matched.

## Recovery

The function returns a normalized Boolean. It reads five halfword entries
at object offsets `0x2A..0x32`, skipping zeros. For each entry,
`func_080CA7A4(entry, 0x12)` selects an effect record. Nonzero pair markers
must equal object byte `7`, and the pair value must equal the requested
low-byte index. A matching pair returns one; exhaustion returns zero.

`func_080C7EA4(object, 3) == 4` enables an additional search when the request
is `0x1A` or `0x21`: the requested value is searched first, then the other
value. Other inputs use one pass. The signed countdown is decremented before
each pass and stops at minus one.

The table stride is 20 decimal (`0x14`), not `0x20`: the ROM computes
`(index * 4 + index) * 4`. Its count is byte zero and two-byte rows begin at
offset two. The shared tagged `EffectRecord` uses `u8 pairs[9][2]`;
actual agbcc compile-time probes confirm size 20 and row offset two.
An array of two-byte-looking structs is unsuitable here because this
compiler rounds each such struct to four bytes.

The outer table is unsized. No table-index or runtime-count bound is proven.
The typed candidate requires valid selected records and row accesses within
the nine physical rows; it introduces no guard. The object must be valid,
readable and suitably aligned for its halfword fields. The callee signatures
are `s32 func_080C7EA4(const void *, u32)` and
`s32 func_080CA7A4(u16, u8)`. Ordinary-call verification assumes their ABI
contracts; it is not a whole-callee safety or termination proof.

The retained definition uses a genuine `struct EffectObject` tag. If it is
later promoted, callers must use the compatible opaque tagged pointer
declaration rather than an incompatible `const void *` function declaration.
The normalized return permits a `u8` interface but does not uniquely establish
the original nominal return type.

## Bounded Attempts

- A `const void *` formal plus typed local also changes entry normalization
  order; the natural tagged formal restores that order.
- A postfix countdown tests the old value against zero rather than the
  decremented value against minus one.
- A signed nonnegative countdown comparison produces a different 208-byte
  register/frame arrangement.
- Explicit signed-word or byte count snapshots produce 212-byte symbols.
- A properly typed pointer-to-two-byte-row traversal produces 216 bytes.
- The retained indexed loop with a meaningful current-row pointer is closest.
  No packing, register steering, assembly, volatile accesses, or inert work
  was added.

## Verification

The last active-source check used the frozen reviewed toolkit:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/kit-reviewed-d7f9a0a/tools/match.py \
  --root /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp 0x080CD1FC
```

Result: `NOT MATCHING - bytes differ`, source plausible, complete 200-byte
symbol. The nonmatching active source and report were removed; only this
parked candidate and diagnosis remain.
