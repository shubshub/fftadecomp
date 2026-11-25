# 0x080BFDB0 - battle position search evaluator: bytes identical, refused by kit #350's callee-saved check (1054 bytes)

Parked 2026-11-25, kit d1e27356f (kit #350 with its bx r3 thunk, on kit main c6d104b52), decomp main 9157cc3ea73.
`u32 func_080BFDB0(PositionSearch *search, void *work)` is one of the position search evaluators that
`func_080C01D0` returns (`include/battle_position_search.h`, which keeps its declaration for that caller). It was in
`src/` with a MATCH report; kit #350 now refuses its proof.

## Byte identity

`080BFDB0.c` is the merged `src/080BFDB0.c` unchanged (SHA-256
`a0d1e685f4b0d0c2b42e3dbf6cd71010b3d3aeda8742065b0adf5792834ba7c3`). Its report at kit c6d104b52 said
`MATCH - byte identical - 1054/1054 bytes` under `--owner-runtime-profile named-data-buffer-v1`. Kit #350 adds a proof
check and changes nothing in how a source is compiled or linked, so the bytes are the same; the refusal is in the
proof.

## Refusal

`match.py --root . --no-write --owner-runtime-profile named-data-buffer-v1 0x080BFDB0` at kit d1e27356f:

```
error (WatchRefusal): callee 0x0812FE38: a store at 0x0812FFCE writes the owner's frame above the checked callee's entry SP
```

The checked call is `bl func_080BE494` at 0x080BFFDC, made while R6 and R10 hold owner stack addresses. The walk goes
through `func_080BDECC` (call at 0x080BE566) and `func_08130200` (call at 0x080BDF54) to `func_0812FE38` (call at
0x08130238). There it reaches:

```
0812FF84  bl 0x0812F8A4
0812FF88  lsls r0, r0, #0x10
0812FF8A  lsrs r7, r0, #0x10      ; r7 = (u16) func_0812F8A4(...)
...                               ; 0x0812FF92-0x0812FFAC fill sp+0xc+i, i = 0..8
0812FFC0  mov r4, sp
0812FFC2  adds r4, r4, r7
0812FFC4  adds r4, #0xc
...
0812FFCA  bl 0x0812FC74
0812FFCE  strb r0, [r4]           ; sp + 0xc + r7
```

`func_0812FE38` has a nine-byte array at sp+0xc, which the loop before it fills for indices 0 to 8, and the store
writes element `r7`. The walk bounds `r7` only to 0..255, not to the array: it has R4 as sp+0xc plus 0 to 255,
which is 200 bytes below to 55 bytes above the checked call's SP. That range passes `func_0812FE38`'s entry SP
(144 bytes below the checked call's SP) and reaches the owner's frame, so the check refuses.

## What would readmit it

A bound on `r7` at 0x0812FFCE would readmit it: `func_0812F8A4`'s return below 9, carried into the walk as a proved
range, or a reviewed index premise for that site of the kind `config/stack_index_premises.json` records for owners.
With that bound, the store stays inside `func_0812FE38`'s nine-byte array. The C goes back to `src/` unchanged.
