# 08042E48 bounded matching attempt

The accepted target is the complete 112-byte Thumb body at
[0x08042E48, 0x08042EB8). No MATCH was obtained. The final owned source was
moved from src/ to this directory after two distinct natural forms.

Both normal default native runs exited 1 with:

    signed remainder caller requires exact complete mapped ROM bytes

The parent classified the initial error as an ordinary compiled extent or
byte mismatch because the qualified owner, current index, complete target,
and mapping pins pass. This error combines extent and byte equality guards;
it does not independently establish unsupported addressed remainder calls.

The one authorized compiler-only diagnostic of unchanged form 1 emitted a
108-byte symbol, versus the 112-byte target. Full emitted bytes, ELF, command
results and disassembly are retained under
state/matching-08042E48-author/attempt1-compiler-diagnostic/. The compiled
form preserved r8 for width and sb for the control mask; the ROM additionally
copies width from r8 to sb and preserves the mask in sl. Initialization order
and the resulting prologue/epilogue also differ. No exact-byte match credit
follows from that diagnostic, which called no proof API.

Form 1 used an s32 remaining count initialized by the observed u16 narrowing.
Form 2, retained here, used a u16 count: the initial narrowed doubled helper
result and decrement only while nonzero justify that bounded count domain.
Helper ABI, record fields, selection narrowing, pointer arithmetic and control
mask stayed unchanged. Form 2 still failed the normal native guard. Its exact
compiled extent and byte difference are unknown: no second diagnostic was
run or authorized. No third independently grounded natural form was found.
Duplicate locals solely to force an extra register copy were not introduced.

The source calls the actual addressed s32 func_08142950(s32,s32), with no
percent operator, invented nonzero guard, or numerical remainder theorem.
The record/helper contract and CpuSet call remain conditional ordinary-call
contracts. 08041FB4.c served as an unproven source analogue; it was not treated
as successful native evidence. No natural-C impossibility claim is made.

Inputs and exact outcomes are frozen in
state/matching-08042E48-author/final-unmatched.json. Two native executions,
one authorized compiler-only diagnostic, zero successful proof replays,
zero MATCH credit, and no generated native match report.
