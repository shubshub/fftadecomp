# 080CC3C8 bounded unsuccessful match

One natural packed-field getter source form was authored under accepted native claim 6536294203 (sol-C3C8). The first and only default native check exited 1:

```
compile failed:
switch caller requires an exact mapped Thumb span
```

The unchanged-source compiler-only diagnostic used the same default cpp, agbcc, assembler and linker flags with the existing named object binding. It emitted a 358-byte function symbol; the target is 326 bytes, so this source is 32 bytes too long. Linked .text is 360 bytes including trailing alignment. The first byte difference is at offset 8. This is a compiled extent mismatch; this attempt does not establish a proof-model refusal or a MATCH.

The emitted assembly additionally computes byte offsets by adding constants to the table base before adding the record offset, while the saved target uses a common record address and immediate byte-load offsets. The emitted source uses mask instructions and shared mask tails where the target uses paired shifts. These are observed code-generation differences. No source variant, register shaping, literal-pool steering or extra operation was attempted.

The source preserves the observed two low-byte inputs, seven-byte stride, nine grouped field-reading bodies and mapped data_08528C24 identity. The array declaration describes the observed accesses; it does not prove a historical object type, extent, allocation, readability or game purpose. No helper ABI or numerical behavior beyond the source operation is claimed.

Accounting: one source form, one native matching attempt, one authorized unchanged-source compiler-only diagnostic, zero native replays, zero MATCH credit. No generated native match report was produced. The failed active source was moved only to this owned Parked directory.

Immutable receipts and exact source/body/compiled-byte evidence:

- `state/matching-080CC3C8-author/attempt1-source.c`
- `state/matching-080CC3C8-author/attempt1-native-exit.json`
- `state/matching-080CC3C8-author/attempt1-native.stdout`
- `state/matching-080CC3C8-author/attempt1-native.stderr`
- `state/matching-080CC3C8-author/diagnostic/commands.json`
- `state/matching-080CC3C8-author/diagnostic/result.json`
- `state/matching-080CC3C8-author/diagnostic/f.s`
- `state/matching-080CC3C8-author/diagnostic/f.elf`
- `state/matching-080CC3C8-author/diagnostic/compiled-symbol.bin`
- `state/matching-080CC3C8-author/result.json`

The parent owns release and integration. No further C candidate or proof replay is authorized by this receipt.
