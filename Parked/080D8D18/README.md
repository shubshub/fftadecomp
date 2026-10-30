080D8D18 bounded matching attempt

Accepted claim: 6525169961, lane sol-8D18.
Target: [0x080D8D18, 0x080D8D76), 94 bytes, 44 reached Thumb instructions.

One natural candidate queries the byte height for byte column/row, expands
coordinates through the defining signed-halfword 0801CA78 input/output contract,
and calls the five-input-word effect helper with mode 0 and effect 0x15.
0801CC18 uses its defining u8(u8,u8) signature. The effect helper's five-s32
compatible declaration comes from a matched caller and complete bounded entry
ABI evidence. Its historical nominal prototype is not uniquely recovered.

Native command (isolated GAME working directory):
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080D8D18

Native exit: 1. Exact refusal:
buffer callee 0x080A92E4: literal read is not an aligned word inside the function

The effect helper's PC-relative load at 0x080A93C0 references the literal at
[0x080A93F8,0x080A93FC), while its existing index ends at 0x080A93F8.
Complete bounded evidence was already retained in the candidate packet.
The assigned target's own 94-byte span is fully reached code without literals.
No shared mapping or toolkit change was made. No second C form can remove the
recorded boundary prerequisite. No native report, plausibility verdict, or byte
comparison was produced, so no byte-identical or match claim is made.

Only this genuine candidate was attempted. No native success was replayed.
Source, native log/exit, current-machine runtime, source fingerprint, exact target
bytes, and input hashes are retained under state/matching-080D8D18-author/.
