# ![Final Fantasy Tactics Advance decompilation](docs/clan-crest.svg)

A matching C decompilation of **Final Fantasy Tactics Advance** for the Game Boy Advance. Each recovered function is compiled and compared byte for byte with the USA and Australia cartridge.

[Build the project](#build-the-project) · [Match a function](#match-a-function) · [Source map](docs/modules.md) · [Cartridge notes](docs/cartridge.md)

<!-- ffta-status:start -->

## Decompilation progress

| Metric | Matched / indexed | Progress |
| :--- | ---: | :---: |
| Functions matched | 5,249 / 5,600 | **93.73%**<br><img src="/docs/badges/functions.svg" width="82" alt=""> |
| Bytes matched | 1,031,024 / 1,341,981 | **76.83%**<br><img src="/docs/badges/bytes.svg" width="82" alt=""> |

Each match reproduces the original ROM bytes. Byte coverage counts overlapping function spans once.

<details>
<summary>ROM regions and library units</summary>

The main index covers functions starting below `0x08150000`. Its totals can change as function boundaries are recovered.

**Additional verified late-ROM spans: 21 functions; 3,236 complete-body bytes.** These are counted separately.

[Functions badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Ffunctions.json) · [Bytes badge](https://img.shields.io/endpoint?url=https%3A%2F%2Fraw.githubusercontent.com%2Fshubshub%2Ffftadecomp%2Fbadges%2Fbytes.json)

Matched bytes by 64 KiB ROM region

```
0x08000000  ████████████████░░░░   82.4%    468/494 fns
0x08010000  █████████████████░░░   85.4%    406/424 fns
0x08020000  ██████████████████░░   90.6%    381/398 fns
0x08030000  ██████████████░░░░░░   69.2%    163/173 fns
0x08040000  █████████████░░░░░░░   66.0%    189/203 fns
0x08050000  █████████████████░░░   87.1%    185/194 fns
0x08060000  ████████████████░░░░   81.4%    271/280 fns
0x08070000  ███████████████░░░░░   77.0%      69/79 fns
0x08080000  █████████████░░░░░░░   63.9%    157/172 fns
0x08090000  ████████████████░░░░   82.4%    269/284 fns
0x080A0000  ██████████░░░░░░░░░░   52.2%    125/144 fns
0x080B0000  ███████████░░░░░░░░░   56.2%    142/155 fns
0x080C0000  ████████████████░░░░   78.8%    473/486 fns
0x080D0000  █████████████████░░░   83.9%    414/432 fns
0x080E0000  ████████████████░░░░   79.3%    136/152 fns
0x080F0000  ███████████████░░░░░   75.9%    107/127 fns
0x08100000  ██████████████░░░░░░   71.2%     98/114 fns
0x08110000  █████████████████░░░   84.5%    125/137 fns
0x08120000  ██████████████████░░   89.4%    402/414 fns
0x08130000  ████████████████░░░░   78.6%    420/435 fns
0x08140000  ████████████████░░░░   79.6%    249/303 fns
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
| Everything outside library units | | default | 5,114 / 5,464 | |

</details>

<!-- ffta-status:end -->

## Build the project

Clone the game and its toolkit side by side. You'll need Python 3, Make, Capstone, and your own copy of the game.

```sh
git clone https://github.com/shubshub/fftadecomp.git
git clone https://github.com/shubshub/fftadecomp-kit.git
cd fftadecomp
python3 -m pip install capstone
```

Place your ROM in the project root as `baserom.bin`, then run `make split check`. This splits the ROM using the tracked index, rebuilds it, and checks that every byte agrees.

| Cartridge | Size | SHA-1 |
| :--- | ---: | :--- |
| USA / Australia · `AFXE` | 16 MiB | `4ac05441f4de70a4ec3dd932116346c61b8783d9` |

## Match a function

1. Set up [agbcc and the ARM toolchain](docs/toolchain.md). Try `make match ADDR=0x08017514` to reproduce an existing match.
2. Pick an open address from the [function index](symbols/functions.txt). Check and claim it with the [reservation tool](https://github.com/shubshub/fftadecomp-kit/blob/main/AGENTS.md) before writing C.
3. Run the match command with the address you claimed. A byte-identical function goes in [src](src/) with its [match report](docs/match/). Keep partial recoveries and notes in [Parked](Parked/), then release the address.

The [contributor guide](AGENTS.md) covers source placement and the publication checks. The [module map](docs/modules.md) groups recovered code by the game state it uses.
