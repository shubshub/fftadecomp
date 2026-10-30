# 08020780: bounded natural attempts did not match

The accepted claim was6525743307, lane sol-0780. The complete target is116 bytes,
55 instructions, at[08020780,080207F4). No target index or toolkit gate changed.

Three native commands failed with `buffer caller requires an exact complete
mapped span`: (1) unsigned-halfword locals with explicit signed interpretation;
(2) a signed point output with corresponding unsigned-pointer casts preserving
E700's defining signature; (3) the signed point with a shared boolean result.
All preserve actual E700/E674/E680 signatures and halfword narrowing.

Failed-candidate diagnostics show attempts 1 and 2 compile to 114-byte
function symbols with 54 instructions. Their raw .text sections are 116 bytes
because of trailing alignment outside the complete ELF symbol. Attempt 1 saves
one instruction in the vertical sum through a high-register addition. Attempt 2
uses two instructions for that sum instead of the target's three; its remaining
output addressing and register assignments also differ.

Attempt 3 compiles to a 122-byte symbol with 58 instructions and a 124-byte raw
.text section. Its shared boolean occupies r10, adds initialization and result
moves, and requires saving and restoring an additional high register. It is
6 bytes and 3 instructions larger than the complete target. The native gate
correctly refuses all three callers because their complete symbol spans differ
from the 116-byte target. No exact relocated comparison was admitted and no
native report was emitted. Unlinked diagnostic BL bytes are retained as
diagnostics only, not match evidence.

Exact sources, native stdout, commands, native include-header/current-map pins, assembly,
object symbol sizes and unlinked byte diagnostics are retained under the task
packet `state/matching-08020780-author/`. The current third candidate was moved
here from the owned active source; other sources were untouched. There were
three native failures, zero successes/replays, and three additional diagnostic
compilations of failed candidates. No asm, pragmas, volatile, dead operations,
compiler steering, profile changes, shared edits, Git or broker operations.
The native run metadata field named `all_header_inputs` contains only the four
include/ files. Five src/ headers were omitted from that run-time field. The
final receipt pins all nine headers at receipt time, labels each composite as a
current diagnostic binding, and does not assert historic src-header identity.
