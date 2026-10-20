# 0x080CF118

Status: natural recovery, not byte-identical. No MATCH report or promotion is
claimed. The retained candidate also has a different ordered read footprint.

## Complete boundary

The actual function occupies `[0x080CF118, 0x080CF310)`: 504 bytes and 234
reachable Thumb instructions. Its instruction regions are
`[0x080CF118, 0x080CF20E)` and `[0x080CF21C, 0x080CF300)`, totaling 474 bytes.
The zero halfword at `0x080CF20E` is internal alignment. Seven required literal
words occupy the remaining 28 bytes:

| Address | Value |
| --- | --- |
| `0x080CF210` | `0x0855AE4C` |
| `0x080CF214` | `0x02002B08` |
| `0x080CF218` | `0x0836D4B8` |
| `0x080CF300` | `0x0000FFFB` |
| `0x080CF304` | `0x02000080` |
| `0x080CF308` | `0x02002E34` |
| `0x080CF30C` | `0x0836D4B8` |

The single return is at `0x080CF2FE`. The following indexed function starts at
`0x080CF310`; its bytes are not part of this target. The target saves 32 bytes
of registers and allocates another 12 bytes for local values. No incoming or
outgoing stack arguments are observed.

Target SHA-256:
`ab9b25437c49470113051305eb045eac22ce6a7ce76128dae99019215aaf6c8f`.

## Recovered contract and order

The compatible retained interface is `void(u8 *data, u8 enabled)`. Only the
pointer and low eight bits of the second argument are consumed; incoming
`r2`, `r3`, and stack arguments are not used. This does not identify an original
typedef or prove there were no unused formal parameters.

- The input identifier is assembled from byte `+0x00` and the low two bits of
  byte `+0x01`. It initially selects a 70-byte ROM record at `0x0855AE4C`.
- Input bytes `+0x04` and `+0x05` are visited in that order. Each nonzero value
  is searched among 64 four-byte records at `0x02002B08`. The first record
  matching byte `+0x00` and halfword identifier `+0x02` has its halfword
  `+0x02` cleared, then its byte `+0x01` cleared.
- When enabled, ROM record bytes `+0x36` and `+0x37` and the assembled field at
  `+0x41/+0x42` control two independent region-operation paths. Local masks
  `0x0F` and `0xF0` suppress repeated calls on those respective paths. The
  second comparison reloads the matched record byte after the first possible
  call, rather than assuming that call left it unchanged.
- Input byte `+0x05` is cleared before byte `+0x04`.
- A 24-entry scan at `0x02000080` uses stride `0x108` (264 bytes). Every
  iteration reloads the input identifier. Matching halfword `+0x16` (22) is
  cleared before bit `0x0004` is cleared in halfword `+0x28` (40).
- If the initially selected ROM record's byte `+0x02`, masked by seven, is
  one, five six-byte entries at `0x02002E34` are searched for their nine-bit
  identifier. A failed search still selects the fifth entry. That entry's
  byte `+0x02` gains bit `0x40`, byte `+0x04` becomes zero, and bit `0x01` in
  byte `+0x05` is cleared. Its previously read byte `+0x02` bit `0x20`
  controls the final region-operation call.

The three actual BL sites are `0x080CF1C0`, `0x080CF202`, and `0x080CF2EC`.
They use `_call_via_r2` at `0x0814224C`, whose actual thunk is `bx r2`.
The pointer at `0x0836D4B8` is `0x03005E79`. Its copied Thumb body
`[0x03005E78, 0x03005EAA)` comes from ROM
`[0x08A38A2C, 0x08A38A5E)` and clears the requested positive byte count.
The observed arguments are `(record, 4)`, `(record, 4)`, and `(entry, 6)`;
the source uses the compatible destination/signed-count callback type.

## Attempts and remaining differences

Two bounded natural forms were compiled with ordinary
`agbcc -mthumb-interwork -O2`:

1. A `void *` formal with a byte-view local and direct assembled flag tests.
2. The retained byte-pointer formal and explicit `u16` locals for the assembled
   flag fields before their mask tests.

Both symbols were 448 bytes, 56 bytes short of the actual function. There was
no compiler-flag sweep, forced inline helper, packed layout, assembly,
`volatile`, artificial lifetime or register constraint.

The retained ELF contains exactly one function: 448 bytes and 206 reachable
instructions. Its linked whole-symbol SHA-256 is
`5c0ba5a61fc3c9b86e84cfe94f71e5415b36a76624d8f0898e80390a1eaa445a`.
Against the target, 35 bytes agree at the same offsets, 413 common-position
bytes differ, and 56 target bytes have no candidate counterpart. Ten
instructions agree at the same addresses. These positional counts are
diagnostics, not a match score or a relocated-equivalence claim.

Important differences include elimination of the ROM record's upper-byte
reads at `+0x42`, reordered field/identifier reads, hoisted identifier
assembly in the final search, and reuse of a previously loaded entry byte
`+0x05` instead of the target's reload after stores. Stack/register allocation,
loop code, branches and pool positions also differ. No read barriers or other
steering were introduced to force the target's accesses.

The normal frozen `kit-reviewed-2e2a664` matcher rejects the source before
comparison with:

```text
compiled symbol is shorter than the indexed span: 448 < 504
```

A separate compiler-only diagnostic verified the linked candidate's supported
fixed-frame CFG and named-data literals. The scoped strict plausibility check
reported no findings. Neither diagnostic bypasses the full-symbol-size gate.

## Bounded behavioral evidence and limits

There were 364 paired actual-target/candidate cases, or 728 executions. They
used the actual call-via-register thunk and actual copied 50-byte clear
routine, not callback stubs. Each side executed 254 clear calls: 170 calls of
four bytes and 84 calls of six bytes. All 234 target instructions, all 206
candidate instructions and all 25 clear-routine instructions were covered.

Cases include zero and nonzero enable values with upper argument bits,
identifiers `0`, `1`, `0x101`, and `0x3FF`, skipped or missing binding values,
first/last matches, duplicates, both suppression masks, the post-clear reload
case, every final-slot match position and exhaustion, and both category paths.
Twenty-eight additional machine-level alias cases place the input within a
binding, scene identifier/flags, or selected-entry region. Those alias cases
do not establish that every such arrangement is valid under the C type rules.

Every pair agreed on final synthetic RAM contents, exact ordered data writes,
callback arguments and call order, preserved `r4-r11`, restored SP, and return
control. All 364 pairs differed in their ordered read trace and consequently
their complete read/write trace. The candidate is therefore not claimed to
preserve the target's complete memory-access sequence.

Fixtures used synthetic RAM and synthetic selected ROM-table records to cover
branches. They do not prove original allocation extents or unrestricted
pointer validity. The declared `State` and opaque `SceneRecord` match the
existing global declaration; the local `SceneFields` view still requires an
appropriate aligned storage/effective-type contract. A portable strict-aliasing
claim would need coordinated canonical field recovery, not emulator success.
No new null guard, bounds guarantee, or alias restriction is asserted as an
original contract. Entry evidence is the indexed prologue and complete CFG;
no inbound-reference provenance was established in this task.
