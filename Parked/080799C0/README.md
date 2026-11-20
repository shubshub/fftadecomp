# 080799C0 • Parked

The USA owner spans `[0x080799C0, 0x0807A094)`. Independent control-flow reconstruction reached 762 Thumb instructions occupying 1,528 bytes, with 212 bytes of literal pools and 8 alignment bytes. Both descendant calls target `func_080CB48C`, at `0x08079E20` and `0x08079F3C`. There is one return, through `0x0807A088`. SHA-256 of the 1,748-byte ROM owner is `5b5e3ab0c848c2b722884b1bd6c337ed967e70c9f04745a093e5ba516a1974de`.

## Source and gate

`080799C0.c` builds as a complete 1,624-byte linked symbol using the public agbcc (Thumb, interworking, -O2). Its 704 reached instructions occupy 1,412 bytes, with 196 bytes of pools and 16 alignment bytes. SHA-256 of the relocated candidate is `d81d0d588673d8aac9897f206d5e4f16ca58052597863341c751d4929778ea3d`. The first byte difference is offset 0x0A. The original loads its 0x61C stack adjustment through `ldr r4, [pc, #0xFC]` (`3F 4C`) and C loads it through `ldr r4, [pc, #0xF4]` (`3D 4C`). At 0x080799E0, the original allocates the selection sentinel to r6 and the candidate to r7. The 40-byte first inventory loop at 0x08079A52 matches byte for byte. The five bank scans use the same primary base, overflow delta and save-base delta. The original spills the narrow first-bank count to SP+0x60C, maintains both an output count spill and a separate index cursor across the helper calls, and positions its pools differently.

The default public owner gate stops at `inconsistent possible pointer offsets at control-flow join`. The separately linked candidate differs from the ROM as described above.

## Interface

`s32 func_080799C0(u16 mode, struct EquipmentList *list, u16 *selected)` returns the number of 20-byte rows and stores it at list+0. It writes the first available row (or zero) as a halfword. The context owns an inline row array starting at 0x230. Both outgoing calls take a unit pointer, item ID as u16 and slot as u8, matching the existing helper source. Only the low result bit is consumed.

Twelve direct incoming calls belong to 0807A79C, at 0807A8F2, 0807A9BA, 0807AA3C, 0807AA7C, 0807AAFE, 0807AC18, 0807ACAE, 0807AD2C, 0807ADAE, 0807B1D2, 0807B2A6 and 0807B31C. The thirteenth is at 08080ED4 in 08080EB8. The latter is the sole current game source that calls this owner. The caller declares its output as a u16 and uses an opaque tagged list pointer. Its 64-byte match is recorded in [the caller report](../../docs/match/08080EB8.md).

The candidate references the existing symbols `g_state_02000000`, `g_table_0851D180`, `g_table_08526680`, `data_03002818` and `func_080CB48C`. The five mode cases filter item categories into 256 local item records and 256 local u16 slot indices. They visit 361 primary slots and 14 extra slots. Each bank count narrows independently to u8. The ROM compares the input ordinal with the individual counts to choose a row's bank.

## Differential runs

The differential comparison ran the real linked candidate and the USA owner against identical RAM and real item definitions, with a controlled clobbering helper returning both accepted and rejected results. All 120 pairs agreed on the return value, all bytes of a 0x1800-byte output buffer, selection and adjacent guard bytes, and the ordered helper arguments. Each call preserved SP and R4–R11. Fixtures cover the five modes, fallback 0xFFFF, both flag paths, empty and mixed inventory, zero quantity, fully equipped stocks, all rejected, and 255/256-count boundaries including a wrapped primary count followed by accepted extra items. This comparison exercises the caller interface using a modeled helper and does not establish universal equivalence.
