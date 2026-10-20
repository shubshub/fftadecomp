# Parked: func_0812352C

Status: plausible recovery, not byte-identical. There is no verifier blocker
and no evidence that this function is inherently unmatchable.

## Recovery

The ROM function spans `0x0812352C..0x08123564`: 25 Thumb instructions
occupying 52 bytes, followed by the four-byte return-value literal `0x115`.
The provisional index ends at `0x08123554`, inside the call instruction.

The function decodes an inclusive range from the two nibbles of `script[2]`.
It calls `0x08127AF8` with the context, `script[1]`, the low nibble,
the unsigned-byte range length `(high nibble - low nibble + 1)`,
`script[3]`, and zero, then returns `0x115`.

Bounded Binary Ninja 5.2.8722 analysis loaded only the 56-byte function slice
at its actual address using the `thumb2` platform. Its lifted code confirms
the two nibble extractions, signed low-byte subtraction, unsigned-byte count,
six call arguments, and return value.

## Remaining difference

The canonical recovery compiles with `agbcc -mthumb-interwork -O2` to a
52-byte complete ELF symbol: 22 instructions occupying 46 bytes, two
alignment bytes, and the four-byte literal pool. The required command
accepted the source as plausible and the linked caller as supported, but
reported `NOT MATCHING - bytes differ`:

```text
PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 \
  python3 ../fftadecomp-kit/tools/match.py --root . 0x0812352C
```

The ROM retains three conversions of the masked low nibble:

```text
0x08123538  lsls r4, r4, #24
0x0812353A  lsrs r2, r4, #24
0x0812353E  asrs r4, r4, #24
```

The compiler simplifies these conversions because the mask already limits
the value to `0..15`. It keeps the low nibble directly in `r2`, saves only
`r4` rather than `r4` and `r5`, and consequently changes the selector register,
subtraction register, call displacement, and epilogue. Removing six
instruction bytes introduces two alignment bytes before the pool, giving
the net 56-versus-52-byte difference. The verifier's byte comparison reports
37 of the compiled 52 bytes equal; that is not a match of the full target.

## Attempted natural representations

- Signed-byte low-nibble local with unsigned-byte call parameters.
- The same local with explicit unsigned-byte casts and word-sized call parameters.
- Unsigned-byte local with an explicit signed-byte subtraction conversion.
- Split byte loading and masking, including signed and unsigned locals.
- Signed packed-byte local and signed script pointer with unsigned field conversions.
- Separate signed-byte count local.
- A packed script structure containing two four-bit fields.
- A local two-byte range structure.
- Modulo-16 and byte-truncating nibble-shift extraction.

The straightforward scalar forms simplify away the same conversions.
Split signed-byte masking preserves conversions but moves the mask to the
high byte, yielding a different 60-byte symbol. The script bitfield form
uses word loads and different extraction shifts; the local range structure
adds field-insertion instructions and literal masks.

The canonical expression was also checked at `-O1`: it produces 56 bytes
but uses a duplicate packed-byte load and a register copy instead of the
ROM's conversion sequence. All other attempts used `-O2`.

The parked source retains the simple scalar recovery. No assembly,
optimization pragmas, volatile access, artificial control flow, helpers,
or other compiler-steering additions were used.
