# 0802D7A0 — Parked

Target: complete indexed Thumb function `[0x0802D7A0, 0x0802D822)`,
130 bytes and 55 reachable instructions.

The recovered function compacts a four-slot halfword list. It obtains the
nonzero-slot count, shifts remaining slots over each zero using the genuine
copy callback in `data_0836D4BC`, and clears the vacated tail slot. The source
reference is the observed `g_state_02002FC4 + 0xC72`; the destination reference
is the genuine mapped `data_02003C34` array.

Fresh native verification used the approved ROM, fixed agbcc
`-mthumb-interwork -O2`, and `--function-address-profile canonical-thunks-v1`.
It exited 1 at compilation/profile verification with:

`inert-spin complete body differs from ROM`

The byte-identical result and source-plausibility gate were not reached.
This is a remaining generated-code mismatch, not a claim that indirect calls
or the function's metadata are unsupported.

Bounded natural attempts covered walking source/destination pointers with
signed and unsigned removal counts, an indexed for-loop that revisits removed
slots, and the retained indexed while-loop. Fixed-compiler assembly confirms
the common residual: agbcc introduces a running tail-address induction
variable and decrements it by two when removing a slot. The target instead
retains capacity four and recomputes the tail offset from the removal count.
Register allocation, pointer setup and literal order also differ. The retained
C preserves the complete operation and ABI; no flags, assembly, volatile,
dead expressions or artificial code-generation constraints were introduced.

The final native diagnostic is retained outside the repository in the private
v583 address scratch as `native-result.txt`. No unmatched active source or
match report remains.
