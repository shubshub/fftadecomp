# 08046910 — unmatched natural C

Target: `0x08046910..0x080469F6`, complete 230-byte symbol and 104 reachable instructions. The retained fixed `agbcc -mthumb-interwork -O2` candidate also has ELF symbol size `0xE6` (230 bytes) and 104 emitted instructions, including the natural compiler-generated `__ashldi3` call and five literal words. Its frame is 20 bytes. No addressed helper alias, alternate flags, truncation, or steering was introduced.

The fresh shared-toolkit native matcher exits 1 with `ashldi3 caller requires exact complete mapped ROM bytes`. The canonical runtime helper is supported; this remaining refusal concerns actual caller bytes, not missing helper support. No successful native report is generated. The existing standalone source-plausibility command exits 0. This is not an accepted native match.

The routine scans 64 twelve-byte unlock records, excludes existing bits in a 64-bit flag set, checks eight interleaved stat values against the record requirements, and returns the first eligible record's packed identifier and result byte after updating its flag. Both the shifting scan mask and `(UnlockBits)1 << i` remain natural 64-bit C expressions. The RAM-state layout places the stat entries at 0x21B6 and the flags at 0x2C08, as established by the named addresses.

The complete emitted assembly agrees in extent, loop and return structure, packed record reads, literal values, 20-byte frame, and semantic register roles: found is ip, index is r8, flags pointer is sl. Scan snapshots occupy stack offsets 4/8 and write snapshots C/10, matching the target. The remaining source gap is two instruction-order groups. At entry the target copies zero from r1 to ip and then r8; the candidate copies to r8 and then ip. At the first inner comparison the target initializes r3, loads the stat-table address and its first byte, and then copies r3 to ip; the candidate copies r3 to ip immediately before those two loads. These order differences affect five instruction positions. No native aligned-diff score or same-offset byte-equality count is claimed.

Natural variants covered direct flag objects versus the containing RAM-state layout, explicit scan/write snapshots, narrow versus word boolean values, counter initialization scope, loop forms, equivalent requirement-test branches, compound versus expression flag updates, operand ordering, and interleaved stat layouts. The containing state layout eliminated a duplicate rematerialized flag address. Initializing the inner counter before clearing found removed the extra instruction. Explicit scan/write snapshots recovered the target stack slots. Moving the outer initialization into the loop initializer, alternative condition forms, and narrow raw-stat access changed extents or register allocation without closing the ordering gap. The best full-length candidate was restored and freshly checked.

Source SHA-256: `f335303cb267f00a1ee2b06f7ce5f9fc2d4201c591a337ef6fe8f37b32941dd2`.
Emitted assembly SHA-256: `8eb2dc2d90d36703e57c9479146944bdd32572eb4879f0f284be80440feb32d6`.
Fresh native refusal log SHA-256: `f15259c79b358e80f0801ac0c198c60c6d6cf6faa80fead73b600ef6bd0af39e`.

The private active source/report are removed. This pair is preserved for root integration with no exact-match credit and no main-tree edits.
