# 080CFA48 — recovered, not byte-identical

## Complete target and outcome

The target occupies `[0x080CFA48, 0x080CFAD4)`: 140 bytes, 60 instructions,
128 code bytes, and three four-byte literals, with no internal alignment
gap. The literals at `0x080CFAC8`, `0x080CFACC`, and `0x080CFAD0` are
`0x02002CB4`, `0x085653F0`, and `0x0000059F`, respectively.
Its complete body SHA-256 is
`37bff1a0f6f4e8288c730e74f491e2e06c4d4acf606d49107372ab6f8599ec05`.

The retained source emits one function and no additional text: 136 bytes,
57 instructions, 122 code bytes, two alignment bytes, and three literals.
The diagnostic linked-byte SHA-256 is
`fc3bb36d1ecb4b085b30c10c44246409488abd8cee66e78c04e5b2e4dc6dd0f3`.
It is not byte-identical to the target.

The reviewed `2e2a664` matcher rejects the compiler-generated `__modsi3`
reference with:

```text
compile failed:
call target must be an undefined addressed function
```

The source deliberately uses ordinary signed `%`, not an explicit runtime
call to evade the verifier. A separate scratch-only diagnostic binds that
generated runtime symbol to the audited Thumb remainder at `0x08142950`
and binds the actual function/data symbols with their ELF types. It checks
one full `STT_FUNC`, complete `.text`, and absence of residual relocations.
This diagnostic establishes a real code mismatch, not an official match or
new proof profile. No active source or successful match report is retained.

## Recovery and contracts

The interface is `void func_080CFA48(u8 index)`. The actual ROM normalizes
the input to its low byte, saves five words, and has no local stack frame.
No additional incoming register or stack argument is consumed. The
candidate saves four words and restores the same required callee-saved ABI.

The selected record is at `g_state_02002CB4 + 12 * index`. The meaningful
local view puts flags at byte `0x01` and status at byte `0x02`; unknown bytes
describe the observed 12-byte stride. It preserves the existing opaque
`extern u8 g_state_02002CB4[]` declaration. The table remains an unsized byte
array, with rows reached by the observed stride 38; no table bound or padded
38-byte structure is invented.

The ordered operations are:

1. Read the selected flags and store `(flags & 0xF7) | 2`, then clear status.
2. Snapshot table byte `38 * index + 1` before calling the RNG.
3. Narrow the RNG result to signed 16 bits, take the signed remainder with
   the snapshot shifted right one, add the snapshot, and narrow to `u8`.
   Replace a resulting zero with one.
4. Call `func_080C95C0((u16)(index + 20), amount)`.
5. Scan records one through thirty in ascending order. Return at the first
   flags byte whose low two bits are not both set. If all pass, call
   `func_080C9574(0x59F, 1)`.

The compatible helper declarations are `u32 func_08002804(void)`,
`void func_080C95C0(u16, u32)`, and `void func_080C9574(u16, u16)`.
The real RNG updates the state at `0x030034B0` with the audited LCG and
returns a value in `0..32767`. Thus its signed-16-bit conversion is exact;
negative synthetic RNG results are not asserted to be real helper outputs.
The remainder runtime returns a signed remainder, not a quotient.

## Zero-divisor boundary

The actual table has zero base bytes for rows zero and one. Rows two through
six and row thirty have 255; rows seven through twenty-one and twenty-three
through twenty-six have 40; row twenty-two has 35; rows twenty-seven through
twenty-nine have 25. This evidence does not justify a universal nonzero
divisor contract.

Ordinary C `%` is undefined when the base is zero or one, since `base >> 1`
is then zero. The ROM nevertheless calls its runtime: the actual zero case
invokes the no-op handler at `0x0814274C`, then returns zero. With base zero,
the caller consequently stores amount one. The tested compiler happens to
emit that same runtime call on these inputs. This is machine-code behavior
of the built candidate, not defined C semantics or a repaired zero-divisor
contract. No guard or named runtime call has been inserted to conceal the
limitation.

## Bounded natural attempts

Both attempts used the standard agbcc `-mthumb-interwork -O2` flags:

- Direct byte-array views with separate base and amount locals: 132 bytes.
- The retained grounded record view, named counter index, and ordinary
  amount accumulation: 136 bytes.

The ROM preserves a shifted snapshot as well as its byte value across RNG
and derives the divisor from that shifted value. The candidate instead
retains the directly loaded byte and shifts it once to form the divisor.
Register allocation, save set, instruction ordering, and branch/literal
offsets also differ. It has six fewer code bytes and two additional alignment
bytes, accounting for the four-byte total difference. No artificial storage,
register assignment, forced alignment, bitfield, or control flow was added.
This is a bounded local recovery result, not a claim of inherent
unmatchability.

## Reproducible behavioral evidence

The retained diagnostic is
`/home/user/.codex-work/ffta-ulw/080CFA48/check_recovery.py`, with its adjacent
`known.s` and `diagnostic.ld` typed-link fixtures. They are diagnostic
artifacts, not game implementation code. From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/080CFA48/check_recovery.py Parked/080CFA48/080CFA48.c
```

All 1,078 paired fixtures, 2,156 executions, pass with actual ROM RNG,
signed remainder, zero handler, and both setters. No helper is stubbed.
The fixtures use synthetic RAM and controlled RNG seeds; 868 pairs retain
the pristine ROM table. The remaining 210 use explicitly synthetic base
bytes, including byte-index edge cases without claiming original allocation
bounds. Cases cover upper input bits, base values zero/one and nonzero,
amount wrap-to-zero, scan failures at the first/interior/last record, the
all-pass path, unrelated flags, and actual RNG outputs from zero to 32767.

Exactly 116 pairs encounter a zero divisor and are labeled machine-only
evidence; the remaining 962 have defined nonzero remainder operands.
Coverage reaches all 60 target and all 57 candidate instructions, plus 138
distinct actual helper instructions. No exhaustive runtime coverage is
claimed. Ordered calls and arguments, state/table data reads, nonstack
writes, full final RAM, updated RNG state, and unchanged table bytes agree.
Instruction-literal fetches and stack accesses are not part of the data-read
comparison. Registers `r4` through `r11` and SP are preserved on return.

The source otherwise assumes valid aligned storage for its local record
view and all accessed table/state bytes. The opaque backing symbol and
machine fixtures do not prove arbitrary C object-lifetime or overlapping
alias cases valid. No allocation extent, incoming cross-reference, or
nonzero-divisor invariant is inferred. The plausibility checker reports no
findings, but that does not remove the explicit zero-divisor C limitation.
