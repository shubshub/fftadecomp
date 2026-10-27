# 08029F7C — bounded natural reconstruction

Target: complete indexed Thumb span `[0x08029F7C, 0x0802A1FC)`, 640 bytes and 283 reachable instructions.

Recovered behavior: handle repeated down/up input; move a signed byte row within the visible list or invoke the optional typed scroll callback; clamp or wrap when scrolling is disabled; update old/new row highlighting; dispatch the provided 12-byte button-action records using pressed input. The complete control flow is reconstructed, including both independent direction tests in the scroll-enabled branch and the final action table.

## Native result

Three bounded natural candidates were tested with unchanged agbcc `-mthumb-interwork -O2` and the approved ROM. The final native command was:

```
env FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' TMPDIR=/home/user/.codex-work/ffta-ulw PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v612-matching/matching-root --function-address-profile canonical-thunks-v1 0x08029F7C
```

All three returned exit 1 during compilation/native extent admission with `inert spins require an exact unique nonoverlapping Thumb span`. No native byte-match or plausibility success is claimed. The preserved best candidate emits one complete 628-byte target ELF function (`st_size = 0x274`), versus the required 640 bytes. Its typed indirect calls use actual `_call_via_r1` and `_call_via_r2` canonical thunks.

## Precise remaining differences

The ROM reloads the signed cursor byte in each scroll-boundary branch, after also loading the same byte unsigned for the new row: `ldrb` then `movs r0,#0; ldrsb r0,[cursor,r0]` at target `0x0802A026..0x0802A02C` and `0x0802A0A8..0x0802A0AE`. The candidate shares the byte load and subtracts/adds directly before the byte narrowing. Those two omitted two-instruction sequences account for 8 bytes.

In the two no-scroll wrap/clamp tests, target `0x0802A0FC` and `0x0802A15A` reload the changed flag from `[sp,#0x10]` before testing flag bit 0. The candidate retains the just-assigned constant 1 in a register and omits those two loads, accounting for another 4 bytes. Literal-pool placement, conditional branch displacements, register allocation, and the first scroll callback's selected thunk consequently also differ. This is not a claim that the candidate differs at only six same-offset instructions.

## Natural forms tried

1. Unsigned row locals: complete 612-byte ELF function, with additional differences in signed byte arithmetic and highlight argument promotion.
2. Signed row locals and promoted signed highlight arguments: complete 628-byte ELF function, correctly reproducing the byte increment/decrement form and highlight argument sign extension.
3. Unsigned stored cursor byte with explicit signed interpretation for the previous row calculation: identical 628-byte output to candidate 2. This final complete natural form is preserved.

No assembly, volatile, forced inlining, flag changes, artificial reads, dead expressions, or register steering was introduced. Active unmatched source and report were removed. No function match credit is earned.
