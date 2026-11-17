# 0x080A10D4 - path state setup: bytes identical, refused (incoming halfword arguments read through `mov Rd, sp`) (264 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. A ten-argument initialiser. It clears the 0xA38-byte
state through `g_callbacks_0836D4B8[0]` (`_call_via_r2`, 0x080A10FA), stores the scalar arguments, the source
pointer and a copy of the 8-byte target position into it, reads the source and target coordinates, gets an owner
from `func_08099C30(source->object)`, clears the first 0x4C bytes again through the same callback (0x080A119A),
stores the two coordinate triples and the owner there, and calls `func_080A0FF0(state)`. The index row
`080A10D4 080A11DC 264 120 return` is right (120 reachable instructions, four pool words). `g_callbacks_0836D4B8` is
already in `config/data_symbols.json`.

The frame is 0x24 bytes (`push {r4-r7, lr}`, `push {r8-r10}`, `sub sp, #4`), so the six stack arguments are at
`sp + 0x24` to `sp + 0x38`. Three of them are stored as halfwords and read with the zero-offset form of the narrow
read:

```
080A110C  mov  r1, sp
080A110E  ldrh r1, [r1, #0x2c]    @ arg6 -> state->unknown_1DE
080A1118  mov  r3, sp
080A111A  ldrh r3, [r3, #0x30]    @ arg7 -> state->unknown_1DA
080A112E  mov  r3, sp
080A1130  ldrh r3, [r3, #0x28]    @ arg5 -> state->unknown_1E2
```

`arg4` (`sp + 0x24`) and `arg9` (`sp + 0x38`) are read as words. A fourth `mov r0, sp; ldrh r0, [r0, #0]` at
0x080A11AC reads a local below entry SP, which is an ordinary in-frame access.

## Byte identity

`080A10D4.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x080A10D4, with `func_08099C30`, `func_080A0FF0`,
`_call_via_r2` at 0x0814224C and `g_callbacks_0836D4B8` bound to their ROM addresses (4 `R_ARM_THM_CALL`, 1
`R_ARM_ABS32`). The 264-byte symbol equals the ROM span `[0x080A10D4, 0x080A11DC)`: SHA-256
`9ae76f6b2b1be4c3fae367a501bc7ac9af1301a8075e1c8e1581842aaa019a0f` for both. `.text` is exactly 264 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/080A10D4.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values, `--function-address-profile canonical-thunks-v1`, `bounded-buffer-conditional-thunks-v1` and its three scratch variants (8) | `stack-alias access is unaligned or outside the tracked frame` |
| `named-data-buffer-v1`, `restoring-owner-acyclic-v1`, `bounded-buffer-root-return-scratch-v1`, `ordinary-multiple-switch-source-v1` and 58 other owner selectors (62) | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `bounded-buffer-runtime-summaries-v1`, `bounded-buffer-bios-mixed-fast-fill-runtime-summaries-v1` | `runtime summary owner requires exact canonical division entries and no thunks` |
| `--control-flow-profile mixed-return-inert-spin-v1` and 41 addressed-runtime selectors (42) | `function address requires a canonical addressed function` |
| `--addressed-signed-runtime-profile addressed-native-bios-ordinary-r2-callback-data-v1`, `addressed-signed-runtime-r2-callback-data-v1` | `addressed runtime ELF requires actual addressed calls and no unresolved symbols` |
| `conditional-known-query-stack-buffer-v1`, `conditional-finite-local-word-loops-v1`, `conditional-finite-spilled-scalar-loops-v1` | `refused: function-address evidence does not support runtime call thunks` |
| `conditional-scheduler-descriptor-calls-v1` and its three payload variants | `scheduler contract requires one actual scheduler call` |
| `--switch-data-profile switch-thunks-v1`, `switch-thunks-frame-v1` | `switch thunks require a complete local switch, objects and no other runtime` |

The other 89 selector values stop on requirements this function does not meet (a runtime, a switch, a scheduler
call, an external alignment pad, the -O0 toolchain, the float shapes).

## Cause

The same as `0x08021618`. The default path accepts both compiler `_call_via_r2` calls (the state is not a local) and
the word reads of the incoming arguments, and refuses at the halfword reads above. Since #205 the kit admits a narrow
read of an incoming word only as `add Rd, sp, #imm` followed by `ldrb`/`ldrh Rd, [Rd, #imm5]`, where the `add`
"addresses entry SP or above" (kit `README.md:751-769`). With a 0x24-byte frame the load's own immediate reaches the
incoming words, so agbcc writes the base as `mov Rd, sp`, the zero-offset case of that pair; the base is then below
entry SP although the word read is an incoming argument. The owner and runtime selectors stop earlier, on the
`_call_via_r2` thunk.

## Source notes

- `g_callbacks_0836D4B8` is declared without `const` (the ROM loads the table word before each call, at 0x080A10F6
  and again before 0x080A119A). Declared `const`, as several matched sources do, the function is 268 bytes.
- Ten parameters, named `arg3` to `arg9` where their meaning is not known; their types follow the ROM: `u16 arg3`
  and `u8 arg4` are narrowed on entry (0x080A10EA-0x080A10F0), `(s8)arg4 << 5` is the `lsls #24; asrs #19` at
  0x080A111E-0x080A1120, and arguments 5 to 7 are stored as halfwords.
- The coordinates are read into six `s32` locals before the second clear, in the ROM's load order, and stored after
  it.

## Ruled out

- `const` on the callback table: 268 bytes (above).

kit issue: shubshub/fftadecomp-kit#75 (the `mov Rd, sp` form of the narrow incoming read)
