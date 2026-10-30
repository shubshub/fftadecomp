# 08037DF0

Recovered operation: use an unsigned record index with stride0xCC, pass the
object at state+index*0xCC+0x9CC and a signed-byte adjustment to func_08017B68,
then reload g_state_03002810 and store the returned low byte at
state+index*0xCC+0x98A. The helper signature and its halfword members at0x18
and0x1A come from existing src/08017B68.c. The global pointer mapping is
already present at0x03002810.

The retained source is plausible, but is not byte identical. Its native
complete56-byte symbol matched19/20 instructions and54/56 bytes. At0x08037DFC,
target bytes20 18 encode adds r0,r4,r0; compiled bytes00 19 encode
adds r0,r0,r4. No arithmetic equivalence is claimed as a match.

Command executed with default flags -mthumb-interwork -O2:

    python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x08037DF0

The native report is native-not-matching.md. Its historical src/ path refers
to the unchanged source now parked here. The source-bound receipt is retained
at state/matching-08037DF0-author/attempt-04-receipt.json under the handover
root. The receipt records this machine and source SHA256.

Five candidates/checks were retained: incomplete flexible-array syntax was
rejected by agbcc; a nested typed record acquired ABI alignment inconsistent
with the observed stride; byte-offset and global-slot forms reached the full
symbol with47/56 and54/56 identical bytes; a byte-record array form produced
52 bytes rather than56. Default native verification was retained throughout.
No flags, assembly, pragmas, volatile, dead operations, toolkit profiles, or
verification workarounds were added. No source remains in src/ for this address.
