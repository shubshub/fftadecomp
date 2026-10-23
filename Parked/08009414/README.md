# 08009414 — Parked, complete natural recovery

## Disposition

The first natural C form is retained unchanged. With the approved software-double-v3
toolkit and fixed agbcc `-mthumb-interwork -O2`, the official matcher accepts the
supported `elf-symbol-thumb-frame-data-v1` verification profile and reports
**NOT MATCHING — bytes differ** (exit 1). This is a genuine compiler-byte mismatch,
not a verifier limitation. No active source, MATCH claim, or status credit is proposed.
No source, flag, statement-order, register, or spelling search was performed.

Both the target and complete candidate are 168 bytes, 73 instructions, with the
same 48-byte caller frame, calls, literal addresses, and owned extent. Exact positional
comparison gives **153 equal bytes and 15 different bytes**, with no missing or extra
bytes. The matcher's sequence-alignment display separately reports 156/168 bytes and
62/73 instructions; that display is not the positional byte count.

The differences occupy instructions at 0800943E/40/42 and 08009454/56/58/5A/5C/5E/60/62.
The candidate uses r3 where the target uses r1 while forming the work, descriptor,
and scratch offsets, and schedules the resource literal load before the scratch
arithmetic instead of after it. `build.json` records all 15 differing byte positions;
`official-report.md`, `original-object.txt`, and `compiled.txt` retain exact evidence.

| Item | SHA-256 |
| --- | --- |
| Source | `07a6257db6336c4ba628f1bf78f394eabb4551698cbf5fe43a1b353512188c7a` |
| Complete ROM body | `94efaee8572a876488f163fde8743b28f88e3aa3210cb6f6b42dde0537acec65` |
| Complete linked candidate | `3b1178c9f123c2aa2b6bc122882251032ad7fb764e1b801b6565c557716cea61` |

## Ownership and metadata

Independent Capstone CFG traversal and Binary Ninja instruction lengths establish:

- Code: `[08009414,080094AE)`, 154 bytes, 73 instructions including four four-byte BLs.
- Internal alignment: `[080094AE,080094B0)`, two zero bytes.
- Literals: `[080094B0,080094BC)`, three words: 02009188, 0836D4B8, 084E8FD4.
- The next indexed prologue starts at 080094BC. There is no external alignment or
  truncated suffix. No new or interior function entry is proposed.

The two function maps need only instruction count **84 → 73**. Endpoints, modes,
kinds, and neighbors stay unchanged. `metadata-proposal.diff` is pinned to immutable
game502's mappings, not applied to production. It also proposes the two independently
grounded data bindings `g_callbacks_0836D4B8 = 0x0836D4B8` and
`g_table_084E8FD4 = 0x084E8FD4`. Their C declarations are unsized arrays; neither
binding claims a nominal allocation length.

The callback's observed first word is 03005E79. Published `src/0800718C.c` independently
uses the same slot as a `void (*)(void *, u32)` callback. The resource window used by
the bounded checks has indices 0..9, with offsets 16, 6C, C4, 120, 17E, 1DC, 230,
292, 2E2, 348 (hex). Headers are 1628 at indices 2/5/9 and 162A otherwise.
The retained accessed/model-read window `[084E8FD4,084E933E)` is not an allocation-size
claim. Index 10 has offset FFFF and is excluded; no safe sentinel behavior is inferred.

## Recovered contract and typing

`void func_08009414(u8 index)` agrees with the frozen 08009394 caller declaration.
The low byte of the incoming index is consumed. A state pointer is loaded from
02009188. The initial display buffer and row are used to capture the destination
`buffer + row * 32 + 0x2680` before any external call.

1. Call the first callback slot with the current state work buffer at +6C8 and size B00.
2. Reload the state pointer, capture descriptor +360, and call 08013E9C with that
   descriptor, resource table, scratch +3E0, index, and two null optional outputs.
3. Reload the state pointer and call 080154D8 with renderer +24, current work +6C8,
   the previously captured descriptor, width 22, and five zero stack arguments.
4. Reload the state pointer and call 0814186C with current work +6C8, the original
   captured destination, and control 580.

Ten target-compiler assertions verify 32-bit pointers/function pointers, state size
11C8, state offsets 2/18/24/360/3E0/6C8, and display-buffer offset 10. Unknown members
and byte-array regions express observed offsets, not proven original field identities
or full allocation boundaries. `u16` row multiplication by 32 fits the target signed
32-bit promoted type, but valid C pointer arithmetic still requires sufficient backing.

The 0814186C prototype agrees exactly with published `src/080DBC58.c`. The six-argument
08013E9C and nine-argument 080154D8 declarations reflect inspected register/stack loads
and narrowings, but neither has a recovered definition in this immutable baseline.
Their higher-level object types, the original aggregate declarations, and whole-program
C compatibility remain unresolved. The clear callback's wider unsigned-size behavior
is not established: its actual body tests a signed count; this caller passes positive B00.

## Compiler and report evidence

The isolated fixture copies all nine baseline headers and uses only private corrected
mapping copies. The original ELF contains one complete function symbol at offset 1,
size 168, text size 168, alignment 4, and no external text padding. The original
relocations are four `R_ARM_THM_CALL` entries (canonical `_call_via_r2`, 08013E9C,
080154D8, 0814186C) and two `R_ARM_ABS32` data references. The natural callback call
emits `_call_via_r2`; no addressed-runtime alias is introduced.

A separate diagnostic typed link checks unique Thumb function bindings, odd function
symbol values, object types, exact call/literal relocations, unchanged nonrelocated
bytes, absence of veneers/unresolved relocations, and complete ELF extent. This link
does not override the official NOT MATCHING disposition. Compiler diagnostics are
empty and the ordinary plausibility check passes. Strict replay rejects the original
nonmatch, the same report with a forged MATCH result, and a bare MATCH/log forgery.

## Bounded runtime evidence and limits

Fourteen cases execute both ROM and the freshly linked candidate: **28 executions**.
An independently expressed caller/wrapper oracle checks argument order, captured versus
reloaded pointers, ordered non-stack writes, complete EWRAM, IWRAM outside active
frames, initialized consumed reads, current-stack allocation, outgoing stack words,
caller save image, r4-r11 preservation, restored SP, and Thumb/ARM return state.
Paired complete stack traces agree. Caller depth is 48 bytes; the deepest exercised
helper increases depth to 68. All 73 target and all 73 candidate instructions execute.

Actual executed code:

- 0814224C BX-r2 thunk: 1/1 instruction.
- The ROM clear body `[08A38A2C,08A38A5E)`, installed at 03005E78 in the fixture:
  19/25 instructions, exercising the aligned positive B00-byte word-clear path.
- 08013E9C with the required literals through 08013F20: 48/59 instructions. Both
  compressed and uncompressed observed headers execute, optional output pointers stay
  null, and the bit-0 codec at 08013F20 is not exercised. Modeled decoder return values
  exercise actual low-16 narrowing and the uncompressed subtraction threshold.

The fixture copies the full 176-byte ROM installation image into IWRAM before execution.
Actual installer 08002768 references that image's endpoints and destination, and the
callback table points to its Thumb entry. **The installer and BIOS are not executed.**
Executable RAM identity, successful initialization, preservation, and valid function
pointer representation remain explicit fixture assumptions, not consequences of a ROM
hash alone. IWRAM image bytes remain unchanged during the positive executions.

Explicit models, not actual helper executions:

- 0800543C and 0801407C perform deterministic bounded 32-byte scratch/descriptor
  transformations and provide arbitrary ABI return values. They do not prove actual
  decompression/descriptor-format behavior.
- 080154D8 performs bounded marker writes and can replace the state pointer. Its
  rendering, retained-pointer behavior, termination, and real backing needs are unproved.
- 0814186C is intercepted before its `svc #0xb; bx lr` body. The model interprets
  control 580 as a forward halfword copy of B00 bytes between disjoint live buffers.
  No BIOS image, actual SVC execution, or universal BIOS behavior is claimed.

External models deliberately clobber r0-r3, r12, and condition flags within the assumed
ordinary ARM ABI while preserving the callee-saved state and SP. State-pointer changes
after decoding/rendering exercise the caller's reloads while the initial destination
and captured descriptor remain live. Models share their declared contracts with the
oracle; passing tests do not independently validate those external contracts.

Positive cases cover real table indices 0..9, several nonzero upper input bytes,
rows 0..127, boundary decoder return values, state swaps, both return modes, and
word-aligned stack variants. They require aligned live state/display objects, initialized
consumed data, nonoverlapping destination/source buffers, and sufficient capacities.
The fixture's objects and buffers are disjoint; no general alias, retention, lifetime,
concurrent mutation, invalid-index, maximal-row, or whole-game termination proof exists.

Ten executed negative controls reject altered row stride, clear size, resource index,
renderer width, ninth stack argument, work-pointer reload, BIOS control, actual clear
store value, an uninitialized row, and an uninitialized modeled copy source. Two
separate input-domain guards reject index 10 and row 128. Guard rejection is not
execution evidence for those excluded inputs. Full case details, input pins, uncovered
helper addresses, and controls are in `runtime-results.json`.

## Reproduction and cleanup

Run from any directory with the approved local dependencies installed:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  python3 /home/user/.codex-work/ffta-ulw/08009414-author/check.py
```

The checker uses named disk-backed fixtures below this directory and deletes generated
compiler objects, linked binaries, layout outputs, and fixture trees on exit. It reads
immutable game502, approved software-double-v3, the local ROM, frozen 09394 CFG support,
and all nine headers. `input-pins.json` binds the exact local inputs. The script writes
its reproduced textual evidence in its own directory; copy the textual directory into
separate review ownership before rerunning if the original freeze must remain untouched.
Only source and this README are proposed for eventual Parked integration. ROM-derived
disassembly/logs and scratch evidence must not be committed to the game repository.
