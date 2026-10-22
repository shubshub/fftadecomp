# 08064CCC: natural recovery, not a match

## Complete target and candidate

The actual ROM function is `[0x08064CCC, 0x08064DB4)`: 232 bytes and
83 instructions, including 180 code bytes and 52 literal-pool bytes.
Complete target SHA-256:
`469f6219bb3b55311fa74033dcfe80492a933bc7aaf6db13aeabd637222a55dd`.

The retained natural C compiles with agbcc `-mthumb-interwork -O2` to one
complete 236-byte function containing 84 instructions. Its linked symbol
SHA-256 is `4ff1dc2abbafbbb86aa8a3ce35b89144525c3c57dd5392ae9e995634a2e93181`.
Only 159 of the first 232 byte positions agree. This is not an exact match,
and no active source or match report is retained for it.

Two meaningful source organizations were tried, both producing 236 bytes
and 84 instructions. The retained first-use-local organization saves eight
bytes and reserves 24 outgoing argument bytes; the ROM saves 12 and reserves
24. The compiler reloads constant one near the final reset instead of
preserving it in r5, and introduces an internal zero halfword. Register
allocation, instruction positions and literal references consequently differ.
No fabricated shared constant, forced register, alignment directive, volatile
access or artificial control flow was introduced. No optimization-flag sweep
or verifier change was attempted; this is not a claim of inherent
unmatchability.

## Recovered behavior and boundaries

The routine initializes control/global fields, conditionally refunds 5000
resource units modulo 32 bits, releases a context payload, resets display
state, allocates an object, passes ten explicit initializer arguments, updates
controls and resets the live script state to count one, entry one and current
state `0x34`. Global pointer reloads and the absence of an allocation-failure
guard are preserved.

The locally grounded views have measured target-compiler layouts:
`ExtendedScriptState` size `0x888`, flags `+0x54`, context `+0x6C`, object
`+0x884`; `ReleaseContext` size 12, payload `+8`; `StateView` size `0x3C2C`,
resource `+0x1F64`, fields `+0x219E/+0x3C24/+0x3C28/+0x3C2A`.
These are access descriptions, not proof of original allocation, universal
type compatibility or safety for arbitrary pointers.

## Bounded verification

A fresh separate typed link resolves all seven calls and the existing named
data binding, with no remaining relocations. Plausibility and target layout
checks pass. The diagnostic link does not bypass the failed exact-byte gate.

The retained author harness was repaired after its worker hit a usage limit:
its linker call had omitted the existing ROM/data-map arguments. Neither the
candidate C nor the verifier was changed. A fresh root rerun passes 199 paired
cases / 398 executions: 192 ordinary synthetic-storage pairs and seven
explicit machine-only alias/full-pointer-model pairs. All 83 ROM and 84
candidate instructions execute. Ordered nonstack data effects, call arguments,
outgoing stack arguments, complete RAM/I/O images outside the stack and saved
register/SP behavior agree with a separate effect oracle. Literal-read traces
differ in all 199 pairs and are not claimed equal.

Actual ROM helpers execute for `080C746C`, `08022854`, `08022840`, `080C95C0`,
`08004C40`, `0801339C`, `0802A2C0` and the SVC wrapper. `08007170`, `08007138`
and `0801174C`, BIOS fill and hardware memory are explicitly modeled. No real
allocator, initializer, BIOS, hardware-timing or universal termination proof
is claimed. Machine-only cases do not establish valid C behavior outside the
declared storage domain.

The address-scoped reproducer is retained locally as
`08064CCC-author/check.py`; it accepts this Parked source path as its first
argument. Its temporary build files are disk-backed and self-cleaning.
