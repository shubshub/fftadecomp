# 080CBF34: 187 of 191 instructions; the retry loops lack a byte narrowing

Target: `[0x080CBF34, 0x080CC0DC)`, 424 bytes. It fills `picks[20]` at `0x02001F6A + 0xEFA` with `mod(rand, 11) + 10` random draws from a 58-byte-row table. The range for each draw comes from a roll out of 100. Draws repeat while the result is 0. `0x55` is added according to the flags in `g_table_08528F34`. It needs the data symbols `data_02001F6A` and `data_08528C86`.

`080CBF34.c` differs in 4 instructions (2 short). In each of the three retry loops, the ROM has `ldrb r0,[r0]; strb r0,[r4]; lsls r0,r0,#24; cmp r0,#0`, but the source's plain `ldrb` makes the compiler drop the `lsls`. After the draw, the ROM uses `ldrb r2,[r4]` where ours has `ldrb r0; adds r2,r0,#0`, and the first block's `mov r3,r8; adds r4,r5,r3` comes before the pool loads in the ROM.

What was ruled out: draw locals of every width and signedness, inline helpers, s8/u16/s16 pick arrays, 1-D tables and `while ((x = ...) == 0)` forms.
