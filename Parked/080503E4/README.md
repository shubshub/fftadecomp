# 080503E4: bounded ordinary byte mismatch

Accepted reservation: sol-03E4, claim 6531355514. Three distinct natural forms
ran through the default native matcher with plausible source and exit 1.
No unsupported native-model refusal occurred and no success was replayed.

The target is the complete 216-byte Thumb symbol [080503E4,080504BC).
Attempt 1 uses a signed scalar index over halfwords 23 down to 21; it emits
216 bytes but retains a scalar loop counter and hoists the signed tile value
across the initial helper calls. Attempt 2 traverses the pointer range directly;
it emits 220 bytes with an unsigned entry guard and unsigned loop backedge.
Attempt 3, retained here, uses the genuinely nonempty reverse pointer do-loop;
it emits 216 bytes but keeps unsigned BHS and extra pointer/register moves,
where the target uses signed BGE with a different induction allocation.

All three preserve defining 08017FA8(ValuePair*,u32,u16,u16), genuine qualified
ROM-object pointer-to-word casts, and actual observed helper inputs. Under that
required fourth u16 formal, the coordinate expression emits LSRS #16; the target
uses ASRS #16. Neither a changed prototype nor a signed-address comparison cast
was introduced to force these bytes. The attempted forms are not an exhaustive
proof that no other natural C exists.

The exact source, native reports, full target and compiled symbol bytes, source
and complete-header composite hashes, all nine header pins, selected host cpp13
and agbcc/tool pins, current runtime and three map pins are retained under
state/matching-080503E4-author in the handover root. Each native call has its
own pre-run, stdout and exit receipt. Earlier forms and failed reports remain
unchanged there. No compiler-only diagnostic was run. ABI and real-object
qualification receipts remain immutable. Shared inputs were not changed.
