# 08043F64 bounded native span refusal

The accepted sol-3F64 claim6526908934 authorized this one scalar updater. The candidate sets the established five-bit selection field at global+0x2E54 to18, preserving its upper three bits, then copies the field to ordinary byte+0x1F69. The local layout follows matched08043F90 and the byte field follows matched0805FFF0.

The first and only native command returned exit1 before compilation:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x08043F64
no valid indexed span for 0x08043F64
```

The pinned config/functions.json contains08043F64..08043F90. However, the pinned symbols/functions.txt has no entry with start08043F64. Native match.py lines3754..3756 takes its span from function_span using symbols/functions.txt and exits when no positive span exists. This is an exact current native-input refusal. No map or toolkit edits, alternate profile, compilation replay or further source forms were attempted.

There is no native report, compiled body, byte-comparison verdict or source-plausibility verdict. Exact compiled differences are unavailable because compilation was not reached. The44-byte body retained in the receipt is the observed ROM body, not a successful comparison.

The exact authored source is preserved here. Source/raw+composite hashes, all nine headers, current runtime/compiler/tools, three mappings, complete ROM body, command and full output are bound in ../../../../matching-08043F64-author/attempt1-receipt.json under the handover state root. The authoritative absolute receipt path is /home/user/Desktop/FFTA-handover-2026-10-30/state/matching-08043F64-author/attempt1-receipt.json. No active source or report remains for this address.
