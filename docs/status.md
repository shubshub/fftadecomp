<!-- ffta-status:start -->

## Decompilation progress

| Metric | Matched / indexed | Progress |
| :--- | ---: | :---: |
| Functions matched | 5,057 / 5,600 | **90.30%**<br><img src="/docs/badges/functions.svg" width="82" alt=""> |
| Bytes matched | 791,968 / 1,341,977 | **59.02%**<br><img src="/docs/badges/bytes.svg" width="82" alt=""> |

Each match reproduces the original ROM bytes. Byte coverage counts overlapping function spans once.

<details>
<summary>ROM regions and library units</summary>

The main index covers functions starting below `0x08150000`. Its totals can change as function boundaries are recovered.

**Additional verified late-ROM spans: 14 functions; 1,062 complete-body bytes.** These are counted separately.

[Functions badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Ffunctions.json) · [Bytes badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Fbytes.json)

Matched bytes by 64 KiB ROM region

```
0x08000000  ███████████████░░░░░   73.1%    452/494 fns
0x08010000  ██████████████░░░░░░   72.4%    399/424 fns
0x08020000  ████████████████░░░░   80.8%    372/398 fns
0x08030000  █████████░░░░░░░░░░░   46.1%    154/173 fns
0x08040000  ███████████░░░░░░░░░   52.5%    179/203 fns
0x08050000  ██████████░░░░░░░░░░   50.3%    176/194 fns
0x08060000  █████████████░░░░░░░   64.3%    266/280 fns
0x08070000  ██████░░░░░░░░░░░░░░   31.0%      57/79 fns
0x08080000  ██████████░░░░░░░░░░   51.1%    150/172 fns
0x08090000  █████████░░░░░░░░░░░   46.4%    259/284 fns
0x080A0000  ███████░░░░░░░░░░░░░   34.8%    117/144 fns
0x080B0000  ███████░░░░░░░░░░░░░   35.9%    136/155 fns
0x080C0000  █████████████░░░░░░░   67.5%    467/486 fns
0x080D0000  ███████████████░░░░░   77.0%    407/432 fns
0x080E0000  ██████████████░░░░░░   70.1%    130/152 fns
0x080F0000  ██████████████░░░░░░   67.8%    101/127 fns
0x08100000  ████████████░░░░░░░░   60.4%     90/114 fns
0x08110000  ████████████░░░░░░░░   58.8%    106/137 fns
0x08120000  ███████████████░░░░░   74.1%    390/414 fns
0x08130000  ████████████░░░░░░░░   59.5%    405/435 fns
0x08140000  ██████████████░░░░░░   71.7%    244/303 fns
0x08150000+ assets and data; 1,400 index entries
```

Library functions are included in the totals above.

| Unit | Range | Toolchain | Functions matched | Bytes matched |
|---|---|---|---|---|
| boot -O0 | `0x08000438`-`0x080007C8` | `agbcc-O0-v1` | 10 / 10 | 910 / 910 |
| DMA channel control -O0 | `0x08003A08`-`0x08003A6C` | `agbcc-O0-v1` | 2 / 2 | 98 / 98 |
| agb_flash FLASH512_V130 | `0x0814189C`-`0x0814220C` | `agbcc-O1-v1` | 24 / 24 | 2,406 / 2,406 |
| libgcc dp-bit | `0x08142BE8`-`0x081439C8` | `old-agbcc-O2-v1` | 20 / 20 | 3,538 / 3,538 |
| libgcc fp-bit, _cmpdi2, _lshrdi3 | `0x081439C8`-`0x081443AE` | `old-agbcc-O2-v1` | 22 / 22 | 2,514 / 2,514 |
| m4a.c (MusicPlayer2000) | `0x08145098`-`0x081465E6` | `old-agbcc-O2-v1` | 57 / 58 | 5,424 / 5,428 |
| Everything outside library units | | default | 4,922 / 5,464 | |

</details>

<!-- ffta-status:end -->
