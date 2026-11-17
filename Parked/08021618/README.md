# 0x08021618 - resource-state setup: bytes identical, refused (incoming halfword arguments read through `mov Rd, sp`) (224 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_08021618(owner, state, alternate, second, category,
selector, index)` looks up the resource list `func_08021004(category, selector)` and returns -1 when entry `index`
is empty. With an existing `state` it re-binds it through `func_08021C84(state, state->first, state->second)`;
otherwise it asks `func_08021C90(owner->pool, alternate, second)` for a slot (returning 0 if negative), allocates a
0x48-byte state with `func_08007138`, clears it through `g_callbacks_0836D4B8[0]` (`_call_via_r2`, 0x0802167E), links
it into two lists with `func_080C7A74`, and binds it. It then initialises the state from the resource (frame
pointers, limit, counter -1, flags 0x45, or 0x65 when `selector & 3` is 2 or 3) and stores `category` and `selector`
as halfwords. The index row `08021618 080216F8 224 112 return` has the right extent; 112 is half the byte count, and
the reachable instruction count is 102 (the kit's own refinement agrees). `g_callbacks_0836D4B8` is already in
`config/data_symbols.json`.

The frame is the pushes alone: `push {r4-r7, lr}` and `push {r8, r9}`, 0x1C bytes. Arguments 5 to 7 are at
`[sp, #0x1c]`, `[sp, #0x20]`, `[sp, #0x24]`. They are read as words for the calls, and the two halfword stores at
the end read `category` and `selector` again with the zero-offset form of the narrow read:

```
080216C8  mov  r0, sp
080216CA  ldrh r0, [r0, #0x1c]    @ category (argument 5)
080216CE  mov  r1, sp
080216D0  ldrh r1, [r1, #0x20]    @ selector (argument 6)
```

## Byte identity

`08021618.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08021618, with every callee, `_call_via_r2` at
0x0814224C and `g_callbacks_0836D4B8` bound to their ROM addresses (8 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The
224-byte symbol equals the ROM span `[0x08021618, 0x080216F8)`: SHA-256
`a0defb0fce2f47af678961327286fb7d45a4314ca5f7725f6ec2fb00277d34ae` for both. `.text` is exactly 224 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

The buffer clear is written as the indirect call `g_callbacks_0836D4B8[0](state, sizeof(*state))`; agbcc emits the
`_call_via_r2` call for it. The earlier copy of this source named the thunk instead
(`func_0814224C(state, sizeof(*state), g_callbacks_0836D4B8[0])`), the spelling kit #133 is about; it gives the same
bytes and the same refusal, and is not kept.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08021618.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `--function-address-profile canonical-thunks-v1`, `bounded-buffer-conditional-thunks-v1` and its three scratch variants (8) | `stack-alias access is unaligned or outside the tracked frame` |
| `named-data-buffer-v1`, `restoring-owner-acyclic-v1`, `bounded-buffer-root-return-scratch-v1`, `ordinary-multiple-switch-source-v1` and 58 other owner selectors (62) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `runtime summary owner requires exact canonical division entries and no thunks` |
| `--control-flow-profile mixed-return-inert-spin-v1` and 41 addressed-runtime selectors (42) | `function address requires a canonical addressed function` |
| `--addressed-signed-runtime-profile addressed-native-bios-ordinary-r2-callback-data-v1`, `addressed-signed-runtime-r2-callback-data-v1` | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| `conditional-known-query-stack-buffer-v1` | `refused: function-address evidence does not support runtime call thunks` |
| `conditional-scheduler-descriptor-calls-v1` and its three payload variants | `scheduler contract requires one actual scheduler call` |
| `--switch-data-profile switch-thunks-v1`, `switch-thunks-frame-v1` | `switch thunks require a complete local switch, objects and no other runtime` |

The other 91 selector values stop on requirements this function does not meet (a runtime, a switch, a scheduler
call, an external alignment pad, the -O0 toolchain, the finite-loop or float shapes).

## Cause

The default path accepts the compiler's `_call_via_r2` call on the non-local state pointer, and the word reads of
the incoming arguments. It refuses at the halfword reads above. The kit admits the narrow read of an incoming word
since #205, but only in the form `add Rd, sp, #imm` followed by `ldrb`/`ldrh Rd, [Rd, #imm5]`, where the `add`
"addresses entry SP or above" (kit `README.md:751-769`). When the frame is small enough for the load's own immediate to reach the incoming word, agbcc forms
the base with `mov Rd, sp`, the zero-offset case of the same idiom, and that form is not admitted: the base is SP
itself, below entry SP, so the rule's "at or above entry SP" test fails on the base, although the address read
(`sp + 0x1c`, `sp + 0x20`) is the incoming argument word. `0x080A10D4` is refused the same way.

The owner and runtime selectors stop earlier, on the `_call_via_r2` thunk.

## Source notes

- The allocation, clear and list insertion are a `static inline` helper, `new_state(owner)`. Written out at the call
  site with the same statements, the function is still 224 bytes, but 35 bytes differ from 0x08021620 on, so the
  helper is load-bearing. No out-of-line function with its text is known in the ROM.
- `category`, `selector` and `index` are `u32` arguments stored as halfwords, which is what makes agbcc re-read the
  two stack words with `ldrh`.
- `state->counter = -1` and the `variant` switch (cases 2 and 3 set flags 0x65) follow the ROM's order of stores.

## Ruled out

- Calling the thunk by name, `func_0814224C(state, sizeof(*state), g_callbacks_0836D4B8[0])`: same 224 bytes and the
  same refusal (the earlier copy of this source); not kept, because the compiler emits that call itself.
- The helper written out in the function body: 35 bytes differ (above).

kit issue: shubshub/fftadecomp-kit#75 (the `mov Rd, sp` form of the narrow incoming read)
