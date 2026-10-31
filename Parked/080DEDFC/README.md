# 080DEDFC

One natural source form was checked once with the published default native matcher under accepted lease 6537419956 (sol-EDFC). Native exit 1: `compile failed: switch caller requires an exact mapped Thumb span`. No MATCH or unsupported-model conclusion follows.

The authorized one unchanged-source compiler-only diagnostic used the same cpp13, agbcc `-mthumb-interwork -O2`, assembler and exact native linker script/Thumb bindings. It emitted a complete 400-byte function, compared with the complete 404-byte target. Compiled body SHA256: `0c043d60ade147a2851bb472789f44ec368068d76980fcc027b77a5093747e49`. Target body SHA256: `5878953456eb5f1e2c04495b6daaa1304d2f1a535e6cb17caf94f501a51e6dff`.

Observed differences include an additional object-pointer reload between the two state-1 halfword clears in the compiled source. The target has one pointer load. The target switch case 0 and case 1 each sign-extend the saved byte with LSL24/ASR24 before comparison; the compiler omits those conversions when comparing the source's signed-byte casts to 0 and 2. Later corresponding interpolation and scaling instructions follow the same observed operations at shifted locations. The literal table layout and branch displacements also move. The exact full diagnostic bytes and all 296 differing byte positions, including absent trailing bytes, are retained in the diagnostic receipt.

The natural source preserves the actual defining helper interfaces, accessed offsets and signed/unsigned conversions. No definite semantic source bug was established. No alternate source, lifetime/register/type/spelling adjustment, extra operation, padding, flags change, proof replay or second native check was attempted. This is a bounded ordinary compiled-extent mismatch.

Evidence: `/home/user/Desktop/FFTA-handover-2026-10-30/state/matching-080DEDFC-author/`. Original source SHA256: `0f028516535aee91e0e61a22a9d36951235742fcbbb471c4269ce2c1ffe2f5aa`. Original source plus nine-header native composite: `478576e5acebbfd057b2765b9141ca18496d27ae6fded56dd8628b2ec77a92c8`. The source is unchanged in this directory. No generated native match report exists.
