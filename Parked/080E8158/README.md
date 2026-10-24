# 080E8158, first candidate preserved as NONMATCH

**Preservation only. NOT MATCHING, with source classified IMPLAUSIBLE.**
No compiled match, source-plausibility approval or runtime equivalence credit.

The owned Thumb body is [080E8158,080E8384),556 bytes and231 reached
instructions:494 code bytes,56 literal bytes,6 internal alignment bytes.
It is a three-pointer callback registered through05B6C with52-byte payload;
all reached returns produce the full word0.

Exactly one natural candidate was frozen before exactly one canonical
`$HOME/agbcc/gcc/agbcc -mthumb-interwork -O2` compile. Main return, SystemExit
and actual process status were all1. There were no output-driven source,
declaration, spelling, register, ordering or flag revisions and no native runs.
This file is byte-identical to that frozen candidate, including target bytes.

## Exact result

The compiled function symbol is566 bytes and241 reached instructions,
partitioned as514 code bytes,48 literal bytes and4 internal alignment bytes.
Both original and linked .text sections are568 bytes; their final two `c046`
alignment bytes are outside the function symbol and excluded from comparison.
The original1904-byte ELF contains one Thumb function and16 R_ARM_THM_CALL
relocations to15 distinct mapped targets. The linked1924-byte ELF has no
residual relocation or unresolved symbol. Call multiplicities agree with ROM.
Ordinary framed structural checking passes for each complete body separately;
that establishes neither byte equality nor recursive callee correctness.

Within the **556 owned ROM bytes**,51 bytes agree at the same offset and505
differ. Only2 of231 reached ROM instructions have identical bytes at the same
address. The compiled symbol has10 excess bytes, `a146aa46f0bc02bc0847`.

The canonical diagnostic/report compares a566-byte ROM window and prints
368/566 aligned bytes plus81/226 linear/aligned instructions. That display
includes10 bytes of the next entry, `f0b5474680b48cb08046`, after080E8384.
These are not owned-byte equality metrics or true reached-instruction counts.
No part of that successor is credited to this function.

Observed differences include32 saved-register bytes rather than28, differing
register allocation/branch positions, extra low16 normalization around the
mask return, pointer-base reuse, and relocated/reduced literal pools. Local
frame size remains16. These observations describe the single result; no
alternate source or compiler experiment was attempted.

## Independent plausibility failure

Canonical output reports one `SUSPECT: rom-address` at source line57, the
readonly delay-table pointer initializer at08397F8C, and classifies the entire
source **IMPLAUSIBLE (not on the allow list)**. The ROM address has an
inventory-backed data interpretation, but that does not waive the checker or
provide a named-data relocation binding. Byte mismatch and plausibility
classification are separate reasons this candidate does not enter src.

## Semantic scope and assumptions

The candidate preserves phase0 selector/flag narrowing and effectful DD748
coordinate extraction, including the optional-null fourth output and upstream
-2/DE268 behavior. DD73C's bit15 result is tested through low8; true subtracts8
from signed y with halfword wrap. Phase100 adjusts y through the halfword ROM
table only for D49FC, while D6098 receives stored y. Ordered creation, mask
effects, selector/flags reloads and final descriptor-phase reload remain.

Phase101 always polls resource, coordinate, sequence and single task in that
order, even when an earlier result remains nonnull. Mask clearing requires
old-resource-nonnull/new-resource-null. Phase102 polls wrapper-task; record-task
at+30 is never polled. Phase0 does not initialize later resource/task slots.

Valid selectors, descriptor/payload pointers, phase-dependent initialization,
allocation success, child lifetimes and ABI-preserving callees are external
preconditions. D6134 has no initial null guard. Compatible narrow declarations
do not establish unique original public types; DD73C is declared u32 with the
explicit caller u8 test. No guessed guards, zeroing, allocation or lifetimes
were added. Static semantic recovery has not been runtime-validated.

## Immutable bindings

- Source SHA256: da018acb907afbfe3951d61346160fccddbc15c8478d17dc4284227bd3157e2d
- Source plus nine-header fingerprint: 725e993476ce47b4bb8144f1b4b1562323306ee4b95a8ed5cfb6577140204949
- Captured mapping SHA256: f596e6796b52306a76bc7913b8ab5faa0cf722514ddf7c5876820d1363c31d71
- Original ELF SHA256: 863e0d83fc3f326310f28fd38cbeb7877bccdf06f9a3f9ceb470315093108dcb
- Linked ELF SHA256: 8c7d458c197d4729db4bc72809821b26f05bea97a957fdd608ec1e9796fabd12
- Diagnostic NONMATCH report SHA256: e19f42a9bca185bd581c7307bec779006c93f8de83d1f1390d6e525c55fe300e

The report is diagnostic evidence retained in the author bundle, not a report
for production match admission. Raw ELF bytes/metadata, assembly, complete
body disassemblies, owned-range positional differences, precompile chronology
and input seals are retained there. Canonical generated binaries were removed;
no further compiler or runtime execution followed the nonmatch.
