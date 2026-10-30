# 0803652C bounded unmatched result

The complete target is 88 bytes at [0x0803652C, 0x08036584): 38 reached
instructions, 80 code bytes and eight referenced literal bytes. Three grounded
natural forms were attempted under the accepted lease; none matched. The final
source is parked here. No natural-C impossibility or unsupported-selector claim
is made.

The root keeps one selected six-byte record pointer across four helper calls.
Each nonzero helper result updates that same record's low-five-bit field,
preserving its high three bits. The actual void(u8) root and the defining
helper signatures were retained in all forms.

Form 1 used the defining helper's packed record type and a direct global member
address. Normal native matching exited 1: compiled symbol 80 < indexed 88.
The one authorized unchanged-source compiler diagnostic confirmed 80 bytes and
showed a single folded g_state_02000000+0x2E36 literal. Its packed bitfield store
already matched the target's mask/read/modify/write sequence, so no bitfield
type change was made.

Form 2 used the actual defining helper's local named-state pointer view and
initialized the loop counter before selecting the cached record. Normal native
matching found a plausible complete 88-byte symbol, but it was NOT MATCHING.
The remaining difference is two pointer-construction instructions: compiled
loads the numeric offset then adds it before the named base; the ROM adds the
named base first and then loads/adds the numeric offset. The exact absolute
byte differences are listed in the final receipt. The native aligned summary
was 36/38 instructions, 85/88 bytes; that summary is not an absolute-address
Hamming byte count. Its exact source remains in the owned state attempt2.c,
and its source-bound NOT MATCHING report is attempt2-native-report.md here.

Form 3, retained as 0803652C.c here, used the same global's byte-array view
already present in 080363C0.c and the actual packed six-byte record, computing
the observed base + index*record-size + field-offset address. Normal native
matching again exited 1: compiled symbol 80 < indexed 88. No second diagnostic
was run; its complete compiled bytes are unavailable. The former docs report
was left over from form 2, not generated for form 3. A separate binding note
corrects the captured attempt3 run's report field explicitly.

Final evidence: state/matching-0803652C-author/final-unmatched.json.
Three normal native executions, one authorized compiler-only diagnostic,
zero successful proof replays and zero MATCH credit. No further form is
licensed or required. The parent owns reservation release and integration.
