# Parked

Work that does **not** produce an exact byte match yet.

The rule for this repo: only byte-exact matches are committed to `src/`. When
a function compiles but differs, its C, its header fragment and its match report
go in `Parked/<address>/` until a compiler or flag change makes it exact -
then it moves to `src/`.

Currently empty: every attempt so far has either matched or been fixed.
See "Matching" in the top-level README for the rule and the current results.
