# 0x08059344 matching attempt

Parked after three bounded natural source forms. No byte-identical match was obtained.

The complete ROM span is [0x08059344, 0x080593E0), 156 bytes. It contains 66 reachable instructions and four referenced literal words. All three native checks exit 1 with:

```
compiled symbol is shorter than the indexed span: 152 < 156
```

The candidates used a typed 16-byte record array, a byte-addressable global with observed offsets, and an aligned u32 view of the record's first word. Each preserves the three u8 inputs, existing u32 CCB28 return with explicit byte narrowing, actual ten-argument 29864 prototype, call order, and final four-u8 A370 call. The retained source is the third form.

The linked diagnostic contains 66 reachable instructions and three literal words. The compiler shares the observed offsets 0x2E7D and 0x2E78 through a subtract-5 sequence, while the ROM retains both literal words. Address-add association/register allocation also differs. No extra operations, asm, pragmas, volatile, fake parameters, or compiler steering were added.

The standalone existing plausibility checker exits 0. Native matching stops at the complete-symbol size gate before generating a match report, so no native MATCH or matching-profile verdict is claimed. `native-failures.log` preserves all three exact native outputs. Complete source/header/mapping/runtime receipts, generated assembly, and both complete linked byte strings are retained in `state/matching-08059344-author/` at the handover root.

Only this lane's active source was moved here. Shared inputs and other sources were preserved. Reservation release and integration belong to the parent executor.
