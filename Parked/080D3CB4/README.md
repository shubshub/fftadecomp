# 080D3CB4: one bounded natural source attempt

The complete indexed Thumb target is [0x080D3CB4,0x080D3E9C), 488 bytes,
224 reached instructions. This exact unchanged source was authored under
accepted native lease 6538721283. It remains a nonmatch, with zero MATCH credit.

The single original default matcher attempt used agbcc with
`-mthumb-interwork -O2` and exited 1 after 0.308756 seconds:

```
compiled symbol is shorter than the indexed span: 476 < 488
```

No native match report was generated. The one authorized unchanged-source
compiler-only diagnostic preserved the original assembly/relocatable ELF,
linked ELF and complete 476-byte compiled symbol. Against all 488 target
bytes, 136 positions are identical at the same offset; 352 positions differ
or are absent. This is a fixed-offset comparison over the complete extent,
not an instruction-alignment score or native MATCH.

The saved assembly shows different phase dispatch, including a literal for
257. The compiler emits ordinary byte-field stores without five unused
pre-store byte loads present in ROM at 080D3D54, 080D3D5C, 080D3DC6,
080D3E08 and 080D3E82. Branch/pool placement also differs. These facts diagnose
this source form; they do not prove the owner impossible to match. No second
form, artificial discarded read, volatile field, invented bitfield or width,
register/lifetime/ordering adjustment, alternate flags or proof retry was used.

The source preserves the actual three-formal scheduler callback view,
word-zero return, observed State and packed sequence fields, six-s16
interpolation members and actual 080D3BD0/080E064C/080E0690 interfaces. The
State member offsets and source/header/input hashes are frozen before native
execution. The packed sequence view is grounded in byte-pair reads and the
same sequence's existing packed count definition, not introduced as padding.

Evidence is in state/matching-080D3CB4-author/: form01.c,
form01-before-native.json, native-result.json, native-stdout.txt,
native-stderr.txt, target.bin and compiler-diagnostic/diagnostic.json with
all exact commands, full emitted/target bytes and differences. final-receipt.json
binds the frozen source and this README. All work was isolated from PRIMARY;
no new ROM read, shared map/header/tool change or publication action occurred.

The source view and ordinary direct calls remain conditional on compatible
returning ARM ABI. No historical unique type, transitive helper equivalence,
allocation/readability, initialization, effects, numeric, memory-safety or
universal termination theorem is asserted. Lease release and integration are
owned by the parent session. No active source or match report is retained.
