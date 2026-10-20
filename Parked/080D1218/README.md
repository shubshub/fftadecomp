# 080D1218: bounded recovery, not a match

## Complete target and retained result

The complete Thumb function is `[0x080D1218,0x080D17C4)`: 1452 bytes,
630 reachable instructions, 1286 instruction bytes, 40 literal words and
three internal zero halfwords at `0x080D152E`, `0x080D15B2` and `0x080D1692`.
The next function begins immediately at `0x080D17C4`; no next-function bytes
are included. The complete target SHA256 is
`6df3af35686aebee62c32f4e7a28b12fd094fe0b20a7fa47db0cc78efcf4d7ac`.

The retained source compiles with agbcc `-mthumb-interwork -O2` to exactly
one emitted function of 1436 bytes and 617 instructions. Its whole `.text`
is also 1436 bytes: 1260 instruction bytes, 41 literal words and 12 internal
alignment bytes. There are no separately emitted inline helpers or omitted
function suffixes. The diagnostically linked whole-symbol SHA256 is
`a65e99f89b706f7106a550c3579b17ca3db62a8eed07e5219ca75d701eb194ae`.
Only 183 same-position bytes and 28 same-address instructions agree with the
target. The complete 1452-byte comparison therefore has 1269 differing or
missing byte positions, including the 16-byte size shortfall.

Frozen toolkit `2e2a664` rejects the natural generated `__modsi3` reference:
`call target must be an undefined addressed function`. Diagnostic linking
alone binds that alias to the audited signed remainder at `0x08142950`.
This is not an official runtime proof, report replay, or MATCH. Both complete
bodies pass the separate raw structural CFG check with exact direct-call
targets; that check is not the official typed compilation gate.

No active source, private include, or match report is retained for this
address. Source and private header pass the frozen plausibility check.

## Source recovery and bounded attempts

The compatible interface is
`u8 func_080D1218(const SelectionRecord **output, u32 requested, u32 category)`.
The count and category are full-word inputs. No hidden fourth or stack input
is consumed. The nominal original typedefs and count signedness are not
uniquely established. The target saves 32 bytes and allocates four local
bytes; the retained build saves 32 bytes and allocates eight local bytes.

The two passes preserve list order, selecting definition kinds 4/5 before
2/3. Each rejects the wrapped-u16 identifier interval `0x150..0x166`, nonzero
record category, definition flag `0x400`, and a mismatching full category.
The return is the low byte of the emitted count PLUS a first-pass `0x80`
marker, not an OR. Zero count and an initially null head return zero.

When capacity remains and category-row byte 1 has bit `0x08`, a 16-byte
scratch record is cleared and initialized from the 38-byte definition row,
the counter getter and `(s16)RNG % 0x136`. Replacement priority remains the
first excluded identifier, a free record, `080CEF78(2,2)`, then
`080CEF78(0,3)`. Removal resolves the first matching data pointer in the
64-node pool rather than assuming the located list node is that pool entry.
Unlink, clear, data-null store, free-record search, copy, free-node search,
tail append and output store remain ordered. No pool-failure guard is added.

The private ordinary inline helpers express repeated identifier decoding,
pool searches, unlinking and append operations. Inlining is a recovery
inference, not proven original source provenance. There are no forced-inline
attributes. `SelectionRecord` and `Node` match the existing parked `080CEF78`
interface. Canonical `ScriptEntry` is included unchanged. Existing globals
remain opaque `u8[]` or their existing compatible table declarations.
The machine relation `0x02002CB4 - 0x3EC == 0x020028C8` is not converted into
an invented encompassing C object; head access uses the observed field from
the existing `0x02000000` backing view.

Three bounded natural representations were compiled:

1. Direct signed-remainder expression with short-circuit flag expressions:
   one 1420-byte function.
2. Separate signed-word RNG staging followed by remainder: 1416 bytes,
   609 instructions. This removes a redundant generated signed-halfword
   normalization after the runtime call.
3. Retained explicit `u16` decoded flag locals within the existing guards:
   1436 bytes, 617 instructions. This makes the observed flag-field width
   explicit, without changing its meaning or adding artificial accesses.

The remaining mismatch includes register allocation, frame size, branch
layout, literal placement and memory-read elimination. In particular, agbcc
omits definition byte `+0x41` because only bit `0x400` of the decoded word is
tested; the target reads bytes `+0x41` then `+0x42`. No volatile access,
barrier, invented getter, or forced lifetime was added to prevent this.

## Bounded actual-code verification

126 paired fixtures produced 252 target/candidate executions. Every helper
executed its actual machine instructions, with no helper stubs:

- Counter getter `080C95A8`, RNG `08002804`, signed remainder `08142950`.
- Selector `080CEF78`, using only its actual modes 2 and 0.
- Both real BX thunks, `0814224C` and `08142250`.
- Clear `[0x03005E78,0x03005EAA)`, copied from ROM
  `[0x08A38A2C,0x08A38A5E)`, and forward copy
  `[0x03005EE8,0x03005F26)`, copied from ROM
  `[0x08A38A9C,0x08A38ADA)`.

RAM, lists and pool records were explicitly synthetic. Six fixtures retained
the actual ROM definition/category/script records; other fixtures patched
specific synthetic table fields to exercise branches. Cases cover zero and
large requested counts, full categories through 256, both passes and their
capacity boundaries, excluded-ID endpoints, flag rejection, first/middle/last
pool slots, head/middle/tail removal, single-node replacement, full-pool
selector priorities and failure, counter values and RNG remainder boundaries.
Synthetic long lists of 127 through 260 entries exercise addition and low-byte
return wrap; these fixtures do not establish the original list allocation.

Both bodies agree with an independent final-state/call model on return value,
whole synthetic EWRAM, non-stack IWRAM, RNG state, call arguments and order.
All paired ordered non-stack writes agree. R4-R11, SP and return control are
preserved. Per body, the tests execute 91 clear calls, 65 copies, 72 counter
reads, 72 RNG calls, 72 remainder calls and 26 selector calls. Maximum observed
stack depth including actual callees is 56 bytes for the target and 60 for
the candidate.

Exact read traces differ in 60 pairs. The first demonstrated difference is
the target read at definition byte `0x0855AED3` (`+0x41` of row 1), while the
candidate proceeds to `0x0855AED4`. Thus this is not an exact ordered-read
recovery and not a claim about MMIO or concurrent mutation. Other differences
are not excluded by final-state agreement. The reproducer compares read
traces separately rather than silently ignoring them.

Coverage is 607/630 target instructions and 598/617 candidate instructions.
Uncovered branches include pool-search failure/null dereferences, redundant
capacity checks, a later-null-head path, and mode-2 head-unlink/empty-append
paths not reached by these well-formed unique-data lists. This is not complete
path coverage. Actual helper coverage is clear 19/25, copy 24/31, counter 8/8,
RNG 10/10, remainder 92/102 and selector 87/104. Aligned 16-byte callbacks do
not exercise their general byte-tail or unaligned paths.

## Domain and reproduction

The recovery requires valid typed record/node objects, readable referenced
tables, writable output capacity, appropriate pool resources and functioning
callbacks. The local backing-state cast and fixed RAM views are target ABI
descriptions, not a portable strict-aliasing or allocation proof. Cyclic lists
need not terminate. Failure searches can produce null pointers subsequently
dereferenced by the original code; no safety claim or added guard is made.
The actual RNG produces `0..32767`, so its signed-halfword conversion is
lossless on these calls and the constant remainder divisor is nonzero.
General out-of-range signed narrowing remains target-implementation-specific.
Entry evidence is the indexed prologue, closed CFG and adjacent entry, not a
discovered inbound reference.

The address-scoped reproducer is retained at
`/home/user/.codex-work/ffta-ulw/080D1218-08/check_recovery.py` for independent
review. It recompiles this parked source/header, performs diagnostic-only
typed runtime linking, checks the whole ELF symbol and runs the paired tests:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 /home/user/.codex-work/ffta-ulw/080D1218-08/check_recovery.py
```

Only its text and compact evidence log are retained; generated preprocessor,
assembly, object and ELF artifacts are removed after verification. The script
regenerates those exact address-scoped files when rerun. No ROM binary or
disassembly is included in this parked recovery.
