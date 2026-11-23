# AGENTS.md

Working rules for agents decompiling FFTA (AFXE). **Read the kit's
[AGENTS.md](https://github.com/shubshub/fftadecomp-kit/blob/main/AGENTS.md)
too** — the reservation and matching rules live there and this file assumes
them.

## The repo

* decompilation: **this repository**
* tooling: **fftadecomp-kit**, a sibling checkout at `../fftadecomp-kit`

```sh
python ../fftadecomp-kit/tools/analyze.py baserom.bin .   # re-scan; not on a checkout
python ../fftadecomp-kit/tools/split.py   baserom.bin .   # -> asm/, files/
python ../fftadecomp-kit/tools/rebuild.py .               # split is byte-exact
python ../fftadecomp-kit/tools/match.py 0x08017514        # compile + diff
python ../fftadecomp-kit/tools/plausible.py src include   # implausibility gate
python ../fftadecomp-kit/tools/status.py --write --verify # progress block
```

The compiler is **agbcc** (`gcc 2.9-arm-000512`, Thumb/elf) with
`-mthumb-interwork -O2`; it is a raw cc1, so `cpp` runs first (match.py does
this). The library units in `config/library_units.json` are the exception:
each names its own toolchain, and `match.py --unit-toolchain <id>` verifies
its functions. Full details in [`docs/toolchain.md`](docs/toolchain.md).

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
its globals live on - `src/20101/` is the folder for the state at
`0x020101xx`, which is where eight of the sixteen functions of the 0x080C1438
file candidate (`module_0C1430.c`) live.

A function with no folder yet is written to `src/<addr>.c` and stays there
until the evidence puts it somewhere.  **Do not create folders yourself and do
not move files** - `python ../fftadecomp-kit/tools/modules.py --root .
--moves` prints the plan, and the orchestrator applies it.  The tools find a
source wherever it lives, so both layouts work.

## First: initialise the generated tree

`asm/` and `files/` are **derived from the ROM** and are gitignored on
purpose - the disassembly and the raw runs are Square's data, and a
repository should not carry it.  They are produced from the user's own ROM:

```sh
make split check   # asm/ and files/ from baserom.bin, then prove them exact
```

Expect this once per machine.  `config/`, `symbols/` and `logs/` are tracked.
The function index in them was analysed from the ROM and has since been
corrected from the match reports, and `config/data_symbols.json` holds the
reviewed data mappings.  `match.py` sizes a function from
`symbols/functions.txt` and links named data from `config/data_symbols.json`,
so every checkout has to agree on them.  Do not run `make init`, `make regen`
or `analyze.py` on a checkout: they replace the index with a fresh scan of the
ROM, and `refine` then refuses the result.  `split` also rewrites
`symbols/ffta.sym`; restore it with `git checkout -- symbols/ffta.sym` unless
you meant to change it.  Never commit `asm/` or `files/`; the push gate
refuses the push if it finds `asm/`, `files/`, `baserom.bin` or a `.gba` in
the index.

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
* **Do not fake a match.** No inline asm, no optimisation pragmas, no
  `volatile` beyond the two exceptions the kit README defines, nothing that
  exists only to steer the compiler: a tricked match proves nothing.  What
  counts as a trick, and what is evidence, is the next section.

## Evidence first: what is a fake

A fake is source that exists because it moved the bytes.  Source that exists
because the ROM shows it is not one, even when it does nothing at run time:
the original had it, and dropping it is the less faithful reading.  Other
matching projects keep such code when evidence explains it - pokeemerald has
kept a [test whose arms do the same thing][pe-arms] since 2017 (the same text
since 2021), Ocarina of Time ships [`dz is always 0`][oot-zero], Dragon Quest
IX [`one of these is always zero`][dqix-zero] - and so does this one.  Some
(Ocarina of Time, Majora's Mask) also ship unexplained fakes under a marker;
this project parks those.

**Ships.**  Inert code and a once-through loop carry a comment that cites the
ROM ("Mark it" below); a helper carries one when it has shared text to cite:

* **Inert code the ROM contains.**  A test whose arms compute the same thing,
  when the ROM still performs the test: the two `ands` at 0x0800AF94 and
  0x0800AF9A whose results are never used; in 0x0800ADD8 the bit-0 test at
  0x0800ADF0 and a 0x4000 test on each side (0x0800ADFA, 0x0800AE08), whose
  paths enter the same two bodies, one side alone adding `mov r2, ip`
  (0x0800AE48).  A term that is always zero on its path, when the
  instructions need it and the term is one of the function's own variables,
  with other values on other paths: `height = y - start` with `start` 0 gives
  the `beq` loop entry at 0x0800F8AC, `height = y` gives `ble`, and the next
  arm sets `start = y - height`.  The ROM cannot choose between `y - start`,
  `y + start` and `y | start`; write the one with a meaning.  A zero made for
  the purpose is a spare temporary.  A sibling with the same shape is the
  strongest evidence.
  **Compile the plain form first.**  agbcc duplicates a loop's entry test by
  itself, so a second test in front of a loop is just the loop
  ([pokeemerald #2323][pe-2323]).  If the plain form matches, it is the
  source.
* **A `static inline` helper that does a real operation** - a lookup, a draw,
  a clamp, a test with a meaning.  One expression is enough when it computes
  something: `tile_at` in 0x080BE074 is a grid lookup, `map + (y << 4) + x`.
  A missing out-of-line copy is not evidence against it: the compiler drops
  unused copies (pokeemerald's [`SetU8`..`SetPtr`][pe-inline] are absent from
  its symbol file).  Text shared with a matched sibling, or a verbatim copy
  of a real ROM function
  (`/* An inlined copy of func_080A83A4 (src/080A83A4.c). */`), is the
  strongest evidence: cite it when it exists.  Shared text counts only when
  the sibling is already merged on `main` and the PR leaves the sibling's
  matching text alone; otherwise the PR is writing its own evidence.  A PR
  may move a merged sibling onto a shared statement macro only when the ROM
  repeats the block instruction for instruction, with the same result
  registers (`HEIGHT_DIFFERENCE`: 0x080A014E-0x080A0170 and
  0x080A035A-0x080A037C, in 0x080A0014 and 0x080A0254, which differ only in
  where the call arguments come from), and its comment gives both ranges.
* **A once-through loop** (`do { ... } while (0)`, `for (;;) { ...; break; }`)
  only as the body of a statement macro the ROM shows expanded more than once
  ([OoT's `CLOSE_DISPS`][oot-macro] is the same idea, evidenced by its debug
  build).
* **Switch cases with the same body under separate labels**, when the ROM
  tests each value on its own: in 0x0800D7B4 modes 1 and 2 are compared at
  0x0800D7C8 and 0x0800D7D6 and enter one body at 0x0800D7E4;
  `case 1: case 2:` compiles to a range test instead.  This is ordinary C,
  not inert control flow.
* **The same statement in two arms that otherwise differ**, when the ROM
  keeps it in each: `src/080CBA84.c` scales the index by 32 in both arms, and
  the ROM has the shift in each block (0x080CBA9A, 0x080CBAAC).  For a store
  at the end of both arms the evidence is the ROM storing and at once
  reloading the same location, where the two tails were merged; compile the
  single store after the join first.  The arms differ, so this is not the
  identical-arms case under "The gate does not move".

**Does not ship** - nothing in the ROM can point at these:

* a helper in one of the four shapes the [DQIX kit refuses][dqix-shapes]: an
  identity wrapper (returns a parameter, unchanged or cast), a constant
  offset-add (a pointer parameter plus a constant), local-then-return
  (`T v = expr; return v;`), or a [chain][dqix-chain] of three or more
  wrappers that each only call the next.  The exception is shared text as
  defined above: a helper in one of these shapes still ships when a sibling
  already merged has the same text or it is a verbatim real ROM function,
  and that shared text is its evidence;
* a once-through loop written bare in a function body;
* a spare temporary, a cast that changes no value, a dead initialiser, a
  self-assignment, or a type chosen for where the allocator then puts the
  value (an `s16` local for a byte the ROM loads with a plain `ldrb`).

**Declaration order is not a device.**  Every source has one, so a match that
depends on the order of its locals is a match, and the PR description records
the dependence.  It is a fake only when the order exists purely to steer in
combination with locals that have no other reason to be there - and then the
locals are the fake.

**Mark it.**  A `/* */` comment at the construct, a few lines at most, saying
what the ROM shows and where: the address of the dead or duplicated test, or
of the instructions whose order needs the term.  If all the comment could say
is "needed to match", there is no evidence and it is a fake.  The PR
description states the same ROM evidence for every inert construct it ships,
and for every helper what it does or which text it shares.  Write the
comment as a fact about the ROM: `plausible.py` refuses comments that say the
code steers the compiler (`so the compiler will`, `to make it match`,
`workaround`).

**The gate does not move.**  `plausible.py` stays the authority on what CI
accepts, and nothing here licenses respelling a construct to get past one of
its findings.  Its `dead-code` rule (the kit's "dead code") refuses `if (0)`,
`while (0)` and `#if 0`, exempting only the `while (0)` that closes a
nonempty `do { ... } while (0)` making up the whole body of a `#define`.  Its
`inert-control-flow` rule (the push gate's "no inert control flow") refuses
`if (c) X; else X;` with single-statement arms of the same text, and no
`plausible:` comment clears it.  Braces, a parenthesised condition, an
`else if` chain or spacing inside an arm (`x=1` against `x = 1`) hide such
arms from the rule but do not change what they are, and braces added only to
pass the gate are the respelling ruled out above.  Identical arms of one
statement each therefore stay parked, braced or not, until
[kit issue #201][kit-201] is decided; the proposal there is a
maintainer-owned entry per function in place of a rule about layout.  Arms
that declare or run more than one statement are braced because C requires
it, and ship with the evidence and comment above.

**Fakes are debt.**  `Parked/` is this project's
[`NON_MATCHING`][non-matching], source kept out of the build, and it also
takes byte-identical C that needs a fake: its README names the device, and
the address is retried.  Shipped inert code is not a fake; its comment is how
the next reader finds it and re-checks it.  pokeemerald marked its fakes,
removed [the last marked one in 2021][pe-1412] and has kept replacing
constructs it shipped since ([#2323][pe-2323]).

agbcc idioms that read as dead code or steering but are source - a bit-field
register store, a numeric hardware address, a size halved at the call - are in
[`docs/toolchain.md`](docs/toolchain.md#idioms-that-look-like-steering-but-are-source).

[pe-arms]: https://github.com/pret/pokeemerald/blob/9103e529c2fbdd7add4a1ff3350c6c1f92112c42/src/scrcmd.c#L1926-L1929
[pe-inline]: https://github.com/pret/pokeemerald/blob/9103e529c2fbdd7add4a1ff3350c6c1f92112c42/src/battle_setup.c#L1039
[pe-1412]: https://github.com/pret/pokeemerald/pull/1412
[pe-2323]: https://github.com/pret/pokeemerald/pull/2323
[oot-zero]: https://github.com/zeldaret/oot/blob/14759abf9abb4295de142cdc1452998630ea70fb/src/overlays/actors/ovl_Boss_Goma/z_boss_goma.c#L628
[oot-macro]: https://github.com/zeldaret/oot/blob/14759abf9abb4295de142cdc1452998630ea70fb/include/gfx.h#L102-L107
[dqix-shapes]: https://github.com/ZevyaDev/dqix-decomp-kit/blob/ff36e0d6ecdd056db7262a211fdb3a3777d35b36/plausible.py#L729-L756
[dqix-chain]: https://github.com/ZevyaDev/dqix-decomp-kit/blob/ff36e0d6ecdd056db7262a211fdb3a3777d35b36/plausible.py#L1041-L1058
[dqix-zero]: https://github.com/DQIX/dqix-decomp/blob/cbebe1e6a98e886d852aba2ee31715aa506260da/src/Filesystem/Overlay_33/Ov33BackgroundLoader.cpp#L244-L249
[non-matching]: https://github.com/zeldaret/mm/blob/3be2e24123f5e71fd13f939ecc0f9d7f73252639/docs/CONTRIBUTING.md#non_matching-and-non_equivalent
[kit-201]: https://github.com/shubshub/fftadecomp-kit/issues/201
