# 080CEC78 — unsigned percentage adjustment (not matching)

This is a plausible recovered implementation, not an accepted match. One
ordinary C candidate was compiled with agbcc `-mthumb-interwork -O2`; no
alternative optimization flags or compiler-steering variants were tried.

## Complete symbol and two independent limitations

The target is `[0x080CEC78, 0x080CECF2)`: 122 bytes and 53 reachable Thumb
instructions. It contains 112 code bytes, two four-byte literal words at
`0x080CECCC` and `0x080CECD0`, and internal zero alignment at
`[0x080CECCA, 0x080CECCC)`. The zero halfword at `0x080CECF2` is external
alignment and is excluded. The entry evidence is its indexed prologue and
closed bounded CFG; no inbound-reference claim is made.

The frozen `kit-reviewed-2e2a664` matcher rejects the candidate with:

```
division evidence excludes literal, switch and thunk combinations
```

The candidate genuinely requires named data relocations together with
`__udivsi3`. This is a supported-profile limitation, not permission to rename
the runtime helper or replace named data with unchecked numeric addresses.
No matching report was generated.

Separately, a diagnostic typed absolute link emits one 124-byte function and
a 124-byte `.text`: 55 instructions, 116 code bytes and the same two literal
words, without internal alignment. There are no veneers or unresolved
relocations. The candidate is therefore a real code-generation nonmatch,
even if the mixed proof profile becomes supported. It adds a state-address
increment and an extra factor/base move, uses different saved-register
allocation, and differs in conditional-mask and factor-combination
scheduling. Only 57 of the target's 122 byte positions agree; that comparison
does not include or excuse the candidate's additional two bytes. No prefix
match or matching percentage is claimed.

The diagnostic linked symbol SHA-256 is
`793ca886c1bf4caba4fd52b8bfb649f9ed709e277bd22a0865798c7c3e1f393f`.
This link checks emitted bytes for diagnosis; it is not the official
versioned relocation, CFG, or saved-report proof.

## Grounded interface and behavior

The compatible interface is `u32 func_080CEC78(u16 index, u8 slot, u8 entry)`.
Only the low 16 bits of the first input and low eight bits of the other two
inputs are consumed. No incoming fourth argument or stack argument is used.

The function first calls `u32 func_080CE4DC(u16, u8)` with selector `0x36`
and retains its full result. A zero result returns before any caller table or
state read. The helper declaration agrees with its separately parked
recovery; this does not depend on that helper having matching C.

For a nonzero base, the caller reads one flag byte at
`0x02002CB4 + 12 * slot + 1`. When both low flag bits are set, it reads one
factor byte at `0x08528984 + 96 * slot + 0x41 + entry` and subtracts
`base * factor / 100`. Otherwise it reads the two bytes at row offsets
`0x40` and `0x41`, in that order, combines them little-endian, and adds the
same unsigned quotient. Multiplication and the final addition/subtraction
have ordinary `u32` wrap semantics; division is unsigned and its divisor is
the nonzero constant 100. The result is not narrowed or clamped.

The two unsized byte-array declarations use the independently audited named
bindings, without asserting a record count, row-subobject bound, or arbitrary
allocation size. In particular, `entry` has no extra range check: a high byte
value can address beyond one 96-byte stride. The caller's C domain requires
the addressed table and state bytes, and the helper's own required storage,
to exist. Bounded execution does not establish those allocation or caller
preconditions for all possible game states.

## Bounded behavior evidence

A separate diagnostic freshly compiled the retained source and compared it
with actual target ROM instructions in Unicorn. All 140 paired cases
(280 executions) passed, covering all 53 target and 55 candidate instructions.

- 108 cases use explicitly synthetic record/table bytes and RAM flags, with
  actual `080CE4DC` selector-`0x36` code and actual `08142AB0` unsigned division.
- 16 cases use pristine ROM record/table bytes and synthetic RAM flags, with
  those same real helpers.
- 16 additional cases explicitly model only the full-word result and
  caller-clobbered registers of `080CE4DC`, using values outside its actual
  selector-`0x36` range to stress multiplication wrap. The division helper
  still executes its real ROM body. These are not claimed as real helper
  output values.

The actual selector-`0x36` path reads byte `0x3E` of its 70-byte record and
multiplies it by 200, so its observed result range is 0 through 51,000.
The real-helper tests include zero-base early return and subtraction wrap;
the explicitly modeled cases separately exercise full-width multiplication
and addition wrap. All tests check results, exact ordered nonstack reads and
helper arguments/call order, no nonstack writes, unchanged fixture storage,
callee-saved registers, balanced SP, and the return PC. They also cover input
high bits, all four low-flag combinations, unrelated flag bits, and high
byte indices. No runtime helper is stubbed in the real-helper cases, and
the zero-divisor dependency is not exercised because the divisor is 100.

The reusable diagnostic is local, not a production test dependency:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
PATH=/home/user/armtc/root/usr/bin:$PATH \
python3 /home/user/.codex-work/ffta-ulw/080CEC78/check_recovery.py \
    Parked/080CEC78/080CEC78.c
```

Run it from the game root. It uses the neighboring diagnostic bindings and
linker script, creates a scoped disk-backed build, and removes that build
after execution. Generated binaries and raw ROM dumps are not retained.
