# 080082EC: exact diagnostic recovery, unsupported official profile

## Disposition

Parked, not an official MATCH. The first natural C form reproduces the entire
106-byte ROM function after diagnostic-only canonical runtime linking. The
approved matcher instead exits 1 with `call target must be an undefined
addressed function`. Its supported profiles do not bind this caller's
`__floatdidf`, `__subdf3`, `__floatsidf`, and `__divdf3` calls. It emits no report;
there is no strict report replay success or progress credit to claim.

Only one source form and the fixed agbcc `-mthumb-interwork -O2` flags were used.
The source uses natural signed-integer conversion, double subtraction, and
division, without addressed runtime declarations, assembly, artificial storage,
or compiler steering. Diagnostic linker symbol definitions are separate test
artifacts, not an official verifier bypass. No production files or tools were
edited. Integration and the accepted reservation's release remain coordinator-owned.

## Complete ownership and compilation

The complete interval is `[080082EC,08008356)`: 106 bytes, 48 instructions,
including five four-byte BLs. Recursive Capstone CFG coverage accounts for
every byte as code, with no pools or internal padding; Binary Ninja agrees on
each instruction boundary. No indexed entry overlaps this interval. The zero
halfword at `08008356` is external alignment before indexed entry `08008358`.
The sole metadata proposal changes 53 to 48 instructions in both maps, leaving
endpoints, mode, byte size, and kind unchanged.

The original ELF contains one complete 106-byte function and 108-byte,
four-byte-aligned `.text`, ending with external assembler alignment `c046`.
Canonical `R_ARM_THM_CALL` relocations are:

| Offset | Name | Diagnostic ROM target |
| --- | --- | --- |
| 24 | `__floatdidf` | `081428E4` |
| 50 | `__floatdidf` | `081428E4` |
| 62 | `__subdf3` | `081430B4` |
| 72 | `__floatsidf` | `0814383C` |
| 84 | `__divdf3` | `0814339C` |

The diagnostic link checks function mode/alignment/full size, exact relocated
targets, unchanged non-relocation bytes, no unresolved relocations, no generated
stubs or other nonempty allocated sections, and equality of objcopy output with
ELF `.text`. The complete function, not a truncated prefix, equals the ROM:
106/106 bytes and 48 instructions. Both bodies have SHA-256
`156815ce4bb16acab2a0ade1dab51deee88519f76bdc5aa709adfe04879e42f7`.

## Recovered contract

Arguments are a record-array pointer, output-state pointer, two opaque 32-bit
values, a signed count, and signed step count. The last two are read from
entry-SP and entry-SP+4. The caller saves 20 register bytes and allocates 8
local bytes, so those reads occur at current-SP+28 and +32.

Each record has an observed 80-byte stride and begins with a signed 64-bit
coordinate. The remaining 72 bytes are named unknown bytes, justified by that
stride rather than added to influence compilation. The output prefix is 48
bytes: opaque words at offsets 0/4; cleared words at 8/12; count/steps at 16/20;
and double start/end/increment at 24/32/40. Names describe the recovery, not
proven original types or subsystem identity.

The function writes the two opaque words, count, and steps; converts the first
record coordinate to double and stores start; converts record count-1 and
stores end; stores `(end-start)/steps`; then clears offset 12 followed by offset
8. It returns void. It does not check count, capacity, pointer validity, or a
zero step count.

The tested C contract requires count >= 1, a live record array of at least
count elements, a live writable state object, correct target alignment, and
valid pointer/index arithmetic. The first and last consumed record coordinates
must be initialized before their reads; unused record bytes need not be initialized. Records, state, and stack are disjoint in the
tests. Steps must be nonzero; negative steps including INT_MIN are supported
by selected cases. Zero-denominator C semantics are not asserted. Arbitrary
aliasing, undersized objects, or invalid counts are not treated as defined
inputs. Sixteen target-compiler assertions verify sizes and all listed offsets.

Signed 64-bit integers use low-word-first little-endian representation; target
doubles instead store the high 32-bit word first, each word little-endian.
Separate freshly compiled initializers verify both conventions. Double helper
operands use high/low register pairs, while the signed64 conversion accepts
low/high. Conflating those layouts would invalidate the oracle.

## Actual dependencies and bounded verification

Local agbcc `libgcc/libgcc2.c` and `libgcc/fp-bit-base.c` structurally support
the canonical helper identification. The signed64 conversion scales the signed
high word by 65536 twice and adds the unsigned low word; the signed32 conversion,
subtract, and divide paths agree with their emitted canonical names. This is
not an official byte-identity proof or an independently rebuilt runtime library.

`check.py` recursively classifies the closed twelve-window ROM dependency graph,
including all referenced literal words. Window hashes and call edges are saved
in `results.json`, and decoded code/literals in `DEPENDENCIES.txt`. Windows
may include external alignment; they are not metadata repairs or newly claimed
functions. All runtime helpers and reached descendants execute their actual ROM
instructions. No helper-return hook, BIOS model, or arithmetic helper model is used.

Sixteen paired cases (32 successful executions) compare ROM and the diagnostic
candidate. Counts 1 through 4 exercise identical endpoints and different first/last
records. Values include positive/negative small integers, signed-word boundaries,
2^32 and 2^53 boundaries, and exactly representable INT64_MIN; denominators
include positive/negative integers and INT_MIN. Every selected conversion,
difference, and quotient is exactly representable, so the Python numeric oracle
does not claim untested rounding behavior. Passing cases do not establish all
signed64 conversions or general software-floating correctness.

Each execution checks exact ordered external writes and caller helper operand
bits, complete initialized EWRAM contents, permitted record reads, guarded stack
bounds, r4-r11 preservation, SP restoration, incoming stack-argument preservation,
and ARM/Thumb return state. The paired executions also have identical external
read traces. Both word-aligned entry-SP variants are exercised. The conservative
closed-call-graph stack bound is 248 bytes; observed depths are 232 and 240 bytes.

All 48 caller instructions and the signed64 conversion, signed32 conversion,
add, subtract, and negation wrappers are covered. Other dependency coverage is
partial, recorded per window: divide 135/188, pack 94/139, unpack 48/97, parts
272/302, multiply 220/323, integer multiply 53/56, and logical shift 0/27.
Static closure is not evidence that every helper branch executes.

Three caller mutants (stride, count destination, cleared field), one actual
signed32-conversion helper mutant, and two record-capacity negatives are all
detected. There is no claim about NaN/Infinity, subnormals, exceptional inputs,
rounding modes, floating environment, or arbitrary helper RAM state. Some helper
paths depend on mutable object `03005E50`; the harness rejects accesses outside
the active stack, and none of the passing cases accesses that object. ROM hashes
alone would not establish its initialization or lifetime.

## Reproduction

The isolated fixture uses immutable `game-next-94d6d0c` (497-source baseline),
all nine headers from its source/include paths, and approved `kit-next-702e7f3`.
Input/source/header/tool hashes are recorded and checked unchanged after the run.
No prior source or Parked entry for this address exists in that baseline.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

The script uses the requested official `--mode thumb --no-write` invocation,
then performs separate diagnostic and runtime checks. Temporary compiler and
fixture trees are self-cleaning. Only source, documentation, and reproducible
text/JSON evidence remain. The count-only patch is pinned to the immutable
baseline and must be reconciled with newer coordinator mappings, not used to
replace them wholesale.
