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

## Where a source file goes

One file per function, always - agbcc compiles each source on its own and
`match.py` depends on that, so two functions are never merged into one file.

The **folders** are grouping, and the grouping is evidence rather than taste:
`docs/modules.md` has the derivation.  The game laid its state out
contiguously in RAM, so functions touching the same block of globals belong to
the same subsystem, and a subsystem is one directory named after the RAM page
its globals live on - `src/20101/` is everything that touches the state at
`0x020101xx`, which is where the six functions of the 0x080C module live.

A function with no folder yet is written to `src/<addr>.c` and stays there
until the evidence puts it somewhere.  **Do not create folders yourself and do
not move files** - `python ../fftadecomp-kit/tools/modules.py --root .
--moves` prints the plan, and the orchestrator applies it.  The tools find a
source wherever it lives, so both layouts work.

## First: initialise the generated tree

sm/, iles/, config/, symbols/ and logs/ are **derived from the ROM**
and are gitignored on purpose - the disassembly and the raw runs are Square's
data, and a repository should not carry it.  They are produced from the user's
own ROM:

`sh
make init          # analyze -> split -> check, from baserom.bin
`

Expect this once per machine.  If symbols/functions.txt is missing, match.py
cannot size a function and you have not run init.  Never commit any of it; the
push gate refuses the push if it finds sm/, iles/, aserom.bin or a
.gba in the index.

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
python ../fftadecomp-kit/tools/status.py --write --verify   # re-verifies everything
git fetch origin && git rebase origin/main                # not merge
git push --force-with-lease
```

**Audit before you trust a claim.** `status.py --write --verify` recompiles
every file in `src/`, but do not assume a match claim in a commit message is
true — an audit of all 46 sources found one commit that claimed a match while
the file it shipped did not produce those bytes (a retired `Parked/` copy had
been moved over the newer `src/<addr>.c`).

Two rules that would have prevented it:

* **Never move a file over `src/<addr>.c`.** A sub-agent may already have
  replaced it with its working version. `git diff` first, and if the working
  copy is newer, keep it and delete the parked copy instead.
* **Re-read `src/<addr>.c` immediately before committing** any match.

CI (`matches`) refuses a PR that is behind `main`, rejects any function in
`src/` without a report saying byte-identical, rejects `IMPLAUSIBLE` reports,
and fails if the README status block is stale.

## Verification boundaries

* **Fixed Thumb frames are supported.** The framed profiles track fixed SP
  adjustments, bounded stack accesses and return provenance. Dynamic adjustments,
  unsupported alias escapes and unbalanced returns still fail. A rejection of
  one operation or profile combination is not a blanket ban on framed functions.
  `docs/match/08005B6C.md` records a complete framed match.
* **Named data literals are supported through typed linking.** Real external
  data symbols must have evidence-backed entries in `config/data_symbols.json`;
  eligible `R_ARM_ABS32` relocations must occupy complete aligned, referenced
  in-function literal words. All linked bytes are compared and reports bind
  the mappings. Do not invent addresses or assume arbitrary relocations qualify.
  Consult the current kit README and `docs/toolchain.md` for the limits.

* **Stack arguments sit one word lower than you think.** The *n*-th incoming
  word is at `frame_size + 4*(n-5)`, not entry-SP arithmetic — see
  `docs/toolchain.md`.  Being off by one still compiles, just wrongly.
* A `lsls #24` with no `lsrs #24` after it is a `u8` narrowing, and a 4-bit
  field insert shows up as `(b << 24) >> 20`, not `lsls #4`.

* **Read the shift amount, not the operation.** `lsrs #14` after a `u16` is
  usually `* 4`, not `>> 14`: agbcc expands `(u16)x << n` as
  `>> (16 - n)`.  A real `>> 14` on a `u16` folds to one `lsrs #30`.  When a
  masked shift looks impossible, change the operation rather than hunting for
  another spelling - `docs/toolchain.md`.

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
