# 0805417C — shared-success block placement

The complete indexed target is 0x0805417C..0x080541AE: 50 bytes and 25
reachable instructions. The preserved candidate compiles to 48 bytes and 24
instructions with agbcc `-mthumb-interwork -O2`. Its final native matcher run
exits 1 with `compiled symbol is shorter than the indexed span: 48 < 50`.
That extent refusal precedes native plausibility evaluation; no match credit
or final-candidate plausibility verdict is claimed.

The function permits movement for key 0x40 when signed halfword `top` at
offset 0x1A is nonzero, or for key 0x80 when `top + 4` is less than signed
halfword `count` at offset 0x18. All other keys return zero.

The remaining difference is branch layout. In the target, both tests precede
the shared `movs r0, #1` success block. The 0x40 case branches forward to that
block, while the 0x80 case branches forward to failure on `bge` and otherwise
falls through to success. The candidate places success immediately after the
0x40 case. Its 0x80 case uses a backward `blt` to that block. The candidate
therefore omits one unconditional branch and is two bytes shorter.

Tested natural forms included positive early returns (the preserved form),
negative failure guards with a common success return, explicit key switches,
and a local result flag. The switch forms reached 50 bytes but grouped both
key comparisons before their case bodies and placed failure earlier. The
local-result form emitted 54 bytes, an additional saved register, and a
branchless nonzero conversion. Those forms did not reproduce the target.
No compiler settings, forced emission, or assembly were introduced.
