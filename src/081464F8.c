#include "ffta.h"

typedef struct WaveData WaveData;

typedef struct {
    u8 unknown_00[0x28];
    WaveData *wave;
    u8 unknown_2C[0x14];
    const u8 *cursor;
} CommandContext;

/* Complete [0x081464F8, 0x08146540): 72 bytes, 27 instructions.
 * 10b50a6c0c48044010780443507803020a4804401c4390780304094804401c43
 * d0780306074804401c438c6204320a6410bc01bc0047000000ffffffff00ffff
 * ffff00ffffffff00
 * m4a.c ply_xwave (SAT-R sa2 MP2K_event_xwave): read a four-byte wave
 * pointer from the track's command stream into its tone and step the stream
 * past it.  Each byte is inserted into the pointer's word in turn: ldrb,
 * lsls #8n, ands with the pool mask ~(0xFF << 8n), orrs (0x081464FC-0x08146520);
 * the word is r4, never written before the first ands at 0x081464FE.
 */
void func_081464F8(void *owner, CommandContext *context)
{
    union {
        u8 *a;
        u8 d[4];
    } u;

    u.d[0] = *(context->cursor + 0);
    u.d[1] = *(context->cursor + 1);
    u.d[2] = *(context->cursor + 2);
    u.d[3] = *(context->cursor + 3);
    context->wave = (WaveData *)u.a;
    context->cursor += 4;
}
