# 080D4D58: byte-identical; the verifier refuses a variable index into a stack table

Target: `[0x080D4D58, 0x080D4DA0)`, 72 bytes, 33 instructions. The function copies the read-only table `data_08149AB4` onto the stack. The table is four pointers to the BG0CNT..BG3CNT shadows at `0x03000942`..`0x03000948`. The function then picks one with `background` (`u8`, below four) and sets or clears the mosaic bit `0x40` there, according to `mosaic`.

`080D4D58.c` compiles to the ROM's instructions exactly. The only literal is the `R_ARM_ABS32` to `data_08149AB4`, which equals the pool word `b49a1408`. That was checked by hand-linking, and in a scratch root once the symbol was mapped. No selector admits it:

- default: `unsupported stack-address materialization` (`add r0, r0, sp`);
- `named-data-buffer-v1`: the same refusal;
- `local-rom-halfword-table-v1`: `complete aligned forty-byte local table owner required`;
- `local-shadow-halfword-matrix-v1`: `sole complete96-byte Thumb function required`;
- `mutable-four-local-index-three-call-native-v1`: `mutable index inventory requires actual ordinary direct calls`.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/135
