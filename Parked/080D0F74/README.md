# 080D0F74 — recovered, not byte-identical

## Complete symbol and measured difference

The complete ROM body is `[0x080D0F74, 0x080D1218)`, 676 bytes and 290
reachable Thumb instructions. It contains 610 code bytes, fourteen literal
words (56 bytes), and five internal zero alignment halfwords (10 bytes).
There is no trailing external alignment in this span: the final literal at
`0x080D1214` ends immediately before the separate prologue at `0x080D1218`.
The whole target SHA-256 is
`bb1da80879c8374aad53959a687511eacb580901fece5c1f071253b789e55049`.

The internal zero halfwords are at `0x080D100A`, `0x080D104E`,
`0x080D107E`, `0x080D111E`, and `0x080D113A`. Literal words are at
`0x080D100C`, `0x080D1010`, `0x080D1014`, `0x080D1050`,
`0x080D1080`, `0x080D10A4`, `0x080D1120`, `0x080D1124`,
`0x080D113C`, `0x080D1184`, `0x080D1188`, `0x080D118C`,
`0x080D1190`, and `0x080D1214`.

The retained candidate emits one complete `STT_FUNC`, no other function
text, and no residual linked relocations: 632 bytes / 266 instructions,
comprising 562 code bytes, fourteen literal words, and fourteen alignment
bytes. Its complete linked SHA-256 is
`38514ea39df818fc49a96705c48104ba5dfebf1d52ea5b3b835e847da261552a`.
Only 25 corresponding byte positions agree; 607 positions differ and the
candidate lacks the final 44 target positions. This positional comparison
is not an instruction-alignment score.

The frozen `2e2a664` matcher correctly rejects it:

```text
compiled symbol is shorter than the indexed span: 632 < 676
```

The candidate is not trimmed, padded, or compared against a shortened ROM
prefix. Both full bodies pass the existing structural CFG check. The failure
is a genuine code-generation mismatch, not an unsupported verifier feature.
No active source, header, or successful report is retained.

## Natural recovery and contracts

The compatible interface is `void func_080D0F74(void *object)`. Only incoming
`r0` is consumed. The ROM saves 32 bytes of registers and uses one four-byte
local; the candidate saves 28 bytes and needs no local frame. Neither consumes
an incoming stack argument. Nominal original parameter names, unused formals,
and source return typedef are not uniquely established.

The object is a readable/writable byte view through offset `0x05`. When byte
`0x03` has bit `0x80` clear, the function invokes the callback loaded from
`0x0836D4B8` with `(object, 6)`. Otherwise it clears that bit first and packs
a nine-bit identifier from bytes `0x04` and `0x05` bit zero.

For a nonzero identifier, it selects a `0x46`-byte definition at
`g_table_0855AE4C`. Byte `0x05 & 0xFE == 0xC8` first sets flag
`identifier + 0x2FF`. Exactly two adjustments follow. Each iteration reloads
object byte `0x05`; a zero masked value chooses adjustment slots two/three,
otherwise slots zero/one. Each four-byte adjustment starts at definition
offset `0x12`: two identifier bytes, operation byte, and operand byte.

- Operation one with index above `0x05FF` reads counter `index - 0x600`,
  adds the signed operand, narrows to `u16`, then applies an unsigned upper
  cap of 255. Negative sums therefore wrap before the cap; no lower clamp
  is introduced. The setter receives the resulting low byte.
- Operation two in the same range compares the unsigned counter with the
  signed operand. A greater counter subtracts it; otherwise the result is
  zero. The result narrows through `u16` to `u8`, without an added upper cap.
- Operation three writes the operand byte directly for a high index. For
  index at most `0x05FF`, it sets or clears the flag according to operand
  nonzeroness. Indices `0x0587..0x059E` whose resulting flag is clear then
  call `080CFA48` with the low byte of `index + 0x80`, hence `0x07..0x1E`.
- Other operations, and low indices for operations one/two, do nothing.

After the adjustments, the identifier is reloaded. Identifier `0x6E` tests
counter `0x81`: values at most three set flag `0x582`, other values set flag
`0x583`; counter `0x81` is then cleared. Identifier `0x2E` clears flag `0x36D`.

Next the object clears byte `0x02` bit `0x40`, sets its bit `0x20`, and sets
byte `0x01` bit `0x80`. A reloaded nonzero identifier searches the linked list
at state offset `0x28C8` for the first matching ten-bit record identifier.
Nodes have record pointer at offset zero and next pointer at `0x08`, stride
`0x0C`. The selected record's byte `0x02` clears mask `0x1C`.

The ordinary private inline lookup returns null on exhaustion. Its caller
deliberately retains the unconditional record access: missing matches read
address `0x00000002`. This is a fault-domain boundary, not valid C behavior
and not a reason to insert a new guard. Cyclic lists are not assumed to
terminate. Ordinary inlining is a plausible recovery, not historical proof.

Finally object byte `0x05` becomes `(old & 1) | 0xF0`. An eight-bit index
packed from byte `0x02` bit seven and byte `0x03` low seven bits selects the
canonical twelve-byte `ScriptEntry`; its `unknown_00` byte goes to
`08036330`. Object byte `0x02` is reloaded after that call, and its low five
bits are replaced by the result's low five bits.

The source uses the existing opaque `extern u8 g_state_02000000[]`, the
compatible unsized `const u8[][0x46]` definition declaration, and unchanged
canonical `script_entry.h`. The local state view describes only the observed
head offset. No total global allocation, table extent, record count, no-alias
contract, or general memory safety is inferred. The signed-byte conversion
uses the target compiler's signed-eight-bit representation; this is not a
portable claim for every C implementation.

## Dependencies and real execution

Existing helper contracts are `u8 C9540(u16)`, `void C9574(u16,u16)`,
`u8 C95A8(u16)`, `void C95C0(u16,u32)`, and `u8 36330(u8)`.
The already audited, separately Parked `CFA48` has compatible `void(u8)` ABI.
Its actual ROM body, not its nonmatching recovery, is used in these tests.
Within this caller, indices `0x07..0x1E` select pristine CFA48 base bytes
25, 35, 40, or 255. Thus that helper's actual signed remainder divisor is
positive on the tested caller paths. This does not establish its unrestricted
input contract or certify a future C implementation.

The callback ROM slot contains `0x03005E79`. Tests execute the real
`0814224C` thunk and the actual fifty-byte clear routine copied from
`[0x08A38A2C,0x08A38A5E)` to `[0x03005E78,0x03005EAA)`.
The recovered callback uses a word-sized positive count six; its original
nominal count signedness is not uniquely established. The real RNG at
`08002804` and signed remainder at `08142950` execute when CFA48 is called.
No helper return or callback is stubbed.

## Bounded attempts and behavioral evidence

Both attempts used standard agbcc `-mthumb-interwork -O2`:

1. Retained direct byte-field expressions and meaningful inline first-match
   lookup: 632 bytes / 266 instructions.
2. Ordinary inline accessors for the repeated nine-bit identifier and signed
   adjustment operand, plus the same lookup: 636 bytes / 267 instructions.
   These additional accessors were removed in favor of the simpler recovery.

The ROM separately hoists the operation and operand bases, stores one base in
its local frame, and keeps another high register. The candidate reuses one
adjusted row pointer, uses signed-byte loads instead of separate extension
sequences, and folds masks and address arithmetic differently. Save sets,
register assignments, conditional selection, branch/literal positions, and
alignment consequently differ. No forced storage, artificial field layout,
register allocation, alignment, or control flow was added.

The retained reproducer is
`/home/user/.codex-work/ffta-ulw/080D0F74-74/check_recovery.py`:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080D0F74-74/check_recovery.py
```

It freshly compiles and typed-links the full candidate, checks one function,
complete text and own-file plausibility, probes target-compiler layouts, and
reproduces the official short-symbol rejection in an isolated `--no-write`
root. Target layouts are node size/alignment `0x0C/4`, record pointer offset
zero, next offset `0x08`, state head offset `0x28C8`, and ScriptEntry size
`0x0C` with `unknown_00` at zero.

There are 880 paired fixtures / 1760 executions: 877 returning pairs, two
missing-record fault pairs, and one instruction-budgeted cyclic-list pair.
RAM is synthetic. Twelve fixtures retain pristine definition rows; the
remainder explicitly replace adjustment records to exercise operation/index/
operand boundaries. CFA48's auxiliary table, ScriptEntry data, callback slot,
and all helper code remain actual ROM. Cases include inactive clearing,
zero identifier, both adjustment banks, special identifiers, negative
operands, unsigned wrap then cap, maximum counter index, duplicate IDs,
first/last matches, object/record byte aliases, and a setter alias that changes
object byte `0x05` before the second adjustment selection.

Both binaries agree with the independent mutation/call oracle and each other
on whole synthetic RAM, RNG state, helper arguments and order, ordered writes,
and exact ordered non-stack data reads. No read-footprint difference was
observed in the returning or fault cases; the budgeted cycle agrees on the
common read prefix. All returns preserve r4-r11 and restore SP/return control.
The two null accesses are explicit machine-code comparisons outside defined
C semantics. The cycle check is finite evidence, not a general termination
theorem or unrestricted alias-safety claim.

Coverage reaches all 290 target and 266 candidate instructions. Real helper
coverage is RNG 10/10, category getter 12/12, flag getter 22/22, flag setter
23/23, counter getter/setter 8/8 each, CFA48 59/60, signed remainder 92/102,
thunk 1/1, and copied clear 25/25. CFA48's zero-result replacement is not
reached with these actual positive bases; the remainder's excluded sign/zero
paths are not fabricated. Generated binaries and consumed disassembly
artifacts are removed; only the small reproducer remains in scoped scratch.
