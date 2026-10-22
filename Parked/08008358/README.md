# 08008358: one-step fixed-point cubic evaluation, Parked

## Disposition and exact differences

The first natural C recovery is retained without source variants, flag searches,
assembly, artificial storage, addressed runtime aliases, or toolkit changes.
It is not a MATCH. The approved ordinary profile rejects the canonical runtime
relocations with `call target must be an undefined addressed function`, and no
official report is produced. There is also an independent genuine byte/extent
mismatch; supporting those runtime bindings alone would not make it exact.
This caller has no spin or loop, so the toolkit's explicit inert-spin profile
is neither relevant nor attempted.

ROM owns `[08008358,08008480)`: 296 bytes and 139 instructions, including nine
four-byte BLs. All bytes are reachable code; no literal pool or internal padding
exists. Recursive Capstone CFG and Binary Ninja agree on instruction boundaries.
The next indexed function begins immediately at `08008480`, with no alignment
gap or overlapping indexed entry. The count-only two-map proposal corrects 148
to 139, preserving endpoints, mode, kind, and byte size.

The candidate's complete ELF function is 286 bytes/134 instructions, ending at
`08008476`. Its four-byte-aligned `.text` is 288 bytes, with external `c046`.
Over the 286-byte overlap, 122 bytes agree and 164 differ; the remaining ten
ROM bytes have no candidate counterpart. No prefix truncation is used. ROM
saves 32 register bytes, candidate 28; neither allocates local SP space. The
first difference is at `0800835A`, with further register allocation, output
address scheduling, and return-path differences. The saved-frame difference
is not presented as the sole mismatch.

ROM body SHA-256:
`6bec81d78eec02bbb30186e31ed52154d4ef54730011744bdf2ef761f239fd09`.
Diagnostic candidate body SHA-256:
`e9536b7feddec63acec2868b732713aabd60a72e76eabd1883ab5ce936c2597d`.

Original ELF relocations are canonical `R_ARM_THM_CALL` entries at offsets
26,40,52,56,80,148,174,200,246: `__floatsidf`, `__muldf3`, `__adddf3`,
`__fixdfdi`, `__floatdidf`, three `__muldi3`, then `__floatdidf`. A separate
diagnostic typed link binds the real ROM helper addresses solely to inspect
and execute the candidate. It checks complete function size/mode/alignment,
relocated targets, unchanged non-relocation bytes, no unresolved relocations,
no generated stubs or other allocated payload, and objcopy/ELF `.text` equality.
It is not the official verifier, an addressed-source fallback, or a match report.

## Recovered state and operation

Arguments are an 80-byte-stride record-array pointer and a writable state
pointer. The record begins with five signed64 fields at offsets 0,8,16,24,32:
coordinate, constant, linear, quadratic, and cubic coefficients. The remaining
40 bytes are unknown, justified by the observed stride. The state prefix has
double output pointers at 0/4, signed position and segment at 8/12, unused
count at 16, signed step limit at 20, start double at 24, unused end at 32,
and increment double at 40. These are recovery names, not proven originals.

If position >= steps, return zero without changing state or output. Otherwise:

1. Convert `start + increment*position` to signed64, truncating toward zero.
2. Store double `(coordinate >> 16)` to horizontal[position].
3. If coordinate >= records[segment+1].coordinate, increment segment once.
4. Set delta to coordinate minus the selected record coordinate.
5. Evaluate the signed64 fixed-point Horner recurrence: multiply cubic by delta,
   arithmetic-shift 16 and add quadratic; multiply by delta, shift and add linear;
   multiply by delta, shift and add constant.
6. Store double `(value >> 16)` to vertical[position], increment position, and
   return whether the new position is still below steps.

This is one step, not a search or loop. It advances segment at most once even
if a coordinate passes several knots. The count and end fields are not read;
they do not enforce capacity or the segment domain.

## Domain and ABI limits

Both objects and output arrays must be live, correctly aligned, and sufficiently
large. Tests use disjoint records, state, outputs, and stack. On the active path,
position is nonnegative and is a valid index in both output arrays; segment and
segment+1 refer to valid records, including after the optional increment.
Pointer/index arithmetic must stay in the objects. The inactive path permits
negative signed values satisfying position >= steps and never dereferences the
record/output pointers.

The computed floating coordinate must be finite and its truncation representable
as signed64. Delta subtraction, each multiplication and coefficient addition,
and signed indices must not overflow. ROM integer operations are modular, but
that does not make signed C overflow defined. Negative signed right shift is
target-defined: the compiler probe and ROM ASR instructions establish arithmetic
shift for this toolchain, not portable ISO C behavior. The bounded cases explicitly
check every signed64 arithmetic intermediate before executing the caller.

Twenty-three compiler assertions cover record/state sizes, field offsets,
scalar sizes, signed right shift, and fractional truncation. Separate initialized
objects prove signed64 low-word-first little-endian and binary64 high-word-first,
with each double word little-endian. Integer64 and double helper register-pair
conventions differ accordingly. The caller uses r0/r1 arguments and preserves
r4-r11 and SP; bounded tests also check ARM and Thumb return state.

## Actual-helper tests, not models

`check.py` classifies a closed twenty-window dependency graph from the real ROM,
including referenced literals. `DEPENDENCIES.txt` and `results.json` retain
code/literal classification, call edges, window hashes, and partial runtime
coverage. Window ends can include alignment; these are diagnostic ownership
windows, not additional metadata corrections or author claims. Local agbcc
`libgcc2.c` and `fp-bit-base.c` structurally corroborate canonical identities;
this is not an official runtime identity proof or byte-exact library rebuild.

Sixteen paired cases run ROM and candidate, for 32 successful executions. All
reached arithmetic helpers and descendants execute their actual ROM instructions;
there are no helper-return hooks, arithmetic substitution models, or BIOS calls.
Cases cover inactive exits, remaining/final positions, nonconstant cubic terms,
positive/negative coordinates, fractional truncation, negative intermediate
shifts, equal knots, signed high-word and unsigned low-word comparisons, and
one-only segment advancement despite passing multiple knots.

For these selected inputs the floating arithmetic and integer-to-double results
are exact; the Python numeric oracle is scoped to that domain. The subsequent
float-to-integer truncation is tested separately, including negative fractions.
No universal floating-rounding, NaN/Infinity, subnormal, overflow, exception,
floating-environment, or arbitrary runtime-state claim is made. Some untested
helper paths depend on mutable `03005E50`; the harness forbids access outside
the active stack and passing cases never use that object. A ROM hash would not
prove its initialization or lifetime.

Each run checks ordered external writes, exact caller/helper argument bits,
the complete initialized EWRAM arena, output capacity and record/state access
bounds, stack guards, callee-saved registers, SP, return value, and return mode.
ROM/candidate write and argument traces agree; their external read traces are
recorded but not required to have identical order. Stack contents are not
equated across the different frames. Both word-aligned entry-SP variants are
exercised. Conservative closure bounds are 292 bytes (ROM) and 288 (candidate);
observed maxima are 284 and 280, with inactive depths 32 and 28.

The runtime suite covers all 139 ROM and 134 candidate instructions, but not
every helper path. Per-window coverage is retained rather than implying full
dependency coverage. Six negative controls detect three caller changes
(unsigned knot comparison, signed fixed-point shift, and position destination),
an actual signed32-to-double helper mutation, and undersized output capacity
for each caller. These finite tests support the recovery within the stated
domain, not all-input equivalence or an official MATCH.

## Reproduction and isolation

The immutable baseline is `game-next-94d6d0c`, with all nine source/include
headers. The approved toolkit is `kit-inert-spin-candidate-v2` (published
`c0279edb`), using its ordinary default profile. The baseline contains no source
or Parked entry for this address. Exact input/header/tool/source hashes are
recorded and checked unchanged around the run.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

The reproducer invokes the requested official `--mode thumb --no-write`
command before diagnostic linking. No official report exists, so no strict
replay success is claimed. Generated compiler/fixture trees are self-cleaning;
only source and text/JSON evidence remain. Production files, shared headers,
tools, maps, status, and reservations were not edited. The coordinator owns
integration and release. Reconcile the narrow metadata patch with current maps;
do not replace newer maps with this immutable baseline.

## Independent review: initialization limits

Fresh actual-helper executions observe reads before a write in the current stack
allocation at `08142BEE`, `08142BF0`, `08142CE2`, `08142E94`, and `08142E98`.
These are helper instructions, not caller reads. The review initializes machine
stack memory with two concrete nonuniform byte patterns and obtains the expected
results for both callers, in ARM and Thumb return modes. This does not prove
independence from arbitrary initial stack contents or initialized-C semantics
inside the helpers. No arithmetic/helper model replaces these instructions;
mutable helper storage `03005E50` remains forbidden in the passing fixtures.

Consumed state fields must have valid initialized values: `position` and `steps`
on every path, and `horizontal`, `vertical`, `segment`, `start`, and `increment`
on the active path. The inspected next record's coordinate and the selected
record's coordinate and four coefficients must likewise be initialized. Unused
`count`, `end`, and record bytes at offsets 40 through 79 need not be initialized;
the caller does not read them. Outputs require writable capacity, not initialized
prior contents. The finite machine tests are not a universal C-definedness or
all-input equivalence proof, and do not change the Parked disposition.
