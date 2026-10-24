# Conditional startup extension: 080004B0 through 0800052C

**Evidence-only inventory; a conditional installed IRQ callback establishes external Thumb entry at 080004B0. Keep function metadata unchanged pending entry-versus-ownership classification.** The dated evidence below supersedes the earlier missing-entry premise. It does not authorize unconditional 080004B0 insertion, 08000516 deletion, original-symbol reconstruction, or match/status credit.

The original body audit decoded or mapped only `[080004B0,0800052C)`: 124 bytes, SHA-256 `895b06643d776f57dbbece8b3ebef57b7220ff39d75c5e6f952aa3937f0c0e0e`, from the 16 MiB ROM with SHA-1 `4ac05441f4de70a4ec3dd932116346c61b8783d9`. That audit decoded nothing at or beyond 0800052C and no outgoing callee body. The later entry-witness audit separately inspected the startup table and IRQ path described below.

Under the explicit hypothesis of Thumb entry at 080004B0, and conditional on external calls returning in the required state, the complete local partition is:

| Half-open interval | Conditional role | Size |
| --- | --- | ---: |
| `[080004B0,08000524)` | 44 reached instructions | 116 bytes |
| `[08000524,08000528)` | Referenced word pointing to 03000E10 | 4 bytes |
| `[08000528,0800052C)` | Referenced word pointing to 03000EB4 | 4 bytes |

There are six literal accesses, no code/pool overlap, no alignment bytes, and no gaps. The conditional branches target 080004D8 and 0800050A. Four syntactic local paths restore the saved entry return word and r7 with an eight-byte local save, **assuming calls preserve the frame and required callee-saved state**. Without assumed callee returns, traversal stops at the first external call after three instructions. These are static checks, not execution or feasibility proofs.

The existing 08000516 coordinate is reached by ordinary fallthrough from 08000514 and consumes earlier register values and the saved frame. An ordinary empty-frame activation at 08000516 underflows during restoration. This rejects that particular standalone interpretation, not an unknown alternate entry supplied with an appropriate context. The original startup and 08000460 inspection found no incoming call establishing either entry; the later IRQ callback witness establishes conditional 080004B0 activation, not a separate 08000516 activation. No exhaustive incoming-reference search was performed.

Fourteen direct call targets remain unaudited. Targets 08144AF0 and 081451B4 have no exact entries in either captured index. The other twelve are **present in both indexes, with Thumb mode recorded in JSON**; the text index has no mode column and does not independently attest instruction mode. Target entry validity, helper semantics, return/preservation behavior, memory initialization/aliasing, and hardware effects remain open.

Independent raw instruction-field arithmetic, Capstone decoding, and actual-address Binary Ninja checks agree on the conditional 44-instruction graph. BN is seeded at 080004B0, not discovering an established entry. The first word also decodes in ARM mode; decoder success alone is not mode evidence. Seven structural negative controls reject, while three numeric/condition mutations remain structurally acceptable and are excluded only by original-byte identity, demonstrating the limits of structural checks.

Captured maps: JSON `767ba6096c6b3bae03acec2cb0fc754125fd159882529c4440b282127a60c45d`; text `04553d57b6be95acfc65bd5df3c35bd2d6651abb06c36598f83bae1a654d9359`. Frozen author contract `3ebf0c4eeabe4763bc0df5d109adde45378e7786189704d8689fd0c3180cd7b8`; manifest `e4bb0388eb619d45563a19d4f5c73fc413d290734a317679839ac7c6ce0aff25`. This annotation contains no raw ROM or disassembly and is not input to function counting or matching tools.

## Installed IRQ entry witness — 2026-10-24

ROM table word `08149434` contains the Thumb pointer `080004B1`. Startup literals at `08000388` and `0800038C` supply destination `030008D0` and source `0814942C`; the copy at `080002C2`/`080002C4` installs that word into `030008D8`.

In the retained ARM IRQ graph, pending mask 1 selects table offset 8 and the branch at `0800013C` reaches `0800018C`. The dispatcher loads table base `030008D0`, adds the offset, loads the installed pointer at `080001B4`, and branches through it at `080001C0`. Its low bit selects Thumb entry `080004B0`; the preceding return-address construction yields ARM continuation `080001C4`.

This is independent entry and mode evidence, conditional on installation, slot retention, valid interrupt context and realization of that pending-mask path. It does not prove runtime activation, dominance, persistent RAM identity, or the behavior of outgoing callees. The table range `[0814942C,08149468)` hashes to `3291ab7e80b386ab1f6229999bc990085679648bcbc4552fd86f314e6e9cb284`; the body hash above remains unchanged.

The remaining inventory decision is how to represent the witnessed entry and conditional complete range while preserving historical `08000516` provenance and its unknown alternate-entry contract. Under the witnessed activation, `08000516` is an internal tail. The current flat index and bounded refiner do not exercise a non-owning subentry representation: adding overlapping complete-function rows would double-count ownership and truncate refinement at `08000516`. No function-map replacement is made here.

Independent review SHA-256: `4573adf094b9c8427f162256b83d1e403c69edba01148878fed0bae3e36c90da`; retained review manifest: `c3d6a297e5d65b3d71f4e7b0eb8502cb4588ff9dcbd6e6ba8619953cca6469d8`. The review approves this evidence update, not a recovered original symbol or an exhaustive code inventory.
