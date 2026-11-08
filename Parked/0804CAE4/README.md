# 0804CAE4

Complete indexed target [0x0804CAE4, 0x0804CBB2), 206 bytes.

The function dispatches on a 5-entry jump table (cases ordered 0, 1, 3, 2, 4).
One case clears `data_0201F544` through `g_callbacks_0836D4B8[0](data_0201F544,
0x2C)`, an indirect call via `_call_via_r2` at 0x0814224C. A u16 queue index
is maintained.

## Code: identical

`0804CAE4.c` compiles instruction for instruction to the target, including
the jump table, the thunk call and all pool words. Both data names already
exist. The 206-byte size leaves a trailing two-byte alignment pad.

## Why it is not in src/

* Default and `--switch-data-profile u16-scalars-v1`: "switch evidence
  excludes object, callback and runtime-thunk bindings".
* `canonical-thunks-v1`: "switch requires one exact adjacent unsigned guard
  and five-op dispatch". The guard `cmp r0,#4; bhi` follows a `push` / `adds`
  / `ldrb` sequence, which probably fails the adjacency test.
* `canonical-thunks-zero-word-pool-v1`: "canonical pool requires adjacent
  unsigned low guard and default branch".
* `restoring-owner-r3-thunk-switch-v1`, `ordinary-multiple-switch-source-v1`
  and `restoring-owner-switch-entry-two-words-data-v1`: "owner requires sole
  complete Thumb ELF function", probably because of the external alignment
  pad.
* `numeric-data-switch-source-v1`: "numeric switch requires ordinary calls,
  zero-addend data and local table words". It rejects the thunk call.

Verifying this needs a profile that admits a jump-table switch, named data and
a `_call_via_rN` thunk in a framed function with a tail pad. No tooling was
changed.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/74
