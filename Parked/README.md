# Parked

Work that does **not** produce an exact, plausible byte match yet.

The rule for this repo: only functions that are byte-exact *and* whose source
looks like code a developer would have written are committed to `src/`. When a
function fails either gate, its C, its header fragment and its match report go
in `Parked/<address>/` until it is fixed - then it moves to `src/`.

See `tools/plausible.py` for what counts as implausible, and the
`matches` workflow, which enforces the rule on every push.

Currently empty: every attempt so far has either matched or been fixed.
See "Matching" in the top-level README for the rule and the current results.
