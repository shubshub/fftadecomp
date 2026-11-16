# 0x080ED308 - byte-identical only with volatile on a non-allowlisted buffer (176 bytes)

Retry of Parked/080ED308 on 2026-11-16, kit fcdf2d45, default flags (no selector applies: the refusal is the plausibility gate). Recorded as
unmatchable: the evidence requires maintainer review.

The source here compiles to all 176 bytes (84/84 instructions). match.py refuses it:
  bytes   identical
  source  IMPLAUSIBLE (not on the allow list)
  verdict HAND-ASM REQUIRED BUT NOT ALLOWED
  080ED308.c:11: ERROR: volatile
  080ED308.c:12: ERROR: volatile

Not shipped: volatile is admitted only on evidence-backed declarations in include/ on the plausible.py allow list; this buffer is reached through
a pointer, which the allow list cannot express. Kit issue: #168 (volatile on per-scanline HDMA and OAM RAM buffers reached through pointers).

What closed the 16 bytes from the older parked attempt:
- six dead ldrb before strb: the output element is a packed pair of full-width volatile bitfields, the member typing of bldalpha_lo / bldalpha_hi in
  include/control_flags.h: `typedef struct __attribute__((packed)) { volatile u8 eva : 8; volatile u8 evb : 8; } BlendLine;` (packed for the 2-byte stride);
- table + 1 held in ip: `extern const u8 gUnknown_083992B8[][2];` indexed [i][0] / [i][1] directly, no local table pointer (flat [i * 2 + 1] gives adds r1, #1; adds r1, r1, r6);
- loop shape `while (i <= 30) { ...; i++; y++; line++; if (y > 159) break; }`, with line++ in the increment clause of the two fill loops.

Without volatile the same source is 164 bytes, exactly the six loads short. A plain vu8 * store emits no load; an unpacked bitfield struct has a 4-byte
stride (172 bytes); a local table pointer loses the ip base.

The buffer is 160 two-byte pairs holding 0..16, apparently a per-scanline BLDALPHA table reached through a pointer (consumer not traced). The kit's
tools/volatile_allow.json is keyed to one named symbol, not a heap buffer. The other three callers of func_080D9B08 show the same load-before-store
shape in a raw scan (080F5BE4 14 of 15 strb, 080FD6E8 6 of 7, 08109300 1 of 3; control-block stores not separated out).
