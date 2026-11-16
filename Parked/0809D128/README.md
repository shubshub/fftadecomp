# 0x0809D128 - near miss (464 bytes): 448 compiled, two structural residuals

Retry of Parked/0809D128 (444 bytes) on 2026-11-16, kit fcdf2d45, default flags. match.py: 'compiled symbol is shorter than the indexed span:
448 < 464'. plausible.py: no findings. Index [0x0809D128, 0x0809D2F8) correct; uses only g_callbacks_0836D4B8 and data_0836D4BC. Not shipped:
not byte-identical.

The source here writes the body of 0x0809D464 as a static inline start_movement(slot->movement, slot->object, slot->route, slot->count) with that
neighbour's struct names and its set_phases / set_state inline copies of func_0809D620 / func_0809D638 (these fix the movs r0,#2; movs r1,#3;
movs r2,#4 preload). The free-slot search is an inline returning &slots->slots[i] or 0. Helper rule: start_movement copies a real ROM function
(0809D464) that has no shippable source yet, set_phases / set_state are body copies but not verbatim copies of src/0809D620.c / src/0809D638.c,
and find_free_slot has no shared text, so each would need that settled before this could ship.

Residual 1 - free-slot loop and the out-of-line found block. The ROM has a counter in r5, an address cursor in r3, a byte-offset cursor in r4,
a dead copy adds r2, r4, #0, and the found block (r7 = r6 + (r4 + 8)) after cmp type,#2; beq; b L2e2 and the middle literal pool. agbcc's
find_and_verify_loops (loop.c) moves a loop-exiting block only if a top-level BARRIER already follows the join; a natural if/&& has none there,
so the block stays in the loop. With any barrier on the type != 2 path the ROM loop comes out exactly (dead r2 copy and pool position included)
- produced by duplicating slot->active = 1; return; in the caller, or a dead count = 0; return; in the inline. Both are steering. Ruled out: a
switch on the type, early returns, a value-returning inline, split or nested inlines, if/else forms, a data local, break/index/u8 loop forms,
while / do / != 0 walk loops. Unconfirmed lead: the barrier could come from the second delete_null_pointer_checks pass (if (p != 0) on a
dereferenced pointer becomes jump + barrier) or merge_blocks; no natural null check found that fits.

Residual 2 - tail register split, the same quirk as Parked/0809D464 (its `point = (RoutePoint *)state` contrivance reproduces this tail exactly
when inlined here). The movement pointer is in r4 for the first half and r4 then becomes the loop cursor; a second copy spilled to [sp+4] is used
only for the length store after func_08148A98. One natural source for 0809D464 would likely close both. Ruled out: a caller-local movement
argument, route++ cursors, split inlines (init + adjust).

Small diffs, probably knock-on: the alloc block's strh r5, [r0, #2] off a +0xDC base (ours folds to +0xDE; a Status * local did not change it);
the ROM loads 0x124 separately for its two calls; incoming registers state r6 / route sb / count r8 in the ROM vs r8 / stack / r9 here. With both
contrivances combined only these register choices and a 20- vs 16-byte frame remain.
