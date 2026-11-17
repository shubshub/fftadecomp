# 0x08066C28 - menu confirm: payload store and event 0x102: bytes identical, refused (local descriptor passed to func_08005C04) (112 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. In mode 4 (`ldrb [r0, #8]; cmp #4` at 0x08066C2E) the
function takes the payload of `menu->handle` from `func_08005BFC` and, if bit 0 of its byte at +9 is set, passes it
to `func_080670B4`. Otherwise it looks up `menu->table->entries[func_08017B68(menu->list, menu->row)]` (table base
+0x424, 0x08066C62-0x08066C6C), stores the entry at +0x108C of the handle's payload (0x08066C70-0x08066C78), and
sends event 0x102 to the same task: a 28-byte request on the stack with first halfword 0x102 (0x08066C7A-0x08066C80)
is passed with `menu->handle` to `func_08005C04` (0x08066C84). The second arm has the shape of `0x0805F69C`. The
index row `08066C28 08066C98 112 47 return` is right (47 reachable instructions, then two pool words). No data symbol
is used.

## Byte identity

`08066C28.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08066C28, with `func_08005BFC`, `func_080670B4`,
`func_08017B68` and `func_08005C04` bound to their ROM addresses (5 `R_ARM_THM_CALL`). The 112-byte symbol equals
the ROM span `[0x08066C28, 0x08066C98)`: SHA-256
`90a7154e51f697b5c0b96c7fffd4fbdff17a359caadba97c929d02d74521e563` for both. `.text` is exactly 112 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08066C28.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-v1`, `named-data-buffer-stack-index-v2`, `bounded-buffer-root-return-scratch-v1` and 15 other buffer selectors, both `--*-quotient-profile` values (21) | `buffer callee 0x08005C04: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `static-callback-buffer-v1`, `static-callback-unwritten-r7-v1`, `descriptor-output-alias-v1` and 10 other static-callback / descriptor selectors (13) | `buffer callee 0x08005C04: static callback target register is not an exact Thumb function pointer` |
| `static-callback-restoring-r6-v1`, `static-callback-restoring-r6-target-v1` | `buffer callee 0x080670B4: static callback target register is not an exact Thumb function pointer` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08005C04: buffer callee 0x08142250: structural inventory is not closed` |
| `conditional-scheduler-descriptor-calls-v1` and its three payload variants | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-local-output-word-call-v1` | `output-word contract requires one actual indexed output-word call` |
| `restoring-owner-acyclic-v1`, `--control-flow-profile mixed-return-inert-spin-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-conditional-thunks-v1` and its three scratch variants | `conditional buffer thunks require canonical compiler call names without division` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |

The other 163 selector values stop on requirements this function does not meet: an arithmetic or float runtime, a
switch, a BIOS wrapper call, a scheduler call, an external alignment pad, or the -O0 toolchain.

## Cause

As in `0x0805F69C`: `func_08005C04` (matched, `src/08005C04.c`) calls the task's own callback, loaded from the
task's first word, through `_call_via_r3` (0x08142250) with R1 unchanged. R1 holds the address of the local request
at 0x08066C84, so the buffer walk follows it into `func_08005C04` and the thunk and stops at `bx r3`; the
static-callback selectors need a fixed Thumb target in R3; and the scheduler-descriptor contracts do not pin
`func_08005C04`. Two static-callback selectors stop earlier, on the mode-4 arm, inside `func_080670B4`.

## Source notes

- `func_08005C04` is declared `void` here; the matched `src/08005C04.c` returns `u32`. The result is not used, so the
  bytes do not decide it.
- The payload type returned by `func_08005BFC` differs per arm: `Task08066C28` (a flag byte at +9) in mode 4 and
  `Target08066C28` (a word at +0x108C) otherwise. Both are views of the same payload; its layout is not recovered.
- `Command08066C28` names only the event halfword, the one member written; the rest of the 28 bytes is not pinned
  here.
- `func_08017B68` is declared returning `u16` with an `s8` row, as the ROM's sign extension of the row byte
  (0x08066C5A-0x08066C5C) and zero extension of the result (0x08066C62-0x08066C64) show.

## Ruled out

Nothing beyond the source above was needed: it was byte-identical as first written, and no alternative spellings
were compared.

kit issue: shubshub/fftadecomp-kit#226
