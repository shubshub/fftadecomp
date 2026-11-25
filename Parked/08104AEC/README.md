# 0x08104AEC - party effect scheduler: bytes identical, refused by kit #350's callee-saved check (1366 bytes)

Parked 2026-11-25, kit d1e27356f (kit #350 with its bx r3 thunk, on kit main c6d104b52), decomp main 9157cc3ea73.
`u32 func_08104AEC(void *task, Command08104AEC *command, State08104AEC *state)` schedules a party effect: its five
child tasks, the mode-six position and the map-query scratch on its stack (`tools/party_effect_scheduler.py`). It was
in `src/` with a MATCH report; kit #350 now refuses its proof.

## Byte identity

`08104AEC.c` is the merged `src/08104AEC.c` unchanged (SHA-256
`43632d91d2c5129186fdcf0528f21a88ab27039c411f95eed015d316981242ad`). Its report at kit c6d104b52 said
`MATCH - byte identical - 1366/1366 bytes` under `--owner-runtime-profile conditional-party-effect-scheduler-v1`.
Kit #350 adds a proof check and changes nothing in how a source is compiled or linked, so the bytes are the same;
the refusal is in the proof.

## Refusal

`match.py --root . --no-write --owner-runtime-profile conditional-party-effect-scheduler-v1 0x08104AEC` at kit
d1e27356f:

```
error (WatchRefusal): callee 0x08021004: an access at 0x0802100E goes through a frame address of unknown provenance (not a stack array base plus an index)
```

The checked call is `bl func_0801CC7C` at 0x08104C46, made while R4, R5, R7, R9 and R10 hold owner stack
addresses. The refusal is in the walk of the owner's own code after that call (its continuation). That code calls
`func_080DE268` at 0x08104D0E. The walk follows it through `func_080DE278` (call at 0x080DE26E),
`func_0809836C` (call at 0x080DE2B2) and `func_08021618` (call at 0x08098962) to `func_08021004` (call at
0x0802162C), which does:

```
08021008  ldr r1, [pc, #0x20]     ; 0x08390E44, a ROM table
0802100A  lsls r0, r0, #2
0802100C  adds r0, r0, r1
0802100E  ldr r3, [r0]
```

R0 is `func_08021618`'s fifth argument (`ldr r0, [sp, #0x1c]` at 0x08021628). `func_0809836C` stored that argument
at 0x08098958 from its own frame word at sp+0xc. Every store the ROM makes to that word writes either a constant
(0 at 0x08098398, 0xB9 at 0x08098868 and 0x0809887A, 0x7E at 0x0809889A, 0x7C at 0x080988A2) or the return of
`func_080CA7A4(r7, 9)` (0x080986CE). At the refusal, the walk's frame record
has both the word and its copy as possibly holding frame addresses: one of `func_0809836C`'s own saved-register
slots, and addresses in deeper callees' frames. That is what kit #350's rule for code it does not walk allows:
such code, given frame addresses, may write any of them into any unpushed word of the frames they point into. The
scaled index therefore counts as a frame address of unknown provenance, and the table load refuses.

## What would readmit it

A proof that `func_0809836C`'s word at sp+0xc holds plain data when it is passed on would readmit it. Two kinds of
proof would do:

* bound what the code the walk does not follow may write in `func_0809836C`'s frame (a summary of which frame words
  it writes), so that the word keeps the value one of its writers stored; or
* track those writers (constants and one call's return) to the load at 0x08098956.

Then the index into the ROM table at 0x08390E44 is data, not an address. The C goes back to `src/` unchanged.
