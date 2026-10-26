# 0800EA0C — parked natural C attempt

Complete indexed target: `[0x0800EA0C, 0x0800ED58)`, 844 bytes and 404 reachable instructions.

The complete candidate implements the circle delegation and both midpoint ellipse scanline branches, including signed 16-bit midpoint updates, cached major-axis division, signed row clipping, and the global right-edge bias. The two axis helpers use signed center coordinates and 32-bit arithmetic for radii.

The latest unchanged native matcher invocation compiled the function to 836 bytes, eight bytes shorter than the indexed target. The matcher stopped at its symbol-extent gate; no byte/instruction similarity result or native plausibility verdict was produced. This is not an exact match.

Bounded natural forms tested: branch-local coordinates, direct signed coordinate parameters, and separate inline major-axis helpers; the midpoint negative-error update was aligned with the captured post-decrement expression. The helper form reproduces the target's branch-local signed center conversions. The remaining diagnosed difference is allocation across the two division calls: the diagnostic helper build retains radiusY in SL, spills the minor-axis loop variable and uses a 52-byte frame; the target spills both radii, retains the wide-ellipse minor variable in SL and uses a 48-byte frame. These allocation differences also change multiplication operand moves and surrounding stack accesses. Widening helper radius parameters to 32 bits retained the 836-byte extent. No register steering, volatile storage, assembly, or compiler changes were used.

Preserved source SHA-256: `59c953829f9ffdb32964a05533ad255f8ec6637d7c5a7b6db2509834d20c2c89`.

Latest native output: `/home/user/.codex-work/ffta-ulw/audio-following-v98-matching/0800EA0C/native-output.txt`.
Native output SHA-256: `903f51452200037372fa6012e59d66d6b886c90686c4b42d7a19247206c2b4a5`.

The unmatched private main source and generated report are absent. The complete captured target remains in the address scratch directory. Root owns integration and lease release.
