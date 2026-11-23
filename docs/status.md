<!-- ffta-status:start -->

## Decompilation progress

| Metric | Matched / indexed | Progress |
| :--- | ---: | :---: |
| Functions matched | 5,131 / 5,600 | **91.62%**<br><img src="/docs/badges/functions.svg" width="82" alt=""> |
| Bytes matched | 878,212 / 1,341,977 | **65.44%**<br><img src="/docs/badges/bytes.svg" width="82" alt=""> |

Each match reproduces the original ROM bytes. Byte coverage counts overlapping function spans once.

<details>
<summary>ROM regions and library units</summary>

The main index covers functions starting below `0x08150000`. Its totals can change as function boundaries are recovered.

**Additional verified late-ROM spans: 20 functions; 2,472 complete-body bytes.** These are counted separately.

[Functions badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Ffunctions.json) · [Bytes badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Fbytes.json)

Matched bytes by 64 KiB ROM region

```
0x08000000  ███████████████░░░░░   77.1%    457/494 fns
0x08010000  ███████████████░░░░░   75.4%    400/424 fns
0x08020000  ████████████████░░░░   82.0%    375/398 fns
0x08030000  ██████████░░░░░░░░░░   51.1%    159/173 fns
0x08040000  ████████████░░░░░░░░   60.9%    183/203 fns
0x08050000  ███████████████░░░░░   76.3%    183/194 fns
0x08060000  █████████████░░░░░░░   65.8%    267/280 fns
0x08070000  ███████░░░░░░░░░░░░░   33.2%      59/79 fns
0x08080000  ████████████░░░░░░░░   57.7%    155/172 fns
0x08090000  ███████████████░░░░░   74.2%    262/284 fns
0x080A0000  ████████░░░░░░░░░░░░   37.8%    119/144 fns
0x080B0000  ████████░░░░░░░░░░░░   37.6%    137/155 fns
0x080C0000  ██████████████░░░░░░   71.1%    470/486 fns
0x080D0000  ████████████████░░░░   81.2%    411/432 fns
0x080E0000  ███████████████░░░░░   73.5%    132/152 fns
0x080F0000  ██████████████░░░░░░   71.2%    103/127 fns
0x08100000  █████████████░░░░░░░   64.6%     92/114 fns
0x08110000  ██████████████░░░░░░   69.8%    113/137 fns
0x08120000  ████████████████░░░░   81.1%    395/414 fns
0x08130000  █████████████░░░░░░░   64.1%    414/435 fns
0x08140000  ██████████████░░░░░░   72.1%    245/303 fns
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
| Everything outside library units | | default | 4,996 / 5,464 | |

</details>

<!-- ffta-status:end -->
