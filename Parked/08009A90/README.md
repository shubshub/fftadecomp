# 08009A90: conditional record-based adjustment

**Disposition: Parked.** This is the unchanged first natural C recovery. With
`agbcc -mthumb-interwork -O2`, its complete linked function is 96 bytes and 42
instructions; the ROM owns 108 bytes and 45 instructions. Of the 96 shared
positions, 15 bytes agree and 81 differ, with another 12 target bytes absent.
It must not enter `src/` or receive matched-byte credit.

The source SHA256 is
`af6efc06ef40fde65706d477edfa3822e3765b43b87585fb78507b81112d7ce8`.
No source iteration, alternate optimization level, assembly, pragma, volatile
access, artificial padding, helper alias or report substitution was attempted.

## Recovered behavior

The argument and result are unsigned 16-bit values. If the argument's low byte
is greater than 239, the function returns its difference from 240 narrowed to
one byte. Otherwise it obtains a record through `func_08009A14`, using the
halfword at `0x02002192`. If record byte 2 is not 61, it returns the original
argument. For byte 2 equal to 61, it reads `0x02003C2A`, decrements a nonzero
value, takes unsigned remainder modulo 10, and returns the original argument
plus 24 times that remainder, narrowed to 16 bits. These field names describe
offsets; subsystem names and the table's original C declaration remain unknown.

## Complete ownership and compiler difference

The existing endpoint `0x08009AFC` is retained. The full interval
`[0x08009A90,0x08009AFC)` contains 94 instruction bytes, two alignment bytes at
`0x08009AE6`, and three internal literal words at `0x08009AE8`, `0x08009AEC`
and `0x08009AF0`. The return-value instruction at `0x08009AF4` and interworking
epilogue at `0x08009AF6` are part of this body. Both conditional and
unconditional paths around the pool are traversed. The proposed metadata
change is only the instruction count, 54 to 45, in both indexes.

The diagnostic candidate owns 88 instruction bytes and eight literal bytes,
including an internal literal at `0x08009ABC`. Its frame is 12 bytes instead
of the ROM's 16 bytes. Differences include the saved register set, low-byte
narrowing, folded state addresses, literal placement and branch layout. The
comparison includes the entire function symbol and every relocated byte;
the size mismatch is not a shortened instruction-only comparison.

## Official verification and diagnostic binding

The published verifier rejects the canonical `__umodsi3` call with
`call target must be an undefined addressed function`. Both ordinary and
`--no-write` invocations exit 1 and create no match report. That unsupported
profile is separate from the demonstrated compiler mismatch.

For diagnosis only, the original object's two `R_ARM_THM_CALL` relocations
at offsets 30 and 66 are linked to typed Thumb function symbols for
`func_08009A14` at `0x08009A14` and `__umodsi3` at `0x08142B28`.
The linked ELF has no remaining relocation, veneer or unexpected allocated
section, and nonrelocated bytes are unchanged. The complete 192-byte ROM
remainder helper equals locally assembled canonical `lib1thumb.asm`, including
its call binding to `__div0` at `0x0814274C`. Runtime checks execute the actual
ROM lookup and remainder helpers, not compiled substitutes or call models.

## Bounded validation

The frozen local evidence bundle records 44 paired caller cases, or 88 caller
executions, with all 45 ROM and 42 candidate instructions visited. Cases use
unchanged ROM record bytes and cover early return, record mismatch, zero and
nonzero counters, arithmetic boundaries, 16-bit result wrapping, ARM/Thumb
return state and two stack alignments. Four pairs with noncanonical high
argument bits are machine-only probes, not additional defined-C inputs.

Checks enforce helper arguments, ordered literal/data/stack accesses,
initialized consumption, final RAM and stack contents for each body's own
frame, restored stack pointer and callee-saved registers. The two bodies have
different stack footprints, so byte-for-byte equality of their residual
stack contents is not claimed. An independent numeric oracle checks results.

Another 255 executions of the actual remainder helper cover every dividend
0 through 254 reachable from the byte counter, with divisor 10. Those runs
visit 88 of its 95 instructions; the divide-by-zero and remaining
out-of-domain paths are not runtime-covered. Eighteen executed negative
controls detect changed threshold, divisor, decrement, record field, lookup
stride, remainder subtraction and missing initialization. A separate invalid
fixture-index control is rejected before execution. Twelve target-compiler
layout/narrowing assertions pass, a conflicting helper return declaration
fails compilation, and the unchanged caller compiles alongside the frozen
lookup source after deduplicating its identical record typedef.

These checks assume valid backing and object lifetime for the consumed state
fields and selected table records, the target's integer-to-pointer ABI, and
separation of ROM table, RAM state and stack. They do not establish the table's
array bound, arbitrary-index validity, a unique original source type, concurrent
hardware behavior or universal C equivalence.

## Reproduction and evidence scope

The local frozen author bundle, rather than the two-file `Parked/08009A90/`
publication, contains `check.py`, `runtime.py`, `build.json`,
`runtime-results.json`, `CLASSIFIED.txt`, `DEPENDENCIES.txt`, compiler logs,
`CONTRACT.md`, `HANDOFF.md`, `input-pins.json` and the freeze manifests.
Generated object files, linked executables, raw binary slices and temporary
fixtures are removed by the check. Disassembly and raw evidence stay local.

From that local bundle, with its pinned snapshot and toolchain available:

```sh
env -u FFTA_ROM PYTHONDONTWRITEBYTECODE=1 TMPDIR="$PWD" \
  PATH=/home/user/armtc/root/usr/bin:$PATH python check.py
```

`metadata-proposal.patch` changes only this function's count against the
pinned snapshot. Rebase that single row against the integration candidate;
its neighboring rows may already have independent ownership repairs.
