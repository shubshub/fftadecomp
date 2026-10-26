# 080A8430 recovered, not matched

Target: complete indexed 0x080A8430..0x080A8498, 104 bytes and 51 reachable Thumb instructions.

The complete recovered C computes absolute x/z differences, passes their signed-16-bit sum and the signed-16-bit y separation to the established angle helper, converts its upper byte to the complemented offset angle, subtracts 15, clamps to 0..127, and divides by 16. The angle helper's u16 return and two s16 arguments agree with the existing 08007AD0 caller.

The final fixed native agbcc `-mthumb-interwork -O2` run returned exit 1 with plausible source and a verified complete 104-byte ELF symbol. The aligned diff score is 38/51 instructions and 92/104 bytes. Direct same-offset comparison gives 83/104 equal bytes; the aligned score is not same-offset byte equality.

The preserved candidate matches the entire signed coordinate loading, absolute-difference, argument preparation, call, and initial return-width conversion sequence through 0x080A846E. The remaining gap is the angle expression's post-call register allocation and copy placement. The target extracts into r1, uses r0 for the 0xFF complement mask, copies the masked value to r1 for clamping, then copies to r0 for division. The candidate extracts into r0, uses r1/r2 for the mask, and clamps in r0. This places one copy before the mask operation instead of after clamping and shifts the intervening branch sites by two bytes; both complete bodies are 104 bytes.

Bounded natural forms tried: direct signed-height argument casts with a byte cast compiled to 98 bytes. Explicit signed height differences and separate signed component locals recovered signed loads; byte/word angle temporaries and combined/separate subtraction forms generally compiled to 102 bytes. The preserved u16 intermediate with a separate signed clamping local produced the complete 104-byte body. A signed-16-bit clamping local produced 112 bytes; a byte function return produced 106 bytes; a coherent inline quantization helper retained the 102-byte result. Mask operand order did not resolve the gap. No flags, assembly, volatile accesses, dead code, or steering constructs were used.

The source is unchanged from the final native run. Its report and output remain in address scratch as `best-report.md` and `last-native-output.txt`. No match credit is claimed, and this records a bounded source/allocation gap rather than permanent impossibility.
