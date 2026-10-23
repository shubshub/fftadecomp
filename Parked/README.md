# Parked

Work that does **not** produce an exact, plausible byte match yet.

The rule for this repo: only functions that are byte-exact *and* whose source
looks like code a developer would have written are committed to `src/`. When a
function fails either gate, its C, its header fragment and its match report go
in `Parked/<address>/` until it is fixed - then it moves to `src/`.

See `tools/plausible.py` for what counts as implausible, and the
`matches` workflow, which enforces the rule on every push.

Each address subdirectory preserves a reviewed recovery that has not cleared
both gates. This includes genuine compiler mismatches, unsupported verification
profiles, and exact output rejected by the current plausibility policy. Parked
entries receive no matched-function or matched-byte credit until they are
independently verified and promoted to `src/`.

See "Matching" in the top-level README for the rule and the current results.
