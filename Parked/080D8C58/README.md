# 080D8C58: Parked, native proof not established

Target [0x080D8C58, 0x080D8CD2) is exactly 122 bytes. The candidate selection evidence proves its complete reachable span and records all four defining helper interfaces. The native checker nevertheless rejected each authored candidate with exit 1 and the exact message `compile failed: buffer caller requires an exact complete mapped span`.

No native MATCH, byte-comparison verdict, or plausibility verdict was issued, and no native report was generated. Raw compile diagnostics were captured solely to explain the extent refusal; they are not substitute proof. Unlinked BL relocations in those diagnostic objects must not be compared as linked ROM call encodings.

Three natural local-data representations were checked:

1. Two signed-halfword arrays for the two input coordinates and three intermediate outputs: 104-byte compiled symbol. The compiler uses a shared base for each array and reconstructs addresses near calls.
2. Signed two-component and three-component structures: 112-byte compiled symbol. The compiler packs the input-coordinate structure into a register and uses a 16-byte stack frame.
3. Two-coordinate signed-halfword array with three separate signed-halfword output locals: 116-byte compiled symbol. This final candidate uses a 20-byte stack frame and saves r8/r9, whereas the ROM saves r8/r9/r10. The candidate input array starts at sp+8 and its intermediate outputs at sp+12, sp+14 and sp+16; the ROM input coordinates are at sp+16/sp+18 and intermediate outputs at sp+8/sp+10/sp+12. The ROM prepares several addresses before the first call; the candidate prepares them nearer their uses.

The actual helper contracts were retained: identity `void *(void *)`, lookup `u8(u8,u8)`, three-output `void(s16,s16,s16,s16*,s16*,s16*)`, and two-output `void(s16,s16,s16,s16*,s16*)`. No artificial padding, register declarations, assembly, volatile operations, dead operations, fake helper arguments, toolkit edits, or gate bypass was used.

The native command was `python3 /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x080D8C58`, run from the isolated batch3 game worktree. Its actual functions/data-symbol input hashes and current-machine runtime are retained in receipt.json. PRIMARY's unrelated 0806406C/080640D4 mapping split was not imported into this worktree.

The three candidate sources, logs, raw assembly diagnostics, and source-bound receipts remain in `state/matching-080D8C58-author/` at the handover root. The final source has been moved out of active src after the bounded failure.
