# func_08148914: the priority-tree walks visit a node twice when they climb back from its left child

**Status: latent. No caller in the ROM can trigger it.** The walk needs a tree
with at least two nodes. The game resets the tree before every script step,
and each step inserts at most one node, so every walk the game makes sees a
single node. `repro.py` shows the single-node game path, and the double
visits on the trees the game never builds.

## The bug

`func_08148914(amount)` shares `amount` out over the tree that
`func_08148860` builds in `g_state_03005F30`, then hands each node its share
through `func_08148B60`. Both walks are the same iterative reverse in-order
traversal: right subtree, then the node, then the left subtree, highest
priority first. Each uses a `prev` pointer to tell which way it arrived.

On arrival at a node, the walk descends right unless it has just come back
from the right child **or the left child**:

```
081489B8  ldr r1, [r4, #0x14] ; cmp r1, #0 ; beq visit    ; no right child
081489BE  cmp r1, r5 ; beq visit                          ; came back from the right
081489C2  ldr r0, [r4, #0x10] ; cmp r0, r5 ; beq visit    ; came back from the left
081489C8  prev = node ; node = node->right ; loop
081489CE  visit: if (value_06 != 0) bl func_08148B60 (0x081489E2)
081489E6  descend left unless left == prev, else climb to the parent
```

The third test stops the walk going right again after the left subtree, but
nothing skips the visit. A node with a left child is therefore visited on the
way down and again on the way back up. In the dispatch walk, such a node with
a non-zero share has `func_08148B60` run twice.

The share-out walk has the same shape. Its left test is at
0x0814894A-0x0814894E, and on the second visit it charges the node again: the
priority is added into `value_06` at 0x08148974-0x0814897E and subtracted from
the budget.

## Trigger and reachability

Insertion (`func_08148860`) puts a node of equal or lower priority to the
*left*. Any tree with two or more nodes therefore has a node with a left child
unless every later priority is strictly higher. So the trigger is any walk of
a tree with two or more nodes, unless the priorities strictly rise in
insertion order.

The game never walks such a tree. The call graph was checked by a word and BL
scan of the whole ROM, and none of these functions is referenced as a
pointer:

* `func_08148914` has one caller, `func_0809A5E0` (bl at 0x0809A5F6). Just
  before the walk (bl at 0x0809A5F0), that caller inserts one node with
  priority 0xFF, callback `func_08097814` and amount 1.
* `func_08148860`, the only inserter, is called only from `func_0809A5E0`.
* `func_0809A5E0` is called from two places, both inside the event-script
  interpreter `func_08092784`:
  * directly, bl at 0x08093BF2 (state 0x4E, entry 0x08093BEA);
  * through bl 0x08093394 (state 0x18, entry 0x08093382) -> `func_080BC984` ->
    `func_080BBE00`
    (bl at 0x080BBE9E) -> `func_080BDD40` -> `func_080BD8CC` (bl at
    0x080BD9D8).
* `func_08092784` is called only by the per-frame task `func_08096E78` (bl
  at 0x08096EA0). Unconditionally and immediately before that call, the task
  empties the tree with `func_08148830` (bl at 0x08096E8C), which is the
  tree's only reset (root = 0, count = 0).
* `func_08092784` runs one script state per call. It dispatches through its
  127-entry table once (0x080929B6-0x080929CE), and no path branches back.
  A control-flow walk of the function, following its jump tables, finds that
  neither insert site is reachable again after either one returns, before
  the function returns. The same check holds after 0x080BBE9E in
  `func_080BBE00` and after 0x080BD9D8 in `func_080BD8CC`.

So each run of `func_08096E78` starts from an empty tree and makes at most one
insert-and-walk. The walk always sees one node with no children, and the
double visit cannot happen.

Because the game's only priority is 0xFF, the share-out also always takes its
`priority > 254` exit at the first node (0x08148966-0x0814896E). That node
gets share 0xFFFF, which `func_08148B60` receives as -1, meaning no step
limit.

## Behaviour against correct behaviour

From `repro.py`. Shares are the nodes' `value_06`, and dispatches are
(node, share) in call order.

| tree (insertion order), amount | ROM | correct |
|---|---|---|
| one node, priority 0xFF, 1 (the game) | `[-1]`, `[(0, -1)]` | the same |
| two nodes, both 0xFF, 1 | `[-1, 0]`, `[(0, -1), (0, -1)]` | `[-1, 0]`, `[(0, -1)]` |
| A 4, B 8, C 2; 20 | `[8, 16, 2]`, `[(B, 16), (A, 8), (C, 2), (A, 8)]` | `[4, 16, 2]`, `[(B, 16), (A, 4), (C, 2)]` |
| rising priorities (no left children) | equal to correct | |

In the third row, A is charged a second time when the walk climbs back from
C. It ends with twice its share and is then dispatched twice. On 300 seeded
random trees the fixed build equals an independent recursive model every
time, while the ROM differs on 217.

## Impact

None in the shipped game. With a single node, the second-visit path is never
taken, as described above.

Had the game ever put two objects in the tree in one frame, the
higher-priority object would have been run twice by `func_08148B60` (which
steps an object's script; share -1 means no step limit). With mixed
priorities, nodes with left children would also have taken double shares.

## Developer intent

The intent was a non-recursive reverse in-order walk over a parent-linked
tree, visiting each node once.

The likely misunderstanding is in the case analysis of the "came from"
states. Such a walk has three arrival states:

* from the parent: go right first;
* from the right child: visit, then go left;
* from the left child: climb.

The code folds "from the left child" into the test that stops the right
descent, and then falls into the visit as if it had arrived from the right.

Evidence:

* Both walks share the same flaw. They were written once and copied.
* The structure is general: up to 16 nodes, priorities, budgeted shares, and
  `amount` restarting over the tree while budget is left. FFTA uses only a
  degenerate case of it: one node per frame, at priority 0xFF. The faulty
  branch is unreachable in that use, which explains why testing would not
  have exposed it. This is an inference from the call sites, not a known
  history of the code.

## The fix

```c
/* share-out walk, before the visit */
#ifdef BUGFIX
            if (node->left == prev)
                goto climb;
#endif
            ...
#ifdef BUGFIX
        climb:
#endif
            if (node == first)
                break;

/* dispatch walk */
#ifdef BUGFIX
            if (node->left != prev)
#endif
            if (node->value_06 != 0)
                func_08148B60(...);
```

`prev == node->left` holds exactly when the walk has just climbed out of the
left subtree. `prev` starts as `(PriorityNode *)-1` and is otherwise always a
node, so a null `left` never equals it. Skipping the visit there, and going
straight to the climb, makes each walk visit every node once, in
right-node-left order.

The default build is unchanged:

* it MATCHes 242/242;
* `plausible.py --strict` exits 0;
* the preprocessed default token stream is identical to the parked source.

## Reproduction

`repro.py` does the following:

1. Links the default build at 0x08148914 and requires it to equal your ROM's
   242 bytes.
2. Builds each tree with the ROM's own `func_08148830` / `func_08148860` (and
   its done test `func_08149368`).
3. Runs the ROM bytes, the `-DBUGFIX` build and a recursive Python model.

`func_08148B60` is stubbed to record its arguments. The game case also runs
the ROM's `func_0809A5E0`. Requires unicorn and the repository toolchain (see
the docstring).

```
$ python3 docs/bugs/08148914/repro.py baserom.bin
source src/08148914.c: default build == ROM bytes [08148914, 08148A06)

1. The game: func_08096E78 empties the tree, then one script step calls
   func_0809A5E0 once (amount 1, priority 0xFF).  One node, one dispatch.
  [ok] ROM func_0809A5E0 dispatches (object, value_08, share, value_0C): [('0x2010000', '0x8097815', -1, '0x2030100')]
  [ok] ROM walk / BUGFIX walk on that tree: (([-1], [(0, -1)]), ([-1], [(0, -1)]))

2. Trigger (the game never does this): two func_0809A5E0 calls with no
   reset between them.  Both nodes have priority 0xFF, so the second goes
   left of the first; the first walk stops at the root (priority > 254).
  [ok] ROM    shares, dispatches: ([-1, 0], [(0, -1), (0, -1)])
  [ok] BUGFIX shares, dispatches: ([-1, 0], [(0, -1)])
  [ok] model  shares, dispatches: ([-1, 0], [(0, -1)])

3. Trigger in the first walk too: priorities A 4 (root), B 8 (right),
   C 2 (left), amount 20.  A is charged again when the walk climbs back
   from C, and dispatched twice.
  [ok] ROM    shares, dispatches: ([8, 16, 2], [(1, 16), (0, 8), (2, 2), (0, 8)])
  [ok] BUGFIX shares, dispatches: ([4, 16, 2], [(1, 16), (0, 4), (2, 2)])
  [ok] model  shares, dispatches: ([4, 16, 2], [(1, 16), (0, 4), (2, 2)])

4. Non-trigger: no node has a left child (priorities rising: each new
   node goes right).  Both agree with the model.
  [ok] [3, 5, 9] amount 40: ROM == BUGFIX == model: True
  [ok] [1, 2, 3, 4] amount 7: ROM == BUGFIX == model: True

5. 300 seeded random trees (2-8 nodes, priorities 1-60 or 0xFF):
  [ok] BUGFIX equals the model on all 300: 300
  the ROM walk differs from it on 217 of them
  [ok] the ROM walk differs on some: True

all assertions hold
```
