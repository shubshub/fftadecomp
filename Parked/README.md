# Parked

Work that does **not** produce an exact, plausible byte match yet.

The rule for this repo: only functions that are byte-exact *and* whose source
looks like code a developer would have written are committed to `src/`. When a
function fails either gate, its C, its header fragment and its match report go
in `Parked/<address>/` until it is fixed - then it moves to `src/`.

See the kit's `tools/plausible.py` for what counts as implausible, and the
`matches` workflow, which enforces the rule on every pull request and every
push to `main`.

Each address subdirectory preserves a reviewed recovery that has not cleared
both gates. This includes genuine compiler mismatches, unsupported verification
profiles, and exact output rejected by the current plausibility policy. Parked
entries receive no matched-function or matched-byte credit until they are
independently verified and promoted to `src/`.

See "Match a function" in the top-level README for the workflow, and its
progress table for the current results.
