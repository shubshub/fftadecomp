# 0x080447B4 - menu panel phase task: bytes identical, refused by kit #350's callee-saved check (1500 bytes)

Parked 2026-11-25, kit d1e27356f (kit #350 with its bx r3 thunk, on kit main c6d104b52), decomp main 9157cc3ea73.
`void func_080447B4(void *task, u8 *phase)` runs a menu panel task: a five-entry phase switch (jump table at
0x080447D8) over the panel's entries, with a 16-pointer item list on the stack. It was in `src/`
with a MATCH report; kit #350 now refuses its proof.

## Byte identity

`080447B4.c` is the merged `src/080447B4.c` unchanged (SHA-256
`39ae59c34f61ef4c9670d10a167db0ce9586d66a96a80486693b8e9a14a0c43c`). Its report at kit c6d104b52 said
`MATCH - byte identical - 1500/1500 bytes` (default path, owner-switch data-buffer proof). Kit #350 adds a proof
check and changes nothing in how a source is compiled or linked, so the bytes are the same; the refusal is in the
proof.

## Refusal

`match.py --root . --no-write 0x080447B4` at kit d1e27356f:

```
inconsistent stack aliases at control-flow join; owner-switch data-buffer proof: buffer callee 0x080D17C4: callee 0x0809A77C: an indirect call at 0x0809A78A receives in R0 the address of a frame word that may hold an owner stack address
```

The first clause is the plain data-buffer proof's refusal; the owner-switch proof, the one the report recorded, is
tried next. It walks the buffer callee `func_080D17C4`. Kit #350 checks its call at 0x080D182E to
`func_0800A5D4`, made while R7 holds the owner's stack address. The walk goes through `func_0800A06C` (call at
0x0800A5E2) and `func_08009E9C` (call at 0x0800A096) to `func_0809A77C` (call at 0x08009FA4):

```
0809A77E  sub sp, #0xc
0809A782  ldr r0, [pc, #0x28]     ; 0x0836D4B8, g_callbacks_0836D4B8
0809A784  ldr r2, [r0]            ; its first word, 0x03005E79
0809A786  mov r0, sp
0809A788  movs r1, #4
0809A78A  bl 0x0814224C           ; _call_via_r2
```

The target, 0x03005E79, is Thumb code in IWRAM, not in the ROM, so the walk treats the call as code it does not
walk. It receives in R0 the address of `func_0809A77C`'s own frame word at SP. The walk keeps the
words earlier walked callees left below SP, and by that record this word may still hold the owner's stack address.
Unwalked code given its address could read the address and use it, so the check refuses.

## What would readmit it

A proof of what the IWRAM routine at 0x03005E78 does with the four bytes at R0 would readmit it. The routine is
reached through the ROM word at 0x0836D4B8; after the call, `func_0809A77C` reads only `ldrb r0, [sp]`. Two kinds of
proof would do:

* walk the routine's ROM image (the code the game copies to 0x03005E78), or
* a reviewed per-site premise that the routine writes those four bytes and reads nothing through R0 before writing.

Either way, the routine does not observe the stale word. The C goes back to `src/` unchanged.
