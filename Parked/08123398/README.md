# Parked: func_08123398

Status: byte-identical recovered C, blocked by the verifier's stack-argument
alias boundary. This is not an inherently unmatchable function and is not a
verified match.

## Recovery

The complete ELF symbol covers 96 bytes at `0x08123398..0x081233F8`, including
the two trailing literal words at `0x081233F0` and `0x081233F4`. The provisional
function index covers only 48 bytes and ends inside the first call.

The function constructs an eight-byte record from script bytes 1 through 6.
Its selector and mode are unsigned eight-bit bitfields, followed by signed
halfword coordinates and an unsigned halfword amount. It calls `0x08124E74`
with the selector, two signed script bytes, and pointers to the coordinates,
then passes the completed record by value to `0x08127B80` and returns `0x115`.

Bounded Binary Ninja 5.2.8722 analysis used the 96-byte ROM slice loaded at
`0x08123398` with the `thumb2` platform. Its lifted code confirms the byte
insert, both coordinate addresses, remaining script fields, the two calls,
and the return value.

## Validation

The candidate compiled with `agbcc -mthumb-interwork -O2` and was assembled
with the installed ARM binutils. A diagnostic build used the toolkit's
`call_bindings`, `link_calls`, and `linked_function_bytes` checks to resolve
the two indexed Thumb callees. The resulting complete 96-byte ELF symbol
equals the corresponding ROM slice, including the literal pool. There are
no remaining byte differences.

The body contains 42 Thumb instructions before the eight-byte literal pool.
The focused `plausible.py --quiet --addr 0x08123398 --json` check reports
zero findings for the parked source.

The required command, run while the candidate was temporarily under `src/`,
failed:

```text
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
  python3 ../fftadecomp-kit/tools/match.py --root . 0x08123398

compile failed:
unsupported stack-alias use or escape
```

At `0x081233C2`, `add r4, sp, #8` computes `&parameters.y`. At `0x081233C4`,
`str r4, [sp]` stores that pointer in the outgoing fifth-argument slot.
Exception tracing confirms that the verifier rejects this instruction at
`0x081233C4`, before reaching the call at
`0x081233C6`. The fourth argument in `r3` is another local field address,
`sp + 6`; register-only call-buffer support alone cannot accept the fifth
argument.

The raw-byte diagnostic does not replace the official verifier. The source
is parked pending supported proof for a bounded local pointer passed through
an outgoing stack-argument slot. No verifier checks were disabled, and no
alternative flags or compiler-steering source were needed.
