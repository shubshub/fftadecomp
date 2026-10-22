# 08008D50 — byte-identical diagnostic result, unsupported official profile

**Parked, not an official MATCH.** The first natural typed C form produces
all 172 target bytes exactly with agbcc `-mthumb-interwork -O2` after a
diagnostic typed link. The unchanged approved matcher exits 1 with:

```text
function-address evidence does not support runtime call thunks
```

The C's indirect copy call naturally emits `_call_via_r3`; its later
registration call takes the address of `func_08008DFC`. Their combination
is excluded by the published function-address proof profile. The source
does not replace the indirect call, hardcode the callback as an integer,
erase its type or use any other verifier bypass. No official report is
emitted. There is no strict successful MATCH report to replay.

## Exact body and source

The complete body is `[0x08008D50,0x08008DFC)`: 146 code bytes containing
68 instructions, two zero alignment bytes at 0x08008DE2, and six required
literal words at 0x08008DE4 through 0x08008DF8. The adjacent entry at
0x08008DFC is excluded. The existing endpoint is correct; the instruction
count needs correction from 86 to 68.

Original and diagnostic final ELF symbols are both 172-byte Thumb
functions with no external padding or extra allocated content. Original
relocations are five `R_ARM_THM_CALL` calls and two `R_ARM_ABS32` words
(the known control object and callback). The diagnostic link assigns
function/object ELF types, resolves every relocation and compares the
entire symbol, including all pools. This is byte/extent evidence only,
not an authorized proof-profile extension.

Target and diagnostic compiled SHA-256:
`2706eb110de8e96c549cbb116d8015c8c8b834dcb76996cebeb9f88dcb93454a`.
No byte discrepancy, length discrepancy, source iteration or flag search
was needed. The pre-existing `g_state_020020D0` data binding is reused
unchanged; it is grounded by the target's 0x020020D0 literal, not a new
arbitrary mapping.

## Recovered behavior

The function caches a 16-byte descriptor at active state +0x2B4 and a
44-byte render record at +0x2C4. It invokes the copy callback stored at
0x0836D4BC to copy 16 bytes from 0x0836D4C4, increments descriptor byte 2
by two, and changes byte 3 to twice its value plus eight, narrowing each
result to `u8`. It reloads the active state, reads words at +0x14 through
the pointers at state +0x18/+0x1C, and passes those with descriptor fields
to the existing 12-argument initializer 0x08017424. Eight arguments occupy
the 32-byte outgoing stack area.

It writes render byte +0x13 minus five to control +0xAE, calls 0x08013B7C
with descriptor/render/storage pointers, reloads descriptor byte +8 for
0x08016C90, and registers callback 0x08008DFC with context zero through
0x080098F4. The returned low byte is stored at +0x20 of a freshly reloaded
active state. Field names describe the observed layout, not recovered
original names or complete enclosing types.

## Bounded validation and limitations

The author evidence directory contains reproducible scripts and hashes:
`/home/user/.codex-work/ffta-ulw/08008D50-author/`.

- 28 separate ROM/compiled executions cover ARM/Thumb returns, all four
  available registration slots and a full registry, plus explicit modeled
  descriptor/global mutation cases that test required reloads.
- The actual thunk, installation-conditioned RAM copy, 0x08017424
  initializer and 0x080098F4 registration are executed. The larger
  0x08013B7C and 0x08016C90 calls are whole returning ABI models with
  precisely enumerated writes and caller-saved clobbers, not executions
  or proofs of those helpers or their transitive callees.
- All 68 caller instructions are reached. Checks cover register/stack
  arguments, initialized reads, exact ordered non-stack effects, complete
  EWRAM/IWRAM contents, callee-saved registers, balanced return, and the
  80-byte deepest caller/initializer stack extent.
- Eight negative controls fail, covering arithmetic, outgoing arguments,
  control source offset, callback Thumb identity, undefined resource data,
  changed installed copy code and a model that breaks the saved-register
  ABI. Twenty-one target-compiler scalar/layout/arithmetic assertions pass.
- The ROM callback word is 0x03005EE9. Actual copied code is the 62-byte
  `[0x08A38A9C,0x08A38ADA)` body, installed at 0x03005EE8. Current RAM byte
  identity and non-overlap with objects/stack are explicit fixture
  premises. Startup installation, actual BIOS execution, dominance and
  persistent identity under arbitrary later writes are not proved.
- Registration retains the callback; it does not invoke it in this leaf.
  Its later invocation, lifetime, original C prototype and scheduler ABI
  are not verified. The recovered `u8(void)` declaration matches the
  inspected callback's consumed-register/return shape but is not a proof
  of its historical source type.
- Byte arithmetic is C-defined: promoted intermediate ranges are 2..257,
  8..518 and -5..250; conversion to `u8` gives modulo-256 narrowing.
  Valid aligned, sufficiently large target objects and implementation
  address-to-pointer conversion remain explicit C/platform assumptions.
  Sampling and byte equality do not establish arbitrary aliasing,
  concurrency, hardware timing or whole-game correctness.

Production files and verifier behavior are unchanged. The only proposed
metadata edit is this function's instruction count. The remaining blocker
is the unsupported proof composition, not an unexplained compiler-byte
difference. Integration, independent review and claim release are
coordinator-owned.
