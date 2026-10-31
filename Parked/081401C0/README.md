# 081401C0 bounded matching attempt

One natural C form was compiled under the accepted native broker lease 6536122399
(label sol-01C0). This is an ordinary candidate mismatch, not a native MATCH or
an unsupported-profile claim. No successful proof was replayed.

The complete target is [0x081401C0, 0x08140310), 336 bytes and 157 reachable
instructions. Its original saved bytes have SHA-256
b290bca6a3d0a5655911e916fb675afb62f0fda152c5c695eb3b539350ecb33f.
No new ROM read was used to author or diagnose this attempt.

The original native command used --addressed-signed-runtime-profile
addressed-signed-runtime-data-v1 and exited 1 in
inert_spin_profile.validate_span at its combined exact-span guard. It generated
no match report. The authorized single unchanged-source compiler-only diagnostic
used the fixed native cpp/agbcc/as/link pipeline, without a profile/proof API.
It emitted a complete 320-byte symbol, 16 bytes shorter than the indexed target.
Its linked body SHA-256 is
64c9643893ca3937862dbb52950a7706cad2a98104448606a58a1bfa9e922826.
At fixed offsets, 141 of the common 320 bytes are equal, 179 differ, and the
16 trailing target bytes have no candidate byte: 195 differing/missing offsets
across the full comparison. These are fixed-offset measurements, not an
alignment score or partial matching credit.

The retained C preserves the observed 40-byte records, signed byte timer/count,
phase halfword, actual MotionState fields and defining ordinary helper ABIs.
Both canonical addressed runtime calls and explicit s16/u8 narrowings remain.
The seven outgoing scalar words are 0,1,0,0,0,0,NULL. The named resource is an
unsized external byte base; its binding establishes identity only, not readable
extent or allocation. Ordinary helpers and addressed runtime operations remain
conditional returning ARM ABI boundaries, without numeric quotient/remainder
or transitive helper equivalence claims.

The diagnostic exposes different register choices and coordinate-load addressing;
no distinct grounded operation correction was identified. No declaration,
register, loop, spelling, type or constant steering was attempted. The one source
form, original stderr/exit receipt, actual original ELF, linked ELF, raw assembly,
full linked bytes and complete differences remain under:
state/matching-081401C0-author/ in the handover workspace. No match report exists.

Raw source SHA-256:
f129aafac95fb13a4891bc8a0eb4b08c57150dcccca0e90cf40d502bf72e5adf
Native source plus dependency fingerprint at the original attempt:
b73d4e33fa00135f60254dc4838cfba209b19ab4266745f563ee9d89858a8b80
All 115 tools, nine headers, both function indexes, current data maps and five
selected binaries were unchanged across the attempt. Only this owned source was
moved out of src. Parent owns reservation release and integration.
