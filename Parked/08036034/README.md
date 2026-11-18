# 08036034 — refresh expired items

The standard Thumb agbcc recipe reproduces the entire 196-byte symbol, `[08036034, 080360F8)`. SHA-256 for the linked C and the original ROM is `d9a564a2c35e48d3762441f8432dde6cf6a476cd64b64c04acf070d39237662d`. The standard CFG reports 79 reachable instructions and eight direct BL sites. The four literal words at 08036064, 080360B0, 080360D4 and 080360F4 all reference `g_state_03002810`. Both live indexes already give the correct extent and count.

Six direct callers pass an update flag in R0 and a menu value in R1, which this body ignores. The BL sites are 0803083E, 0803096E, 080484C6, 08048690, 0804875A and 080487E6. For example, the first two callers pass (0, 1) and (1, 3), respectively. The return is the full count produced by 080D1C94.

The nonzero update path clears sixteen local item pointers. When the position has changed it synchronizes it with 08035F8C and asks 080D1C94 to write expired items to the panel at +0x24. Otherwise it asks 080D1C94 to write them to the local array. A positive count triggers a scan of all sixteen local slots, followed by a write to the panel's count at +0xAC. The zero update path tests the position a second time if the first query returned zero, fills the panel list, and returns directly. The packed ten-bit ID and panel layout also appear in src/080301B0.c and src/08049ED0.c. The full-register query return agrees with the caller in src/08049ED0.c. Changing only the return type of src/08035FC4.c from u8 to s32 in scratch preserved its independently verified 72 bytes. The genuine callee returns either 0 or 1 in the entire register.

## Original runtime behavior

Exercised the original ROM and all called routines in Unicorn with the real item metadata and a linked list of zero, one or sixteen items. Mode-1 item 0x7B expires on advancement. Mode-2 item 0x80 expires with flag 0x45 set, including on the local-output path. Captured both one-byte reads at 0803607E and 08036080, calls to 080301B0, the panel slots and count, and the sixteen descending stores during initialization.

| Update | Position changed | Number expired | Reads at address 0 / address 1 | Calls to 080301B0 |
|---:|---:|---:|---:|---:|
| 0 | no | 0 or 1 | 0 / 0 | 0 |
| 0 | yes | 1 | 0 / 0 | 0 |
| 1 | no | 1 | 15 / 15 | 1 |
| 1 | yes | 1 | 16 / 16 | 0 |
| 1 | no | 16 | 0 / 0 | 16 |

The original always reads the packed ID before checking its pointer at 0803608E. In the one-local-item case, filling mapped low memory with either zeros or 0xFF left the insert count unchanged. These runs establish which addresses are read. The bytes supplied by actual GBA BIOS protection depend on hardware state. Reading through a null item pointer also has undefined behavior in portable C. Moving the guard before the ID is well-defined for empty slots and changes the program to 179/196 matching bytes.

## Verifier status

With toolkit 47cd658f, the candidate passes `plausible.py --strict`. The default `match.py --no-write` and the named-data stack index v2 profile both refuse `unsupported stack-address materialization`. At 08036044 the clear loop compares the descending cursor in R0 with SP before a signed BGE. The inventory-only SP comparison verifier recognizes the opposite operand order. The conditional finite local word and spilled scalar loop selectors each refuse `finite branch requires exact scalar operands`. Existing maps suffice to link the object; no match report was issued.
