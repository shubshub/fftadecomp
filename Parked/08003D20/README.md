# 08003D20 — Parked

Target: `[0x08003D20, 0x08003D9A)`, 122 bytes and 58 reachable Thumb instructions.

The complete natural C candidate checks the evidence-bound `data_030028A0` state: the 16-bit status at offset 0x124 must be 0x101 and mode at offset 2 must be 3. It updates the low status byte to 2, stores the incoming source and destination pointers at offsets 0x144 and 0x148, computes signed `(length + 5) / 6` into the halfword at 0x130, stores length at 0x138, clears the halfwords at 0x134 and 0x12C, and sets the low status byte to 5. Failure returns 0 and success returns 1. The status byte access uses the permitted unsigned-character alias of the real 16-bit object; no fake data or function alias is present.

One natural candidate and one default native invocation were tested. The matcher exited 1 with:

```text
compile failed:
signed quotient excludes other runtime, literal, switch and thunk profiles
```

The native signed-quotient profile excludes the genuine data relocation. The refusal happened before native byte comparison and plausibility. Native plausibility was not established; zero C-match credit is claimed. The existing gate was honored without runtime aliases, hardcoded addresses, metadata edits, or verifier changes.

A diagnostic compile with unchanged approved `agbcc -mthumb-interwork -O2` produced a sole Thumb function of 110 bytes and 52 emitted instructions, with canonical undefined `__divsi3` and genuine `data_030028A0` relocations. All reconstructed field offsets match the observed accesses. The candidate is 12 bytes and six instructions shorter than the target. It keeps zero in a low register after division instead of saving zero in r8 before division; the target additionally preserves r8 in its prologue/epilogue and transfers that zero back for the clear stores. Low-register allocation and some address-generation scheduling also differ. No complete linked byte equality is claimed, and no additional natural candidates were attempted after the supported-profile refusal.

Native invocation:

```sh
env FFTA_ROM='/home/user/Downloads/Final Fantasy Tactics Advance (USA, Australia).gba' TMPDIR=/home/user/.codex-work/ffta-ulw PATH=/home/user/armtc/root/usr/bin:$PATH PYTHONDONTWRITEBYTECODE=1 python /home/user/Documents/Claude_Chats/2026-10-09/fftadecomp-kit/tools/match.py --root /home/user/.codex-work/ffta-ulw/audio-following-v621-matching/matching-root 0x08003D20
```

Native output is retained at `/home/user/.codex-work/ffta-ulw/audio-following-v621-matching/08003D20/match-current.log`. Unmatched active source/report are absent. The diagnostic intermediate, assembly and object were removed after recording the extent. Shared headers, maps, compiler flags and runtime identities were not changed.
