# AGENTS.md

Working rules for agents decompiling FFTA (AFXE). **Read the kit's
[AGENTS.md](https://github.com/shubshub/fftadecomp-kit/blob/main/AGENTS.md)
too** — the reservation and matching rules live there and this file assumes
them.

## The repo

* decompilation: **this repository**
* tooling: **fftadecomp-kit**, a sibling checkout at `../fftadecomp-kit`

```sh
python ../fftadecomp-kit/tools/analyze.py baserom.bin .   # ROM -> config/, symbols/
python ../fftadecomp-kit/tools/split.py   baserom.bin .   # -> asm/, files/
python ../fftadecomp-kit/tools/rebuild.py .               # split is byte-exact
python ../fftadecomp-kit/tools/match.py 0x08017514        # compile + diff
python ../fftadecomp-kit/tools/plausible.py src include   # implausibility gate
python ../fftadecomp-kit/tools/status.py --write --verify # progress block
```

The compiler is **agbcc** (`gcc 2.9-arm-000512`, Thumb/elf) with
`-mthumb-interwork -O2`; it is a raw cc1, so `cpp` runs first (match.py does
this). Full details in [`docs/toolchain.md`](docs/toolchain.md).

## Hand matching is done by sub-agents

The session that coordinates claims one address and spawns one sub-agent per
address; it does not write the C itself.  See the kit AGENTS.md rule 4 for why
and for the prompt shape.  The orchestrator keeps ownership of git, the status
block and the plausibility sweep; each sub-agent owns exactly one
`src/<addr>.c` and nothing else - no shared header edits, so parallel agents
cannot collide.

## Order of work, every time

1. **Check the ledger, then claim the address** — `reserve.py list`, `check`,
   `claim`. Never take an address that is held, already matched (`src/`), or
   already in an open PR. If the claim is refused, pick another.
2. Write `src/<addr>.c`, one function per file, with a comment giving the
   target bytes.
3. `python ../fftadecomp-kit/tools/match.py <addr>` until it says
   `MATCH - byte identical`.
4. Only byte-exact matches go in `src/`. Everything else goes to
   `Parked/<address>/` with the recovered C and a README explaining precisely
   what differs and what was ruled out.
5. **Release the reservation** — `reserve.py release <addr> --reason "..."`, or
   `--unmatchable --reason "..." --tried "<flags>"` when it cannot be matched.
   This is not optional: a reservation is a lease, and holding one you are not
   working on blocks the next agent.

## Before you commit

```sh
git fetch origin && git rebase origin/main      # not merge
git push --force-with-lease
```

CI (`matches`) refuses a PR that is behind `main`, rejects any function in
`src/` without a report saying byte-identical, rejects `IMPLAUSIBLE` reports,
and fails if the README status block is stale. `make status` must always be run
with `--verify`: a plain `--write` cannot tell that reports are current and will
publish a 0.00% board.

## Things that bite

* **Offsets come from the instructions, not from guesses.** Reconstructed struct
  layouts must put each field exactly where the ROM's immediate offsets say; a
  padding array named `pad` is steering padding — name unknown members
  `unknown_*`.
* **Read the type off the shift.** `lsrs #15` is an arithmetic shift, so the
  value is signed; `lsrs #24` after `lsls #24` is a `u8` cast of a wider
  parameter. `ldrh`+`strb` means the field was read as `u16` and truncated.
* **Strides are arithmetic.** `(x << 3) - x) << 2` is 28, not 40; and the
  compiler only emits that order when the offset is computed *before* the base
  is folded in.
* **Store order is not signature order.** Match the instructions.
* **Do not fake a match.** No inline asm, no optimisation pragmas, no dead
  code, no `volatile`, no contrivance that exists only to steer the compiler.
  `plausible.py` rejects those, and a tricked match proves nothing.