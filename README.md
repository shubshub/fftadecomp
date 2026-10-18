# FFTA (AFXE) — decomp workspace

A byte-exact, from-scratch disassembly and layout of *Final Fantasy Tactics
Advance* (USA, `AFXE`), ready to start decompiling.

The analysis, split and matching harness live in`**fftadecomp-kit**`; they produced everything
here from the ROM in this directory. No third-party decomp tool output is used.

---

## The ROM

| | |
|---|---|
| File | `Final Fantasy Tactics Advance (USA).gba` (copy kept as `baserom.bin`) |
| Size | 16,777,216 bytes (16 MiB) |
| SHA-1 | `4AC05441F4DE70A4EC3DD932116346C61B8783D9` |
| Title / code | `FFTA_USVER` / `AFXE` (USA), maker `01` |
| Entry point | `0x080000C0` (`b 0x080000C0` at `0x08000000`) |
| Verified rebuild | `rebuild.py` (in the kit) → SHA-1 matches the base ROM exactly |

### ⚠ Two things about this ROM you should know first

**1. The cartridge header is not a clean retail header.**

* The Nintendo logo at `0x08000004`-`0x0800009F` does not match the BIOS logo:
  148 of its 156 bytes differ.
* The header checksum is wrong: computed `0x85`, stored `0x89`.

Real hardware (and BIOS-accurate emulators) reject a ROM whose logo does not
match, so this file as-is would not boot on a cartridge or a strict emulator;
it runs fine in emulators that skip the logo check. Whatever produced this file
— a re-dump, a re-release build, a header-scrambling pass — it means the header
has been modified, so **treat it as a working copy, not as a pristine baserom.**
If you have another dump of the same revision, compare SHA-1 before starting a
matching build.

**2. This ROM's code region is only the first ~1.3 MiB.**

The layout is not "text, then rodata, then gfx" like an unstripped build:

| ROM range | Size | What it is |
|---|---|---|
| `0x08000000`-`0x080000C0` | 192 B | cartridge header |
| `0x080000C0`-`0x08150000` | **1.31 MiB** | **code region** — Thumb-dominant, data and literal pools interleaved |
| `0x08150000`-`0x08A39820` | ~9.5 MiB | assets: high-entropy blobs (~7.5 bits/byte, compressed or packed) and 4bpp tile data (~3.5-4.5) |
| `0x08A39820`-`0x08FE1350` | ~5.9 MiB | zero padding |
| `0x08FE1350`-`0x08FFFFFF` | ~124 KiB | `0xFF` padding to the 16 MiB boundary |

Startup chain, walked from the entry point:

```
0x080000C0  ARM   crt0: CPSR/user-mode switch, stack and IRQ vectors, then
                    `ldr r1,[pc,#0x154]; mov lr,pc; bx r1` into Thumb
0x08000254  Thumb  init: hardware setup, table copies, then calls into the
                    function at 0x08000670 and others
0x08000670  Thumb  first "real" game function (117 instructions)
```

---

## What the analysis found

`5,455` functions — `5,335` Thumb, `120` ARM — and `156,843` bytes of verified
instruction bodies (`77,268` instructions). Median function body is 10
instructions; the largest found is 128. Function boundaries come from a
prologue pattern **plus** a linear walk that must reach a return or a tail
branch, which is what keeps the 4bpp tile data from producing thousands of
fake functions (the byte pair `0xB5xx` looks like `push {rX, lr}` about once
every 300 KiB of tile data).

Per 64 KiB of ROM, verified code density:

```
0x08000000   17.1%   ##########
0x08010000    6.3%   #####
...
0x08140000    8.1%   #####
0x08150000    0.7%          <- falls off a cliff: assets start here
```

---

## Layout of this repo

```
baserom.bin            verified copy of the ROM (gitignored)
asm/
  ffta.s               master armips script: includes the chunks below
  code_00000000.s ..   one file per 64 KiB of the code region, labelled asm
  code_00140000.s
  tail.s               everything after the code region, .incbin in file order
  manifest.json        every run of the ROM in address order
files/                 raw bytes: data_* and code_* runs (6,675 files)
symbols/
  functions.txt        address end size instrs, human readable
  ffta.sym             address size name (func_08000670 ...)
config/
  rom_layout.json      header, per-segment classification, stats
  coverage.json        code/data runs, RLE-style
  functions.json       the function list, machine readable
logs/analysis.txt      full analysis report (coverage table, segment dump)
tools/               see fftadecomp-kit (this repo's data is produced by it)
src/                 matched C only - one file per function
include/ffta.h       base types, struct shapes, prototypes
docs/toolchain.md    how the compiler was identified, and how to build it
docs/match/          per-function match reports
Parked/              attempts that do not match yet (see the rule in Matching)
Makefile             thin wrapper around the kit
linker.ld            GBA memory map reference
```

The tooling lives in its own repo so it can be used on any GBA image:

```sh
git clone https://github.com/shubshub/fftadecomp-kit.git    # private
make check KIT=../fftadecomp-kit
```

---

## Using it

The analysis needs nothing but Python 3 and capstone, on any OS:

```sh
python -m pip install capstone

python ../fftadecomp-kit/tools/analyze.py baserom.bin .   # ROM -> config/, symbols/, logs/
                                                          # (~10 min, 16 MiB)
python ../fftadecomp-kit/tools/split.py   baserom.bin .   # analysis -> asm/, files/
python ../fftadecomp-kit/tools/rebuild.py .                 # must print: byte for byte
```

`make check` is the same as `rebuild.py`; `make regen` runs all three. Under
WSL/Linux, `../fftadecomp-kit/tools/bootstrap.sh` installs the rest of the toolchain.

### Rebuilding with an assembler

```sh
make rom      # armips asm/ffta.s, then verify against the base ROM
```

The `.incbin` data guarantees every non-code byte is right; the assembly in the
code region is what armips has to re-encode exactly.

---

## Matching

**The compiler has been identified: agbcc — `gcc 2.9-arm-000512 for Thumb/elf`**
(12 May 2005). Full details, build instructions and the flag study are in
[`docs/toolchain.md`](docs/toolchain.md).

```
agbcc -mthumb-interwork -O2
```

Four functions are byte-exact matches, each verified by compiling the C and
comparing it against the ROM:

| address | bytes | what it is |
|---|---|---|
| `0x08017514` | 18 | four byte stores, 4th argument on the stack |
| `0x080112D4` | 20 | copies three `s16` fields out of a struct |
| `0x08006ADC` | 26 | table slot write + flag clear (u8 index) |
| `0x0801CD4C` | 26 | scatters 4 bytes from the table at `0x02007F10` |

```
python ../fftadecomp-kit/tools/match.py 0x08017514   # or: make match ADDR=0x08017514
```

The tool preprocesses (`agbcc` is a raw cc1 and does not run cpp itself),
compiles, assembles, strips, and diffs against the ROM bytes.

Two findings worth keeping in mind while writing C:

* **The compiler reads stack arguments straight off `sp`** — 286 functions in
  the ROM do this, with no frame pointer. Modern GCC will not.
* **Address constants must go in a variable.** For `func_0801CD4C`, writing
  `((u8 *)0x02007F10)[0x0d]` inline makes the compiler fold every access into
  its own literal-pool entry; a local pointer gives the single load the ROM has.

### Rule for this repo

**Only byte-exact matches are committed.** A function that compiles but differs
does not go in `src/` — work on it goes in `Parked/<address>/` with its match
report, until a compiler or flag change makes it exact.

### Flags still open

`-O1`, `-O2`, `-O3` and `-Os` all reproduce the four matched functions; they
only differ on inlining (`-O3` inlines most, `-O1` least). A function that calls
a static helper will pin the level down. `-mthumb-interwork` and "some
optimization enabled" are already established.

---

## Honest limits of this first pass

* **Function bodies are linear sweeps.** They stop at the first branch or
  return, so a function with internal branches currently shows only its entry
  block; the rest is in `files/code_*.bin`. As you match functions, extend the
  bodies.
* **Literal pools are data gaps**, which is why code and data alternate
  throughout the code region. Turning the `data_*.bin` gaps between functions
  into `.pool` + named constants is the first thing to do per function.
* **A few functions come from jump tables** (overlapping ranges, `endby=linear`),
  and a handful of false positives survive deep in the asset regions. Compare
  against a real disassembler (Ghidra/IDA) when you start a specific area.
* **The header is wrong** (see above) — decide what to do about that before
  committing to a matching build.

---

## Next steps for an actual decomp

1. **Work through the small functions.** The four matches are all leaf
   functions with no branches. The next ones to take are the other complete
   leaf/straight-line functions (`0x08011040`, `0x08017AC4`, `0x0801E68C`, …)
   — same shape, same harness, and each one teaches you about struct layouts.
2. **Pin the optimisation level** by finding a function that calls a static
   helper and checking whether the call survives: that separates `-O1` from
   `-O2`/`-Os` from `-O3`.
3. **Set up objdiff** (`cargo install objdiff`) to get per-function progress.
   Note `mips_to_c` does not apply — it only reads MIPS.
4. **Name as you go.** `func_08017514` → whatever it really does, in
   `symbols/ffta.sym` and in the `.global` lines of the asm.