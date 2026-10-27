# 080071E8 — Parked

Target: `[0x080071E8, 0x08007234)`, 76 bytes and 31 reachable Thumb instructions.

The complete natural C candidate normalizes a signed 16-bit angle into 0..359 and returns the signed 16-bit entry from `g_table_08149568[(angle << 8) / 360]`. It uses genuine signed division and the evidence-bound table symbol; no runtime alias or literal hardcoding is present.

The default native matcher exited 1 with:

```text
compile failed:
signed quotient excludes other runtime, literal, switch and thunk profiles
```

The signed-quotient profile excludes the genuine table data relocation. This refusal occurred before the native byte comparison and plausibility checks. Native plausibility was not established, and this candidate earns zero C-match credit.

A diagnostic compile using the unchanged approved `agbcc -mthumb-interwork -O2` configuration produced one Thumb function of 76 bytes, with canonical undefined `__divsi3` and `g_table_08149568` relocations. Its 30 emitted instructions differ from the target's 31: the candidate omits `adds r1, r0, #0` immediately after the division call at target address `0x08007218`; the following index shift uses r0 directly. Alignment accounts for the equal symbol extent. Equal size is not complete byte equality, and no linked exact-match result is claimed.

Native invocation:

```sh
env PATH=/home/user/armtc/root/usr/bin:$PATH TMPDIR=/home/user/.codex-work/ffta-ulw PYTHONDONTWRITEBYTECODE=1 FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v621-matching/matching-root 0x080071E8
```

The retained native output is `/home/user/.codex-work/ffta-ulw/audio-following-v621-matching/080071E8/match-current.log`. The unmatched active source has been removed; no active match report was generated. No metadata, shared headers, runtime identities, verifier gates, or compiler flags were changed.
