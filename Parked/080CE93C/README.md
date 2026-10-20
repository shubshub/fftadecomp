# 080CE93C: natural recovery, not a match

## Complete target and interface

The actual function is `[0x080CE93C, 0x080CEA7E)`: **322 bytes and 141
instructions**. Code occupies `[0x080CE93C, 0x080CEA40)` and
`[0x080CEA5C, 0x080CEA7E)`, totaling 294 bytes. The intervening 28 bytes are
seven literal words:

| Address | Value |
| --- | --- |
| `0x080CEA40` | `0x020021A0` |
| `0x080CEA44` | `0x000005A1` |
| `0x080CEA48` | `0x000005A2` |
| `0x080CEA4C` | `0x000005A3` |
| `0x080CEA50` | `0x000005A9` |
| `0x080CEA54` | `0x08528556` |
| `0x080CEA58` | `0x02001F6C` |

There is no internal alignment gap in the target. The zero halfword beginning
at `0x080CEA7E` is external. The target saves 32 bytes of registers and allocates
four additional bytes for the captured count. Six direct BL sites address three
helpers; no incoming stack arguments or hidden register arguments are consumed.

The compatible interface is `void func_080CE93C(u8 reset)`. Only the low byte of
the incoming argument matters. The return-address use of `r0` is not evidence
of a scalar return value. Entry evidence is the indexed prologue, the closed
body, and the preceding function boundary; no incoming call-site claim is made.

## Recovered behavior and contracts

When reset is nonzero, the function calls `void func_080C9574(u16, u16)` with
`(0x5A1, 0)`, `(0x5A2, 0)`, `(0x5A3, 0)`, and `(0x5A9, 0)` in that order.
It then captures the low-16-bit result of `u16 func_080CE8A8(void)` once, before
scanning records. This uses the callee's grounded ROM contract, not a claim that
its separate C recovery is matched.

The table at `0x08528556` has a 16-byte observed row stride. Rows 1 through 64 are
examined in ascending order. This observed scan does not establish a larger
table allocation or validate arbitrary global state.

- Nonzero row byte 1 requires state byte `+0x14` to meet its lower bound.
- Nonzero little-endian row halfword `+2` requires the unsigned halfword at
  `0x02001F6C` to meet its lower bound.
- Nonzero little-endian row halfword `+4` requires the captured count to meet
  its lower bound.
- Row bytes `+6` through `+0xD` specify eight optional thresholds against state
  bytes `+0x16`, `+0x18`, through `+0x24`. If any threshold is nonzero, **at least
  one**, not necessarily all, must pass.
- A nonzero little-endian row halfword `+0xE` must pass
  `u8 func_080C9540(u16 bitIndex)`.

The first surviving row writes state byte `+0x26`: row byte 0 if at least one
condition qualified, otherwise zero. If all 64 rows are rejected, the previous
selection byte is unchanged. The counters reset for each row. No null checks,
extra bounds checks, or unconditional selection initialization are added.

The state view describes the observed nine two-byte entry positions beginning
at `+0x14`; this function only accesses each entry's first byte. No meaning is
asserted for the intervening bytes. The retained table remains an unsized array
of byte rows, avoiding an invented packed-record or alignment contract.

## Standard compiler result

Under `agbcc -mthumb-interwork -O2`, the retained natural typed-state recovery
emits exactly one function symbol of **308 bytes / 133 instructions**, not the
target's **322 / 141**. It has 278 code bytes, 28 literal bytes, and a two-byte
internal alignment gap. Its saved-register set is smaller and it does not
allocate the target's four-byte local frame: the captured count remains in a
register. Operand allocation, threshold combination, loop addressing, and the
selection-store sequences also differ.

The frozen reviewed toolkit `2e2a664` rejects the retained candidate with:

```
compiled symbol is shorter than the indexed span: 308 < 322
```

This occurs before the ordinary byte-comparison stage. No successful report
replay or retained-candidate byte-match percentage is claimed. The correct
322-byte ROM mapping is unchanged.

Bounded natural organizations tried with unchanged standard flags:

| Organization | Complete symbol bytes |
| --- | ---: |
| Direct byte-array state view | 302 |
| Grounded two-byte-entry state view, retained | 308 |
| Named selection and threshold-array pointer views | 322 |
| Those pointer views initialized at their use sites | 326 |

The equal-size 322-byte alternative still differed substantially in register
allocation, scheduling, and loads/stores. It was not promoted. The clearer
typed-state recovery is retained rather than forcing local lifetimes or
register placement. No assembly, volatile accesses, packing, optimization
pragmas, dummy control flow, compiler changes, or toolkit changes were used.
This local mismatch does not establish that the function is inherently
unmatchable.

## Bounded behavior evidence

A separately linked diagnostic candidate and actual ROM were executed with the
real `080C9574`, `080C9540`, and `080CE8A8` bodies. All record tables, flag state,
statistics, sentinel list data, and category nodes used for these tests were
explicitly synthetic. No helper was stubbed and no synthetic lookup value was
described as an actual game-state value.

The check ran 81 fixtures with four reset words (`0`, `1`, `0x100`, and
`0xABCD0101`) against both bodies: **324 paired cases / 648 executions**.
Cases included reset-induced count changes, inclusive threshold boundaries,
individual rejection paths, one-of-eight threshold acceptance, flag rejection,
all 64 rows rejected, row 64 selected, no-condition selection clearing, and
terminating category-list variants. The bounded fixture lists do not prove
termination for arbitrary linked-list state.

An independent model checked the complete non-stack RAM result and exact helper
call order/arguments. The two executions also agreed on the ordered non-stack
data read/write traces, including the synthetic tables and list nodes. SP,
saved registers `r4` through `r11`, and return to the sentinel were checked.
All 141 target instructions and all 133 candidate instructions were covered.
No scalar return value was asserted for the void function.

The frozen plausibility checker reports no findings. No active source or normal
match report remains. The small diagnostic script and linker definitions are
retained in the address-scoped disk-backed task directory; generated binaries
are removed. The diagnostic link is not an official matching proof and does
not bypass the failed extent check.
