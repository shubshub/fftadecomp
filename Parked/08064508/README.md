# 0x08064508 — input-driven script transition, nonmatching recovery

## Status and complete extent

This is a plausible recovery, not a byte-exact match and not an assertion that
the function is inherently unmatchable. No active source or match report is
retained.

The complete ROM symbol is `[0x08064508, 0x0806461C)`: 276 bytes and 129
instructions. Its SHA-256 is
`36c7a8fe3bb5550f9f5b448faffea359adea5fb7865cbc0eeeb555a5ec36587d`.
Code occupies `[0x08064508, 0x08064536)`,
`[0x0806453C, 0x080645B4)`, and `[0x080645C0, 0x0806461C)`
(258 bytes). The zero halfword at `0x08064536` is internal alignment.
Four literal words at `0x08064538`, `0x080645B4`, `0x080645B8`, and
`0x080645BC` hold `0x0200F450`, `0x03002B50`, `0x03002890`, and
`0x030028A0`, respectively. There are no calls, local frame, jump tables, or
additional hidden arguments. Entry evidence is the indexed prologue and closed
local CFG; an incoming reference was not established.

## Compiler evidence and bounded attempts

All attempts used agbcc with `-mthumb-interwork -O2` and ordinary natural C:

1. Reusing one state pointer for the initial snapshot and later slot reloads,
   with an early return for special input, produced 256 bytes / 120 instructions.
2. Distinguishing the cached state from branch-local resumed state pointers
   produced 272 bytes / 126 instructions.
3. Keeping those meaningful snapshots and expressing ordinary transitions under
   `field_124 != 1`, with the special input in `else`, produced the retained
   270 bytes / 126 instructions. This mirrors the ROM branch organization and
   uses the same 12-byte register-save area.

The official toolkit 4847c93 check rejects the final source before byte
comparison: `compiled symbol is shorter than the indexed span: 270 < 276`.
There is no unsupported verifier feature to fix. The final relocatable ELF has
exactly one `STT_FUNC`, size 270, no relocations, and 272 bytes of `.text`;
the last two `.text` bytes are external compiler alignment, not part of the
function. Raw strict leaf CFG and scoped source plausibility checks pass.

The complete candidate symbol SHA-256 is
`bd81a3de83edff394c1bc385b9956b286de9bae1a43fcb3099cbc93b969730a7`.
A separate diagnostic finds 94 equal positional bytes against the full
276-byte target; this is not an official match percentage. The compiler derives
the input pointer from `0x03002890 + 0x10` instead of loading its own base
literal, and uses a literal for `0x030029C0` to read input `+0x120` instead
of the ROM's shifted offset and addition. Later register allocation and shared
branch/pool offsets differ too. No artificial address relationship was written
in C, and no layout, register, or optimization forcing was attempted.

## Semantics and type/domain contract

The compatible interface is `void func_08064508(void)`. The routine consumes
no incoming arguments and restores LR through r0, so no meaningful scalar
return is inferred.

The pointer slot at `0x0200F450` selects the initial state. If flags `+0x54`
bit `0x10` is clear, it clears bit `0x20` and pops the script stack. Otherwise
it clears state values `+0x6A`, `+0x68`, then signal value/identifier halfwords
`+4`, `+2` at `0x03002B50` and `0x03002890`, in that order.

Input byte `+0x124 == 1` selects state value zero when input byte zero has
bit `0x08`, otherwise value one. It copies state `+0x66`, writes state byte
`+0x51 = 0x10`, reloads the slot, and writes current opcode `0x3A`.
Other input causes a transition only when halfword `+0x120 != 0`, or when
halfword `+0x122 > 200` and byte `+2 != 3`, preserving short-circuit reads.
The cached state's flag word is reloaded. Bit `0x20` causes clear/store, byte
`+0x52 = 0xFF`, slot reload, and pop. Otherwise the routine appends `0x44`,
then `0x34`, storing each as current before updating count/entry, and finally
sets current to `0x36`.

The local tagged types are coordinated with the adjacent recovery without
changing shared declarations. Target-compiler probes establish:

| View | Size / alignment | Observed fields |
| --- | --- | --- |
| `ExtendedScriptState` | `0x6C` / 4 | count `0x02`, entries `0x04`, byte `0x51`, byte `0x52`, word flags `0x54`, halfwords `0x64`, `0x66`, values `0x68`, `0x6A` |
| `ScriptSignal` | 8 / 4 | halfwords identifier `0x02`, value `0x04` |
| `ScriptInput` | `0x128` / 4 | bytes `0x00`, `0x02`, `0x124`; halfwords `0x120`, `0x122` |

The extended prefix preserves existing field offsets but is not claimed
nominally compatible with the shorter canonical `ScriptState`. The recovery
requires genuine appropriately aligned backing objects for the accessed
members, including state storage through `0x6B`; no allocator invariant or
actual object lifetime is inferred. The inherited 34-entry declaration gives
ordinary pop counts 1 through 34 and two-append counts 0 through 32. Counts on
paths that do not index the array are not constrained by those operations.
No capacity, underflow, null, alias, or allocation guard has been invented.
Signal/input structure sizes are compiler-layout evidence, not proven external
array strides or allocation extents. Arbitrary overlapping typed views are not
asserted to be valid ISO C objects.

## Reproducible behavioral evidence

The retained disk-backed reproducer is
`/home/user/.codex-work/ffta-ulw/08064508-author/check.py`. From the game root:

```sh
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/08064508-author/check.py Parked/08064508/08064508.c
```

It freshly compiles the complete candidate and target-layout probe, checks the
single function, lack of relocations, scoped plausibility, and complete strict
CFGs, then executes actual target and candidate instructions in Unicorn against
a separate ordered-operation oracle. There are no helpers or stubs.

The suite passes 605 pairs / 1,210 executions: 588 normal-domain synthetic-RAM
fixtures and 17 explicitly machine-only out-of-array or overlapping-view
fixtures. It covers all 129 target and 126 candidate instructions, both flags,
both selected values, inactive/special/ordinary input, the exact 200/201
comparison boundary, high unrelated bits, zero and boundary counts, and
captured versus reloaded state usage. All successful data reads and writes,
including their order/width/value, and complete nonstack RAM agree with the
oracle. Stack restoration, r4-r11, and return destination agree on the 603
returning pairs. Two machine-only overlapping-view pairs clear their own
count, underflow, and fault on the same out-of-mapped-memory entry read; only
their bounded successful-access prefixes and memory effects are compared.
They are not demonstrations of defined C behavior or safe memory access.

Access traces intentionally exclude stack activity, instruction fetches, and
ROM literal loads. Consequently different address-building/literal sequences
are not described as identical instruction-level traces. These bounded tests
do not prove arbitrary-pointer validity, ISO C alias compatibility, allocation
bounds, or universal behavioral equivalence. Generated binary artifacts are
cleaned by the reproducer.
