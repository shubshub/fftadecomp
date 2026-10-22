# 0800977C — Parked natural recovery

Disposition: **PARKED, not MATCH**. Only the original compiler flags
`-mthumb-interwork -O2` were used. The first natural recovery and its failed
layout checks are retained in `first-form/`; one evidence-grounded slot-layout
correction produces the final source. No ordering, register, flag or spelling
search was performed.

## Complete ownership and metadata proposal

The actual Thumb body is `[0x0800977C,0x08009888)`: **268 bytes, 88 instructions**,
comprising 200 code bytes through `0x08009844` and seventeen reached literal
words through `0x08009888`. There is no unowned gap or alignment inside this
extent. The next indexed prologue at `0x08009888` is excluded. Reachable Capstone
CFG classification and Binary Ninja instruction lengths agree; `CLASSIFIED.txt`
records the ownership rather than treating the linear pool decode as code.

The old 208-byte end `0x0800984C` truncates fifteen required pool words.
`metadata-proposal.diff` changes only this entry's end and count in both maps:
`0x0800984C -> 0x08009888`, `104 -> 88`, retaining kinds and neighbors. It also
proposes two independently grounded data bindings absent from the immutable
baseline: `g_callbacks_0836D4B8 = 0x0836D4B8` and
`g_table_0854CD7C = 0x0854CD7C`. All changes are private fixture/proposals, not
production edits. Input mapping hashes are in `input-pins.json`.

## Natural contract and target layouts

The no-argument, void-return routine calls the installed clear callback for
`[0x02000000,0x02003CA8)` and `[0x02003CB0,0x02007CB0)`, sets the word at
`0x030034B0` to one through `08002824`, copies four ROM bytes from `0x0851BA4E`
to `0x02002FC0`, and calls the bit initializer `080C9340` and `080099C4`.
It reads a halfword count at descriptor offset `0x438` and a record pointer at
offset `0x43C`, then calls `080C9644(destination, source, 0)` for each record,
using destination stride `0x108` and source stride `0x30`. After `080CC0DC`, it
writes nine byte flags at descending two-byte spacing, stores 5000 at
`0x02001F64`, and calls `080CA900` with `(0x16A,10)`, `(0x16F,4)`, `(0x175,4)`
and `(0x177,2)`. It finally clears bytes `0x0300284C` and `0x0300280C` and writes
one to `0x02002185`. Helper results are discarded.

The observed ROM count is six, the source pointer is `0x0852CDE0`, and the six
0x30-byte accessed records occupy `[0x0852CDE0,0x0852CF00)`. These observations
do not establish a nominal table allocation size or validity of larger counts.
The two cleared arenas are disjoint, with an untouched eight-byte gap. The
scene-record view begins at `0x02000080` inside the first arena; this overlap is
intentional and is not a claim that the views are distinct ISO C objects.

Thirteen agbcc assertions verify pointer sizes, `MainState` size `0x3CA8`,
amount/initialized/slots/tail offsets `0x1F64/0x2185/0x21B4/0x2FC0`, two-byte
slot stride, record sizes `0x108` and `0x30`, descriptor size `0x440`, and its
count/pointer offsets. The first form used a two-member `u8` structure for a
slot; agbcc rounded that structure to four bytes, invalidating the slot stride,
tail offset and main-state size. Replacing only that type/use with `u8[9][2]`
corrects the measured layout. `source-correction.diff` records the exact delta.
The first form's 260B/84I output is not transferred as runtime evidence; the
final 260B/85I output has fresh runtime checks.

The direct helper declarations follow existing source contracts. Canonical
`memcpy` uses `unsigned long` for this compiler's `SIZE_TYPE`; there are no
compiler warnings. The raw RAM constants and pointer representations are
target-specific. Existing translation units declare `g_state_02000000` and
`g_state_02000080` with fragmented, incompatible views; these new partial views
do **not** establish whole-program ISO C declaration compatibility, original
aggregate identity, effective types or an independent-object alias model.
Backing, alignment, object lifetime, and helper ABI/retention assumptions remain
conditions of this recovery, not consequences of an exact byte comparison.

## Official rejection and separate complete ELF discrepancy

The approved toolkit's ordinary profile exits 1 with:

```text
compile failed:
call target must be an undefined addressed function
```

The original ELF contains canonical `memcpy`, not an addressed runtime alias.
The current binding path rejects that symbol. No newer composition profile,
source renaming or verifier bypass was used. No official MATCH report exists;
strict replay rejects an attempted MATCH claim made from the rejection log.
This is not a positive replay result or a supported-profile NOT MATCHING report.

Separately, a **diagnostic-only typed link** binds that canonical symbol to the
actual ROM copy routine `0x081443FC`. Other direct calls bind to unique indexed
Thumb functions; callback thunks are checked against their actual BX encoding;
data relocations use the independently grounded mappings. Original relocations,
function symbol type/value/size, full allocated `.text`, relocated words/calls,
and absence of unresolved relocations, veneers or changed non-relocation bytes
are checked. This diagnostic is not official acceptance.

| Complete image | Bytes | Instructions | Code | Literals | Internal alignment |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROM target | 268 | 88 | 200 | 68 | 0 |
| Final candidate | 260 | 85 | 194 | 64 | 2 |

The candidate symbol occupies all 260 bytes of `.text`, alignment 4, with no
external padding. At equal offsets, 60 bytes agree and 200 differ; eight target
bytes are missing. `build.json` gives every differing offset and
`compiled.txt` includes both complete images. Thus even resolving the verifier
limitation would not make this source a byte match. Natural code selects the
r5 callback thunk instead of the target's r2 thunk; this was not steered.

- Target SHA-256: `44bf25879e0e8b0f6ec13a0fbcf6b17362995c521d01f8c61a97b0d50514f0bc`
- Candidate SHA-256: `ac909f9e84bee02cf58a8c4930ff27f1f84e84e0d22f9b64e5a8ab82f84a23d3`
- Source SHA-256: `31ff3305f59959d4709ec7705ebc42ae6c7350b8dcbff7f3cea1b1ececc95cc6`

## Bounded execution evidence and limits

`runtime.py` executes six ROM/candidate pairs, twelve returning executions.
Four pairs retain the original count-six ROM; two explicitly synthetic fixtures
replace only that count with zero or one to cover the loop boundary. They are
not claims about additional original-ROM states. Cases vary RAM fill, discarded
model returns, model side effects, word-aligned SP, and Thumb/ARM return state.

Actual machine code runs for the clear routine, the r2/r5 callback thunks,
`081443FC` copy, `08002824` setter, `080C9340` bit initializer and its `080C9574`
dependency. Complete dependency spans, including needed literals, are pinned
in `runtime-results.json` and decoded in `dependency-classified.txt`.
The clear image executes at RAM `0x03005E78`, copied by the harness from the
actual ROM image beginning `0x08A38A2C`. Installer literals and the ROM callback
slot establish the relevant source/destination association; **installation,
startup and BIOS are not executed or proved**. Correct installed bytes, Thumb
entry, lifetime, stability and call ABI are explicit preconditions.

Four helpers are **whole-call ABI models**, not actual helper execution:
`080099C4`, `080C9644`, `080CC0DC` and `080CA900`. The record model reads sixteen
bytes from each actual ROM record and writes a deterministic destination
marker. Other models write selected initialized-state/marker fields; selected
CA900 cases also overwrite the amount after the caller writes 5000. The models
clobber caller-saved registers and flags and supply arbitrary discarded return
values. They do not prove inventory behavior, full record conversion, hidden
global effects, callback retention, alias safety or helper termination.
Their finite returning, non-retaining behavior is the model contract.

The independent scalar oracle checks the normalized ordered call trace, every
ordered non-stack write, entire EWRAM, IWRAM outside active stack frames, saved
caller registers/LR, restored SP, r4-r11, and interworking return. Actual r2/r5
thunk addresses are separately recorded, not asserted identical. Reads of RAM
require initialization, and stack reads/writes must remain inside the current
allocation; fresh pushes invalidate prior initialization for that allocation.
The caller saves 20 bytes and measured maximum nested depth is 32 bytes in both
images. Their instruction-by-instruction stack traces differ and are recorded
separately; no equality of stack traces is claimed.

All 88 target and 85 candidate caller instructions are reached. Actual helper
coverage is clear 19/25, each thunk 1/1, copy 23/49, setter 3/3, C9340 51/51,
C9574 23/23; unexecuted clear/copy branches are not proved. Nine executed
negative controls detect wrong copy destination, source/destination strides,
slot stride, item identifier/quantity, final flag, actual clear value and actual
copy store address. A separate pre-execution guard excludes count seven from
the bounded observed source window; it does not prove such a count inherently
unsafe. No exhaustive input, universal helper, whole-program or hardware proof
is claimed.

## Reproduction and handoff

From this artifact directory, run:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 check.py
```

The checker uses the immutable `game-next-94599c9` and approved
`kit-software-double-candidate-v3`, all nine unchanged headers, the installed
fixed compiler, the approved ROM, and the pinned read-only CFG decoder from
`08009394-author/check.py`. `input-pins.json` records inputs. Temporary fixture
trees are disk-backed beneath this directory and automatically removed.
Retained artifacts are text only. No source/report is installed into production;
parent coordination owns metadata integration, Parked placement and lease release.
