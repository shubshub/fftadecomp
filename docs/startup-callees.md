# Bounded startup callee inventory

This records local entry and byte ownership, not C matches, original symbol
names, unconditional execution, or complete transitive behavior. The conditional
080004B0 callback witness and its 08000516 reclassification are reviewed
separately in `startup-extension-04b0.md`.

## Witnessed entries

The Thumb call at 080004B4 targets 08144AF0. The Thumb call at 080004FA targets
081451B4, whose call at 081451B6 targets 08144510. These are concrete incoming
entry/mode witnesses under the conditional startup path, not a global caller
inventory.

081451B4 owns the reached local envelope `[081451B4,081451BE)`: 10 code bytes,
four instructions, no pool. Its saved return word is restored after the call
to 08144510 and used for return. The following halfword is outside this reached
body; the next indexed start is not used to invent alignment ownership.
Its return contract assumes ordinary returning callees and their required
preservation behavior. It overwrites r0 with its own saved return address, so
it does not preserve or consume a result from 08144510. This observation does
not establish either function's original C return type.

## 08144510 local ROM ownership

The witnessed normal entry begins before the historical 08144522 prologue.
It loads a state pointer, checks a key, and either returns immediately or
updates that key and falls through to 08144522. The bounded partition is:

| Half-open interval | Role | Bytes |
|---|---|---:|
| `[08144510,0814457A)` | 51 reached Thumb instructions | 106 |
| `[0814457A,0814457C)` | Unexecuted alignment before referenced words | 2 |
| `[0814457C,08144594)` | Six referenced literal words | 24 |

The resulting local ROM envelope is 132 bytes, ending at the last referenced
word, not at the next index row. Each four-byte direct call counts as one
instruction. No other retained indexed envelope overlaps this partition.
The envelope SHA-256 is
`03a4fccd563d99444f3a2da6c0ef6e4c4b7d10204fb59beb8277e28a50e1cafc`.

Normal entry defines r0-r3 before using their incoming values as data; no
incoming r0-r3 data argument is established by this body. A valid incoming
SP/LR is required. The accepted-key path saves the incoming r4-r11 values for
preservation rather than using them as data arguments. It also depends on the
state pointer loaded through 03007FF0 and the memory/hardware state it reads.
This is register-use evidence, not an original function-signature recovery.

The early return leaves SP unchanged and r0 holding the loaded state pointer.
The other path does **not** return locally: it reaches Thumb RAM 030034DC with
a live 64-byte frame and prepared registers. Two intervening direct calls use
the indexed 081448BE register-dispatch stub, whose dynamic destinations and
return behavior remain unresolved. The RAM image's installation, source-ROM
identity, preservation/return behavior and eventual r0 value are not proved.
Nearby ROM code is not assigned to that RAM address without installation
evidence. These transitive limitations do not erase the witnessed ROM entry
or its bounded local code/pool ownership.

The owning JSON row therefore uses 08144510–08144594, Thumb, 51 instructions
and incoming provenance `call`; the text index marks its final transfer
`indirect`, not an ordinary return. Current standalone function verification
still rejects the indirect control flow. Ordinary typed direct-call checking
of the 081451B4 wrapper accepts the corrected target under its existing ABI
summary; it does not recursively certify this callee. Neither check grants
source-match credit.

## Historical 08144522 coordinate

The prior JSON row was 08144522–08144580, Thumb, 47 instructions,
`thumb-prologue`; the text row described 94 bytes ending by `return`.
The addressed symbol table independently claimed only 20 bytes under
`func_08144522`. These inconsistent observations are superseded as **owning**
rows by the witnessed 08144510 envelope and its addressed symbol.

Under the witnessed path, 08144522 is an internal continuation receiving the
state pointer in r0 after the key guard/update. It starts its own save frame;
it does **not** require an already-pushed frame. A distinct contextual entry
with suitable r0 and memory state remains possible. No such incoming witness
was established in this bounded audit, and no exhaustive caller search was
performed. Preserve this historical coordinate as non-owning evidence, not a
second overlapping function row or an authorized typed call alias. A later
positive witness can motivate a separately reviewed entry contract without
double-counting its bytes.

## 08144AF0 remains unresolved

This entry reaches 26 Thumb instructions in `[08144AF0,08144B24)`, with an
adjacent eight-byte pool through 08144B2C. It also reads distant literal words
at 08144D8C and 08144D90. Expanding ownership through them would cross 608
untraversed bytes and the indexed 08144D84 entry. Their exclusive ownership or
sharing is not established. No complete owning row is added for 08144AF0 and
no truncated span is used merely to make the startup call link.

## Scope and provenance

Evidence uses the approved ROM SHA-1
`4ac05441f4de70a4ec3dd932116346c61b8783d9`, the prior startup-entry witnesses,
and bounded fresh instruction/literal checks. The 08144510 audit captured JSON
mapping SHA-256
`0a7f6ce2b32447058cc800bf632fc9d1af5ec31e64b9110068dd5e808cb4c332`, after the
081451B4 addition. Detailed local evidence is retained in the coordinator's
`startup-missing-callees-next` and `startup-callee-44510-next` bundles.
This note contains no raw ROM dump and adds no matched function or byte credit.
