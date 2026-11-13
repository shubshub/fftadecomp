# 08028FF4: byte-identical; a numeric word before the jump table has no selector

Target: `[0x08028FF4, 0x08029188)`, 404 bytes. The outer branch on `event->mode` is a compare tree. Inside it, a jump-table switch runs on the 3-bit field at `g_state_02000000 + 0x2FC1`. The source was hand-linked at its address, and the output equals the 404-byte span.

The pool before the table holds `data_0200F438`, `g_state_02000000`, the plain number `0x2FC1`, and then the table pointer. `switch_layout` only accepts named-data words there, so the default refusal is `switch requires one exact adjacent unsigned guard and five-op dispatch`. `ordinary-multiple-switch-source-v1`, `numeric-data-switch-source-v1`, `two-constants-v2`, `u16-scalars-v1` and `restoring-owner-switch-entry-two-words-data-v1` also refuse. This is the same gap as https://github.com/shubshub/fftadecomp-kit/issues/136: a numeric word interposed before the table.
