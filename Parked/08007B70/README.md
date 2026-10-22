# 08007B70: boundary extrapolation recovery, not a match

## Disposition

Retain the first natural C form as Parked. No source variants, compiler-flag
search, addressed runtime aliases, artificial storage, or tool changes were
used. The approved matcher rejects the compiler's canonical `__adddf3` and
`__subdf3` relocations with `call target must be an undefined addressed
function`. This is a missing supported runtime binding, not a successful proof.
There is independently also a genuine complete-body byte mismatch; adding
runtime support would not make this candidate exact.

The complete ROM and compiled function are both 274 bytes and 129 instructions.
Only 46/274 bytes agree at their corresponding positions; 228 differ. The first
difference is `08007B7A`: ROM allocates 36 local bytes (`89b0`), while the
candidate allocates 32 (`88b0`). Both save 32 register bytes, for caller frames
of 68 and 64 bytes respectively. Register allocation, instruction scheduling,
and call positions also differ. The discrepancy list and complete diagnostic
disassembly are retained locally; a four-byte frame difference is not presented
as the sole mismatch.

No official report is emitted, so there is no official MATCH or strict replay
success to claim. Production source, reports, mappings, and tools were not
modified. Integration and reservation release remain coordinator-owned.

## Complete extent and metadata

The ROM owns code throughout `[08007B70,08007C82)`, with eight four-byte BLs,
121 other two-byte instructions, and no literal pool or internal padding.
Capstone recursive control flow covers all 274 bytes; Binary Ninja independently
agrees on each instruction boundary. The zero halfword at `08007C82` is external
alignment before the next indexed entry `08007C84`, not part of this function.
No indexed entry overlaps the body.

The minimal metadata proposal changes instruction count 137 to 129 in both
maps, preserving the endpoints, byte count, mode, and kind. It is pinned to the
immutable 495-source baseline; it must not overwrite newer coordinating-session
map changes. No dependency metadata corrections are proposed here.

The fresh object has one complete 274-byte function and a 276-byte, four-byte
aligned `.text` section; the final `c046` is external assembler alignment.
There are exactly eight undefined canonical `R_ARM_THM_CALL` relocations,
alternating add/subtract at offsets 86,104,122,132,168,178,200,210. A separate
diagnostic linker binds these names to the real Thumb wrappers solely to inspect
and execute the candidate. It asserts no generated stubs, unexpected allocated
sections, or unresolved relocations; objcopy equals ELF `.text`, and only the
eight relocation sites change from the object. This diagnostic link is not the
official verifier and does not authorize an addressed-alias fallback.

ROM body SHA-256:
`5b97dde70c1101e45e745dcd78827d7ab981b2f401aae54e6e9fc4f65e4c1bdf`.
Diagnostic candidate body SHA-256:
`82da08715dbdcce854be566a9129c0d5e3349d6783885e813d947fe0b0392615`.

## Recovered contract

Four register arguments are a state pointer, horizontal double-array pointer,
vertical double-array pointer, and signed count. Eight target-compiler assertions
check the 16-byte state prefix: pointers at offsets 0 and 4, signed count at 8,
and byte phase at 12; pointer/s32 sizes are 4 and double size is 8. The type names
are descriptive recovery names, not recovered original declarations.

The function first stores count, horizontal pointer, then vertical pointer.
For count <= 1 it returns zero without array access or a phase write. Otherwise,
for side 1 then 0, it performs the following assignments in this order:

1. `horizontal[side] = horizontal[2] + horizontal[2] - horizontal[4-side]`
2. the corresponding vertical assignment
3. `horizontal[count+3-side] = horizontal[count+1] + horizontal[count+1] - horizontal[count-1+side]`
4. the corresponding vertical assignment

It clears phase and returns `(count-1)*8`. This is sequential extrapolation of
two values on each side of the indexed samples, not a simultaneous transform:
for count 2 the second iteration can read a value written during the first.

The bounded C contract requires a live writable state object. On the array
path, both arrays are live aligned double objects with at least count+4
elements, disjoint from state and stack and from each other. Every consumed
array element must be initialized before its first read; an earlier write by
this function may provide that initialization. All indexed
pointer arithmetic must stay in those objects, and count arithmetic plus the
signed return multiplication must be representable. The tests do not establish
aliasing behavior or arbitrary capacity/count safety. There is no dynamic loop
termination assumption: the body loop executes exactly twice on this path.

## Floating-point dependencies and limits

ROM `08143080` and `081430B4` have the structural add/subtract wrapper behavior
in local agbcc `libgcc/fp-bit-base.c`: unpack two operands, optionally flip the
second sign for subtraction, add parts, pack. This is structural corroboration,
not a byte-exact rebuild of the runtime library or an official identity proof.
The closed recursive dependency windows, literal addresses, and hashes are in
`results.json` and `CLASSIFIED.txt`: negation `08142A94..08142AB0`, pack
`08142BE8..08142D34`, unpack `08142D34..08142E10`, parts
`08142E10..08143080`, the two wrappers through `081430F0`, and logical shift
`08144378..081443B0`. Windows include trailing alignment where applicable;
they are not proposed new function extents.

Target double representation stores the high 32-bit word first, with each word
little-endian. The first operand is r0=high/r1=low and the second r2=high/r3=low.
This is verified by the actual unpack code, the compiler's `thumb.h` setting,
and a freshly compiled double initializer. Internal integer64 helper pairs have
a different low/high convention. The harness initially assumed host little-endian
double layout; correcting only that fixture encoding made the unchanged source
and actual ROM agree.

The runtime cases use small finite dyadics with exactly representable
intermediates, plus signed zero; the Python arithmetic oracle is exact on this
limited domain. There is no general IEEE-754, rounding-mode, NaN payload,
infinity, subnormal, overflow, exception, or floating-environment claim. In
particular, parts code can return mutable RAM object `03005E50` on some special
inputs. No initialization or preservation of that object is assumed: the
bounded harness rejects access outside the caller/helper stack, and the passing
cases never access it. ROM identity alone would not prove that RAM dependency.

## Fresh bounded verification

`check.py` rebuilds a self-cleaning isolated fixture using all nine unchanged
baseline headers and fixed `-mthumb-interwork -O2`. It repeats the official
rejection, full-ELF diagnostic checks, plausibility, layouts, and real-ROM
runtime comparison. Reproduce from this scratch directory with:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

Twelve paired cases execute both raw ROM and the diagnostic-linked candidate
(24 successful executions), using counts INT_MIN,-1,0,1,2,3,4,5,6,12 and varied
positive/negative dyadics, cancellation, zero, and signed zero. They execute
the real ROM software-double routines: no helper hook or return model replaces
any helper. Both callers cover all 129 instructions and both wrappers are fully
covered. Dependency coverage is deliberately partial: negation 12/13, pack
94/139, unpack 48/97, parts 272/302, and logical shift 0/27. Listing the complete
static dependency closure does not imply every dependency path was executed.

Each execution checks exact ordered external writes, exact double-call operand
bits, the entire initialized EWRAM arena, object capacities, guarded stack
bounds, r4-r11 preservation, SP restoration, return value, and ARM/Thumb return
state. Both word-aligned entry-SP variants are exercised. External read traces
are recorded but not required to have identical ordering between implementations;
internal stack contents likewise differ with the frame. Maximum observed stack
depths are 204 bytes for ROM and 200 for the candidate. All accesses outside the
live objects, active stack envelope, and classified ROM literals are rejected.

Three caller mutations (small-count comparison, phase offset, return scale)
are detected. Undersized array capacity is rejected for ROM and candidate,
giving five negative controls. These finite tests support the recovered
contract only within their stated domain, not universal equivalence or an
official match.
