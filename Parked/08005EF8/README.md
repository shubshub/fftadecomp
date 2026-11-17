# 0x08005EF8 - transfer task callback: bytes identical, refused (its struct assignment compiles to memcpy, which the default path does not bind) (204 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. `u32 func_08005EF8(void *task, TransferEvent *event,
TransferPayload *payload)` is the callback of the transfer task that the matched `src/08006878.c` creates through
`func_08005B6C`. Event 0 copies the event's `count` packed 12-byte entries into the payload (a struct assignment in a
`u16` loop) and allocates a 0x800-byte buffer with `func_08005B28`. Event 1 frees the buffer (`func_08005B40`). Event
0x100 runs one step of the current entry, `func_08005C54(payload, entry)` for kind 0 or
`func_08005E7C(payload, &entry->descriptor)` for kind 0xF; when the step completes it advances `current` and clears
`payload->progress` through `g_callbacks_0836D4B8[0]` (`_call_via_r2`); past the last entry it sets the event's
state to 2. The index row `08005EF8 08005FC4 204 93 return` is right. `g_callbacks_0836D4B8` is already in
`config/data_symbols.json`.

```
08005F24  lsls r1, r4, #1
08005F26  adds r1, r1, r4
08005F28  lsls r1, r1, #2        @ index * 12
08005F2A  adds r0, r5, r1        @ payload + index * 12
08005F2C  adds r1, r1, r6        @ entries + index * 12
08005F2E  adds r0, #0x34         @ &payload->entries[index]
08005F30  movs r2, #12
08005F32  bl   0x081443FC        @ memcpy
```

## Byte identity

`08005EF8.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x08005EF8, with each callee at its ROM address, the
compiler's `memcpy` at 0x081443FC (the 98-byte copy helper `func_081443FC`), `_call_via_r2` at 0x0814224C and
`g_callbacks_0836D4B8` at its mapped address (6 `R_ARM_THM_CALL`, 1 `R_ARM_ABS32`). The 204-byte symbol equals the
ROM span `[0x08005EF8, 0x08005FC4)`: SHA-256 `70fc1af6b37822811745b4ebaf478769b3eccd55f9b990d6b7ba530d388fd678` for
both. `.text` is exactly 204 bytes. `match.py` refuses before its own byte comparison (below). `plausible.py
--strict` exits 0.

This revision takes its record and progress types from the matched sibling `src/08005C54.c` (`TransferRecord`,
`TransferProgress`) and clears the progress with `sizeof(payload->progress)`. The earlier copy in this directory,
with its own `RequestNode`, a `u16 progress` and a literal 12, gives the same bytes and the same SHA-256.

## Refusals

Kit 18dcc516, `match.py --root . --no-write` with this source copied to `src/08005EF8.c`: the default run and all
213 selector values. None matched.

| Selector | Refusal |
|---|---|
| default; every `--function-address-profile`, `--switch-data-profile`, `--signed-runtime-profile` and `--unsigned-runtime-profile` value; both `--*-quotient-profile` values (22) | `call target must be an undefined addressed function` |
| `named-data-buffer-v1`, `bounded-buffer-conditional-thunks-v1`, `static-callback-buffer-v1`, `restoring-owner-acyclic-v1` and 104 other owner selectors; all 42 addressed-runtime selectors; `--control-flow-profile mixed-return-inert-spin-v1`; `--software-double-profile convert-sub-div-target-v1` (152) | `function address requires a canonical addressed function` |
| `named-data-buffer-rom-table-copy-v1`, `named-data-buffer-stack-index-v1`, `-v2` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `named-data-buffer-finite-small-copy-binding-v1` | `cyclic small-copy prefix requires a separate proof` |
| `named-data-buffer-compiler-copy80-binding-v1` | `cyclic copy prefix requires a separate proof` |

The other 35 selector values stop at checks unrelated to the copy (the aligned-tail owners, the private float and
double profiles, the three `--switch-profile` values, which reject the `.word g_callbacks_0836D4B8` pool entry).

## Cause

The default path binds a call relocation by a `func_XXXXXXXX` name, as a `_call_via_rN` thunk, or as an
arithmetic runtime when its profile is selected; the compiler's `memcpy` is none of these, so the call is refused.
Everything else in the function (the loop, the `_call_via_r2` call on the payload, the named data word) is admitted
on that path. The compiler-copy profiles do bind `memcpy` to the pinned helper, but each needs a local destination,
or a loop-free prefix with one copy and a fixed destination and count, and here the copy is inside a loop, into a
pointer parameter, with neither argument a local address. The function has no stack frame at all
(`push {r4, r5, r6, lr}` only).

## Source notes

- The copy has to be the struct assignment `payload->entries[index] = entries[index];`. The ROM forms the
  destination in two steps around the source (`adds r0, r5, r1; adds r1, r1, r6; adds r0, #0x34`), which is gcc's
  expansion of a structure assignment.
- `TransferDescriptor` and `TransferEntry` are `__attribute__((packed))` 10- and 12-byte records: unpacked, the
  copy becomes `ldmia`/`stmia` and the function is 200 bytes.
- The callback table is declared `const` (`BufferInitializer const g_callbacks_0836D4B8[]`).

## Ruled out

Carried from the earlier attempt (same function body):

- An explicit `func_081443FC(...)` call instead of the struct assignment: an explicit call computes each argument
  in full, and the front end rewrites `&a[i]` as `a + i`. The spellings tried differ by 76 halfwords; with the
  source argument computed first, 8; the closest, a byte-offset spelling, by 2 instructions.
- Unpacked entry types: 200 bytes (above).

kit issue: (to be filed - match.py: the default path cannot bind the compiler's memcpy call (a struct assignment) when no local address reaches it)
