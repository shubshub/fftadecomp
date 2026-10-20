# 080CE490: bounded natural recovery, not byte-identical

The complete target is `[0x080CE490, 0x080CE4DC)`: 76 bytes and 37 Thumb
instructions, with no literal pool or alignment gap. It saves 12 bytes of
registers, allocates no local frame, and has one direct call at `0x080CE4D2`
to `func_080CD774`. The indexed entry and complete CFG provide structural
entry evidence; no inbound-reference provenance is claimed.

## Measured difference

The published frozen toolkit `98fb667`, using agbcc with
`-mthumb-interwork -O2`, accepts the complete compiled symbol and reports
plausible source, but **NOT MATCHING**: 71/76 bytes and 32/37 instructions.
The candidate is also exactly 76 bytes and 37 instructions. Its only
differences are five register-operand bytes:

| Address | Target | Candidate |
| --- | --- | --- |
| `080CE492` | `adds r4, r0, #0` | `adds r3, r0, #0` |
| `080CE4A0` | `movs r3, #0x80` | `movs r4, #0x80` |
| `080CE4A4` | `ands r0, r3` | `ands r0, r4` |
| `080CE4AC` | `ands r0, r3` | `ands r0, r4` |
| `080CE4D0` | `adds r0, r4, #0` | `adds r0, r3, #0` |

The target keeps the object pointer in `r4` and the high-bit mask in `r3`;
the compiler assigns those roles to `r3` and `r4`, respectively. Branches,
loads, narrowing, caps, call target, saved-register set, and returns otherwise
match. No following function bytes are included in either extent.

Three natural forms were tried, all producing the same candidate bytes:

1. Two early returns testing the first and second bytes against literal `0x80`.
2. One enclosing short-circuit guarded block using literal `0x80` for both tests.
3. The retained guarded block with a shared `u8 blocked = 0x80` mask.

No register constraints, forced storage, assembly, volatile accesses,
optimization controls, dummy operations, or artificial control flow were used.
Further register-steering attempts were not pursued.

## Interface and behavior

The recovery uses `void func_080CE490(u8 *data, u8 enabled)` and the existing
compatible helper declaration
`void func_080CD774(u8 *data, u8 first, u8 second)`. The caller consumes only
the low byte of the enable argument. Void is a natural interface choice, not
a uniquely established original nominal return type.

Both `data[0xDA]` and `data[0xDB]` are read, in that order, before either
high-bit test. If either byte has bit `0x80` set, there is no helper call or
data write. Otherwise a nonzero low-byte enable adds three to the first byte;
zero adds three to the second. The selected value is converted to `u8` before
the upper cap of six, then both values are passed to the helper. The preceding
high-bit guards mean the selected addition cannot overflow a byte on this
path, but the observed narrowing is retained.

The actual helper subtracts the smaller value from the larger, leaving the
other zero. It writes byte `0xDA`, updates bit `0x20` of byte `0xEA`, writes
byte `0xDB`, then updates bit `0x40` of byte `0xEA`. Each helper flag update in
the compiled ROM performs one flag-byte read and one write, preserving other
bits. There are no helper stubs in the behavioral checks.

The valid domain requires a nonnull live pointer with readable bytes `0xDA`
and `0xDB`; an accepted path also requires writable bytes `0xDA`, `0xDB`, and
`0xEA`, with `0xEA` readable. No original allocation size, object identity,
general null safety, or inbound-call contract is inferred.

## Verification

A fresh frozen-toolkit `--no-write` compile confirmed the complete-symbol
nonmatch above. The active source and unverified active report were removed;
this recovery is not counted as a match and has no matching-report replay
claim.

An author-side Unicorn check ran 1,024 paired executions of the actual caller
and the compiled candidate, both executing the complete actual 124-byte
`080CD774` helper. Synthetic RAM supplied counter bytes from
`{0, 1, 3, 6, 7, 127, 128, 255}`, enables from
`{0, 1, 2, 128, 255, 0x100, 0xFFFFFF00, 0xFFFFFF01}`, and flag bytes
`{0x15, 0xEA}`. Unrelated incoming registers and condition flags varied.

All cases agreed with an independently specified operation/access model and
with each other: exact ordered data reads and writes, helper arguments and
call presence, complete synthetic RAM contents, return destination, restored
SP, and preserved `r4` through `r11`. Coverage reached all 37 target caller
instructions, all 37 candidate instructions, and all 62 helper instructions.
These are bounded synthetic-storage tests, not a proof of every game object's
allocation or an independent review.
