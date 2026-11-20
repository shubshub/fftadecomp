# 0804DF08 menu blend update

**Parked.** The complete retail symbol and the recovered Thumb ELF function each occupy 254 bytes, spanning `[0x0804DF08, 0x0804E006)`. With original agbcc `-mthumb-interwork -O2` and the original relocations, 213 of 254 bytes agree at the same offsets. The first differing byte is at `0x0804DF1B`. Retail SHA-256 is `b24635a88913594c24b5dd3739948d6149ae697d4cfa2eb3f4a56667981b119d`. The candidate hash is `a48646ec896d2b372c282f4ca021026076556a6f249dbf972ab3bbebba761563`.

The no-argument function gets the menu blend state through `0804CAB0`. Two signed 16-bit key times bracket the signed cursor. Inside the half-open interval, two calls to the retail signed divide helper interpolate the alpha bytes in the existing display shadow. Outside the interval the routine selects the second key directly. Every call increments the 16-bit cursor. The return is zero for interpolation and one for the terminal key. Caller `0804D86C` consumes the low byte. This supports a `u8` declaration, although the native return values are also compatible with wider scalar declarations.

Retail keeps the frame index in R2 and the next-record byte offset in R4. At `0804DF3C` it computes the current address with the index shifted left by two. The candidate instead carries an advancing record pointer through the loop. This also changes register assignments in the blend calculation. Both ELF functions have the same call sites, shadow literals and return boundary. The two bytes of alignment after the return are outside the symbol.

The native tests execute the real scene allocator and initializer, menu dispatcher, state accessor and signed divide helper. Only BIOS services use the kit's existing software model. The fixture supplies writable layer backing storage. States 6 and 7 initialize opposite 12-tick fades. States 3 and 4 each run 13 times and advance to 5 and 8 respectively. Twelve additional cases check inclusive and exclusive bounds, equal and reversed keys, negative and wrapped 16-bit interpolation operands, both coefficient directions, signed rounding and cursor wraparound. The tests check the two divide operands, both shadow values, preserved key records, cursor, stack and callee-saved registers. Both the unmodified ROM and the linked candidate passed.

To replay in an isolated game root, place the C file at `src/0804DF08.c`. Set `FFTA_MENU_BLEND_ROOT` to that root, `FFTA_KIT` to the kit directory, and `TMPDIR` to disk-backed scratch. Run the following from this directory.

```sh
PYTHONDONTWRITEBYTECODE=1 python3 -B test_menu_blend.py -v
FFTA_MENU_BLEND_CANDIDATE=1 PYTHONDONTWRITEBYTECODE=1 python3 -B test_menu_blend.py -v
PYTHONDONTWRITEBYTECODE=1 python3 -B "$FFTA_KIT/tools/match.py" --root "$FFTA_MENU_BLEND_ROOT" --addressed-signed-runtime-profile compiler-signed-runtime-data-v1 0804DF08
```

The exact matcher exits 1 with `inert-spin complete body differs from ROM`. No match credit or kit change is claimed.
