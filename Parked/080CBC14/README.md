# 080CBC14 — Parked

Target: `[0x080CBC14, 0x080CBC92)`, 126 bytes and 52 reachable Thumb instructions.

One complete natural C candidate was reconstructed and tested once with the native matcher. The incoming category is unsigned 8-bit and item is unsigned 16-bit. A typed 32-byte item entry supplies flags at offset 12, base value at offset 4, and minimum at offset 6. If flag 8 is set, the adjustment is read from byte 8 of a genuine 10-byte table row selected by state byte 0x21B4. The existing typed `func_080CC958(u8, u16)` predicate optionally adds 10 to that byte with unsigned 8-bit narrowing. Natural signed C multiplication/division computes `base * (100 - reduction) / 100`. The result is converted to the unsigned return-value local before the minimum comparison, preserving the ROM's unsigned comparison. If flag 8 is clear, the base value is used directly; a final zero becomes 1.

The source uses evidence-bound `g_table_0851D180`, `data_08527E62`, and `g_state_02000000` data symbols, the real indexed direct callee, and compiler-generated canonical `__divsi3`. No hardcoded address or runtime alias replaces a binding.

The single default native matcher invocation exited 1:

```text
compile failed:
signed quotient excludes other runtime, literal, switch and thunk profiles
```

The supported signed-quotient profile excludes this genuine data-relocation combination. The refusal precedes native byte comparison and plausibility. Native plausibility is unproved and this candidate earns zero C-match credit. No verifier or metadata changes were made to bypass the refusal.

A diagnostic compile with the unchanged approved `agbcc -mthumb-interwork -O2` produced a sole Thumb function of 126 bytes and 52 emitted instructions, with undefined `__divsi3`, the real indexed `func_080CC958`, and the three genuine data symbols. The observed item and adjustment-table strides are 32 and 10 bytes as required. Equal extent and instruction count do not establish byte equality: the target initially loads the item-table base into r1, shifts the item index into r0, then adds them; the candidate shifts the index into r1, loads the base into r0, then adds them. No full linked exact result is claimed. No further candidate was attempted after the profile refusal.

Native invocation:

```sh
env FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' TMPDIR=/home/user/.codex-work/ffta-ulw PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v622-matching/matching-root 0x080CBC14
```

Native output is retained at `/home/user/.codex-work/ffta-ulw/audio-following-v622-matching/080CBC14/match-current.log`. Unmatched active C/report are absent. Diagnostic intermediate, assembly and object files were removed after recording the extent. Shared headers/maps, runtime identities and compiler flags remain untouched.
