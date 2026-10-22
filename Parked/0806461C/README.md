# 0x0806461C — paired script handshake, nonmatching recovery

## Status and complete extent

This is a plausible natural C recovery, not a byte-exact match. No active
source or match report is retained, and the bounded attempts do not establish
that the function is inherently unmatchable.

The complete target is `[0x0806461C, 0x08064774)`: 344 bytes and 161 reachable
Thumb instructions. Its SHA-256 is
`e0f8a8a0f6d7bdd79c2eff5420d9b99fe62da8443598ed8884e8b5201a890a6b`.
Code occupies `[0x0806461C, 0x08064678)`,
`[0x08064680, 0x0806472C)`, and `[0x08064734, 0x0806476E)`
(322 bytes). Literal words at `0x08064678`, `0x0806467C`,
`0x0806472C`, `0x08064730`, and `0x08064770` contain
`0x030028A0`, `0x0200F450`, `0x03002890`, `0x03002B50`, and
`0x03002B50`, respectively. The zero halfword at `0x0806476E` is internal
alignment and belongs to the complete symbol. The next function starts at
`0x08064774`; none of its bytes belong to this target.

There are no calls, local frame, or incoming arguments. The routine saves
r4-r7/LR and returns through the saved LR in r0. A compatible interface is
`void func_0806461C(void)`. Entry evidence is the indexed prologue, complete
closed CFG, and adjacent boundary; an incoming reference was not established.

## Compiler evidence and bounded attempts

Both attempts use agbcc with `-mthumb-interwork -O2` and the same grounded
local types. Initially defining both signal pointers at function entry
produced 366 bytes / 172 instructions. Assigning those pointers at their first
actual use produced the retained clearer 360-byte / 166-instruction form.
No register assignment, storage, alignment, optimization, or artificial
control-flow forcing was attempted.

The retained relocatable ELF has one `STT_FUNC`, size 360, exactly 360 bytes
of `.text`, and no relocations. Its complete function SHA-256 is
`224795a2bac2b2800505aeac2f8d71850e2fb0a3b0b71560faa4de8b570c1f44`.
Strict leaf CFG checks and scoped plausibility pass. This is a code-generation
mismatch, not an unsupported verifier feature.

The official toolkit 4847c93 check reports `NOT MATCHING - bytes differ` and
245/360 LCS-equal bytes. Its comparison window follows the emitted 360-byte
symbol and therefore includes 16 bytes after the true 344-byte target. That
display is not a valid target-size or positional-match claim. A separate
comparison against only the complete 344-byte target finds 26 equal byte
positions and a 245-byte LCS. The candidate's different register allocation,
address materialization, branches, and literal placement affect the whole
body: it keeps the input base in r6 and state slot in r7 early, uses an
absolute literal for input `+0x122`, and moves several state accesses through
the high scratch register. The target uses different live pointers and
offset calculations. The C does not encode those compiler-specific choices.

## Semantics and domain

The input at `0x030028A0` triggers an initial transition when halfword
`+0x120 != 0`, or halfword `+0x122 > 20` and byte `+0x02 != 3`, with
short-circuit reads. The state comes from the pointer slot `0x0200F450`.
If state flags `+0x54` contain `0x20`, the routine clears that bit, stores
`0xFF` to byte `+0x52`, reloads the state slot, pops one script entry, and
returns. Otherwise it appends `0x44` then `0x34`, each with current/count/entry
stores in that order, sets current to `0x36`, and continues.

When the incoming signal at `0x03002890` has identifier `+0x02` equal to
state `+0x64`, its value `+0x04` is copied to state `values[1]` if input
byte zero has bit `0x08`, otherwise `values[0]`. After a state-slot reload,
if both values equal state `+0x66`, byte `+0x51` controls completion.
A zero countdown clears state values in order `+0x6A`, `+0x68`, then outgoing
value/identifier at `0x03002B50`, then incoming value/identifier; it pops an
entry, clears flag `0x20`, and returns. A nonzero countdown is decremented
and falls through even when the new value is zero.

The ordinary fallthrough writes input byte `+0x124 = 0x16`, reloads the state
slot, and writes the outgoing identifier from state `+0x64`. Its outgoing
value selection has the opposite polarity: input bit `0x08` selects
`values[0]`, otherwise `values[1]`.

The local tagged views are coordinated with the adjacent `0x08064508`
recovery without changing shared headers or declaring new named globals.
Target-compiler probes establish:

| View | Size / alignment | Observed fields |
| --- | --- | --- |
| `ExtendedScriptState` | `0x6C` / 4 | count `0x02`, entries `0x04`, byte `0x51`, byte `0x52`, word flags `0x54`, halfwords `0x64`, `0x66`, values `0x68`, `0x6A` |
| `ScriptSignal` | 8 / 4 | halfwords identifier `0x02`, value `0x04` |
| `ScriptInput` | `0x128` / 4 | bytes `0x00`, `0x02`, `0x124`; halfwords `0x120`, `0x122` |

The extended view preserves the established prefix offsets but is not claimed
nominally compatible with the shorter canonical `ScriptState`. The recovery
requires appropriately aligned genuine backing objects for all accessed
members, including state storage through `0x6B` and a valid state-pointer
slot. The inherited 34-entry array gives ordinary pop counts 1 through 34
and two-append counts 0 through 32. These are operation preconditions, not
proved runtime invariants; no underflow, capacity, pointer, or alias guard was
invented. Counts on paths that do not index entries need no array bound from
those operations. Signal/input structure sizes are compiler-layout evidence,
not proven external allocation sizes or array strides. Arbitrarily overlapping
typed objects are not asserted to have valid ISO C effective types or lifetimes.

## Reproducible behavior evidence

The retained disk-backed reproducer is
`/home/user/.codex-work/ffta-ulw/0806461C-author/check_recovery.py`.
From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/0806461C-author/check_recovery.py Parked/0806461C/0806461C.c
```

It freshly compiles the complete source with the actual header set, verifies
one function/no relocations, complete CFGs, source plausibility, and target
layouts, then executes actual target ROM and fresh candidate instructions
against an independently written ordered-operation oracle. There are no
helpers or stubs. All RAM contents are explicitly synthetic fixtures.

The suite passes 272 pairs / 544 executions: 260 ordinary-domain cases,
eight explicitly machine-only overlapping-view cases, and four explicitly
machine-only zero-count pop cases. It covers all 161 target and 166 candidate
instructions, both selector polarities, early return and normal fallthrough,
input boundaries 20/21, kind 3 versus other kinds, flags with unrelated high
bits, countdowns 0/1/255, values 0/0x8000/0xFFFF, valid pop counts 1/32/34,
and valid two-append counts 0/1/32.

Every tested pair has the same final nonstack RAM, exact ordered state-memory
reads and writes, preserved r4-r11/SP, and return destination; each target
execution also agrees with the independent oracle. The machine-only fixtures
do not establish defined C array or alias behavior. Trace equality is limited
to EWRAM/IWRAM data accesses excluding stack, ROM literal loads, and instruction
fetches, not equality of machine-instruction traces. The bounded tests do not
prove arbitrary-pointer validity, allocation bounds, general alias equivalence,
or original source provenance. Generated binary artifacts are automatically
removed after every run.
