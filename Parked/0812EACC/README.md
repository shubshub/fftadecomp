# 0812EACC native stack-alias refusal

Target: complete [0x0812EACC,0x0812EB4C),128 bytes. Accepted request6526304423, author sol-EACC.

The preserved source uses the actual defining helper Unit layout and u16 func_0812EA44(const Unit*,const Unit*,u16) interface. It snapshots all four original byteF6/F7 fields before replacement stores, calls the helper using the identifier, narrows the result, restores fields in observed order, and returns the result. Seven incoming formal arguments are evidenced by the complete target ROM. The four snapshots preserve alias behavior.

The sole native run exited1 with this exact refusal:

```
compile failed:
stack alias arithmetic leaves the tracked frame
```

No native comparison, source-plausibility verdict, complete compiled body or match report was produced. No MATCH is claimed.

The native guard in tools/match.py:2093..2108 accepts a computed stack-alias offset only within[-4*depth,0]. In the target ROM, the address for the seventh incoming byte argument is computed by add r3,sp,#0x34 at0812EB14, then read with LDRB at0812EB16. After0x2C bytes of saved registers/local allocation, this is entrySP+8, outside the local-frame interval. This is static evidence of the relevant model boundary; the refusal output does not expose compiled bytes or establish which exact candidate instruction raised it.

The default-profile command was:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x0812EACC
```

Full output and the receipt are retained at:

/home/user/Desktop/FFTA-handover-2026-10-30/state/matching-0812EACC-author/attempt1-native.log
/home/user/Desktop/FFTA-handover-2026-10-30/state/matching-0812EACC-author/attempt1-receipt.json

Before the native run, the receipt was written with current-machine runtime, complete source text, raw/composite source hashes, all9 header pins,3 mapping pins, exact128-byte ROM body, tool pins and command. The receipt now identifies this preserved source path. Existing helper C/report/full-ROM evidence remains in the batch34 candidate capsule.

Stopped immediately after the first precise native gate. No alternate source form, ABI change, frame padding, profile/toolkit edit or proof replay was attempted. Only this address-owned active source was moved here; no native report existed.
