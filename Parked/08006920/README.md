# 08006920: interpolation-task wrapper, verifier-blocked

One natural C form is retained in Parked. Its complete linked function bytes
equal the ROM, but the frozen official matcher rejects its proof profile.
There is no active source or successful match report for this address.
No original-source provenance or inherent unmatchability is claimed.

## Complete symbol and official result

- Target extent: `[0x08006920,0x08006940)`, 32 bytes / 13 instructions.
- Code occupies the first 28 bytes; the final four-byte literal contains the
  Thumb callback address `0x08006721`. No padding lies inside this span.
- Both target and complete linked candidate SHA-256:
  `ec2443a344d0b3540835eb651fb1ab8b2c995ce107350eb905f42581472dc7ff`.
- Standard `agbcc -mthumb-interwork -O2` produces one code-defined `STT_FUNC`
  of 32 bytes, exactly the full `.text`, including its callback pool. Typed
  linking resolves the direct call to `08005B6C` and the function-address
  relocation to `08006720`; there are no extra functions, veneers, unresolved
  relocations or byte differences. Scoped source plausibility passes.
- The frozen `kit-reviewed-4847c93` official command exits 1 with:

```text
compile failed:
stack aliases cannot cross calls in caller-clobbered registers
```

The descriptor address crosses the call in r2. The callback-address manifest
selects `verify_function_addresses`, which invokes local CFG checking without
the outgoing-buffer proof context. That same frozen profile also has an
explicit frameless-caller restriction after its CFG check. Thus the observed
rejection is not a compiler byte mismatch; the function-address and outgoing
stack-buffer requirements are not jointly certified by this profile. The
diagnostic linked comparison is not an official MATCH or successful replay.
No source rewrite, fixed callback integer, custom binding, toolkit change or
flag sweep was used to evade that boundary.

The production index endpoint is correct. The coordinating session applied
the independently reviewed instruction count correction from 16 to 13.
The author did not modify mappings, shared headers or reservation state.

## Interface and partial descriptor

The compatible local interface returns a full task pointer and consumes
`(const void *records, u16 count, void *parent)`. The wrapper stores the full
record pointer at descriptor `+4`, then low16 count at `+0x14`. Original r2
becomes the helper's full parent pointer in r3; original incoming r3 is not an
input. There is no incoming stack argument. The call receives callback 06720,
payload size 12, the descriptor address and parent, in that order. Its full
returned pointer is forwarded unchanged.

The descriptor object is 28 bytes, aligned to four. Only six bytes are
initialized. Its state, unknown members and remaining 22 bytes are not zeroed
or established initialized values. Six target-compiler assertions verify
size, alignment and offsets for state, records, count and the trailing bytes.
The unsigned16 source formal expresses low16 capture; later signed use by the
callback does not uniquely determine the original nominal formal type.

The reused `task-5b6c-contract/CONTRACT.md` establishes that 5B6C forwards this
descriptor to 5954. The latter copies all 28 bytes in seven ascending word
reads into its own local descriptor, overwrites local state halfword 0 with
zero, and dispatches the callback with task/local-descriptor/payload pointers.
The callback scalar result is ignored. 5B6C then reloads manager state and
stores the full manager halfword XOR 1 to the returned task. Allocation,
backing storage, list validity and callback behavior remain the callee
contracts; this wrapper introduces no guards.

The callback's state 0 audit supports copying the record pointer and
sign-extending descriptor count into payload count. Its later traversal,
division and termination domains remain separate obligations. The engine's
machine copy does not prove that arbitrary typed reads of the 22 indeterminate
bytes are valid C, or that a callback may retain either local descriptor
pointer beyond its lifetime. Callback and parent pointer retention in task
storage are separate from descriptor lifetime.

This recovery declares a three-`void *` callback interface matching the active
helper's `TaskCallback` contract. The separate Parked 06720 recovery defines
its second and third arguments using specific event/payload pointer types.
These have the observed three-position machine ABI, but the declarations
are not a demonstrated compatible C function type across those translation
units. Linking an address does not prove C type compatibility. Any future
combined source promotion must coordinate those declarations; no callback
cast, whole-program type proof or shared original typedef is claimed here.

## Bounded independent checks

The reproducer freshly compiles and links the retained source, repeats the
official rejection in an isolated scratch root, validates all 32 symbol bytes,
checks the six layout assertions and runs seven target/candidate execution
pairs, fourteen executions total. Both bodies use their own complete bytes;
the target is read directly from the local ROM.

Five pairs cover readable record addresses, counts 0/1/0x7FFF/0x8000/0xFFFF,
and null/non-null parent pointers. Two additional machine-only pairs exercise
upper incoming count bits, null and arbitrary pointer bit patterns, and zero
or arbitrary helper return values. They do not assert valid C objects or
successful real task creation for those machine-only inputs.

An explicit modeled 5B6C boundary checks callback, size, descriptor address and
parent, then clobbers caller-saved registers and returns a chosen pointer.
An independently constructed byte oracle checks the descriptor's two stores
and all 22 untouched bytes against seeded stack memory. Every execution covers
all 13 wrapper instructions and agrees on the ordered three writes (saved LR,
record pointer, count), 32-byte maximum local depth, full synthetic EWRAM and
IWRAM contents, preserved r4-r11, restored SP, return control and full result.
Seeded physical bytes are test data, not proof of initialized C values.

Neither the real 5B6C/5954 engine nor the dynamic callback executes in these
checks. They are wrapper/ABI evidence under the explicit helper model, not
transitive engine correctness, callback typing/lifetime, universal termination
or blanket C equivalence. The real callee facts above come from the retained
audits rather than the model.

Run the small retained reproducer outside the repository:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/scratch08006920-author/check.py
```

Its isolated roots and generated binaries are removed on completion. Only
the C/README in Parked and the small external reproducer are retained.
