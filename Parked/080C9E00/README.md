# 080C9E00: bounded candidate selection, unmatched loop and base reuse

This is a natural behavioral recovery, not a byte-exact match. No active
source or match report remains for this address.

## Complete target

The complete ROM symbol is `[0x080C9E00, 0x080C9ED8)`: 216 bytes and
97 reachable Thumb instructions. Its 198 code bytes include two ordinary
direct calls. The remaining bytes are the zero alignment halfword at
`0x080C9E22` and four literal words:

| Literal address | Value |
| --- | --- |
| `0x080C9E24` | `0x02000080` |
| `0x080C9E28` | `0x00002F44` |
| `0x080C9ED0` | `0x085680DC` |
| `0x080C9ED4` | `0x00002FC4` |

The ROM body SHA-256 is
`2c554cecb30c28aee89dd9722899e71e070e928c3a07bd55a9cbc4f89a9cf24f`.
The function saves 32 bytes of registers, allocates no local frame and
consumes no incoming stack arguments. Only the incoming object pointer in
`r0` is used semantically. A `void(void *)` interface is compatible; the
machine code does not uniquely establish all original source-level types.

## Recovered behavior and contracts

There are at most four attempts. Each attempt reloads object byte `+6` and
chooses a table base and divisor: greater than five selects `(500,225)`,
four selects `(310,190)`, and all other values select `(0,310)`.
The call to `08002804` returns an unsigned value in `0..32767`; its observed
signed-halfword conversion therefore preserves the value. `08142950`
computes signed remainder, not division. The resulting table index is
nonnegative and at most 724. This arithmetic bound does not establish the
original table's allocation extent or element meaning.

The candidate is a full word from `085680DC`. The function searches the
first 24 records at `02000080`, then the 12 records at `02002FC4`, each with
stride `0x108`, comparing their first words. Both scans are ascending and
stop at the first equality. A duplicate in the first array skips the
second scan. A duplicate triggers another attempt unless all four attempts
are exhausted; the fourth candidate is then accepted even if duplicated.
There is no special exclusion for an input object inside either array.
Finally, the candidate word is written at object `+0`, followed by a zero
byte at object `+0x106`.

The input must support the observed reads and writes, including an aligned
word store. The two record populations and each selected table element must
be accessible. No null guard, original allocation bound or stronger
termination claim is introduced.

The local typed recovery exposes word `+0`, selector byte `+6`, cleared byte
`+0x106`, and the observed record stride. Before any future active
integration, its `SceneRecord`/`State` declarations must be consolidated with
the older byte-array-only declarations used by `08124648`, `080C83CC`,
`08131BB8`, `080C83A4`, and `08123234`. Identical symbol names and byte
offsets alone do not make those differing C declarations compatible. No
shared header or existing source was changed for this parked attempt.

## Compiler evidence and remaining difference

The final official check used the reviewed `2e2a664` toolkit:

```
PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH python3 /home/user/.codex-work/ffta-ulw/kit-reviewed-2e2a664/tools/match.py --root . 0x080C9E00
```

The retained ordinary indexed-loop recovery compiles with agbcc
`-mthumb-interwork -O2` to one complete 208-byte symbol containing 91
reachable instructions, 186 code bytes, five literal words and one internal
zero alignment halfword. The official
matcher rejects it as `compiled symbol is shorter than the indexed span:
208 < 216`. Typed linking and the ordinary direct-call CFG check succeed
when inspected separately; they do not override that failed equality.
The linked candidate SHA-256 is
`c99b240cae7223c47b479c6957d8de585cc7fb5ab20121d9ab13c60bc7dc064d`.
Only 29 of the first 208 positioned bytes equal the 216-byte target; the
remaining eight target bytes have no corresponding candidate bytes.

The ROM keeps first-array, second-array and enclosing `02000000` bases in
`r9`, `r10` and `r8`, respectively, and loads the candidate-table address
inside the retry loop. The recovery instead hoists the table pointer and
two array bases, reloads array bases during the searches, and uses different
search registers. The ROM's shared retry decrement precedes the loop body
and compares against `-1`; the retained C places its ordinary nonnegative
retry test at the bottom. Literal placement and register allocation differ
as consequences, not just one isolated instruction.

Bounded natural forms tried:

- Indexed scans with `attempts >= 0`: 208 bytes; retained as the clearest recovery.
- Indexed scans with the explicit exhausted sentinel `attempts != -1`: 212 bytes.
- The sentinel form with an explicit second-scan `continue`: still 212 bytes.
- Ordinary pointer-iterated record scans with the sentinel form: 176 bytes.

No invented enclosing-object arithmetic, forced register variables, manual
control-flow steering, alternate optimization flags or assembly were used.
This is a local code-generation mismatch, not an inherent-unmatchability
claim.

## Bounded execution evidence

The ROM's actual 216 bytes and the linked 208-byte recovery were executed
separately in Unicorn for 720 scenarios each, 1,440 executions total. Both
used the actual 32-byte RNG, actual 206-byte signed-remainder helper and
actual ROM table contents for the reachable index range. No helper stubs
were used. Record populations, input objects and RNG state were explicit
synthetic RAM fixtures, not claims about a captured game state.

The cases cover selectors `0,3,4,5,6,255`, four seed families, ten duplicate
patterns, and three input positions: independent storage, the first record
of the first array, and the last record of the second array. They exercise
all 97 ROM instructions and all 91 candidate instructions, one through
four attempts, duplicate exhaustion, both array endpoints and scan order.
An independent semantic model checks exact ordered non-stack data reads and
writes, final full RAM, RNG transitions, helper-call order and argument
domains, final store order, saved `r4-r11`, stack restoration and return PC.
All cases pass. These bounded machine tests do not resolve the shared C
type prerequisite or prove validity for arbitrary pointers/table storage.

The task-scoped reproducer is
`/home/user/.codex-work/ffta-ulw/080C9E00/check_recovery.py`; it rebuilds the
parked source into a temporary disk-backed child directory and removes all
generated compiler/linker outputs on completion. No task-owned binary
fixtures remain.
