# 08080F68: 268 of 272 bytes; two loads before the CpuSet call are swapped

Target: `[0x08080F68, 0x08081078)`, 272 bytes. It uses the same state as the matched `08081B24` and the same two callees, so once the bytes match, the likely selector is `--addressed-signed-runtime-profile addressed-native-bios-ordinary-v1`.

`08080F68.c` compiles to the right length. The frame, registers, three stack slots and literal pool are all identical. Only these two instructions differ, at 0x0808103E/40:

```
target:  ldr r2, =0x1FFFFF ; ldr r3, [sp, #0xc] ; ands r2, r3
ours:    ldr r2, [sp, #0xc] ; ldr r3, =0x1FFFFF ; ands r2, r3
```

agbcc's dumps show the cause:
- Loop pass 1 substitutes the single-use invariant `size & 0x1FFFFF` into the r2 set.
- The rerun pass then hoists the mask constant.
- Reload breaks the tie the other way.

In the ROM the constant stayed in the loop. Shapes ruled out: `0x1FFFFF & size`, `u32 size`, five different placements of the `size` assignment, `size &= mask`, a fused `(end - start) & mask`, `(x * 2 / 2)`, increments in the `for` header, 2-D indexing and swapped pointer increments.
