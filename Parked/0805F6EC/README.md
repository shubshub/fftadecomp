# 0x0805F6EC - event 0x103 request: bytes identical, refused (local descriptor passed to func_08005C04) (28 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function sends event 0x103 to the task at
`owner->task` (+0xC): a 28-byte request on the stack whose first halfword is 0x103 (`mov r2, sp; ldr r1, =0x103;
strh r1, [r2]` at 0x0805F6F0-0x0805F6F4) is passed with the task to `func_08005C04` (`mov r1, sp` at 0x0805F6F8, `bl`
at 0x0805F6FA). That is the whole function. The index row `0805F6EC 0805F708 28 11 return` is right. No data symbol
is used.

```c
void func_0805F6EC(Owner05F6EC *owner)
{
    Request05F6EC request;

    request.event = 0x103;
    func_08005C04(owner->task, &request);
}
```

## Byte identity

`0805F6EC.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0805F6EC with `func_08005C04` bound to its ROM address
(1 `R_ARM_THM_CALL`). The 28-byte symbol equals the ROM span `[0x0805F6EC, 0x0805F708)`: SHA-256
`51a5c4829b5192ff8b25556046df7d2058e914747b36eb6dcbc2767339ed3e7c` for both. `.text` is exactly 28 bytes.
`match.py` refuses before its own byte comparison (below). `plausible.py --strict` exits 0.

This revision takes the request type from the matched `src/0805F670.c` (`Request05F670`: the event halfword and a
`void *object` at +4) and types the owner's task pointer. The earlier copy in this directory (`void *task`, the
request's bytes after the event left unknown) gives the same bytes.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/0805F6EC.c`: the default run and all
213 selector values. None matched.

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

`func_08005C04` (matched, `src/08005C04.c`; 16 bytes) is `return task->callback(task, descriptor, (u8 *)task +
0x18);`: it loads the callback from the task's first word and calls it through `_call_via_r3` (0x08142250), passing
R1 through unchanged and overwriting R2 and R3 before the call. R1 holds the address of the local request, so the
buffer walk follows it into `func_08005C04`, then into the thunk, and stops at its `bx r3`. The static-callback
selectors need R3 to hold a fixed Thumb function address; here it is read from the task object at run time. The
scheduler-descriptor contracts summarise the same 28-byte descriptor for their pinned entries (`func_08005B6C`,
`func_08005954` and the wrappers named in their README sections), and `func_08005C04` is not one of them. R2 also
still holds the request's address at the call (the `mov r2, sp` for the halfword store); `func_08005C04` overwrites it
before use. Task callbacks may write the descriptor as well as read it (the parked `0x08005EF8` writes 2 into its
event halfword).

The same request is sent by `0x0805F69C` (event 0x102), `0x080651C8` and `0x08066C28`, and four times by
`0x0802B70C`.

## Source notes

- Only the event halfword of the 28 bytes is written; the request type is the one the matched `src/0805F670.c`
  declares for the same scheduler family, and the bytes do not pin its other members.
- `func_08005C04` is declared `u32 (void *task, void *descriptor)`, as in its matched source; the result is unused.

## Ruled out

Nothing beyond the source above was needed: it was byte-identical as first written. The request-type change in
this revision does not change the bytes.

kit issue: shubshub/fftadecomp-kit#226
