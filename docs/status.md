<!-- ffta-status:start -->

## Decompilation progress

| Metric | Matched / indexed | Progress |
| :--- | ---: | :---: |
| Functions matched | 4,994 / 5,600 | **89.18%**<br><img src="/docs/badges/functions.svg" width="82" alt=""> |
| Bytes matched | 756,780 / 1,341,977 | **56.39%**<br><img src="/docs/badges/bytes.svg" width="82" alt=""> |

Each match reproduces the original ROM bytes. Byte coverage counts overlapping function spans once.

<details>
<summary>ROM regions and library units</summary>

The main index covers functions starting below `0x08150000`. Its totals can change as function boundaries are recovered.

**Additional verified late-ROM spans: 12 functions; 512 complete-body bytes.** These are counted separately.

[Functions badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Ffunctions.json) · [Bytes badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Fbytes.json)

Matched bytes by 64 KiB ROM region

```
0x08000000  ███████████████░░░░░   72.6%    439/494 fns
0x08010000  ██████████████░░░░░░   71.5%    396/424 fns
0x08020000  ███████████████░░░░░   77.4%    367/398 fns
0x08030000  █████████░░░░░░░░░░░   42.7%    152/173 fns
0x08040000  ██████████░░░░░░░░░░   52.2%    177/203 fns
0x08050000  ██████████░░░░░░░░░░   48.9%    174/194 fns
0x08060000  █████████████░░░░░░░   63.5%    264/280 fns
0x08070000  ██████░░░░░░░░░░░░░░   28.3%      55/79 fns
0x08080000  █████████░░░░░░░░░░░   45.6%    146/172 fns
0x08090000  ████████░░░░░░░░░░░░   39.2%    253/284 fns
0x080A0000  ██████░░░░░░░░░░░░░░   30.8%    115/144 fns
0x080B0000  ███████░░░░░░░░░░░░░   32.5%    134/155 fns
0x080C0000  ████████████░░░░░░░░   62.3%    463/486 fns
0x080D0000  ███████████████░░░░░   77.0%    407/432 fns
0x080E0000  ██████████████░░░░░░   67.7%    128/152 fns
0x080F0000  █████████████░░░░░░░   63.8%     99/127 fns
0x08100000  ████████████░░░░░░░░   60.4%     90/114 fns
0x08110000  ███████████░░░░░░░░░   52.7%    101/137 fns
0x08120000  ██████████████░░░░░░   72.2%    388/414 fns
0x08130000  ████████████░░░░░░░░   58.5%    402/435 fns
0x08140000  ██████████████░░░░░░   71.7%    244/303 fns
0x08150000+ assets and data; 1,399 index entries
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
| Everything outside library units | | default | 4,859 / 5,464 | |

</details>

<!-- ffta-status:end -->
