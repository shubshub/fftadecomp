# 080570D8 roster window setup

The indexed Thumb function spans `[0x080570D8, 0x08057270)`, with 408 bytes and 146 reached instructions. Three direct calls reach it at `0x080564B2`, `0x08056666`, and `0x08056762`.

The roster producer `0805459C` filters 24 slots into the entries at state offset `0x2D3A` and returns their count. This setup stores the count at `0x2D52` before filling the list buffer. It starts rendering at the halfword position reloaded from list offset `0x1A`. Both drawing calls receive mode 1. The matched `08055C38` uses a different producer after the fill and passes mode 0. Both use the mapped character memory and the callbacks `08017E80` and `08017F04`.

Using `agbcc -mthumb-interwork -O2` and the native typed function and data relocations, the candidate links to the original 408-byte extent. At identical offsets 403 bytes match. All five differences exchange `r8` and `r9` between the first argument and the count-field offset. They occur at `080570E8`, `080570FA`, `080570FC`, `0805713E`, and `0805714C`. All branches, calls, literal pool words, and padding match. The original SHA-256 is `1acce5df8eb5ea9e11dc8105d495dceaf468c07e4b8d64fb2dd6b945c1b675c8`. The linked candidate SHA-256 is `7c39658ae29e482bbb840601b759fdeb2fc350ccc4c36aa00b82d1baf57684e0`.

The source passes the plausibility check. The twin’s `addressed-native-bios-fill-function-literals-data-v1` profile refuses the complete-body difference. The candidate has no match report.
