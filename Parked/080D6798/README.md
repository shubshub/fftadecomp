# 080D6798 parked attempt

One natural C form and one original default native attempt were made under accepted claim 6537678772 (sol-6798). The native command exited 1 with `buffer caller requires an exact complete mapped span`; no native match report was generated. This is a compiled-extent mismatch, with zero MATCH credit.

The authorized single unchanged-source compiler-only diagnostic succeeded with the native cpp13/agbcc/as/link flags. The complete FUNC is 372 bytes, versus the immutable 438-byte target. The first differing byte is offset 0xA: generated stack allocation is 52 bytes versus 72 bytes in the target. The generated coordinate clipping uses an unsigned 0..31 test where the target has separate signed comparisons, and has different spills, scheduling and literal placement. No concrete semantic source correction was identified. No second form or native retry was attempted.

Source SHA256: d56492d43e98137f7d4967085194df18ef92c12074cb62ec7d2eb954489cfc8e
Compiled FUNC SHA256: c3bc3ad17ac662108d8d5fb15112383ad5bb3f3a2536b205b09e682665d1088c
Target SHA256: c8d646e7544f27ae358f528a29029530575fcbd88d71f115a988579e09197689

Full source-bound runtime, tool, header and map pins, original native stdout/stderr/exit, compiler commands, complete ELF and function bytes, disassembly and exact byte ranges are retained under `state/matching-080D6798-author/`. Historical batch157 qualification pins remain separate from this attempt's published cfcd6885 toolkit pins. No helper/ROM reread, shared-input change, proof replay or successful check occurred. Parent owns release and publication.
