# 0x0802B70C - open or re-signal one of two tasks: bytes identical, refused (local descriptor to func_08005C04 and two func_08005954 sites) (372 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `func_0802B70C(object, flags)` fills a 28-byte request on
the stack (`object` at +4, the `u16` flags at +0x14: `str r0, [sp, #8]` and `strh r5, [r0, #0x14]` with
`r0 = sp + 4`, 0x0802B716-0x0802B71A) and calls `func_08022B24`. With bit 0 of `flags` set it works on
`data_0200F440->second_task` (+0xC), otherwise on `->first_task` (+8):

- if the task exists, it reads its state with `func_08005BAC` and sends it the request through `func_08005C04`, with
  event 0x10A and then `func_08005BA8(task, 0x10B)` when bit 5 of `flags` is set and the state is 0x102 (or 0x10C on
  the first-task path), otherwise event 0 (second task) or 0x104 (first task) and then `func_08005BA8(task, 0x10D)`;
- if not, it creates the task with `func_08005954(data_0200F440->manager, callback, 0x628, &request, 0)`, with
  `func_0802D550` (0x0802B7C8) or `func_0802D0B0` (0x0802B860) as the callback.

On the second-task path it first consumes a pending transfer (`data_0200F440 + 0x391`): two `func_0802BA08` calls,
the first result passed to `func_0802B5A8`, and the flag cleared. It returns the task. `data_0200F440` is already in
`config/data_symbols.json`. The index row `0802B70C 0802B880 372 186 return` has the right extent, but 186 is half
the byte count: the reachable instruction count is 142 (the kit's own refinement agrees), which matters for the
restoring-owner selectors below.

## Byte identity

`0802B70C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0802B70C, with every callee, the two callback words
(`func_0802D550`, `func_0802D0B0` as Thumb addresses) and `data_0200F440` bound to their ROM addresses (16
`R_ARM_THM_CALL`, 8 `R_ARM_ABS32`). The 372-byte symbol equals the ROM span `[0x0802B70C, 0x0802B880)`: SHA-256
`40d635a5d4cba10e3441ac22eb6836d0a3bf0ac40350a4e969cb8741644d58c3` for both. `.text` is exactly 372 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0802B70C.c`, index as on main: the
default run and all 213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default, both `--*-quotient-profile` values | `stack aliases cannot cross calls in caller-clobbered registers` |
| `named-data-buffer-v1`, `named-data-buffer-stack-index-v2`, `bounded-buffer-root-return-scratch-v1` and 15 other buffer selectors (18) | `buffer callee 0x08005C04: buffer callee 0x08142250: non-leaf indirect control flow requires linked CFG verification` |
| `static-callback-buffer-v1`, `descriptor-output-alias-v1` and 11 other static-callback / descriptor selectors (13) | `buffer callee 0x08005C04: static callback target register is not an exact Thumb function pointer` |
| `static-callback-restoring-r6-v1`, `static-callback-restoring-r6-target-v1` | `preserved R6 is not a typed Thumb callback identity` |
| `named-data-buffer-known-query-callee-v1` | `buffer callee 0x08005C04: buffer callee 0x08142250: structural inventory is not closed` |
| `conditional-scheduler-descriptor-calls-v1` and its three payload variants | `scheduler contract requires one actual scheduler call` |
| `conditional-scheduler-entry-descriptor-calls-v1` | `scheduler entry contract requires one actual pinned entry call` |
| `conditional-scheduler-entry-branch-descriptor-calls-v1` | `scheduler entry branches require exactly two pinned wrapper call sites` |
| `conditional-local-output-word-call-v1` | `output-word contract requires one actual indexed output-word call` |
| `restoring-owner-acyclic-v1`, `restoring-owner-scalar-switch-v1`, `restoring-owner-switch-entry-word-v1`, `restoring-owner-switch-entry-two-words-data-v1`, `restoring-owner-ignored-leaf-alias-v1`, `local-rom-halfword-table-v1` | `complete-owner text reachable instruction count differs` (the index row's 186; see above) |
| `--control-flow-profile mixed-return-inert-spin-v1` | `inert spins exclude function-address relocations` |
| `bounded-buffer-conditional-thunks-v1` and its three scratch variants | `conditional buffer thunks require canonical compiler call names without division` |
| `--function-address-profile canonical-thunks-v1` | `function thunks require canonical calls` |

The other 158 selector values stop on requirements this function does not meet: an arithmetic or float runtime, a
switch, a BIOS wrapper call, an external alignment pad, the -O0 toolchain, or (26 addressed-runtime selectors)
`addressed data requires a mapped object and signed32 addend`.

## Cause

The same local request is passed four times in R1 to `func_08005C04` (0x0802B77C, 0x0802B7A4, 0x0802B814,
0x0802B83A) and twice in R3 to `func_08005954` (0x0802B7C8, 0x0802B860), on exclusive paths. `func_08005C04`
(matched, `src/08005C04.c`) calls the task's own callback through `_call_via_r3` with R1 unchanged, so every buffer
walk stops at that thunk, as for `0x0805F69C`. The scheduler-entry contract that summarises `func_08005954` admits
exactly one actual entry call, and the branch variant two sites of a pinned wrapper, not two direct entry calls.
R0 also still holds `sp + 4` at the first call (`bl func_08022B24` at 0x0802B71C, after the flags store). The
default run does not say which call it stops at.

So this function needs the `func_08005C04` contract asked for with `0x0805F69C`, `0x0805F6EC`, `0x080651C8` and
`0x08066C28`, and in addition a scheduler-entry contract that allows two direct `func_08005954` sites on exclusive
paths.

## Source notes

- `func_08005C04` is declared `void`; the matched `src/08005C04.c` returns `u32`. The result is never used.
- The request type names `object` (+4, as the matched `src/0805F670.c` does) and `flags` (+0x14); the rest is
  unknown bytes.
- `func_0802BA08` is called twice and only the first result is used (0x0802B736, 0x0802B73C); both calls are in the
  ROM.
- The second task is re-signalled with event 0 when the bit-5 test fails; the first task with 0x104. Both constants
  are in the ROM (the stores before 0x0802B7A4 and 0x0802B83A).

## Ruled out

Nothing beyond the source above was needed: it was byte-identical as first written, and no alternative spellings
were compared.

kit issue: (to be filed - local event descriptor passed to func_08005C04, which calls the task's own callback through _call_via_r3); this function also needs two direct func_08005954 sites in one scheduler-entry contract
