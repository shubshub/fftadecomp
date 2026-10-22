# Conditional startup extension: 080004B0 through 0800052C

**Evidence-only inventory; independent entry at 080004B0 remains unproved. Keep all function metadata unchanged.** Neither a decoded prologue, an explicitly seeded analysis, nor the existing 08000516 index row establishes an external activation. No unconditional 080004B0 insertion, 08000516 deletion, original-symbol reconstruction, or match/status credit is approved.

Only `[080004B0,0800052C)` was decoded or mapped: 124 bytes, SHA-256 `895b06643d776f57dbbece8b3ebef57b7220ff39d75c5e6f952aa3937f0c0e0e`, from the 16 MiB ROM with SHA-1 `4ac05441f4de70a4ec3dd932116346c61b8783d9`. Nothing at or beyond 0800052C and no outgoing callee body was decoded.

Under the explicit hypothesis of Thumb entry at 080004B0, and conditional on external calls returning in the required state, the complete local partition is:

| Half-open interval | Conditional role | Size |
| --- | --- | ---: |
| `[080004B0,08000524)` | 44 reached instructions | 116 bytes |
| `[08000524,08000528)` | Referenced word pointing to 03000E10 | 4 bytes |
| `[08000528,0800052C)` | Referenced word pointing to 03000EB4 | 4 bytes |

There are six literal accesses, no code/pool overlap, no alignment bytes, and no gaps. The conditional branches target 080004D8 and 0800050A. Four syntactic local paths restore the saved entry return word and r7 with an eight-byte local save, **assuming calls preserve the frame and required callee-saved state**. Without assumed callee returns, traversal stops at the first external call after three instructions. These are static checks, not execution or feasibility proofs.

The existing 08000516 coordinate is reached by ordinary fallthrough from 08000514 and consumes earlier register values and the saved frame. An ordinary empty-frame activation at 08000516 underflows during restoration. This rejects that particular standalone interpretation, not an unknown alternate entry supplied with an appropriate context. The previously inspected startup and 08000460 evidence provides no incoming call establishing 080004B0 or 08000516; no broader incoming-reference search was performed.

Fourteen direct call targets remain unaudited. Targets 08144AF0 and 081451B4 have no exact entries in either captured index. The other twelve are **present in both indexes, with Thumb mode recorded in JSON**; the text index has no mode column and does not independently attest instruction mode. Target entry validity, helper semantics, return/preservation behavior, memory initialization/aliasing, and hardware effects remain open.

Independent raw instruction-field arithmetic, Capstone decoding, and actual-address Binary Ninja checks agree on the conditional 44-instruction graph. BN is seeded at 080004B0, not discovering an established entry. The first word also decodes in ARM mode; decoder success alone is not mode evidence. Seven structural negative controls reject, while three numeric/condition mutations remain structurally acceptable and are excluded only by original-byte identity, demonstrating the limits of structural checks.

Captured maps: JSON `767ba6096c6b3bae03acec2cb0fc754125fd159882529c4440b282127a60c45d`; text `04553d57b6be95acfc65bd5df3c35bd2d6651abb06c36598f83bae1a654d9359`. Frozen author contract `3ebf0c4eeabe4763bc0df5d109adde45378e7786189704d8689fd0c3180cd7b8`; manifest `e4bb0388eb619d45563a19d4f5c73fc413d290734a317679839ac7c6ce0aff25`. This annotation contains no raw ROM or disassembly and is not input to function counting or matching tools.
