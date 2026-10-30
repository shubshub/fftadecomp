# 08062E1C bounded matching attempt

Status: Parked, plausible C, NOT MATCHING. Accepted lane sol-2E1C, claim 6524707462.

The retained best candidate is attempt 3. Native verification accepted the complete 444-byte ELF symbol and plausible C. It matched 439/444 bytes and 200/205 instructions. The only differing instructions are the five byte-assembly operations at 08062F3E through 08062F46:

| Address | Target | Compiled |
| --- | --- | --- |
| 08062F3E | ldrb r2, [r0] | ldrb r2, [r0, #1] |
| 08062F40 | ldrb r0, [r0, #1] | ands r4, r2 |
| 08062F42 | ands r0, r4 | lsls r4, r4, #8 |
| 08062F44 | lsls r0, r0, #8 | ldrb r0, [r0] |
| 08062F46 | orrs r0, r2 | orrs r0, r4 |

Both forms compute the observed low byte plus two high bits. No forced register allocation, volatile, inline assembly, pragmas, dead operations, or extra formal parameters were introduced.

Four bounded natural candidates were checked. Attempt 1 used the initial pointer lifetimes and emitted 448 bytes (416/448 bytes identical). Attempt 2 changed state snapshots and used explicit byte locals; the native extent gate refused its 436-byte symbol. One diagnostic compilation of that failed candidate retained its assembly. Attempt 3 separated the metadata snapshot and retained direct byte assembly, yielding the best exact-extent result. Attempt 4 made low/high reads explicit while keeping the snapshots; register allocation and alignment yielded 448 bytes (429/448 identical). No successful check was replayed.

The local void func_08066018(void *object) declaration follows complete 14-byte callee and 4-byte transitive helper ROM dataflow, plus genuine existing callers. The legacy defining C omits the genuinely consumed input. That discrepancy and the full evidence remain in the candidate checkpoint. No helper was edited or replayed. The func_08066114 declaration retains its actual u32 return type, cast only for the caller's observed address-valued use. Native direct-call reasoning remains conditional on ordinary ARM ABI preservation and return, without proving callee semantics or termination.

The exact active owned source and generated report were removed from src/docs and retained here. All attempts, native logs, generated reports, complete target bytes, current runtime and source-bound hashes are retained in state/matching-08062E1C-author/final-receipt.json. The parent owns release and further integration. No Git, broker, shared maps, headers, toolkit or primary source changes were made.
