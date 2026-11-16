# 0x08010DD0 - near miss: byte-identical only through a steering once-loop in a single-use macro (146 bytes)

Target: complete `[0x08010DD0, 0x08010E62)`, 146 bytes, 59 instructions. Default flags; the list heads
`data_02009174`..`data_02009180` and `data_02009170` are already in config/data_symbols.json. Retried 2026-11-16 with
kit fcdf2d45.

| file | result |
| --- | --- |
| `08010DD0-natural.c` (the siblings' `static inline remove_node`, local node copy declared before `head`) | NOT MATCHING, 49/59 instructions, 136/146 bytes, plausible --strict clean |
| `08010DD0.c` (`REMOVE_NODE` statement macro, `do { } while (0)`) | `MATCH - byte identical`, 59/59, 146/146, plausible --strict clean |

Not shipped. A statement macro ships only with shared text (the same text reproduces a second function) or as a
verbatim copy of a real ROM function, and `REMOVE_NODE` is neither: substituted into the siblings it gives
08010E64 NOT MATCHING (76/98) and 08010F30 NOT MATCHING (50/79). And what it contributes is the once-loop, which is
the open policy question on loops that run once.

## What the function does
It walks the counted node array of the State at 0x02009170, removes each active node whose func_08010AFC update
returns 0 from one of four doubly linked lists (head chosen by `node->list`), and calls func_08010D2C when flag bits 1
and 2 are clear.

## Why only the once-loop matches
The natural form produces the ROM's `adds rX, r4, #0` node copy and every instruction in order; only the node copy and
the list head swap r3/r2 (eight instructions). From the `-dl`/`-dg` dumps: global allocation orders the two pseudos by
floor_log2(refs) * refs / live_length, with references weighted by loop depth. Inside the real loop the copy scores
3*8/34 = 0.706 and the head 3*12/52 = 0.692, so the copy gets r2. The `do { } while (0)` leaves loop notes, flow weights
the references one level deeper, and the scores become 1.06 (copy) and 1.38 (head) - the ROM's order. Nothing else
about the macro matters, and there is no Thumb scheduling pass to reorder the result.

The same once-loop written in the function body (`do { remove_node(node); } while (0);`) is also byte-identical and
plausible.py rejects it as dead-code; the macro carries that loop through the statement-macro exemption.

The operation is a real function: 08011428 is its out-of-line body (57 BL callers), and 08010E64, 08010F30 and
08011484 inline it. One form, `static inline remove_node(Node *node)` with a local copy of the parameter declared
first, matches all four (08011428 as the plain function) and fails only here, by the r2/r3 swap. In a 90-form grid
(inline / do-while macro / brace macro, with and without the copy, every declaration order) nothing matches 08010DD0,
08010E64 and 08010F30 together: 08010DD0 matches only do-while + copy declared before head; 08010E64 matches none of
the do-while forms. The local copy is in the ROM (the same copy appears at the 08011484 inline site) and `removed`
before `head` is the instruction order; only the once-loop is a contrivance.

Also tried, all NOT MATCHING: the siblings' inline verbatim with array heads or separate heads (54/58, no copy); the
inline with a local copy, copy first or head first (49/59, the r2/r3 swap); an inline taking `void *` with a typed
local (49/59); get_head + unlink helpers as in src/080107D4.c, with and without a copy (54/58, 49/59); an indexed loop
passing &nodes[i] to the verbatim inline (copy appears, r2/r3 swapped); a brace-only macro with the copy (49/59); the
macro without the copy (54/58); four separate head externs; for/while loops (add a count check the ROM lacks).

For the next attempt: the ROM needs the removal body, head selection included, one loop level deeper than the node
loop, with a fresh copy of the node. A once-loop around only the unlink step does not do it. The heads are members of
the State at 0x02009170 (+4..+0x10); the siblings' `extern Node *data_02009174[4]` spelling (used in
`08010DD0-natural.c`) also matches with the macro in place of the four separate externs of `08010DD0.c`.

src/0800C224.c (`UNLINK_NODE`) has the same dependency: with `{ }` instead of `do { } while (0)`, or as a static inline,
it is NOT MATCHING (19/28).

kit issue: shubshub/fftadecomp-kit#191 (policy question on loops that provably run once, including `do { } while (0)`)
