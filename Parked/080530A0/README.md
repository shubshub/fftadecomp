# 0x080530A0 - list entry toggle and redraw: bytes identical, refused by kit #350's callee-saved check (336 bytes)

Parked 2026-11-25, kit d1e27356f (kit #350 with its bx r3 thunk, on kit main c6d104b52), decomp main 9157cc3ea73.
`void func_080530A0(u8 *command)` toggles the selected list entry's active flag, plays sound 0x68 or 0x64, redraws
the entry (`func_08053E4C`), recounts the active entries (`func_08053568(&count, &total)`) and redraws the two counts
(`func_08053C74`). It was in `src/` with a MATCH report; kit #350 now refuses its proof.

## Byte identity

`080530A0.c` is the merged `src/080530A0.c` unchanged (SHA-256
`13776c5913d1179b09dcd15d2b88f1b136d6b858c8e98661637158319ccdd66b`). Its report at kit c6d104b52 said
`MATCH - byte identical - 336/336 bytes` under `--owner-runtime-profile named-data-buffer-v1`. Kit #350 adds a proof
check and changes nothing in how a source is compiled or linked, so the bytes are the same; the refusal is in the
proof.

## Refusal

`match.py --root . --no-write --owner-runtime-profile named-data-buffer-v1 0x080530A0` at kit d1e27356f:

```
error (WatchRefusal): callee 0x08013528: an access at 0x0801352E goes through a frame address of unknown provenance (not a stack array base plus an index)
```

The checked call is `bl func_08053C74` at 0x08053196, made while R5 holds `&total`. The walk goes through
`func_0802979C` (the number drawer, call at 0x08053D1A) and `func_08015110` (call at 0x08029828) to
`func_08013528` (call at 0x08015136). It refuses at `func_08013528`'s first store, `str r1, [r5]` at 0x0801352E.
There, R5 is the first argument, and the walk has it as either a plain value or a frame address of unknown
provenance.

That argument is the context pointer `func_080530A0` passes (`data_0200F428` + 0x1A60), and `func_0802979C` keeps
it in its frame:

* it spills its first argument at 0x080297A8 (`str r0, [sp, #0x20]`) and reloads it at 0x08029824
  (`ldr r0, [sp, #0x20]`) as `func_08015110`'s first argument;
* between those two, its digit loop stores bytes through `sp + 4 + 2 * (9 - r6)` (0x080297DA) and the next byte up
  (0x080297EE).

The walk does not bound that index. It therefore takes the two stores to reach any live word of the 40-byte frame,
the spill at sp+0x20 included, and the reloaded pointer loses its provenance.

## What would readmit it

A range proof for the digit index in `func_0802979C` would readmit it. The loop runs `r6` from 0 and goes round
again while `r6 <= 9`, or while `r6 < r7` (the width argument). At this call the width is 2
(`func_08053C74` passes it in R3), so `r6` stays in 0..9 and both stores stay in the digit buffer, sp+4 to sp+0x17.
The spill at sp+0x20 is then untouched, and `func_08013528` gets the owner's plain RAM pointer. The C goes back to
`src/` unchanged.
