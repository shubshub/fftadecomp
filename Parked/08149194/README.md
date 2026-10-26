# 08149194 — recovered, not byte matching

Target: `[0x08149194, 0x081491C0)`, 44 bytes / 22 instructions.

The function addresses a seven-byte entry at `row * 16 + column` and sets or clears bit `0x40` in byte 1 according to the fourth argument. The preserved candidate uses a seven-byte array view and a promoted flag result.

Native matcher at fixed agbcc `-mthumb-interwork -O2`: exit 1, plausible C, complete symbol 44 bytes; 16/22 instructions identical (37/44 bytes). The candidate zero-extends the column before shifting/extending the row; the target delays the column's final right shift until after the row. Address arithmetic and branch destinations then agree. The target carries the updated flag in r0 while the candidate carries it in r1, changing the enabled branch's byte load/mask/OR, the clear branch's AND destination, and the final byte store.

Bounded natural forms checked:

- A byte-field struct with compound flag updates compiled to 40 bytes. agbcc rounds the nominal seven-byte struct to eight bytes, so its stride differs; the clear mask also narrows to `0xbf`.
- The preserved seven-byte array view and common promoted flag result compiled to 44 bytes with the residual above. A signed promoted result and explicit row shift produced the same bytes.
- A flat byte pointer with a local entry index and separate per-branch promoted values compiled to 42 bytes.
- The flat pointer with a common promoted result compiled to the same 44-byte candidate as the array view. Commuted index and mask expressions remained 44 bytes but changed the address-arithmetic register choice and matched 12/22 instructions (33/44 bytes).

No exact match was obtained within these natural forms. This records a bounded fixed-flag result, not permanent impossibility. The nonmatching source and generated report were removed. No assembly, volatile access, compiler pragmas, dead code, or compiler-steering constructs were used.
