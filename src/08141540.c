#include "ffta.h"

struct Song08141540 {
    const void *header;
    u16 music_player;
    u16 priority;
};

extern u8 data_020084D8;
extern u8 data_0200F320[];
extern const struct Song08141540 g_table_0814BB48[];
extern void func_081458AC(void *player, const void *song);

/* Complete target: [0x08141540, 0x08141570), 48 bytes.
 * 00b50004030c0748017802200840002806d00548054ad9008918096804f0a6f901bc0047d884000220f3000248bb1408
 */
void func_08141540(u16 song_id)
{
    if (data_020084D8 & 2) {
        void *player = data_0200F320;
        const struct Song08141540 *songs = g_table_0814BB48;

        func_081458AC(player, songs[song_id].header);
    }
}
