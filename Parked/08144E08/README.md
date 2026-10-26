# 08144E08 — parked

Complete indexed target [0x08144E08, 0x08145008): 512 bytes / 245 instructions. One full natural C candidate implements note decoding, tone resolution, channel selection, linked-list insertion and channel setup. It uses explicit typed arguments for the channel/track helper.

Native matcher exit 1: `compile failed: recursive or intra-function calls are unsupported`. Fresh diagnostic compilation with the fixed approved cpp/agbcc/as options gives symbol size 0x24A (586 bytes), ending at 0x08145052 and therefore crossing the called helper at 0x08145048. Native comparison/plausibility verdicts were not reached; no exact counts are claimed.

A semantic ABI obstacle is independently visible in the target and its callee. The target BL at 0x08144F98 calls 0x08144DD8 without setting r0/r1. The helper directly reads the channel through r4 and track through r5, starting with `ldrb r1,[r4,#0x12]` and later `ldrb r0,[r5,#0x10]`. The natural typed call `func_08144DD8(channel, track)` emits argument moves into r0/r1. Removing those arguments would hide the helper's actual inputs from the C interface; making the target interface explicit would require the prohibited register/assembly steering. Additional custom interfaces are the r1-only track helper at 0x08145048 and callback thunk `bx r3` at 0x08144D84.

No asm, volatile, pragmas, fixed registers, compiler changes or shared edits were used. The native error, diagnostic extent and callee evidence are retained privately in native-output.txt; diagnostic assembly is retained as candidate.s. Nonmatching src/08144E08.c was removed; the matcher produced no native report. This is not the unused-load-before-store family. Root owns the accepted lease and release.
