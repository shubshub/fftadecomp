#include "ffta.h"

typedef struct {
    const void *header;
    u32 status;
} PlaybackState081451EC;

typedef struct {
    PlaybackState081451EC *state;
    u8 unknown_04[8];
} PlayerEntry081451EC;

typedef struct {
    const void *header;
    u16 player_index;
    u16 unknown_06;
} SongEntry081451EC;

extern void func_081458AC(PlaybackState081451EC *state, const void *header);

/* 0x081451EC - 76 bytes.
 * Target: 00b50004094a0a49400b401883885900c9188900891809680b680268934209d0081c111c
 *         00f04cfb0ee0000024bb140848bb14084a688888002801d0002a03da081c191c
 *         00f03cfb01bc0047
 */
void func_081451EC(u16 song_index)
{
    const SongEntry081451EC *song = &((const SongEntry081451EC *)0x0814BB48)[song_index];
    PlaybackState081451EC *state = ((const PlayerEntry081451EC *)0x0814BB24)[song->player_index].state;

    if (state->header != song->header)
        func_081458AC(state, song->header);
    else if ((u16)state->status == 0 || (s32)state->status < 0)
        func_081458AC(state, state->header);
}
