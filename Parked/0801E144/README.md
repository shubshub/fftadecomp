# 0801E144 — bounded natural C attempt

Target: `[0x0801E144, 0x0801E1B8)`, 116 bytes, 51 reachable Thumb instructions. The complete recovered behavior stores the viewport focus, computes origins aligned down to eight pixels, applies the resulting signed 16-bit offsets to the two selected background layers, and calls the viewport refresh. Incoming x/y are narrowed to unsigned 16-bit values; inset arguments are signed 16-bit values. The established named viewport state and scroll-call ABI are retained.

The final native matcher invocation exited 1: `NOT MATCHING - bytes differ`. Complete ELF extent and ordinary direct-call validation passed; the source was reported `plausible`. The compiled symbol is 116 bytes including alignment and the global-address literal. This is not an exact match and receives no match credit.

The remaining instruction difference starts at target 0x0801E162: ROM constructs -8 in r0 (`movs r0, #8; rsbs r0, r0, #0`) and copies it to r2 before the two alignment operations. The compiler constructs -8 directly in r2, omitting the copy. The subsequent arithmetic, field stores, layer loads and scroll updates otherwise retain the target register operations. The omitted two-byte instruction shifts the later calls and return, with an extra two-byte alignment word before the same trailing literal keeping the full symbol at 116 bytes. Native aligned diff reports 107/116 bytes and 42/45 instructions identical; those are aligned comparison figures, not same-offset equality or the complete target instruction count.

Direct alignment expressions, a named alignment mask, and a naturally inline coordinate-alignment helper all retained the same mask-register difference. Computing residual offsets from the stored signed origin fields instead produced a 108-byte symbol and was rejected by the extent gate. The direct-expression candidate was restored and freshly verified for this final record. No assembly, artificial volatile access, forced inlining, compiler flag changes, or inert operations were used.

Compiler: agbcc `-mthumb-interwork -O2`.
Native command, from the private matching root:

```sh
env PYTHONDONTWRITEBYTECODE=1 TMPDIR=/home/user/tmp PATH=/home/user/armtc/root/usr/bin:$PATH FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root . 0x0801E144
```

Final native output: `/home/user/.codex-work/ffta-ulw/audio-following-v457-matching/0801E144/match-current.log`.
Full target: `/home/user/.codex-work/ffta-ulw/audio-following-v457-matching/0801E144/target-disassembly.md`.
