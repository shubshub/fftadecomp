# 0812803C — Parked, no match credit

Target: `[0x0812803C, 0x081286DA)`, 1694 bytes / 732 reachable instructions.
Fixed compiler: agbcc `-mthumb-interwork -O2`.
Function-address profile: `canonical-thunks-v1`.

The retained complete C candidate compiles and assembles into one defined Thumb
function, 1674 bytes / 719 assembly instructions. The typed clear and copy
callbacks emit the compiler's undefined `_call_via_r2` and `_call_via_r3` calls.
These are compiler diagnostics, not native call-proof or plausibility results.

The final native matcher returned **exit 1** at:

```text
inert spins require an exact unique nonoverlapping Thumb span
```

The extent check refuses the 20-byte size difference before byte comparison or
source plausibility. No native plausible verdict or byte-match credit is claimed.
The shell invocation also ran diagnostic compilation after this refusal; its final
shell exit is not the native matcher exit.

## Recovered behavior

All request phases are implemented: cleanup and allocation, selection and palette
setup, text/icon construction, background transfers, both animation bands,
alpha transitions, timed/input dismissal, effect teardown, and completion. The
abort path stops and destroys an existing effect, clears its pointer, and returns
zero. Incoming argument 0 is unused; arguments 1 and 2 hold the request and state.
The tilemap is represented as a flat 28-entry buffer with a 14-entry row stride.

## Remaining difference

The ROM contains 13 retained byte loads before constant assignments to the
blend/alpha/brightness shadow bytes at `g_control_flags_03000940 + 0x4A..0x4E`:

- `0812827A`, `08128282`, `0812828C`, `08128294`, `0812829C`
- `08128462`, `0812846A`
- `08128502`, `0812850A`
- `08128690`, `08128696`, `0812869E`, `081286A6`

The retained candidate's full-byte bitfield assignments compile to direct byte
stores and do not reproduce those loads. The original field declarations remain
unproved. No discarded C expressions, artificial reads, volatile qualifiers, or
assembly were added to force them. These sites remain an explicit unresolved
source-type issue rather than being omitted from the target.

Other observed differences include tilemap address/constant scheduling,
transfer-record offset register reuse, and the resulting pool/branch layout.
The instruction-count difference of 13 is diagnostic only; it does not establish
that the rest of the function is byte-identical.

Bounded genuine variants tested ordinary full-byte bitfields, word-based
full-byte bitfields, a packed display container, actual blend/alpha subfields,
and ordinary naturally inlined semantic setters. They produced single-function
bodies of 1674–1718 bytes and failed the unchanged native extent gate. The packed
container also decomposed halfword control accesses into bytes; it was rejected.
The semantic setters emitted no additional helper functions but did not recover
the retained loads. The simpler complete 1674-byte candidate is preserved here.

## Evidence and replay

The final native output and diagnostic counts are retained outside the game tree:
`../../../0812803C/match-current.log` and
`../../../0812803C/remaining-gap.json`. The original captured complete target is
`../../../0812803C/target-disassembly.md`.

From the private matching root, after restoring this candidate to its owned
`src/0812803C.c` path:

```sh
env PYTHONDONTWRITEBYTECODE=1 \
  TMPDIR=/home/user/.codex-work/ffta-ulw \
  PATH=/home/user/armtc/root/usr/bin:$PATH \
  FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' \
  python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py \
  --root . --function-address-profile canonical-thunks-v1 0x0812803C
```

The unmatched active C/report were removed. No maps, headers, reservations,
shared files, main tree, or toolkit were changed.
