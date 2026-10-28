# 080895A0 bounded natural-C attempt

Target: complete [0x080895A0, 0x080895D0), 48 bytes / 15 reachable instructions. Claim 6481172801 was ACCEPTED with exit 0.

Recovered behavior: initialize the four background-control halfwords at offsets +2, +4, +6, +8 from the existing g_control_flags_03000940 binding to AE0B, AC0A, 2B02, 2A00. The retained source uses ordinary u16 members and direct assignments.

Fresh fixed-toolchain native matcher exit 1: `compiled symbol is shorter than the indexed span: 40 < 48`. This extent gate precedes the native plausibility/report gates; no byte-exact or native-plausibility success is claimed. The complete compiler ELF is 40 bytes / 11 reachable instructions, including its literal pool.

Exact instruction residual: the target additionally reads each destination halfword before replacing it with a constant, at 080895A2, 080895A8, 080895AE, 080895B4. Each read is immediately overwritten in r1. The ordinary assignments omit these four reads (8 bytes), shifting the later instructions and pool displacements. Store addresses, values and order agree.

Natural forms checked under unchanged agbcc -mthumb-interwork -O2: individual background-control bitfields produce a 220-byte body with byte accesses and additional masking; whole-width u16 and u32 16-bit bitfields both produce 40 bytes; explicit mask-clear plus OR updates likewise produce 40 bytes. The final direct assignments are the clearest complete equivalent candidate. RAM volatile and artificial read preservation were not used.

Original unmodified compiler relocatable ELF, assembly, disassembly and native refusal log are preserved outside matching-root in the sibling 080895A0 artifact directory. Active unmatched source/report were removed. Zero match credit.
