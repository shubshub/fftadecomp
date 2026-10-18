# Parked (was: func_08092084)

func_08092084 now matches byte-for-byte — see `src/08092084.c` and
`docs/match/08092084.md`.  The old attempt and its diagnosis are kept in the
history; the short version of what it taught us:

* the signedness was already right (`asrs #15` is an arithmetic shift, so the
  index is `s16`), and the stride is 2;
* what was missing was that `adds r0, #1` is an **in-place pointer increment**
  (`base++`) between the two stores - that is what keeps the base live, and the
  frame follows from the register pressure rather than being its own problem;
* agbcc emits the two-operand add base-first only when the offset is a
  **variable**; with the multiply inlined into the address expression it comes
  out index-first.
