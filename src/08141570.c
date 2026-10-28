#include "ffta.h"

struct Song08141570 {
    const void *header;
    u16 music_player;
    u16 priority;
};

extern u8 data_020084D8;
extern u8 data_0200F2E0[];
extern u8 data_0200F320[];
extern const struct Song08141570 g_table_0814BB48[];
extern void func_081458AC(void *player, const void *song);

/* Target: [0x08141570, 0x081415C0), 80 bytes, 30 instructions. */
void func_08141570(s32 player_id, u16 song_id)
{
    void *player = 0;

    if (data_020084D8 & 2) {
        switch (player_id) {
        case 1:
            player = data_0200F2E0;
            break;
        case 2:
            player = data_0200F320;
            break;
        }
        {
            const struct Song08141570 *songs = g_table_0814BB48;

            if (player != 0)
                func_081458AC(player, songs[song_id].header);
        }
    }
}
