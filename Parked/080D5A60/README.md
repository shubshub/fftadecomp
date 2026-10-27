# 080D5A60 — Parked

The full indexed ROM target is `0x080D5A60..0x080D5C1E`: 446 bytes and 212 reachable instructions. The tested natural C preserves the command phases, 28-byte movement descriptor copy through a typed callback, signed coordinate offsets, distance-based speed clamp, direction override, animation lifecycle, and indexed final-position update.

The final native invocation used the approved ROM, fixed `agbcc -mthumb-interwork -O2`, and `--function-address-profile canonical-thunks-v1`. It returned exit 1 at the compile/extent guard:

```text
compile failed:
inert spins require an exact unique nonoverlapping Thumb span
```

A direct compile with the same compiler flags emitted only `func_080D5A60`, with ELF symbol size 422 bytes and 202 instructions, versus the complete 446-byte/212-instruction target. The compiled symbol is 24 bytes shorter. No native byte-match score or plausibility verdict was produced.

The remaining differences are specific: the compiler removes the empty phase-1 switch entry and dispatches around phase `0x100`, whereas the ROM retains phase 1 and pivots at `0x101`; it emits two literal-pool words rather than the ROM's three. The command pointer occupies R6 rather than R7. Across the distance call, the candidate keeps end Y in SL and spills start Y at SP+28; the ROM keeps start Y in R6 and spills end Y there. The candidate holds speed in R7 and direction in IP, versus IP and R8 in the ROM. Natural signed-coordinate locals, inline offset/square expressions, option-copy ordering, and explicit empty-state return forms were tested without closing these differences.

The unchanged final tested C is preserved here. No active unmatched source or native report remains, and no match credit is claimed.
