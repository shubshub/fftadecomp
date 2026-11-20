# Resource-layer request at 080200C8

The ordinary Thumb build with agbcc, -mthumb-interwork and -O2 spans all 428
bytes from 0x080200C8 through 0x08020273. The default matcher reports 425/428
bytes and 200/203 instructions identical. The remaining three instructions
use a different temporary for the address of data_02007F10.

| Address | ROM | Candidate |
| --- | --- | --- |
| 0x080200E4 | ldr r3, [pc, #0x5c] | ldr r5, [pc, #0x5c] |
| 0x080200E6 | ldrh r1, [r3] | ldrh r1, [r5] |
| 0x0802011A | adds r6, r3, #0 | adds r6, r5, #0 |

All following instructions, branches, direct calls, four literal words and
their positions agree. Using a typed record array and expressing the two
readiness predicates in the forms used by their out-of-line siblings did not
resolve the register difference. The default verdict is NOT MATCHING.

The default and named-data-buffer-v1 paths also reject the compiler's private
stack accesses during the volatile-semantics check. At 0x080200D8 through
0x080200DC the function zero-extends its incoming u16 index and stores the
resulting word at [sp]. At 0x08020220 through 0x08020226 it copies sp to r1,
reads the low halfword at [r1] and writes it to request.index. The slot remains
private, and its value does not change between the store and the load. The
checker reports a partially overlapping stack access. The named selector
stops before its own verification. Both the ROM and the candidate have these
same instructions.

The two readiness checks at 0x0802011E/124 and 0x08020130/136 agree with
0x08020490 and 0x080204B0 at offsets 0x168 and 0x16C in g_state_02007F40.
Either busy field returns zero. The successful path selects a packed record,
computes three resource-relative pointers, and chooses its entry range at
0x08020194. It writes a mode-zero request at state + 0x184, including its
layer, two destinations, index and coordinates. It calls 0x080035A8(3) at
0x0802022A and 0x0801E648() at 0x08020236. The last branch at 0x0802023E
controls a further call to 0x080035A8(2) at 0x08020242. It clears the
corresponding display bits, advances the selection, and returns one.

No direct Thumb caller or direct short branch landing on this entry was found
in the USA ROM, and no aligned word contained the entry address or its Thumb
function-pointer encoding. The argument roles come from the entry code and
request fields, corroborated by sibling 0x0801FEB8. The packed table format
and selection fields agree with 0x08020008, 0x0802006C and 0x08020274.

Seven paired Unicorn runs executed the original code and the linked candidate
with real ROM callees. Three used unmodified ROM data, including both busy
exits. Four used an in-memory packed-record fixture to exercise both entry
range modes under both display settings. The runs independently checked the
return, the selection and request bytes, the display mask and the sequence of
calls. All seven pairs agreed and covered both outcomes at all six conditional
instructions. These fixtures establish behavior for the selected inputs. No
in-game invocation was observed.
