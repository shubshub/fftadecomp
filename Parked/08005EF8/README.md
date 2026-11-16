# 0x08005EF8 - byte-identical, refused: its struct copy compiles to memcpy, which no profile binds here (204 bytes)

Retry of Parked/08005EF8 on 2026-11-16, kit fcdf2d45. The source here compiles to the ROM's bytes, proved by linking the
object by hand with memcpy bound to 0x081443FC and each callee at its ROM address (204 bytes, sha256
70fc1af6b37822811745b4ebaf478769b3eccd55f9b990d6b7ba530d388fd678 = ROM [0x08005EF8, 0x08005FC4)); plausible.py --strict
reports nothing. match.py refuses it:

| Command | Refusal |
| --- | --- |
| default, also `--function-address-profile canonical-thunks-v1` | `call target must be an undefined addressed function` (the call is to memcpy) |
| `--owner-runtime-profile named-data-buffer-rom-table-copy-v1` / `-stack-index-v1` / `-stack-index-v2` | `acyclic owner excludes arithmetic runtimes and indirect thunks` |
| `--owner-runtime-profile named-data-buffer-finite-small-copy-binding-v1` | `cyclic small-copy prefix requires a separate proof` |
| `--owner-runtime-profile named-data-buffer-compiler-copy80-binding-v1` | `cyclic copy prefix requires a separate proof` |

Kit gap: the per-entry copy is a struct assignment, which agbcc emits as a call to memcpy (= func_081443FC). Every existing
memcpy binding needs a stack destination and/or no loop before the copy; here it copies inside a loop into a pointer
parameter, in a function that also calls through _call_via_r2 (g_callbacks_0836D4B8[0]).

No explicit func_081443FC(...) spelling can match: the ROM builds the destination in two steps around the source
(`adds r0,r5,r1; adds r1,r1,r6; adds r0,#0x34`), which is gcc's expansion of a struct assignment; an explicit call
computes each argument in full and the front end rewrites &a[i] as a + i (76 halfwords differ; source first: 8; the old
byte-offset spelling: 2 instructions).

Names agree with those used for the transfer step 0x08005E7C (Parked/08005E7C) (TransferDescriptor, RequestNode, limit at +4, progress at +0xC,
request at +0x18, entries at +0x34) and with the merged creator src/08006878.c (TransferEvent, prototype
`u32 func_08005EF8(void *task, TransferEvent *event, TransferPayload *payload)`). TransferEntry is packed
{ TransferDescriptor descriptor; u8 kind; u8 value; } (unpacked: ldmia/stmia, 200 bytes; src/08006878.c declares its own
unpacked TransferEntry, which does not affect its bytes). Index row 08005EF8 08005FC4 204 93 is correct.

kit issue: (to be filed) - no profile binds a compiler-emitted memcpy (a struct assignment) that copies inside a loop
into a pointer parameter in a function that also calls through `_call_via_r2`.
