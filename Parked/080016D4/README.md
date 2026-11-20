# 0x080016D4 — OAM list emitter

The indexed Thumb function occupies 460 bytes, from `0x080016D4` through `0x0800189F`. It clips six-byte sprite records against the screen, writes visible entries to the selected OAM shadow list, and returns the updated entry count. The last halfword of each eight-byte entry is preserved.

The accompanying ordinary C produces 424 bytes with the native agbcc compiler and `-mthumb-interwork -O2`. With the sprite dimension table mapped, the current matcher reports `compiled symbol is shorter than the indexed span: 424 < 460`. The first differing instruction is at `0x080016DE`. The ROM allocates 24 stack bytes and the candidate allocates 20.

### Attribute writes

At `0x080017DA`, `0x080017E6` and `0x080017F2`, the ROM reads the old destination halfwords at offsets 0, 2 and 4. Each load is immediately followed by a store replacing the entire halfword. At `0x080017F6` it similarly reads the old Y byte immediately before replacing it. The loaded values are discarded. The ordinary source omits these reads in the generated code.

| Source form | Linked Thumb bytes |
| --- | ---: |
| Unqualified halfword bitfields, as parked | 424 |
| Plain `u16` raw attributes | 424 |
| Plain `u16` raw attributes and two `u8` members for Y and its flags | 424 |
| `unsigned int` bitfields | 424 |
| Explicit halfword masks for X, Y, tile, priority and palette | 412 |

The first three forms produce the same linked SHA-256, `ec8638c74f4e38faa4070f9ed8c64e41e648496b057dbf6489bc0c2d5132a9a6`. The ROM SHA-256 for this function is `d883a53ce5bc4c3b4dd08bf37fddef575da1c3cae2c6d30886fbbbc9976eaac6`.

### Data mapping and archived reconstruction

The PC-relative load at `0x08001730` uses the literal at `0x08001884`, which contains `0x08149510`. Two shape bits and two size bits index 16 pairs of signed halfword dimensions there. The retail literal sits at function offset `0x1B0`. The parked object's `R_ARM_ABS32` relocation for `data_08149510` sits at `0x190`. The current game's data manifest lacks this entry. A private verification fixture added this one mapping to the current manifest.

An archived reconstruction qualifies the raw and bitfield views of the OAM destination as `volatile`. OAM list buffers reside in RAM and are copied to hardware OAM during VBlank. With both views qualified, the compiler reproduces all 460 bytes. Either qualification alone gives 448 bytes (raw view) or 452 bytes (bitfield view). With the archived prototype and confirmed dimension mapping, the current matcher reports `bytes identical`, `source IMPLAUSIBLE (not on the allow list)`, and `ERROR: volatile` on lines 11 and 17 of the archived source. Its qualified source therefore remains an archived comparison.

The archived source also includes `oam_emit.h`, which the current checkout lacks. Building it unchanged first reports `oam_emit.h: No such file or directory`. Supplying that header with the current, unchanged manifest gives `data target must be an undefined mapped object`. The parked ordinary source includes `ffta.h` and declares its own entry type. Its 424-byte result was checked with the single dimension mapping in place.
