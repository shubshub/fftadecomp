# 08006970 — explicit transition endpoints, verifier-limited recovery

This natural C recovery produces the complete target bytes, but remains
**Parked, not an official MATCH**. Frozen `4847c93` `match.py` exits 1 with:

```text
compile failed:
stack aliases cannot cross calls in caller-clobbered registers
```

The descriptor address escapes in r2 at the helper call. Typed callback-address
linking selects the function-address verification profile, whose local CFG
check rejects that alias. The same profile also explicitly limits callers to
frameless bodies; this function has a 28-byte frame. The observed rejection is
the alias diagnostic, not a successful outgoing-buffer proof. No toolkit
change, opaque address cast or alternate source form was used to evade it.
There is no active source or match report.

## Complete byte result

The indexed body is `[0x08006970,0x080069B0)`, 64 bytes / 28 instructions.
Its 58 code bytes end at `0x080069AA`, followed by two zero alignment bytes
and the callback word `0x0800664D` at `0x080069AC`. No bytes from the next
prologue are included. The coordinating session applied the independently
reviewed instruction count correction from 32 to 28; endpoints are unchanged.

The first natural struct-field implementation compiles with the required
`agbcc -mthumb-interwork -O2` to one 64-byte FUNC and 64-byte `.text`.
Separate diagnostic typed linking resolves the BL at `0x0800699E` to
`08005B6C` and the trailing callback-address relocation to `0800664C|1`.
The final executable has no unresolved relocations or added text. All 64
bytes, including alignment and the literal pool, equal the target.

- Source SHA-256: `29e276476b6d3deb1079e0bbc2af3d34857224d4e2f1caff5f28b2789d3f413d`
- Complete target and candidate SHA-256: `4757a486ac2df50543c5f1a8b29988674feb3b9c30f0124d6439a0cc618036ae`

These byte and linking facts do not override the failed official profile.
Only this one grounded source form was tried. No flag sweep, artificial
initialization, volatile access, assembly, pragma, dead control flow or storage
layout trick was used. The individual-source plausibility check has zero findings.

## Interface and initialized fields

The compatible six-position interface is:

```c
void *func_08006970(u8 initial_first, u8 initial_second,
                  u8 target_first, u8 target_second,
                  u16 duration, void *parent);
```

The first four inputs contribute only low8. The fifth and sixth inputs are
genuine entry-stack words at `+0` and `+4`: after 16 saved bytes and 28 local
bytes, they are loaded from current SP `+0x2C` and `+0x30`. Duration contributes
low16; parent remains a full pointer. No argument is omitted or fabricated.

The three ordered stores initialize descriptor halfwords `+0x14`, `+0x16`
and `+0x18` to the packed initial pair, packed target pair and duration.
The wrapper calls `08005B6C(callback, 0x38, descriptor, parent)` and forwards
the full task-pointer result. The callback's scalar return is unrelated.

Six target-agbcc assertions verify `TransitionEvent` size 28, alignment four,
state offset zero and the three stored offsets. Its signed duration field
agrees with the existing callback recovery. Conversion from the u16 argument
to that s16 field relies on the target compiler's observed low16 storage;
the wrapper alone does not uniquely determine the original signed formal.
The local view describes observed offsets, not a uniquely recovered typedef.

## Partial descriptor and callback limits

Only six of the 28 descriptor bytes are initialized. The remaining 22,
including bytes `+0x1A/+0x1B` in the last word, are indeterminate rather than
zero. The reused `task-5b6c-contract/CONTRACT.md` establishes that the immediate
helper forwards the descriptor to `08005954`, whose seven ascending word
reads copy all 28 bytes before it replaces its own state halfword with zero.
The machine copy does not establish safe arbitrary typed reads of those
indeterminate bytes.

The engine dispatches the callback with task, its local descriptor and payload,
ignores the callback result, and can retain callback and parent pointers.
Allocation success, valid backing, finite lists, callback accesses, termination
and retention remain contract obligations. The original descriptor and the
engine's descriptor copy both have local lifetimes; no universal no-retention
claim is made for dynamic callbacks.

The declaration of `0800664C` retains the recorded `TransitionEvent` and
`TransitionPayload` pointer types. Its conversion to the helper's generic
`TaskCallback` matches the machine ABI, but a function-pointer cast does not
prove the actual callback definition is C-call-compatible with a generic
`u32(void *, void *, void *)` invocation. The existing parked callback and
engine need coordinated declarations before any source-wide compatibility
claim. No shared header or another author's source was changed.

## Bounded validation

The self-cleaning reproducer recompiles the retained source in an isolated
disk-backed root with current maps, copied small headers and a ROM symlink.
It reproduces the official rejection, checks source plausibility, complete
ELF size/link closure and all bytes, and runs the six target layout assertions.

Six returning input pairs execute both the actual ROM wrapper and candidate:
12 executions covering all 28 caller instructions. A separately expressed
arithmetic oracle checks the packed fields, exact order and width of both
incoming-stack reads and all three descriptor writes, every descriptor byte
at the call, callback/size/parent positions, full returned pointer, all mapped
RAM, SP and callee-saved registers. A modeled `08005B6C` boundary deliberately
clobbers caller-saved registers and returns distinct task pointers. It does
not execute the real allocation engine or callback.

Fixtures include zeros, maxima, mixed endpoints, `0x7FFF`/`0x8000` duration
boundaries and null/non-null parents. The last fixture deliberately fills
upper input bits and is a raw-machine narrowing diagnostic, not proof of a
source-language call with out-of-range u8/u16 arguments. Varied initial stack
patterns establish that the uninitialized descriptor bytes are left alone
in these executions; they do not supply defined C values for those bytes.
These finite local checks are not transitive callback, lifetime, allocator
or all-input equivalence proofs.

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 \
  scratch08006970-author/check.py
```

The retained scratch directory contains only the small reproducer and its text
log. Temporary compiler objects and binaries self-clean. Parent owns mapping
correction, reservation release and any checkpoint report refresh.
