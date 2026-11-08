# 080898E0

Number drawing helper modelled on the matched sibling `src/080899AC.c`: the same `data_08393D2A` digit table,
explicit `func_08142B28` / `func_081426B8` (unsigned and signed division runtime) calls, and a digit loop in a
`static inline` helper. `080898E0.c` assembles to the 202 target bytes except the four `bl` relocation sites
and the `data_08393D2A` pool word (link-time).

The verifier has no profile for an 8-byte frame that reads four incoming stack words, loops, calls both
division runtimes and references one named data word:

* `--addressed-signed-runtime-profile addressed-integer-runtime-data-v1`: "local branch access leaves its established frame"
* `addressed-integer-runtime-readonly-three-words-data-v1` (the sibling's selector): "entry stack read leaves the declared incoming words" (four are read, `[sp,#0x28..#0x34]`)
* `addressed-integer-runtime-readonly-word0-v1`: "addressed signed runtimes exclude data and irregular relocations"
* `--owner-runtime-profile canonical-integer-scalar-data-source-v1`, `canonical-integer-private-locals-data-source-v1`: "owner requires sole complete Thumb ELF function"
* `canonical-integer-scalar-source-v1`, `conditional-finite-spilled-scalar-loops-v1`: "division runtime requires its canonical versioned proof"
