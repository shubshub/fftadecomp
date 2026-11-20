# 08120BF4 | input-driven transition and piece effects

The native control-flow graph covers 227 reachable Thumb instructions, 482 code bytes, 20 literal-pool bytes, and four alignment bytes in `[08120BF4,08120DEE)`. The original makes 14 calls to 11 distinct helpers. Its three-word callback ABI ignores R0, reads the effect command through R1 and the payload through R2, and returns zero. No direct Thumb BL to the entry or literal entry pointer was found in the USA ROM. The registered child effects at IDs `15A` and `15B` use the callbacks at `080E2750` and `080E28C4`.

The candidate creates the two effects, waits for both, changes the palette with the R button, and selects a piece group and screen position from held directions and newly pressed buttons. Start advances to cleanup. The compiler emits 40 read-only initializer bytes that match the transition parameters and eight coordinate pairs at `08149FD0` and `08149FD8`.

## Remaining difference

With `agbcc -mthumb-interwork -O2`, the linked symbol has the original 506-byte size. **356 of 506 bytes** match at the same positions. The candidate reserves 44 stack bytes, while the ROM reserves 52. The candidate uses R7 for the command and R6 for input, where the ROM uses R6 and R7, respectively. The two literals pointing to the initializers occur four bytes early in the candidate. The public kit at `635c399b` rejects the typed ROM-copy selector with `owner literals disagree on the initialiser address`. No match is claimed.

Paired execution of the original and candidate Thumb bodies agreed in 3,392 cases on the external call order and arguments, command and payload bytes including guards, zero return, and restored SP. The runs used deterministic helper models, exercised both outcomes of each readiness and cleanup call, all eight offset indexes, directional priorities, and palette wrapping. These comparisons cover the handler around the helper calls.

The first offset-table access uses the incoming payload index; the mask to seven occurs only after the action. Phase zero initializes the palette and group, but leaves that index untouched. A verifier needs a documented input condition or an initialization path proving the live index is in `[0,7]` whenever an offset is read.
