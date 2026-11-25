<!-- ffta-status:start -->

## Decompilation progress

| Metric | Matched / indexed | Progress |
| :--- | ---: | :---: |
| Functions matched | 5,170 / 5,600 | **92.32%**<br><img src="/docs/badges/functions.svg" width="82" alt=""> |
| Bytes matched | 952,928 / 1,341,981 | **71.01%**<br><img src="/docs/badges/bytes.svg" width="82" alt=""> |

Each match reproduces the original ROM bytes. Byte coverage counts overlapping function spans once.

<details>
<summary>ROM regions and library units</summary>

The main index covers functions starting below `0x08150000`. Its totals can change as function boundaries are recovered.

**Additional verified late-ROM spans: 21 functions; 3,236 complete-body bytes.** These are counted separately.

[Functions badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Ffunctions.json) · [Bytes badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Fbytes.json)

Matched bytes by 64 KiB ROM region

```
0x08000000  ███████████████░░░░░   77.3%    458/494 fns
0x08010000  ███████████████░░░░░   75.4%    400/424 fns
0x08020000  ████████████████░░░░   82.0%    375/398 fns
0x08030000  ███████████░░░░░░░░░   55.9%    160/173 fns
0x08040000  ████████████░░░░░░░░   62.0%    185/203 fns
0x08050000  █████████████████░░░   85.0%    184/194 fns
0x08060000  ████████████████░░░░   80.3%    269/280 fns
0x08070000  ███████████████░░░░░   74.5%      68/79 fns
0x08080000  █████████████░░░░░░░   62.8%    156/172 fns
0x08090000  ████████████████░░░░   80.7%    264/284 fns
0x080A0000  ████████░░░░░░░░░░░░   41.4%    122/144 fns
0x080B0000  █████████░░░░░░░░░░░   44.1%    140/155 fns
0x080C0000  ███████████████░░░░░   73.7%    471/486 fns
0x080D0000  █████████████████░░░   83.4%    412/432 fns
0x080E0000  ███████████████░░░░░   76.0%    134/152 fns
0x080F0000  ███████████████░░░░░   72.6%    104/127 fns
0x08100000  █████████████░░░░░░░   64.6%     92/114 fns
0x08110000  ███████████████░░░░░   73.9%    117/137 fns
0x08120000  ████████████████░░░░   81.1%    395/414 fns
0x08130000  ██████████████░░░░░░   70.8%    417/435 fns
0x08140000  ███████████████░░░░░   76.4%    247/303 fns
0x08150000+ assets and data; 1,400 index entries
```

Library functions below `0x08150000` are included in the totals above; those at or above it are among the additional late-ROM spans.

| Unit | Range | Toolchain | Functions matched | Bytes matched |
|---|---|---|---|---|
| boot -O0 | `0x08000438`-`0x080007C8` | `agbcc-O0-v1` | 10 / 10 | 910 / 910 |
| DMA channel control -O0 | `0x08003A08`-`0x08003A6C` | `agbcc-O0-v1` | 2 / 2 | 98 / 98 |
| agb_flash FLASH512_V130 | `0x0814189C`-`0x0814220C` | `agbcc-O1-v1` | 24 / 24 | 2,406 / 2,406 |
| libgcc dp-bit | `0x08142BE8`-`0x081439C8` | `old-agbcc-O2-v1` | 20 / 20 | 3,538 / 3,538 |
| libgcc fp-bit, _cmpdi2, _lshrdi3 | `0x081439C8`-`0x081443AE` | `old-agbcc-O2-v1` | 22 / 22 | 2,514 / 2,514 |
| m4a.c (MusicPlayer2000) | `0x08145098`-`0x081465E6` | `old-agbcc-O2-v1` | 57 / 58 | 5,424 / 5,428 |
| debug monitor -fprologue-bugfix | `0x08FE1638`-`0x08FE1FF8` | `agbcc-O2-prologue-bugfix-v1` | 4 / 8 | 1,080 / 2,492 |
| Everything outside library units | | default | 5,035 / 5,464 | |

</details>

<!-- ffta-status:end -->
