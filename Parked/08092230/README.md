# 08092230

Complete recovered teardown/control-state restoration for 0x08092230..0x08092288. It destroys a nonnull child at source offset 4, restores four saved bytes at source offsets 0x48..0x4B into global 03000940 offsets 0x4A..0x4D, and destroys the source object.

Fresh canonical native matching with fixed agbcc `-mthumb-interwork -O2` exited 1 at the extent gate: `compiled symbol is shorter than the indexed span: 80 < 88`. Target: 88 bytes / 39 reachable instructions. Preserved complete ELF candidate: 80 bytes; fixed compiler assembly contains 35 instructions. No native byte-diff or plausibility verdict was reached, and no gate-accepted plausibility claim is made.

The target reads each destination byte immediately before overwriting it, without using the old value: LDRB at 0809224A, 08092256, 08092264 and 08092272. The candidate emits all four source-byte loads and stores in the captured order, plus the same conditional child-destruction and final destruction calls, but omits these four old-value reads. These four missing instructions explain the eight-byte extent gap; the reduced register pressure also changes global/pointer register assignment.

Bounded natural layouts tested under the unchanged fixed flags:

- Eight-bit destination bitfields declared with `u8`, `u16` and `u32` storage types: every candidate was 80 bytes and omitted the old-value reads.
- Signed 32-bit eight-bit destination fields: same 80-byte extent.
- Matching unsigned 32-bit eight-bit packed fields in both saved source and destination: same 80-byte extent.
- The simplest ordinary byte fields in both structures were then restored and freshly checked; this is the preserved complete recovery.

No explicit dead loads, volatile accesses, assembly, forced inlining, flag changes or inert control flow were introduced. This records a bounded failure to explain the observed reads with the tested natural field types, not permanent impossibility or a native eligibility rejection. The target's native eligibility was supplied separately by the parent. Native extent output and fixed compiler assembly remain in private address scratch. Unmatched active source/report were removed.
