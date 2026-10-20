# 080CAF78: natural recovery, not a match

The complete ROM function is `[0x080CAF78, 0x080CB0D6)`: 350 bytes and
161 instructions, including an interior zero halfword and the object-address
literal at `0x080CB020`. It saves 32 bytes of registers and allocates eight
additional local bytes. It has eleven direct calls to nine targets.

The retained ordinary typed-entry recovery compiles to a single 342-byte
function symbol with 158 instructions, an eight-byte local frame, and the same
eleven direct calls. Its object literal is at symbol offset `0xA4`, whereas
the ROM literal is at `0xA8`. It is not byte-identical.

## Verification and differences

The reviewed `kit-reviewed-d7f9a0a` matcher was run with the standard
`agbcc -mthumb-interwork -O2` flags. It stops at:

```text
compiled symbol is shorter than the indexed span: 342 < 350
```

This is an extent rejection before the official byte comparison and
plausibility result. There is no verified matching-byte count. Separate
assembly and ELF inspection establish the candidate extent and instruction
count; they do not bypass the match gate.

The retained candidate differs in ordinary compiler scheduling and address
formation:

- The object-pointer copy follows argument normalization rather than preceding
  it; the old/new comparison also uses the opposite operand order.
- The cached flags-byte read forms its address with one fewer instruction.
- The later flags-byte clear combines the index with the action-state base and
  uses an immediate load/store offset, requiring two fewer instructions than
  the ROM's separately materialized address.
- These differences change internal alignment, literal position and branch
  displacements.

Bounded natural forms tried at the same standard flags were:

| Source form | Symbol bytes | Local frame bytes |
| --- | ---: | ---: |
| Byte view with separate original-object and slot-base locals | 348 | 16 |
| One consistent byte view with direct slot accesses | 338 | 8 |
| One byte view retaining a named slot-array base | 346 | 12 |
| Retained typed-entry view | 342 | 8 |

No optimization-flag sweep, register forcing, artificial control flow,
assembly, pragmas or volatile accesses were used. This is a local code-generation
gap, not a claim that the function is inherently unmatchable. The corrected ROM
extent must not be shortened to accommodate the candidate.

## Recovered contracts

The public interface remains `void func_080CAF78(void *, u16, u8)`. The ROM
consumes only these three arguments, normalizes the entry and slot widths,
and has no incoming stack arguments. The object must support all selected
reads, writes and helper contracts. The five-slot view reflects the established
entry layout and observed callers; it does not prove that every possible
eight-bit slot argument is valid.

The shared declaration of `g_table_08520080` is a const, unsized array of
`EffectRecord` objects containing a count byte, an unknown byte and
`u8 pairs[9][2]`. Actual agbcc layout is 20 bytes, with pairs beginning at
offset two. This describes physical storage, not a proven runtime
`count <= 9` invariant or an outer table length. No count guard, subindex
bound, null guard or `restrict` promise has been introduced.

Helper declarations preserve the audited contracts:

- `080CA7A4`: `s32(u16, u8)`.
- `080CD480`: `const u8 *(u8, u8)`, not an integer result.
- `080CD1FC`: `u8(const void *, u8)`.
- `080CD620`: `void(void *, u8)`.
- `080C8240`: `u8(void *)`.
- `080C8260`: `u8(const FlaggedObject *)`, with the exact existing
  `unknown_00[0x28]` and `u16 flags` declaration.
- `080C9540`: `u8(u16)`.
- `080CAB24`: `void(u16, u8)`.
- `080CCF44`: `void(void *, u16)`.

## Preserved mutation order

The nonzero old entry is captured before calls. Only a nonzero old entry equal
to the replacement returns early; replacing zero with zero still reaches the
later checks and final application call.

For nonzero removal, the old entry's effect record is selected before clearing
the slot. The slot is cleared before the first count/pair scan. The count and
object group are read on each iteration. A matching nonzero marker caches
the selected pair value and the object's low-seven-bit level before calling
`080CD480`; the pointer result's byte seven supplies the comparison threshold.

When the threshold and `080CD1FC` tests permit removal, the first matching
selection byte is cleared in descending address priority `0x3C`, `0x3B`,
`0x3A`. The flags byte is reloaded after those helper calls, its high bit is
cleared, and `080CD620` is called. A nonmatching `0xFF` marker separately
checks the old entry's selector-three result before clearing byte `0x3D`.

Inventory updates preserve the short-circuit order `080C8240`, `080C8260`,
then `080C9540(0x3E)`. Only when all are false are nonzero old/new entries
passed to `080CAB24` with decrement/increment modes. Finally, the replacement
entry is stored in the original slot before `080CCF44(object, entry)`.

Helper termination and arbitrary mutation behavior are not established by
the local match profile. No active source or match report is retained.
