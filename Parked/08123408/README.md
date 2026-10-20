# 0x08123408: byte-identical candidate, unsupported pointer-call verification

The recovered C compiles to the complete 108-byte ROM function at
`0x08123408..0x08123474`, including the interior mask literal at `0x08123458`
and return-value literal at `0x08123470`, with
`agbcc -mthumb-interwork -O2`. A compiler-only comparison after typed linking
of the three direct calls found all 108 bytes identical. This is not an
official match: the verification gate does not accept the pointer-call shape.

The function builds an eight-byte parameter record, resolves signed script
coordinates through `func_08124E74`, copies the mode and amount, dispatches
to `func_08127C10` when `script[5] == 1` or `func_08127BC4` otherwise, and
returns `0x115`. The first two record members are eight-bit `u32` bitfields;
the following members are `s16 x`, `s16 y`, and `u16 amount`.

## Verification blocker

With the candidate temporarily in `src/08123408.c`, the required command:

```sh
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
  python3 ../fftadecomp-kit/tools/match.py --root . 0x08123408
```

exits 1 with:

```text
compile failed:
unsupported stack-alias use or escape
```

At `0x0812342C`, `r3` holds the address of the local `x` field at `sp+6`.
At `0x0812342E`, `r4` holds the address of the local `y` field at `sp+8`.
The instruction at `0x08123430` stores that pointer at `[sp]` as the fifth
argument of the direct call at `0x08123432`. Supporting only register-passed
stack buffer arguments cannot verify this call; its fifth argument also
needs a bounded stack-pointer argument model.

## Boundary evidence and attempts

- The existing index span ends at `0x08123434`, inside the first `bl`.
  The complete compiler symbol ends at `0x08123474`, where the next function
  starts.
- A bounded Binary Ninja 5.2.8722 `thumb2` view of these 108 bytes recovered
  blocks `[0x08123408,0x0812344A)`, `[0x0812344A,0x08123456)`,
  `[0x0812345C,0x08123466)`, and `[0x08123466,0x08123470)`, confirming the
  two-way dispatch around the interior literal pool and the shared return.
- The first natural C candidate produced identical bytes. No optimization
  sweep, compiler steering, assembly, pragmas, volatile qualifiers, or
  verifier changes were needed or attempted.
- No official match report was generated. Re-run the standard gate after
  the toolkit supports this outgoing stack pointer argument; this is a
  tooling limitation, not evidence that the function is unmatchable.
