# 08009920 — Parked byte-mode configuration

## Verdict and first form

**NONMATCH; Parked only.** The one natural switch-based C form remains
unchanged from the first compile, SHA256
`69bc329630851c72f94a267509b90ae665d0bb5ba27d78bbcd2f9e2e60e1d095`.
The fixed `agbcc -mthumb-interwork -O2` candidate is46B/23 instructions,
versus the complete ROM68B/26 instructions. No source spelling, statement
order, register, type, control-flow or compiler-option iteration was used.

The compiler synthesizes03000000 once with `movs`/`lsls`, then uses a compact
two-comparison dispatch. ROM repeats `cmp #1`, has a signed less-or-equal
default edge after the first equality test, and materializes03000000 through
three separate literal words. Block ordering, allocation and stores differ.
There are33 positional differences in the46-byte common prefix, first+6,
and22 additional target bytes. The target extent was not shortened.

The unchanged approved toolkit rejects the candidate at the complete-symbol
gate: `compiled symbol is shorter than the indexed span: 46 < 68`. The
requested `--no-write` run and a separate report-generation attempt both exit1.
No report is emitted, so there is no accepted report or strict-replay success
claim. A forged bare MATCH is rejected. This is a real code-generation/extent
mismatch, not an unsupported canonical helper or special-profile limitation.

## Complete ownership and metadata

The indexed span `[08009920,08009964)` is complete and does not overlap the
next indexed entry08009964. Raw branch/literal calculations, reachable
Capstone CFG and Binary Ninja instruction lengths establish:

- 52 code bytes containing26 instructions, no BL or other helper calls.
- Required literals at0800993C,0800994C and08009960, each03000000:12 bytes.
- Two internal zero halfwords at0800994A and0800995E:4 bytes.
- Total68 bytes; no external alignment in the owned ROM span.

The existing34 count treated all halfwords as instructions. The separate
`metadata.patch` changes only34→26 in both maps, with endpoint/mode/kind
unchanged. There are no data-symbol proposals or header changes.

The complete candidate symbol is46 bytes, all executable, with no literals
or internal alignment. Its original .text is48 bytes because an external
`c046` assembler-padding halfword follows the symbol; that halfword is
explicitly excluded from the46-byte candidate and cannot fill the target gap.
Original and linked ELF symbols are typed Thumb functions of size46 at
values1 and08009921. Both have zero relocations and no undefined symbols.
A separate ordinary leaf link changes no .text bytes and introduces no stubs.
It is an extent/ELF check, not an alternate official MATCH path.

## Natural semantic contract

`void func_08009920(u8 mode)` writes two bytes through a fixed byte view of
03000000. After unsigned low8 normalization, mode1 stores(15,4) at offsets
0A/0B; mode2 stores(25,8); all other byte values store(10,2). Offset0A is
written before0B. It reads no previous field value, makes no calls, has no
C return value and has no stack arguments. The actual4B frame saves LR,
then restores it into r0 for interworking return; incidental final r0 is
not a recovered C result.

The byte view states access widths and offsets, not the nominal type or size
of the surrounding game allocation. Premises are live writable storage through
offset0B at this fixed target RAM address, a valid word-aligned stack frame
separate from those bytes, and valid ARM/Thumb return control. Integer-to-pointer
conversion is target-specific. No portable-host pointer claim, concurrency,
arbitrary alias, hardware side effect or lifetime proof is inferred.

## Fresh verification

Immutable base: `game-next-89c9cb3` (published84ef534,504 active).
Approved toolkit: `kit-software-double-candidate-v3`. The isolated fixture
copies all nine fingerprint-scope headers, applies only the grounded count
correction, and uses the unchanged ROM and fixed compiler flags.

`check.py` freshly compiles the source and runs1048 executions:262 input
register values × ROM/candidate × ARM/Thumb return. The262 values comprise
all256 canonical u8 inputs plus six raw upper-bit probes:100,101,102,
FFFFFFFF,DEADBEEF,80000002 (hex). Raw contaminated-register cases test the
observed machine narrowing separately; they are not claims about arbitrary
noncanonical C call conventions. No helper body, ABI model or BIOS is used.

An independent scalar oracle predicts both byte values. All26 ROM and23
candidate instructions are reached. Checks cover exact ordered stores and
literal/stack reads, no incoming RAM-value dependency, full unchanged EWRAM,
all untouched IWRAM bytes, both word-aligned SP residues modulo8, balanced SP,
saved r4-r11, and ARM/Thumb return. The tests exercise all byte-valued modes
under concrete entry/memory states; this is not universal proof over arbitrary
stack/global overlap, asynchronous mutation or target hardware behavior.

Six executed negatives detect either wrong output, a changed selector,
wrong byte narrowing, a relocated global literal and a widened store touching
adjacent bytes. Seven target scalar assertions pass. The matching
`void (*)(u8)` function-pointer declaration compiles without diagnostics;
u32-parameter and u8-return alternatives produce the expected incompatible
type warnings. These checks do not change the source signature or flags.

Complete original/linked ELF details, full candidate hex, classified code,
all positional differences, exact inputs and test results are retained as
text in `08009920-author`. Source plausibility has no findings. The two
initial evidence-harness issues (assuming an emitted report after early
rejection, and handling empty linker-stub sections/cleanup filenames)
were corrected in the checker only; they did not change the C or its bytes.

## Reproduction and cleanup

Run in a sibling copy of the frozen author directory:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 probe.py
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

The scripts capture/recheck source, headers, maps, toolchain, parent dump,
toolkit and ROM. Temporary fixtures, ELF/object/preprocessor/assembly files
are removed, including failed-run fixtures. Prior freezes and all production,
shared-header, Git, status and broker state remain untouched. Parent owns
claim6352033260 release, count integration and independent review.
