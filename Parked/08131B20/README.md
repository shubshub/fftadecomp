# 0x08131B20 - parked, byte-exact but the verifier cannot model it

**The source is lost.**  It was written and verified byte-exact, but it never
got a committed match report - the verifier refused it - so it was never staged
and never committed, and it was removed from `src/` when the park was made.
What survives is this note, which is enough to rewrite it.

## What it did

A switch on a `u8` kind, with a 47-entry table of Thumb callbacks at
`0x083A86F8` and a jump table at `0x08131B74`.  The pool held `0x0200F3F0`
(the state object), the callback table, the jump-table base, and five switch
entries: kinds 1, 2, 4 and 5 to one arm, kind 3 to another.  150 bytes, 35
instructions.

## What was needed in the source

- The callback table must be a **named global**.  With a literal address,
  agbcc materialises the table base *after* the index; the ROM loads it
  first, and only a symbol reference keeps the early load.  Hence
  `"g_table_083A86F8": "0x083A86F8"` in config/data_symbols.json.
- `lsls #24` with no `lsrs` after it is a `u8` narrowing before the `!= 0`
  test; `cmp r0,#4 / bhi` is an unsigned switch on the kind; `pop {r1};
  bx r1` is the non-void return.
- The agent's own measurement: the compiled ELF symbol at `0x08131B20` is
  0x96 bytes and identical to the ROM.

## Why it was parked rather than committed

The switch profile refused it three times over, and each refusal was a real
gap in the verifier rather than a source problem:

1. `function_address_target` refused any target that is a runtime thunk:
   *"function-address evidence does not support runtime call thunks"*.  But
   agbcc calls through a callback table with `bl _call_via_r1`, and the ROM's
   own instruction at `0x08142248` *is* that thunk - no source spelling can
   avoid it.
2. The switch binding check refused a runtime thunk among the switch's
   targets: *"switch evidence excludes object, callback and runtime-thunk
   bindings"*.
3. Underneath both is the switch verifier's own control-flow analysis: a call
   through a thunk creates an edge the switch's CFG model does not know, and
   the selector's bound then looks bypassable - *"switch selector bound is
   bypassed by an unverified predecessor edge"*.

A partial attempt to relax (1) and (2) was tried and reverted: it let the
binding stage through but then broke the verifier for functions that had
already matched.  The change needs the switch verifier to model a call target
that is a thunk rather than an addressed function, and that is not a small
change.

## The fix, when someone takes it

`function_address_target` should accept a target in `RUNTIME_HELPERS.values()`
when the ROM's bytes at that address really are `bx r<n>; mov r8,r8` - the
check `thunk_is_call_via` already does for the linked profile - and the switch
verifier's CFG needs to treat such a call as a call, with the same edge it
gives an ordinary call.
