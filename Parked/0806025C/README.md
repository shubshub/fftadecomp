# 0806025C: byte-identical; needs an index entry and a switch-with-function-words selector

Target: `[0x0806025C, 0x080603F4)`, 408 bytes. It is a six-entry menu switch on `menu->type`. Cases 3, 5 and 6 register the callbacks `func_08060100`, `func_080601B4` and `func_080601A4` via `func_08017AC4`. It also uses `data_0200F44C` and a 4-byte stack local.

The source was hand-linked with every callee at its address, and the output equals the ROM span, jump table and pool included. Two blockers remain:

1. `0x080601A4` is a 12-byte Thumb function that is not in the index (`push {lr}; adds r0, r1, #0; movs r1, #0; bl func_08060154; pop {r1}; bx r1`). match.py refuses the function word with `function address is unknown, ambiguous, misaligned, or not Thumb ROM code`.
2. With that row added in a scratch root, the default refusal is `switch evidence excludes object, callback and runtime-thunk bindings`. The `restoring-owner-switch-*`, `ordinary-multiple-switch-source-v1` and `restoring-owner-runtime-v1` selectors each refuse on their own layout rules.
