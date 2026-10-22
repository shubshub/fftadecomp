# 0x080D1B80 — parked, not matching

The retained natural recovery has the correct complete size and tested behavior,
but six register-operand bytes differ. It is not a byte-exact match and is not an
active source or saved matching report.

## Complete-symbol evidence

- Target: `[0x080D1B80, 0x080D1C94)`, 276 bytes / 121 reachable Thumb instructions.
- Target SHA256: `7da796fea24641b0bd2b75179a41b9d8dff3cc2e8be7f5d5a1a1756d182cafaa`.
- Retained candidate: one emitted `STT_FUNC`, 276 bytes / 121 instructions; `.text` is also exactly 276 bytes.
- Linked candidate SHA256: `aa197f7f6091517586147aa3a74ca38c3d1c735d0eb92bffa6a899b6a8b35690`.
- Both contain 254 code bytes, 20 literal-pool bytes and two internal zero-alignment bytes. The next entry at `0x080D1C94` is not part of this symbol.
- Code intervals are `[0x080D1B80,0x080D1BE6)`, `[0x080D1BF8,0x080D1C44)` and `[0x080D1C48,0x080D1C94)`.
- Literal intervals are `[0x080D1BE8,0x080D1BF8)` and `[0x080D1C44,0x080D1C48)`; internal zeros occupy `[0x080D1BE6,0x080D1BE8)`.
- Frozen toolkit `2e2a664` accepts the typed data/call linkage, complete local CFG and source plausibility, then reports `NOT MATCHING - bytes differ`. There is no matching-report replay claim.

Exactly 270/276 same-position bytes and 115/121 same-address instructions agree.
The six differing instructions are:

| Address | ROM | Retained candidate |
| --- | --- | --- |
| `0x080D1BC0` | `ldrb r1,[r5,#2]` | `ldrb r4,[r5,#2]` |
| `0x080D1BC4` | `lsls r4,r0,#8` | `lsls r0,r0,#8` |
| `0x080D1BC6` | `orrs r4,r1` | `orrs r4,r0` |
| `0x080D1C1E` | `ldrb r1,[r5,#5]` | `ldrb r4,[r5,#5]` |
| `0x080D1C22` | `lsls r4,r0,#8` | `lsls r0,r0,#8` |
| `0x080D1C24` | `orrs r4,r1` | `orrs r4,r0` |

Each changes one operand byte. Both forms read the low byte before the high
byte and produce the same unsigned halfword in r4. All other instructions,
branches, calls, pool words, internal alignment and the four-byte local frame
agree. This semantic observation does not turn differing instructions into a
match.

## Bounded natural attempts

1. The retained direct scan uses `row[low] | (row[high] << 8)` for both condition
   IDs. Its complete result is 276 bytes / 121 instructions as documented above.
2. An ordinary private `static inline u16 read_condition(const u8 *bytes)`
   returning `bytes[0] | (bytes[1] << 8)` factored the two genuinely repeated
   little-endian reads. It produced 294 bytes / 129 instructions, with wider
   register-allocation and loop-address differences. That version and its
   private header were removed. Its extra 18 bytes were not counted as part of
   the 276-byte target or compared as a truncated prefix.

No original inline-helper provenance is claimed. No register forcing, forced
inline attribute, volatile access, artificial control flow, padding or manual
assembly was used, and no further compiler variants were attempted.

## Interface and ordered behavior

`u32 func_080D1B80(const u8 **output, u32 capacity, u32 filter)` is a compatible
interface, not a uniquely established original nominal type. Only the three
argument registers are consumed; there are no hidden r3 or incoming stack
arguments. The count is returned in the full word, without narrowing the
capacity or filter.

The actual callback slot at `0x0836D4B8` contains `0x03005E79`. Through the
`0x0814224C` BX-r2 thunk, the function first invokes the copied clear routine
with the output address and the wrapped 32-bit `capacity << 2` count. The
recovery uses the established `void(void *, s32)` callback interface; converting
an out-of-range unsigned count to signed is target-implementation-defined.
Only after the callback returns does it read table rows.

The scan examines at most 127 eight-byte rows beginning at the actual observed
address `0x085573F4`. A zero byte 0 skips a row. Byte 1 is either zero, meaning
wildcard, or must equal the full-word filter. Bytes 2/3 and 5/6 are little-endian
condition IDs; bytes 4 and 7 are their thresholds. The unsized byte-array
declaration does not invent an original table allocation or a preceding row.

For the first condition, IDs above `0x05FF` call `func_080C95A8(id - 0x0600)`
and require the returned byte to be at least the subsequently loaded threshold.
Other IDs really call `func_080C9540` twice unless the first call's result of 1
and threshold 0 reject early. The second call's zero result with threshold 1
also rejects. First-condition ID zero is not a bypass.

For the second condition, IDs above `0x05FF` instead require the byte-helper
result to be strictly below the subsequent threshold. ID zero bypasses the
test entirely. Other IDs call the bit helper once, cache its byte result, and
reject result/threshold pairs 1/1 or 0/0. Thresholds are not artificially
restricted to Boolean values. Conditional threshold loads and the first
condition's repeated calls remain present.

An accepted row pointer is stored, the output cursor and count advance, and
the remaining capacity is decremented. The scan stops when that decrement
produces zero or all 127 rows have been visited. There is no final terminator
store and, importantly, no initial zero-capacity guard.

## Behavioral evidence

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/d1b80-inventory/check_recovery.py`:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/d1b80-inventory/check_recovery.py
```

It freshly compiles this Parked source in an isolated disk-backed root with
all current headers and frozen toolkit `2e2a664`, verifies the single complete
ELF function, and independently checks each execution against a byte-level
operation model. It does not replace any executed helper with that model.

- 146 target/candidate pairs, or 292 executions, pass. Eight pairs use the
  actual bounded table bytes from the ROM; the remaining 138 use explicitly
  synthetic table rows. All RAM fixtures are synthetic.
- All 121 target and 121 candidate caller instructions are covered.
- Actual `0x080C9540` executes in 3,719 paired calls and covers all 22
  instructions; actual `0x080C95A8` executes in 77 paired calls and covers all
  eight instructions.
- The actual thunk and the actual 50-byte clear routine copied from
  `0x08A38A2C` to `0x03005E78` execute in all 146 pairs. Clear coverage is 19/25
  instructions: aligned pointer outputs and four-byte-multiple counts do not
  exercise its byte-tail/unaligned paths. No helper is stubbed or modeled.
- Every pair agrees on the full ordered nonstack data-access trace, including
  ROM literal and callback-slot reads; helper call order and arguments; all
  EWRAM and nonstack IWRAM; return value and return target; SP and r4-r11.
  Instruction fetches and stack traffic are not claimed identical traces.
- Cases exercise both bit values, condition IDs 0/1/7/8/`0x05FF`/`0x0600`/
  `0x0601`/`0xFFFF`, threshold boundaries and non-Boolean thresholds, wildcard
  and full-word filters, skipped/mixed/final rows, and capacity stops at
  1/2/126/127/128/256.
- Six pairs explicitly probe zero or large wrapped capacities as machine-domain
  fixtures with oversized mapped output storage. They are not evidence that
  a caller-supplied allocation of that capacity is valid.

## Limits

The intended C domain requires suitably aligned writable output-pointer
storage, readable selected table/state bytes, and a callback count compatible
with the available destination storage. For ordinary capacities the clear
needs `capacity * 4` writable bytes. Capacity zero still permits up to 127
pointer stores after its count underflows; large capacities may wrap the clear
size or convert it to a nonpositive signed value. No guard was added to hide
these observed behaviors.

The fixtures use output storage disjoint from table and helper-state storage.
They do not prove arbitrary aliasing, invalid pointers, MMIO/concurrent
mutation, arbitrary callback replacement or universal termination. The local
row loop is bounded when its helpers return. Entry evidence is structural
index/prologue/closed-CFG evidence, not an established incoming call reference.
