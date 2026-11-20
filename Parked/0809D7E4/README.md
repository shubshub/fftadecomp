# 0809D7E4

The complete 96-byte Thumb symbol at `[0809D7E4,0809D844)` compiles byte-for-byte with `agbcc -mthumb-interwork -O2`. Independent assembly and linking at the original address produced SHA-256 `3f9312d822e6a46e51524542175b6fc4c6186eb8edd426e80b07366de48ca7e2`. Both the public verifier and the current verifier decline a match report. The source passes the plausibility check.

## Recovered operation

The function invokes slot zero of the callback table at `0836D4B8` with the 48-byte state at `0200F740`. It stores the supplied actor, value and coordinate offsets at state offsets `20`, `24`, `28` and `2A`. Both direct callers pass 16, −120 and −86 for the last three arguments. The function then asks `0801E6F0` for the two camera coordinates and copies its halfword outputs to the first two state fields.

## Return-register evidence

The default selector and `--owner-runtime-profile bounded-buffer-conditional-thunks-root-return-scratch-v1` both report `local stack pointer escapes through a return register`. At `0809D81E`, R1 receives the address of the second halfword, entry SP minus 26. The call to `0801E6F0` writes that halfword through R1. The leaf preserves R1 and the wrapper returns via R0 at `0809D83A`, leaving the expired address in R1.

A scan of every Thumb BL encoding within range of the entry found exactly two direct callers. The two continuations kill R1 before reading it on every path.

| Call site | First overwrite of the returned R1 |
| --- | --- |
| `080967B6` | `080967BE` branches. Fallthrough sets R1 to 3 at `080967C4`, and the taken path sets it to 1 at `080967E6`. |
| `080BB072` | `080BB078` branches to `080BB362`. The epilogue loads the saved return address into R1 at `080BB36A`. |

No direct Thumb B or conditional B targets this entry. A bytewise search throughout the ROM found neither the even address `0809D7E4` nor the Thumb-tagged address `0809D7E5`. These scans do not cover targets synthesized by register arithmetic or supplied by RAM. The current root-return policy admits discarded R2/R3 aliases and retains R1. A source-level void signature and the two direct caller continuations do not establish the indirect-consumer coverage needed to extend it.
