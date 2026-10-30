# 0808118C: bounded natural forms remain shorter than the target

Complete indexed target: [0x0808118C, 0x080812E8), 348 bytes and 160 reached
instructions. The retained native structural partition is 326 code bytes,
20 referenced literal bytes and two alignment bytes, with no second entry.

Three natural source forms were checked with the exact native command:

1. Direct rendering calls with a u16 helper-result y base and subsequent
   coordinate arithmetic in the call arguments: 336 bytes.
2. Complete signed32 second-draw y coordinate calculated before rendering
   arguments: 336 bytes.
3. Local inline drawing helper, with mode checks and counter update in its
   caller: 336 bytes.

All three native runs exited 1 at the shorter-symbol gate: 336 < 348.
No match report was generated. No complete source-plausibility or byte-match
verdict is claimed. The final attempted source is retained here unchanged.

The second-form diagnostic assembly has the observed second-draw y-before-x
calculation order and actual helper argument widths. The ROM additionally
preserves r8, copies the incoming record pointer into it, uses that preserved
pointer for the final counter update, and restores r8 on return. The attempted
forms retain the incoming pointer in r5. The missing save/copy/restore and final
pointer transfer account for the 12-byte size gap. Exact native-byte identity
is not claimed for diagnostic unlinked objects.

The actual defining 11-argument renderer signature is used, including byte
flags/mode and pointer source/transform. Actual 08017FC4 C establishes the
u16 result and record prefix. Existing matched 08081078 supplies the mapped
0x4C render-record layout and coordinate arithmetic. No shared inputs,
prototype widths, extra formal arguments or artificial source operations were
changed to force allocation.

All three source snapshots, native failures, current-machine input pins and
two failed-candidate diagnostic assemblies/objects remain in
state/matching-0808118C-author under the handover root. There were three native
match checks, two diagnostic compilations, zero successes and zero replays.
The source-bound failure receipt is retained there as receipt.json.
