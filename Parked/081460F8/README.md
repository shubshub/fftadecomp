# 081460F8 bounded natural-C attempt

Target: complete [0x081460F8, 0x08146120), 40 bytes / 17 reachable instructions. Native claim 6482272803 was ACCEPTED with exit 0.

Recovered behavior: check the music-player signature at +0x34 against 0x68736D53; on success store the incoming u16 scale at +0x1E and store (scale * unsigned halfword at +0x1C) arithmetic-shifted right 8 into +0x20. The u16 operands undergo ordinary signed-int promotion, matching the target arithmetic shift.

Fresh native fixed-toolchain matcher exit 1: `compiled symbol is shorter than the indexed span: 36 < 40`. The complete-extent gate precedes the native plausibility/report gates, so no byte-exact or native-plausibility success is claimed. The complete retained compiler function is 36 bytes / 15 reachable instructions, including its literal pool.

The concrete residual is register allocation and its save/move sequence. The target keeps the narrowed scale in R1, the signature value in R3 and the base tempo in saved R4, then copies R1 into R0 before multiplication. The candidate uses R3 for the narrowed scale, R1 for the signature and R0 for the base tempo; it has only push {lr}, no saved-R4 restoration, and no extra scale-to-result move. The data offsets, guard, store order, multiplication, arithmetic shift, and signature constant agree. The literal and branch offsets consequently differ.

Natural forms checked under unchanged agbcc -mthumb-interwork -O2: direct scale-times-base expression; base-times-stored-scale expression; success block versus early-return guard; a signed intermediate product computed before the scale store; u32 input with an explicit u16 local conversion; and a local u16 base value after the scale store. These forms all produced a complete 36-byte body rather than the target's 40 bytes. No register annotations, volatile, artificial lifetime extension, padding, flags, or helper aliases were used.

The retained source is the simple early-return form with direct arithmetic. The original unmodified ET_REL, generated assembly, and fresh native refusal log are in the sibling 081460F8 artifact directory outside matching-root. Unmatched active source/report were removed. Zero match credit.
