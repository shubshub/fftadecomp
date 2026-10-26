# 08020274

Target: complete `[0x08020274, 0x0802046A)`, 502 bytes / 231 reachable instructions.

The retained natural candidate compiles with the fixed agbcc `-mthumb-interwork -O2` flags to a complete 502-byte ELF function. Native matcher exit 1: source plausible, 500/502 bytes and 230/231 instructions identical. The final full comparison is preserved privately as `native-report.md`.

Only the ordering at `0x08020400` and `0x08020402` differs: the target initializes the boundary pointer with `movs r5, #0` before `ands r0, r1`; the candidate executes the mask before that zero initialization. Both instructions and their values are present. The target cursor reload at `0x080203FA` is also preserved; this is not a missing redundant-load case.

Tested natural forms: the initial whole-loop boundary initialization produced a 502-byte body with a larger stack frame; moving that initialization into the lookup phase and ordering the packed index reads produced 498 bytes. Inlining the layer-data application with its natural `u16` index and using a byte completion predicate recovered the target frame, loop, and call layout. Boundary initialization before or after the complete address expression and an explicit masked-offset local left only its instruction ordering different. A `u16` table-index formulation compiled to 498 bytes. The retained explicit masked-offset form is the tested 500/502-byte candidate, restored without another matcher invocation. No flags, assembly, volatile accesses, or compiler-steering operations were introduced.
