# 0800C4B4: byte-identical; the volatile semantic check exceeds its 256-path bound

Target: `[0x0800C4B4, 0x0800C5F4)`, 320 bytes, 139 instructions. It is a scanline task built on the `ScanlineTask` layout of the matched `0800C3CC`. It picks the back buffer, compares four handles, retargets the shadow registers, and sets a bit in `g_control_flags_03000940.display`.

`0800C4B4.c` compiles byte-identical (320/320), and `plausible.py src/0800C4B4.c` exits 0. `match.py` refuses it before any selector is consulted:

```
source  IMPLAUSIBLE (not on the allow list)
  allowlisted volatile semantic check: func_0800C4B4 has more than 256 paths; the semantic check is bounded
```

The function includes `control_flags.h` for its ordinary store to `display`. That triggers the allowlisted volatile check, whose path enumeration stops at `MAX_PATHS = 256`. The function has two four-iteration loops with several branches each, so it has far more paths than that.

Tracked upstream: https://github.com/shubshub/fftadecomp-kit/issues/137
