<!-- ffta-status:start -->

## Decompilation progress

| Metric | Matched / indexed | Progress |
| :--- | ---: | :---: |
| Functions matched | 5,123 / 5,600 | **91.48%**<br><img src="/docs/badges/functions.svg" width="82" alt=""> |
| Bytes matched | 874,794 / 1,341,977 | **65.19%**<br><img src="/docs/badges/bytes.svg" width="82" alt=""> |

Each match reproduces the original ROM bytes. Byte coverage counts overlapping function spans once.

<details>
<summary>ROM regions and library units</summary>

The main index covers functions starting below `0x08150000`. Its totals can change as function boundaries are recovered.

**Additional verified late-ROM spans: 17 functions; 2,194 complete-body bytes.** These are counted separately.

[Functions badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Ffunctions.json) · [Bytes badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Fbytes.json)

Matched bytes by 64 KiB ROM region

```
0x08000000  ███████████████░░░░░   76.9%    456/494 fns
0x08010000  ███████████████░░░░░   75.4%    400/424 fns
0x08020000  ████████████████░░░░   81.5%    374/398 fns
0x08030000  ██████████░░░░░░░░░░   51.1%    159/173 fns
0x08040000  ████████████░░░░░░░░   58.7%    181/203 fns
0x08050000  ███████████████░░░░░   76.3%    183/194 fns
0x08060000  █████████████░░░░░░░   65.8%    267/280 fns
0x08070000  ███████░░░░░░░░░░░░░   33.2%      59/79 fns
0x08080000  ███████████░░░░░░░░░   57.2%    154/172 fns
0x08090000  ███████████████░░░░░   74.2%    262/284 fns
0x080A0000  ████████░░░░░░░░░░░░   37.8%    119/144 fns
0x080B0000  ████████░░░░░░░░░░░░   37.6%    137/155 fns
0x080C0000  ██████████████░░░░░░   70.5%    469/486 fns
0x080D0000  ████████████████░░░░   81.2%    411/432 fns
0x080E0000  ███████████████░░░░░   73.5%    132/152 fns
0x080F0000  ██████████████░░░░░░   71.2%    103/127 fns
0x08100000  █████████████░░░░░░░   64.6%     92/114 fns
0x08110000  ██████████████░░░░░░   69.8%    113/137 fns
0x08120000  ████████████████░░░░   79.9%    393/414 fns
0x08130000  █████████████░░░░░░░   64.1%    414/435 fns
0x08140000  ██████████████░░░░░░   72.1%    245/303 fns
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
| Everything outside library units | | default | 4,988 / 5,464 | |

</details>

<!-- ffta-status:end -->
