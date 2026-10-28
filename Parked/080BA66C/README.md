# 080BA66C — bounded natural-C mismatch

Target: 0x080BA66C..0x080BA6D0, 100 bytes and 44 reachable instructions.
The complete recovered C increments a signed byte counter at offset 0xA0, rotates seven halfwords every sixth tick through the typed external copy callback, resets the counter, and visits all active linked-list nodes with the recovered coordinate scaling.

Native command: fixed agbcc -mthumb-interwork -O2, approved ROM, match.py --root this private root --function-address-profile canonical-thunks-v1 0x080BA66C. All three bounded attempts exited 1 at the native exact-body validation with: `compile failed: inert-spin complete body differs from ROM`. This diagnostic comes from the shared complete-span validation used by the function-address profile. No report or native plausibility verdict was produced; no exact-match credit is claimed.

The original candidate's fixed-toolchain assembly agrees with the target except for two adjacent independent operations after the callback. Target 0x080BA694 stores the saved first halfword (`strh r5, [r4, #12]`), then 0x080BA696 prepares zero (`movs r0, #0`). Candidate performs those two operations in the reverse order. The subsequent byte-counter store and the complete list traversal agree at the assembly level. The original complete natural reconstruction is retained here; this is an assembly comparison, not a passed native byte/ownership proof.

Bounded forms tried: a u16 saved halfword local; a naturally promoted u32 saved value; and a semantic static inline rotation helper with no forced-inline attribute or compiler changes. None passed the native complete-body comparison. No assembly, artificial volatile, dead expressions, fabricated aliases, or altered flags were used.

Unmatched active source/report and temporary preprocessed/assembly files were removed. Root owns lease release and any integration.
