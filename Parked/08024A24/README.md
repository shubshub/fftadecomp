# 08024A24 native model refusal

The first authorized default native command returned exit1:

```
python3 -B /home/user/Desktop/FFTA-handover-2026-10-30/repos/fftadecomp-kit/tools/match.py --root /home/user/Desktop/FFTA-handover-2026-10-30/state/resumed-matching-batch3-20261030/game-worktree 0x08024A24
compile failed:
buffer callee 0x0801B938: buffer callee 0x08141898: non-leaf calls and interrupts require linked CFG verification
```

This is a decisive native buffer-model refusal. No byte comparison, complete compiled-body extent, source-plausibility verdict or match report was emitted. The attempt is not a matching or plausibility success. There was one native attempt and no replay.

The source retains actual defining signatures for0801BDB0,0801CC18,0801C918,0801C960 and0801B938. Its three s16 coordinate outputs and two outgoing pointer slots have the natural16-byte frame supported by matched080D8BD8. Helper08025238 receives the original object inr0, and its ignored-result object-only interface was qualified by its complete236-byte ROM body. The native buffer analysis nevertheless inspects0801B938 and reaches its08141898 interrupt helper, which the default proof refuses. The semantic scalar interface alone did not prevent this native buffer-dependency path. No fake arguments, alias-clearing expressions, helper changes, profile selector, new buffers or toolkit workaround were attempted.

The native text parser and config JSON both describe the complete150-byte target08024A24..08024ABA. All69 reached instructions fill that span with no literal pool, gap, merged entry or overhang. This index qualification passed; the failure is the nested buffer/runtime verification gate.

The exact source is preserved here. The pre-native and final receipt, full native output, complete ROM bytes, raw/composite source hashes, all9header pins, actual helper-source pins, current runtime/compiler/tool pins and all3mapping hashes remain under state/matching-08024A24-author in the handover workspace. Only this owned active source was moved. No native report existed to move. Shared inputs were unchanged.
