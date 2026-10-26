# 0x0806F46C — bounded natural C attempt

Complete target: `[0x0806F46C, 0x0806F568)`, 252 bytes and 111 reachable instructions. Fixed compiler: agbcc `-mthumb-interwork -O2`.

The complete candidate moves a panel horizontally toward a signed-byte target in four-pixel steps, clears exposed strips in both tilemaps, redraws, and reports whether it was already at the requested position.

Fresh native matching exits 1 at the symbol-extent gate: `compiled symbol is shorter than the indexed span: 248 < 252`. This gate stops before byte comparison and source-plausibility verdicts, so neither exact-byte counts nor a native plausibility pass is claimed.

Observed generated-code differences include:

- The target initially loads the coordinate independently as an unsigned byte and a signed byte, then reloads its previous byte near the direction branch. The candidate shares the initial load, retains its signed form across both movement paths, and keeps another representation in `ip`. This changes live ranges and register allocation.
- The target sign-extends the old coordinate near the positive strip-width calculation. The candidate reuses its previously sign-extended value.
- On the negative path, the target subtracts 14 from the clipped endpoint before loading and subtracting the updated coordinate. The candidate combines these operations as endpoint minus (updated coordinate plus 14).

Six natural candidate forms were tested before restoring this 248-byte candidate: signed/unsigned snapshot locals, branch-local versus common previous-coordinate storage, signed versus raw-byte coordinate fields with explicit conversions, and narrow versus full-width direction/strip arithmetic. Generated extents were 240, 244, or 248 bytes; none reached the 252-byte target. No flags, assembly, volatile, dead code, or shared files were changed.

The unmatched private source and any generated report were removed. The fresh native output remains in the address scratch directory.
