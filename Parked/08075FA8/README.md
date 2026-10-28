# 08075FA8 — bounded natural C nonmatch

The indexed target is the complete 420-byte Thumb function ending at 0807614C, with 173 reachable instructions. The accepted reservation is 6480651477 (codex-sol61-v719-08075fa8).

The candidate recovers the three displayed stat changes. It refreshes the object cache, subtracts the previous halfword values, selects the neutral/decrease/increase tile value from the signed 16-bit difference, and draws each current value through the existing tile-position and number-rendering functions. The two prepared RAM objects supply the previous/current values and display color. No metadata, shared header, toolchain, or other address was changed.

The final native command used the immutable 5707d46c64da4313a2a6c09784e4cfc564053c82 author kit, default ordinary selector, and fixed agbcc -mthumb-interwork -O2. The complete compiler ELF symbol is 420 bytes and the source passes the native plausibility check. The native match exits 1: 360 of 420 positional bytes are equal, and 117 of 171 compiled instruction rows are identical against the 173-instruction target. These are diagnostic comparison counts, not match credit.

The remaining difference is concentrated around the three number-rendering calls. The compiler removes intermediate signed-difference extensions when the result is narrowed to the renderer's halfword value, then assigns different temporary registers and literal-pool offsets. The target retains those signed conversions; the last block also retains its signed-difference intermediate across the tile-position call. Correct total symbol length alone does not resolve these differences.

Meaningful ordinary alternatives were tested: signed versus encoded unsigned halfword differences; a word-sized encoded difference; an explicit signed word display value; a compound update of the difference; typed tile pointers; explicit color snapshots; natural operand order; and halfword versus promoted word argument declarations with explicit narrowing. They produced nonidentical symbols of 416 to 436 bytes. None reached full byte equality. No assembly, volatile RAM access, forced register, artificial helper, padding, flag change, or runtime alias was introduced.

The final tested candidate is preserved beside this README. The unchanged original relocatable compiler ELF, native output, and failed report are retained in the sibling address artifact directory named by result.json. Unmatched active source and report files were removed. No fresh successful report replay is claimed, and this outcome earns zero C credit.
