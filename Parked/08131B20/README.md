# 0x08131B20 - parked, byte-exact but the verifier cannot model it

The source is byte-exact (150/150 bytes) and plausible.  It is parked because
`match.py` cannot *certify* it yet, not because anything is wrong with it.

## What it is

A switch on a `u8` kind, with a 47-entry table of Thumb callbacks at
`0x083A86F8` and a jump table at `0x08131B74`.  The pool holds
`0x0200F3F0` (the state object), the callback table, the jump-table base, and
the five switch entries: kinds 1, 2, 4 and 5 go to one arm, kind 3 to another.

## Why it is parked

The switch profile refused it three times over, and each refusal was a real
gap rather than a source problem:

1. `function_address_target` refused any target that is a runtime thunk:
   *"function-address evidence does not support runtime call thunks"*.  But
   agbcc calls through a callback table with `bl _call_via_r1`, and the ROM's
   own instruction at `0x08142248` *is* that thunk - no source spelling can
   avoid it.  The refusal is now lifted, with the same check the linked profile
   makes: the ROM's bytes at that address must really be `bx r<n>; mov r8,r8`.
2. The switch binding check refused a runtime thunk among the switch's targets:
   *"switch evidence excludes object, callback and runtime-thunk bindings"*.
   That now verifies the thunk the same way and treats it as a call rather than
   a table entry.
3. What remains is the switch verifier's own control-flow analysis:
   *"switch selector bound is bypassed by an unverified predecessor edge"*.
   The call through a thunk creates an edge the switch's CFG model does not
   know about, and the selector's bound looks bypassable because of it.

The third one is real work in the switch verifier - modelling a call target
that is a thunk rather than an addressed function - and it is not done.

## What was needed in the source

- The callback table must be a **named global**.  With a literal address,
  agbcc materialises the table base *after* the index; the ROM loads it
  first, and only a symbol reference keeps the early load.  Hence
  `"g_table_083A86F8": "0x083A86F8"` in config/data_symbols.json.
- `lsls #24` with no `lsrs` after it is a `u8` narrowing before the `!= 0`
  test; `cmp r0,#4 / bhi` is an unsigned switch on the kind; `pop {r1};
  bx r1` is the non-void return.
