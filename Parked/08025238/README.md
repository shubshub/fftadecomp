# 08025238 matching attempt

Target: `08025238..08025324`, 236 complete bytes including 24 literal bytes.
The saved target body SHA256 is
`0394e361334b2694b36add13b8f59e93940d0387270b7e1dc32662ba2973f035`.

The native command `python ../fftadecomp-kit/tools/match.py --root . 0x08025238`
exited 1 before byte comparison:
`buffer-call evidence does not support data relocations`.
The source retains genuine typed callback relocations for the existing
`data_08394038`, `data_08394040` and `data_08394054` mappings. No verifier,
profile, data map or shared header was changed.

A separate diagnostic used the native compiler and typed linker only. Its
complete linked output is 236 bytes, SHA256
`70b35eb5cebf2b497c4dfdb2d4006810337dc0d1ba1900bfb97d1992758742e4`.
It is not a match or admission receipt. All saved instruction text agrees
except the table-base load: the target loads `0839141C` into r4 before the
variant byte load and shifts at `080252D6`; the candidate loads that same
constant after those shifts. A normal local table-pointer variable produced
the same output as the original direct table-pointer expression. Neither
candidate changed toolchain flags, used assembly, or changed gate behavior.

The current data map has no exact `0839141C` table symbol. A named-table
source form was not tried because it requires genuine new data binding and
this lane was directed to preserve and park the existing refusal.

Plausibility check exited 1 with one `rom-address` finding on the local
`0839141C` table-pointer assignment. The candidate remains unadmitted; a
genuine named-table binding is needed before attempting that source form.
No byte-identical source or match report was claimed. The coordinating
session owns reservation release.
Detailed logs, compiled assembly/bytes, exact mismatch positions and the
saved-code comparison are under
`state/matching-08025238-author/` in the handover workspace.
