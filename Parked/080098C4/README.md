# 080098C4 — Parked dispatcher recovery

## Verdict and complete extent

The first natural C form is **NOT MATCHING** with fixed agbcc
`-mthumb-interwork -O2`. No source spelling, register, type or flag search was
performed. The unchanged approved toolkit accepts the ordinary runtime-thunk
link/profile, but the complete function bytes differ.

ROM owns `[0x080098C4,0x080098F4)`:48B =44 code bytes/21 instructions plus
the required literal `0x03000890` at `0x080098F0`. There is no internal or
external alignment within the owned span. The next indexed entry is exactly
`0x080098F4`. The existing24 instruction count includes the two literal
halfwords and counts the BL halves separately; the proposal corrects it to21
without changing the endpoint.

The candidate also owns48B, but contains42 code bytes/20 instructions, two
internal zero-alignment bytes and the four-byte literal. There are39
positional differences; the first is offset+2. ROM starts an index at0,
recomputes `table + index*8`, then increments/tests index<=3. The compiler
turns the natural four-iteration loop into a pointer increment of8 and a
countdown from3. Code/pool alignment and branch/BL positions consequently
differ. Both complete ELF symbols are48B with no external assembler padding.
No attempt was made to defeat that natural optimization.

## Recovered machine behavior

Four eight-byte records begin at `0x03000890`. Each has a context word at+0
and callback word at+4. In increasing slot order, a null callback skips the
slot without loading its context. Otherwise the dispatcher loads context
into r0, callback into r1 and calls the actual compiler thunk at `0x08142248`.
That thunk executes `bx r1`; its verifier shape also includes the following
`c046` padding halfword. The indexed executable thunk body is only two bytes.

The dispatcher tests **only the low16 return bits**. A nonzero low halfword
clears the current slot's callback word after return, even if that callback
has replaced itself meanwhile. Zero leaves the possibly changed word alone.
Future slots and their contexts are read when their turn arrives; activating
a later slot can cause it to execute in this pass, while changing an already
visited slot does not revisit it. Context words are not cleared by the caller.

There are no function arguments, result value, incoming stack words or
outgoing stack arguments. The12-byte frame saves r4/r5/LR; the thunk and each
modeled callback preserve SP and callee-saved registers. The function restores
the frame and returns through `pop {r0}; bx r0`. Its incidental final r0 is
not a C return value.

## Callback type boundary and coordinated known-family repair

At this dispatcher's original recovery freeze, the published08D50 and08954
registration declarations accepted `u8 (*)(void)`, and the known08DFC/08E78
callbacks were defined `u8 function(void)`. Those types were incompatible with
this dispatcher's `u16 (*TaskCallback)(u32)` view. Ignoring the supplied context
or returning a zero-extended byte can work at the machine boundary, but does
not make an incompatible C indirect call defined. The original negative probes
and runtime evidence below retain that historical scope.

The bounded follow-up established two known registrations:08D50 registers08DFC,
and08954 registers08E78, both through098F4 with context0. Actual098F4 stores the
callback/context at+4/+0 of a record in03000890; actual098C4 supplies the stored
context in r0 and tests the low16 callback result. Both known callbacks ignore
the incoming context and preserve their existing unsigned-byte helper/local
result semantics. This supports the common reconstructed interface
`u16 (*)(u32)`, without claiming it was the unique historical C spelling.

The coordinated source revisions use that type consistently:

- 08DFC and08E78 definitions become `u16 function(u32 context)`, retaining
  their u8 helper declarations and existing statements/local narrowing.
- 08D50's callback typedef and08DFC declaration, and08954's08E78 declaration
  and098F4 callback parameter, use the same common type.
- This dispatcher already stores `u16 (*)(u32)`. The new098F4 candidate accepts
  that type and retains its separate `u8` registration result.

Fresh fixed-compiler combined-interface and real-source-pair checks accept
this known subset without diagnostics. The dispatcher and registration record
views both occupy8 bytes, with a4-byte context at+0 and callback at+4, aligned
to4 bytes on this target. Old callback definitions/registration types are
rejected by explicit negative controls. This is bounded interface and layout
evidence, not proof of arbitrary object effective types, aliasing or lifetime.
The separate13404/096E0/09728 callback family is unchanged.

The four existing-member revisions have independent approvals, and their exact
source versions pass the combined checks. The new098F4 candidate also has
separate independent Parked-only approval; its genuine byte mismatch remains.
These approvals do not establish completed publication.
Coordinated integration must preserve these versions, refresh applicable
reports for the integrated snapshot and pass the normal parent gates.
No cast or byte-match waiver substitutes for those requirements. Unknown ROM
registrations/table writers, reentrancy, callback lifetime and whole-program
type safety remain outside this bounded inventory.

The type repair does not change this dispatcher's source or its genuine
39 positional byte differences in the complete48-byte candidate. It remains
**Parked, not an official MATCH**. Other Parked family sources retain their
independent byte/profile blockers; interface compatibility grants no match
credit and does not widen any retained runtime model's domain.

## Bounded evidence and limits

Evidence directory:
`/home/user/.codex-work/ffta-ulw/080098C4-author/`.
Base is immutable `game-next-94599c9` (published89c9cb3); toolkit is unchanged
`kit-software-double-candidate-v3`. `probe.py` creates a private fixture with
all nine fingerprint-scope headers and the caller count-only metadata repair.
The requested official `--mode thumb --no-write` command exits1 for byte
differences. A separately logged report-generation invocation emits the
diagnostic NONMATCH report. Strict replay correctly rejects it as accepted
evidence. There is no successful MATCH/replay claim or toolkit bypass.

Original ELF has one `R_ARM_THM_CALL _call_via_r1` at+14. Official typed
linking grounds it at odd Thumb value08142249 against the actual thunk bytes;
final ELF has no unresolved relocations, stubs or other patched bytes.
Complete48B symbol and text extents, reachable CFG, pool and alignment are
checked with raw calculations, Capstone and Binary Ninja. No data mapping is
invented for the fixed RAM table.

`check.py` freshly compiles and passes44 executions:11 cases × original/
candidate × ARM/Thumb return. Across these runs,96 actual `bx r1` transfers
reach **explicit whole-callback models**, using both ARM and Thumb callback
addresses. No game callback body is claimed to execute. Models expose
canonical low16 results, synchronous table mutation and deliberate caller-
saved register/flag clobbers while preserving the ABI. One case supplies raw
32-bit return words with upper-only/nonzero halves to test machine low16
consumption; it is not a proof of a compatible nominal C return type.

All21 ROM and20 candidate instructions are reached. Tests cover empty slots,
all occupied slots, repeated callbacks, self replacement retained/cleared,
future activation/removal/context replacement, prior-slot mutation, exact
table reads/writes and untouched RAM, defined context reads, saved registers,
balanced SP, actual thunk transfer and both callback/return modes. Six
negatives detect low8 return truncation, wrong clear value, shortened loop,
wrong context field, undefined active context and callback ABI violation.
Ten target assertions establish record size/alignment/offsets and scalar
widths; compatible function-pointer use compiles without diagnostics, while
the two known incompatible registrations produce expected diagnostics.

Premises remain:32 bytes of live aligned writable record storage; nonnull
callback words that denote callable code of a suitable ABI; every loaded
context initialized; callback preservation of live frame/control state;
returning callbacks and no asynchronous/reentrant execution outside the
modeled cases. The table is concretely separate from the tested stack; no
general allocator/separation proof is inferred. Synchronous callback writes
are permitted by the C alias model and tested, but arbitrary frees or
recursive dispatch are not proved safe. Hardware behavior and nominal C
function-type compatibility are deliberately separate claims.

Both scripts pin and recheck source, headers, maps, tools, compiler, ROM,
thunk, registration context and known callback declarations. Run them in a
copy of the frozen directory to preserve its manifest:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 probe.py
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp \
  PATH=/home/user/armtc/root/usr/bin:$PATH python3 check.py
```

Self-owned generated ELF/object/assembly files and fixtures are removed.
No production/shared headers/maps/tools, Git, reservations or status were
changed. Parked retention plus the separate count proposal are the only
integration candidates; parent owns release and independent review.
