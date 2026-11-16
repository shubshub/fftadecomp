# 0x08119914 - byte-identical (882 bytes) only under a stack-index premise that is not shown

First attempt (no earlier parked source), 2026-11-16, kit fcdf2d45. plausible.py --strict exits 0.

Needs 11 data symbols (not in config/data_symbols.json): data_083A6410 data_083A6458 data_083A6488 data_083A649C data_083A64A0 data_083A64A4
data_083A64AC data_083A64B4 data_088F58E0 data_0894BE84 data_0894BEAC. With them and --owner-runtime-profile named-data-buffer-stack-index-v2,
match.py stops at: 'stack index: the premise rows of 0x08119914 need a reviewed entry in config/stack_index_premises.json that repeats them
exactly (none found)'. The rows:
- site 0x08119A1C, expression (u32)((ret(0x08119A0E) << 24) >>s 22), bound 15
- site 0x08119A26, the same expression, bound 13
With an entry for exactly these rows the result is MATCH - byte identical (checked with an unreviewed entry that was not kept).

Not shipped: the entry needs a written review that every execution keeps the index below the bound, i.e. that func_080DBC88(payload->object)
(ldrb [r0, #0x1F], sign-extended: the unit's facing byte) returns 0..3. That is not shown: the event-script writer of +0x1F is bounded by ROM data,
but other writers (the battle action-scene payload chain func_080A5B98 / func_080A433C / func_08092784, the func_080DE12C API family, and u8/s8
arguments that reach func_0809836C / func_080975DC) are not bounded by anything visible in the ROM. The same premise holds back 080F7720 and
080FDB98. Kit issue: none (not a verifier gap; the premise needs evidence).

Other refusals: default flags: 'compile failed: unexpected nonempty allocated section'; --owner-runtime-profile named-data-buffer-stack-index-v1:
'stack index: index range is not 2-byte aligned on every path; index is not provably 2-byte aligned'.

Table: a 16-byte stack copy of the ROM table at 0x08149F78, four {s16 x, s16 y} offsets indexed by facing. The only reference to the callback is
task-table entry 330 (id 0x14B) at 0x08395228.

Open doubts: func_080035A8 declared u16(u8); the operand order of payload->x + offsets[facing].x; func_080DD748's fourth s16 * parameter copied
from 081171CC.
