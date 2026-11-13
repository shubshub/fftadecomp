# 0802BC7C: byte-identical; unsigned div/mod by 10 with `_call_via_r2`/`_call_via_r3` callbacks has no selector

Target: `[0x0802BC7C, 0x0802BD44)`, 200 bytes. This is the same digit-tile routine as `0802BD90`. It uses `__udivsi3` and `__umodsi3` on `value / 10u` and `value % 10u`, callbacks through `g_callbacks_0836D4B8` and `data_0836D4BC` (`_call_via_r2` and `_call_via_r3`), and named data `data_0200F440`.

`0802BC7C.c` was linked with the callees and data at their ROM addresses, and all 200 bytes match. `plausible.py --strict` reports nothing. Refusals:

- default: `unsigned remainder excludes other runtime, switch, function and thunk profiles`;
- `unsigned-divmod-ten-v1`: `data target must be an undefined mapped object`;
- `canonical-thunks-v1` and `umod48-r1-thunks-v1`: `division runtime requires its versioned proof profile`;
- `restoring-owner-runtime-v1`, `bounded-buffer-conditional-thunks-v1`: `function address requires a canonical addressed function`;
- explicit runtime and thunk calls under `addressed-unsigned-runtime-data-v1`: `function-address evidence does not support runtime call thunks`.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/134
