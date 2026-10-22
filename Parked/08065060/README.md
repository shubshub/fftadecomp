# 08065060 — natural recovery, not a match

The complete target is `[0x08065060,0x0806514C)`: **236 bytes / 82
instructions**, comprising 168 code bytes, ten literal words, five local
switch-table words and eight internal zero bytes. There is no external
alignment inside this span. The retained candidate also emits exactly one
236-byte ELF function and 236-byte `.text`, with the same instruction
addresses, pool/table positions and alignment. It is nevertheless not exact:
**188/236 positional bytes and 54/82 same-address instructions agree**.
All non-code bytes agree. The remaining 48 byte differences occur in 28
instructions, involving register operands, arithmetic association and load
scheduling within the five cases. The switch, case destinations, calls,
epilogue and full symbol boundary are not truncated for comparison.

- Target SHA256: `02dd19acae16b0325733a011a62e2ec7968fee56029dc3ad3b09132900ad2d69`
- Linked candidate SHA256: `5ff8bdc0f14ee4563cc19b2b47e913ab74866dcafb47b41b67fbe24f772d98b2`
- Source SHA256: `80b5ecb4166b7eebd509ac6c7b3d2ca684527b4b9370603f7855cc3ec6a35891`

## Independent verifier limitation

Frozen toolkit `4847c93`, using the normal `-mthumb-interwork -O2` flags,
rejects the actual source before comparison:

```text
switch evidence excludes object, callback and runtime-thunk bindings
```

The source calls the actual installed function-pointer slot `0x0836D4BC`;
agbcc correctly emits `_call_via_r3`, bound to the actual BX-r3 thunk at
`0x08142250`. It is not renamed or declared as an ordinary direct helper to
evade that restriction. Separate scratch diagnostics link the two real
external function symbols and local section relocations, check the entire
ELF modification surface and compare the complete symbol. Those diagnostics
are not an official proof-profile acceptance or matching report. The source
passes the address-scoped plausibility check. No active source or match report
is retained, and no toolkit extension alone would fix the existing byte
differences.

## Recovered operation and interface

The compatible interface is `u32 func_08065060(void *task)`. The full return
word combines pointer bits and tagged scalar values; a unique historical
nominal return type is not asserted. Only incoming r0 is consumed under the
already grounded ordinary helper contracts. The function saves r4/r5/LR,
allocates no local frame and has no incoming stack argument.

The closed `void *func_08005BFC(void *)` helper returns task+0x18. The local
payload view has container pointer at zero, halfword count at +6 and kind byte
at +8. Target-compiler assertions verify offsets, alignment four and size
12 for this observed prefix; this is not a recovered complete allocation.
Count is read before kind. Subtraction narrows to u16, then the selected case
interprets it as signed16 and multiplies by four. Multiplication fits s32;
conversion from u16 to s16 follows agbcc's target-specific two's-complement
behavior, not a portable implementation-independent promise.

Kinds 3 through 7 address container+0x424 plus that signed displacement:

- Kind 3 loads a source pointer, copies 0x10 bytes to container+0xA3C, reloads
  payload's container pointer after the call and returns the reloaded base+0xA3C.
- Kind 4 loads a pointer, then returns its first unsigned halfword.
- Kind 5 loads a pointer, then returns its first byte OR 0x10000.
- Kind 6 reads the unsigned halfword directly at the slot address and returns
  it OR 0x20000; it does not dereference a pointer stored there.
- Kind 7 copies 0x108 bytes to container+0xA4C, with the same post-call reload.
- Other kind bytes return zero without reading the container or slots.

The function-pointer slot contains `0x03005EE9`. Its audited forward-copy
body is `[0x03005EE8,0x03005F26)`, backed by ROM
`[0x08A38A9C,0x08A38ADA)`. It is not memmove: aligned transfers use ordered
word reads/writes, otherwise byte reads/writes. No null, index, capacity or
copy-failure guards are invented. Ordinary C behavior requires valid aligned
payload and appropriately typed slot/pointee storage, valid pointer arithmetic
and enough copy backing. Signed negative-index machine execution does not
establish an original array bound or authorize out-of-object C access. The
pointer-to-u32 result conversion is specific to this 32-bit target ABI.

## Bounded natural forms

1. A direct byte-offset switch with copy source expressions embedded in each
   call produced one 236-byte/82-instruction function, but only 145 positional
   bytes and 40 same-address instructions agreed. It also saved an extra r6.
2. The retained switch expresses pointer-slot indexing and captures each
   selected copy source before its call. This matches the observed data-read
   sequence and uses the expected save set, without artificial lifetimes or
   register assignments. Kind 6 retains a direct byte-addressed halfword view,
   rather than treating its scalar slot as a loaded pointer. That type-view
   clarification does not change the generated bytes.

No other optimization modes, manual jump table, added guard, forced inline,
storage annotation, volatile access or artificial control flow was tried.
The source is a useful bounded recovery, not a claim of inherent impossibility
or original source provenance.

## Actual-code behavior evidence

The retained self-cleaning reproducer executes **82 independently modeled
target/candidate pairs (164 executions)**. It runs real 5BFC, the real BX-r3
thunk and the actual copied forward-copy code, with no helper stubs. Each side
makes 28 actual copy calls. All 82 caller instructions, both accessor
instructions, the thunk and all 31 copy instructions are covered.

Fixtures cover all five cases and defaults; zero/max scalar values; ordinary
counts 1, 2, 3, 4 and 17; signed-index edges 0/0x8000/0x8001/0xFFFF; aligned
and unaligned copy sources; forward/backward copy overlap; and copies that
overwrite the payload's container pointer before the required reload. RAM and
object contents are synthetic. Twenty selected signed-index edge fixtures and
two payload-overlap fixtures are explicitly machine-only diagnostics, not
valid-C allocation/alias claims. Default cases still avoid all slot accesses.

An independent operation oracle checks exact ordered non-stack reads, writes
and call arguments, return value, complete synthetic EWRAM, unchanged
non-stack IWRAM, r4-r11, SP and return control. Paired traces also agree with
literal/table reads included in every case. Maximum observed stack depth is
12 bytes without copying and 20 with the actual copy helper. This bounded
matrix does not prove arbitrary allocation, alias, initialization or memory
safety conditions.

Reproduce with the retained address-scoped script, which builds an isolated
full-header tree, performs the ordinary rejected check and separate linked
diagnostics, then cleans all generated binaries:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/08065060-author/check.py
```

Only this recovery and README are production files. The small scratch script
and text log are retained for independent review; no ROM or binary artifact
is retained. Entry evidence is structural/indexed-family evidence; no inbound
reference or unique original nominal type is claimed.
