# 0x0805F69C - event 0x102 request with a payload store: bytes identical, refused (local descriptor passed to func_08005C04) (80 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function looks up an entry pointer,
`data_0200F44C->entries[func_08017B68(&owner->list, owner->row)]` (the `u16` result scaled by 4 at
0x0805F6B8-0x0805F6C0), stores it at offset 0x108C of the owner's task payload (`func_08005BFC(owner->task)`,
0x0805F6C4-0x0805F6CC), and then sends event 0x102 to the same task: a 28-byte request on the stack whose first
halfword is 0x102 (`mov r1, sp; strh` at 0x0805F6CE-0x0805F6D4) is passed with `owner->task` to `func_08005C04`
(0x0805F6D8). The index row `0805F69C 0805F6EC 80 33 return` is right (33 reachable instructions; the last two words
are the pool). `data_0200F44C` is already in `config/data_symbols.json`; no new data symbol is needed.

## Byte identity

`0805F69C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0805F69C, with `func_08017B68`, `func_08005BFC`,
`func_08005C04` and `data_0200F44C` bound to their ROM addresses (3 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 80-byte
symbol equals the ROM span `[0x0805F69C, 0x0805F6EC)`: SHA-256
`97e2029d6f93c8dab2472ade188368c5bbac7327647e6bcc3b450afc1ef96028` for both. `.text` is exactly 80 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0805F69C.c`: the default run and all 213
selector values. None matched.

| Selector | Refusal |
|---|---|
| default, `named-data-buffer-v1`, `named-data-buffer-stack-index-v2`, `bounded-buffer-root-return-scratch-v1`, `bounded-buffer-runtime-summaries-v1` and 15 other buffer selectors, both `--*-quotient-profile` values (21) | `buffer callee 0x08005C04: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `static-callback-buffer-v1`, `static-callback-restoring-r6-target-v1`, `descriptor-output-alias-v1` and 12 other static-callback / descriptor selectors (15) | `buffer callee 0x08005C04: static callback target register is not an exact Thumb function pointer` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08005C04: buffer callee 0x08142250: structural inventory is not closed` |
| `conditional-scheduler-descriptor-calls-v1` and its three payload variants | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-local-output-word-call-v1` | `output-word contract requires one actual indexed output-word call` |
| `restoring-owner-acyclic-v1`, `--control-flow-profile mixed-return-inert-spin-v1` | `stack aliases cannot cross calls in caller-clobbered registers` |
| `bounded-buffer-conditional-thunks-v1` and its three scratch variants | `conditional buffer thunks require canonical compiler call names without division` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |

The other 164 selector values stop on requirements this function does not meet: an arithmetic or float runtime, a
switch, a BIOS wrapper call, a scheduler call, an external alignment pad, or the -O0 toolchain.

## Cause

`func_08005C04` (matched, `src/08005C04.c`) is `return task->callback(task, descriptor, (u8 *)task + 0x18);`: it
loads the callback from the task's first word and calls it through `_call_via_r3` (0x08142250), passing R1 through
unchanged. R1 holds the address of the local request at the call, so the buffer walk follows it into
`func_08005C04`, then into the thunk, and stops at its `bx r3`. The static-callback selectors need R3 to hold a fixed
Thumb function address, and here it is read from the task object at run time. The scheduler-descriptor contracts
summarise only their pinned entries (`func_08005B6C`, `func_08005954` and the wrappers named in their README
sections); `func_08005C04` is not one of them. The same request shape is sent by `0x0805F6EC` (event 0x103),
`0x080651C8` and `0x08066C28`.

## Source notes

- The store into the payload is written `*(void **)(func_08005BFC(owner->task) + 0x108C) = entry;`: the payload's
  layout is not recovered, so the offset is spelled as a byte offset from the `u8 *` that `func_08005BFC` returns.
  The ROM loads 0x108C from the pool word at 0x0805F6E8 (`ldr` at 0x0805F6C8) and adds it after the call.
- `Request0805F69C` names only the event halfword. The function writes nothing else in the 28 bytes, so the rest of
  the layout is not pinned here (the matched `src/0805F670.c` names a `void *object` at +4 in the same request
  type).
- `func_08017B68` is declared returning `u16` and taking an `s8` row: the ROM sign-extends the row byte before the
  call (0x0805F6B0-0x0805F6B2) and zero-extends the result before scaling it (0x0805F6B8-0x0805F6BA).

## Ruled out

Nothing beyond the source above was needed: it was byte-identical as first written, and no alternative spellings
were compared.

kit issue: shubshub/fftadecomp-kit#226
