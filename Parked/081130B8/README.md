# 081130B8: Parked, native proof not established

The accepted target is [0x081130B8, 0x08113220), exactly 360 bytes. One natural record-array/interpolation candidate was checked using the actual defining helper types, including the header-defined Struct08011040 and its three u16 output pointers.

The native command exited 1 with `compile failed: buffer caller requires an exact complete mapped span`. No native byte-comparison verdict, source-plausibility verdict, or native report was issued. No MATCH or stronger callee semantic claim is inferred from this refusal.

A separate raw compile diagnostic shows a 372-byte unlinked symbol with the expected eight-byte output frame. This diagnostic is not native proof and its unlinked call encodings must not be treated as linked ROM bytes. The mismatch is not artificial frame size. The actual defining signature of func_080107D4 is `void(void *, u16, u16, u16)`, while this ROM caller passes signed values directly:

- In the flagged branch the ROM sign-extends each interpolation halfword and shifts it right by six, then calls the helper. The faithful u16 declaration emits a further LSL/LSR pair for each argument, adding eight bytes.
- In the unflagged branch the ROM uses signed-halfword loads for the position arguments. The faithful u16 declaration uses unsigned-halfword loads instead, four bytes shorter in aggregate.
- The candidate also recomputes the record address before removal, adding eight bytes. Other differences include register allocation, scheduling and addition order. Thus the overall size delta is twelve bytes; it is not attributed entirely to unsigned argument conversions.

The earlier candidate evidence identified that existing caller declarations use signed argument types although the defining helper C uses u16. The current task requires retaining the defining types. No signed replacement declaration, omitted/variadic prototype, function-pointer cast, helper-source edit, or operation to suppress the required conversion was introduced. The bounded attempt is parked at this type/capability discrepancy rather than iterated to force assembly.

The current-machine receipt contains the exact 360-byte target body, raw and composite source hashes, actual helper-source hashes, and all three actual input hashes: config/functions.json, symbols/functions.txt, and config/data_symbols.json. No shared input was edited.

Native command: `python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root . 0x081130B8`, from the isolated batch3 game worktree. Only the ordinary direct Thumb BL ARM ABI boundary is claimed. The owned active source was moved here; no native report existed to move. The original source-bound receipt, refusal, and raw diagnostic remain in `state/matching-081130B8-author/` at the handover root.
