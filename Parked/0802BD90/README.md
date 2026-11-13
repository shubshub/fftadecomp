# 0802BD90: byte-identical; unsigned div/mod by 10 with `_call_via_r3` callbacks has no selector

Target: `[0x0802BD90, 0x0802BE40)`, 176 bytes. It splits a value into tens and units with `/ 10u` and `% 10u` (`__udivsi3`, `__umodsi3`), places the two digit tiles through callbacks from `data_0836D4BC` (three `_call_via_r3` calls, with the table address held in r7), and queues the result with `func_0802BA08` and `func_08000ADC`.

`0802BD90.c` compiles to the ROM's instructions, registers and literal pool exactly. It was hand-linked, and all eight `bl` relocations name the ROM's callees. `plausible.py` reports nothing. Refusals:

- default: `unsigned remainder excludes other runtime, switch, function and thunk profiles`;
- `canonical-thunks-v1`: `division runtime requires its versioned proof profile`;
- `unsigned-divmod-ten-v1`: `data target must be an undefined mapped object`;
- `addressed-unsigned-runtime-data-v1` (explicit calls): `function-address evidence does not support runtime call thunks`;
- `addressed-signed-runtime-r3-callback-data-v1`: `function address requires a canonical addressed function`;
- `canonical-integer-scalar-data-source-v1`: `six-word integer source requires canonical integer calls and zero-addend named objects`;
- `bounded-buffer-conditional-thunks-v1`: `function address requires a canonical addressed function`.

Sibling `0802BC7C` has the same shape. Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/134
