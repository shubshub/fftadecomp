# Cartridge notes

The USA and Australia release is a 16 MiB Game Pak with game code `AFXE`. Its SHA-1 is `4ac05441f4de70a4ec3dd932116346c61b8783d9`. The cartridge header occupies the first 192 bytes. Its stored complement at `0x080000BD` and the complement calculated from the header are both `0x89`.

## Code copied to RAM

Most indexed code lies below `0x08150000`. Some routines live much later in the ROM. At startup, the game calls BIOS CpuSet to copy 88 halfwords from `0x08A38A2C` to `0x03005E78`. Within that 176-byte image are three Thumb functions and four bytes of alignment.

| Original ROM address | Address in RAM | Function size |
| :--- | :--- | ---: |
| [`0x08A38A2C`](match/08A38A2C.md) | `0x03005E78` | 50 bytes |
| [`0x08A38A60`](match/08A38A60.md) | `0x03005EAC` | 60 bytes |
| [`0x08A38A9C`](match/08A38A9C.md) | `0x03005EE8` | 62 bytes |

Each function earns credit once, at its ROM address. The [installer report](match/08002768.md) records the copy. The [startup notes](startup-ownership.md) trace the code that runs before the main loop.
