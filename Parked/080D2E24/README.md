# 080D2E24

Target: complete 60-byte Thumb function, 23 reachable instructions. Fixed
`agbcc -mthumb-interwork -O2`; native matcher used
`--function-address-profile canonical-thunks-v1`.

The retained first candidate clears the 0x400-byte region at data_020021C8,
then its adjacent 0x300-byte region, then zeroes the word at offset 0x700.
It emits a complete 60-byte ELF function with 23 instructions, but differs
in register allocation and constant lifetime: it saves r4-r6, retains 0x400
in r4 across the first callback, keeps the state in r5 and the callback table
in r6, and copies the second buffer address into r0 immediately before its
call. The ROM saves only r4-r5, keeps state/table in r4/r5, and rematerializes
0x400 after the first call to form the second address directly in r0.

Three natural forms were tested. Structured regions with a callback-table
pointer (retained) and indexed u32 storage with that pointer emit the same
nonmatching assembly. Direct callback-table expressions instead retain the
function pointer in r6 across both calls and use `_call_via_r6`, also failing
the selected profile. No compiler flags or artificial source constructs were
used.

The first and third native invocations exited 1 with
`inert-spin complete body differs from ROM`; the second exited 1 with
`inert spins require an exact unique nonoverlapping Thumb span`. These are
profile validation failures before the normal plausibility/comparison report;
no native plausibility acceptance or N/N equality is claimed. Active unmatched
source/report were removed. No match credit.
