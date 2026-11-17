# 0x0804393C - window-5 menu slot state machine: near miss, 1171/1208 bytes (1208 bytes)

Attempt 2026-11-17, kit 18dcc516, decomp main e13c2cff3e. The function takes a slot index and switches on the
slot's state byte, `g_state_03002810->slots[index].state` (+0x987 + 0xCC * index, 0x0804395E). State 0 does the
setup. It clears `active[index]` (+0x4BE) and opens tile window 5 with `func_0808A268`, using the two resource
pointers and four buffers carved from `data_03002740[5]`. It sets the window's position, border tile and inner
size in `data_030009E0[5]`, draws the slot's panel (`func_08043ECC`, `func_08037C84`) and fills both planes
(`func_08016344`, `func_08016560`). It then writes one tile run (`func_08035678` into `func_0808B8E4(5, 1, 1,
1)`), sets the window status to 2 and parks in 0xFD with `data_0201F4E5 = 1`. State 1 handles input. A
`func_08040388` result of 0xFF sets the slot result to 6 and the state to 0xFF. Button 1 acts on the
selection: 0 and 1 set mode 25 or 26 and fade out, 2 and 3 set the display mode to 30, and any other
selection leaves through 0xFD with 0xFF as the next state. Button 2 plays sound 105, sets the window status
to 3 and also leaves through 0xFD to 0xFF. Otherwise a slot result of 3 calls `func_0808A604(5, 2)`. State
0xFD waits for window 5 to go idle and then takes the state from `data_0201F4E5`. States 0xFE and 0xFF clear `closed[index]` (+0x4B8). The index row `0804393C 08043DF4 1208
487 return` is right: 487 reachable instructions (26 `bl`), code to 0x08043DF4. The named data
(`g_state_03002810`, `data_030009E0`, `data_03002740`, `data_0201F4E5`, `data_02003CB0`) is all in
`config/data_symbols.json` on main.

## Byte identity

`0804393C.c` was compiled with the fixed recipe (`cpp -nostdinc -undef -I include`, `agbcc -mthumb-interwork -O2`,
`arm-none-eabi-as -mthumb-interwork`) and linked by hand at 0x0804393C. Every callee and data symbol was bound
to its ROM address (26 `R_ARM_THM_CALL`, 13 `R_ARM_ABS32`). The symbol and `.text` are both exactly 1208 bytes.
ROM span SHA-256 `cb04d7aca45d0c67760f9edd2cdeca81b2851cd908e160413e87651c08111a0b`, linked symbol SHA-256
`e322379d79d17559c43113e31b328cf64cf39c06750b5363be3bdeb66d6e9ff0`: 37 bytes differ.

`match.py --root . --no-write 0x0804393C` runs its byte comparison and reports `verdict NOT MATCHING - bytes
differ` and `450/487 instructions identical (1171/1208 bytes)`. `plausible.py --strict` exits 0.

All 37 differing instructions come from one register swap. In the ROM, sb holds the address of
`g_state_03002810` (`ldr r0, =g_state_03002810; mov sb, r0` at 0x0804394A-0x0804394C) and sl holds `index *
0xCC` (`mov sl, r2` at 0x08043956). This build swaps them. Every later `mov rN, sb` before a reload of the
state pointer and every `add r0, sl` that indexes the slot then names the other register. Each differing
instruction differs in one byte, at 0x0804394C, 0x08043956, 0x08043998, 0x08043A2E, 0x08043A36, 0x08043A40,
0x08043A46, 0x08043ADC, 0x08043AE0, 0x08043B30, 0x08043B34, 0x08043B40, 0x08043B58, 0x08043B5C, 0x08043B8C,
0x08043B98, 0x08043BA4, 0x08043BD4, 0x08043BE0, 0x08043BEC, 0x08043C0A, 0x08043C1A, 0x08043C50, 0x08043C6E,
0x08043C7C, 0x08043C80, 0x08043C92, 0x08043CC6, 0x08043CD6, 0x08043CE4, 0x08043CE8, 0x08043CF6, 0x08043CFA,
0x08043D0C, 0x08043D36, 0x08043D7A and 0x08043D7E. The frame (56 bytes), instruction order, literal pools and
all other instructions are identical.

## Cause

Two values live across the whole function: the address of the global state pointer, which is reloaded
through it after every call, and the slot offset `index * 0xCC`. The allocator gives them the two high
registers in the opposite order from the ROM. The analysis in this attempt found the allocation priority of
the symbol-address pseudo halved, which puts it behind the slot offset. That analysis was not re-derived for
this entry. No source form tried so far changes the order (see
Ruled out).

## Source notes

- `width` and `height` are locals (8 and 11). The ROM sets r4 = 11 at 0x08043996, before it moves the call's
  register arguments (0x08043998). It also builds `field_4A`'s 6 (0x08043A1E) before its address, as
  `width - 2` computed from a held value. The bytes need the locals (see Ruled out), but the names and the
  `width - 2` / `height - 3` spellings of `field_4A` and `field_4B` are a reading, not pinned.
- States 0xFE and 0xFF are separate cases with the same body, `closed[index] = 0`. The ROM tests each value
  on its own (0x08043980, 0x08043986) and has a body for each (0x08043DD0 and 0x08043DD8, each forming 0x4B8
  in a different scratch register), and the two join at 0x08043DDE for the store. AGENTS.md lists switch
  cases with the same body under separate labels as ordinary C when the ROM tests each value on its own.
- The structures name only the members this function touches. `MenuSlot0804393C` is the 0xCC-byte slot at
  +0x984. Its +0x0E is `buttons`, cleared by selections 2 and 3 (`strh` at 0x08043C72 and 0x08043CEC through
  the offset 0x992), and its +0x10 is `selection`.
- `func_08016560` takes `(first_plane, 8, 11, 0xC0, 8, 1, 12)`: r1 = 8 and r2 = 11, with stack words 8, 1 and
  12 (0x08043A8E-0x08043A98).

## Ruled out

- The previous parked copy (main) compiles to a 1204-byte symbol. `match.py` stops with `compiled symbol is
  shorter than the indexed span: 1204 < 1208`. It also had two semantic errors, fixed here. It passed `11, 3`
  as `func_08016560`'s width and height instead of 8 and 11 (0x08043A8E-0x08043A98). Its selection-2 and
  selection-3 arms cleared `selection` instead of `buttons` (offset 0x992, stores at 0x08043C72 and
  0x08043CEC).
- This source with `width` and `height` replaced by the constants 8 and 11 everywhere: 1204-byte symbol, 788
  bytes differ. The locals are what brings the size to 1208.
- This source with `field_4A = 6` and `field_4B = 8` written as constants (locals kept): 1208 bytes, 43
  differ (6 more than this source).
- From this attempt, not re-run for this entry: about 2,200 source variants aimed at the sb/sl order were
  compiled, and none removed the swap. Their individual results are not recorded here.

kit issue: none (not byte-identical)
