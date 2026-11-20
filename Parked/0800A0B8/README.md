# 0800A0B8 — script context initialization

The complete linked ELF symbol equals **84/84 ROM bytes**, including both literal pools. The matched caller at `0800A06C` branches here from `0800A080` and `0800A0A6`. The final literal occupies `0800A108..0800A10B`, immediately before the indexed entry at `0800A10C`.

The function builds an eight-byte `ScriptContext` on the stack. Its first byte receives the low byte of `mode`. Its second byte receives `g_state_02000000[0x2191]` when the low byte of `enabled` is nonzero, or zero otherwise. The callee reads these two fields and initializes the remaining fields.

## Return type

The parked definition agrees with the existing caller's declaration, `u32 func_0800A0B8(u32, u32)`. The ROM returns the result of `0800A10C` directly. Its current C definition declares a `u8` return, which makes agbcc emit two extra instructions in this caller to zero-extend the result. Changing only the callee's return type to `u32` preserves its byte-valued local and independently reproduces **72/72 bytes** of `0800A10C`. The parked source declares that corrected signature. Both comparisons used agbcc with `-mthumb-interwork -O2`.

## Verification boundary

The ordinary verifier rejects the stack context passed down to the opcode handler.

```text
buffer callee 0x0800A10C: buffer callee 0x0800A154: buffer callee 0x0814224C: non-leaf indirect control flow requires linked CFG verification
```

`0800A154` loads its handler from an opcode-indexed record in `g_table_0836D5A4`. The existing `static-callback-buffer-v1` profile rejects this use with `static callback target register is not an exact Thumb function pointer`. Promotion requires a proof of the handlers' effects on the caller's stack context, together with the callee return-type correction.
