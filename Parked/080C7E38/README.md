080C7E38 native proof refusal

Accepted claim 6525824034, lane sol-7E38.
Target: [0x080C7E38,0x080C7E68), exact 48 bytes of reached Thumb code.
Actual instruction count is 23; old index count24 includes the two halfwords
of the four-byte BL as separate instructions. The extent itself is complete.

One ordinary candidate uses the defining helper's actual contract:
void func_080C7B78(const Pair *source,u32 *second,u32 *first)
Pair has u32 words at0 and4. Two genuine u32 output locals are supplied,
with the observed second-word sentinel initialized to0xFFFFFFFF.
After the call, selection word0 is compared with that output; mismatch returns1,
otherwise the input pointer is stored at selection+4 and the function returns0.
No output-pointer casts, fake formals, replacement helper arithmetic or
invented field semantics were used.

Exactly one native command was run:
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x080C7E38

Native exit:1. Exact refusal:
local stack pointer escapes through a return register

The caller source returns only0 or1; the native verifier did not discharge its
stack-alias return condition. This records the verifier refusal and does not
assert a specific internal root cause or weaken that gate. No native report,
plausibility verdict, or byte comparison was produced. Therefore the candidate
has no MATCH credit and its compiled extent/bytes remain unverified here.

The explicit instruction was to stop at a precise unsupported gate. No second
source form, native replay, compiler diagnostic, toolkit/profile/map change or
helper C was attempted. Active owned C was moved to this directory. Original
command/output, current runtime, all nine headers, three map hashes, raw and
composite source fingerprints, actual helper contract evidence and exact
whole-target body are retained in state/matching-080C7E38-author/result.json.

Parent owns release and integration.
