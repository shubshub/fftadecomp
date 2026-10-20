# 080CA22C: record-dependent initialization

## Grounded target and interface

The complete target is `[080CA22C,080CA268)`: 60 bytes and 29 reachable
Thumb instructions, with no literals or alignment. `080CA268` starts a
separate function.

The compatible interface is `void(void *object)`. The target consumes only
the incoming object pointer and calls the existing
`u32 func_080C92F0(void *, u32)` with selector `0x21`. If the full returned
word is nonzero, it writes byte `0xE4` at `object + 0x40 + result`.
There is no result narrowing.

After that optional store, it reads byte `object + 7`. A nonzero byte equal
to `0x44` or `0x45` causes bit `0x0800` to be set in the halfword at
`object + 0x28`. The ROM explicitly retains the initial zero test, followed
by an unsigned byte-range comparison. The recovered source preserves this
ordering and the post-call load.

There is no null guard. The object must provide the helper's required
readable fields, the readable category byte and aligned flags halfword,
and the selected writable byte when the lookup result is nonzero.
No allocation length is inferred. The helper's possible record-redirect
cycles are not assumed to terminate.

The initializer callsite at `080C9AB4` supplies its object in `r0` and
discards the result immediately. The target itself restores its saved
return address into `r0`, corroborating the void interface.

## Remaining mismatch

The retained ordinary typed-header and byte-region representation compiles
to a complete 62-byte symbol with 30 instructions, rather than the target's
60 bytes and 29 instructions. Source plausibility and the mapped direct-call
CFG checks pass, but the bytes do not match.

The compiler saves both `r4` and `r5` and inserts `adds r5, r4, #0` after
copying the object to `r4`. It uses `r4` for the indexed byte store and `r5`
for the later category and flags accesses. The target saves only `r4` and
uses that register for both portions. This adds one instruction and changes
the saved-register masks, later base registers, and branch/call positions.

The 62-byte comparison printed by the matcher includes the next function's
first halfword on its ROM side. That halfword is not part of this target,
and no prefix or enlarged-span match is claimed.

## Natural forms checked

- A typed view of category byte `+7` and flags halfword `+0x28`, plus a byte
  pointer to the indexed region at `+0x40`, produces the retained 62 bytes.
  Using the same typed pointer consistently for the call and region access
  does not remove the second saved base.
- A raw byte-buffer view with a halfword pointer at `+0x28` also produces
  62 bytes, with additional flag-operation register differences.
- A grounded header ending in a variable-length byte tail at `+0x40`
  also produces 62 bytes with the same second-base copy. This agbcc rejects
  C99 `values[]`; its GNU zero-length trailing-array form compiles, but does
  not improve the mismatch and is not retained.

All compilations used the reviewed `d7f9a0a` matcher and standard agbcc
`-mthumb-interwork -O2` configuration. The retained source received a final
fresh `--no-write` check before parking: exit 1, plausible, not matching.
This is a code-generation mismatch, not a verifier limitation. No failed
production source or report remains.
