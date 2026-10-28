#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x1F];
    void *channel;
    u8 unknown_24[0x1C];
    const u8 *commands;
    u8 unknown_44[0xC];
} MusicTrack;

typedef struct {
    u8 track_count;
    u8 unknown_01;
    u8 priority;
    u8 reverb;
    const void *tone;
    const u8 *parts[0];
} SongHeader;

typedef struct {
    const SongHeader *song;
    u32 status;
    u8 track_count;
    u8 priority;
    u8 unknown_0a;
    u8 check_priority;
    u32 clock;
    u8 unknown_10[0xC];
    u16 tempo_default;
    u16 tempo_scale;
    u16 tempo;
    u16 tempo_counter;
    u16 fade_interval;
    u8 unknown_26[6];
    MusicTrack *tracks;
    const void *tone;
    u32 signature;
} MusicPlayer;

extern void func_08144D94(MusicPlayer *player, MusicTrack *track);
extern void func_081456AC(u32 mode);

/* Complete [0x081458AC, 0x08145990): 228 bytes, 109 instructions. */
void func_081458AC(MusicPlayer *player, const SongHeader *song)
{
    int index;
    MusicTrack *track;
    u8 priority;

    if (player->signature != 0x68736D53)
        return;
    priority = song->priority;
    if (player->check_priority) {
        if ((player->song && (player->tracks->flags & 0x40)) ||
            ((player->status & 0xFFFF) && !(player->status & 0x80000000))) {
            priority = song->priority;
            if (player->priority > priority)
                return;
        }
    }
    player->signature++;
    player->status = 0;
    player->song = song;
    player->tone = song->tone;
    player->priority = priority;
    player->clock = 0;
    player->tempo_default = 150;
    player->tempo = 150;
    player->tempo_scale = 256;
    player->tempo_counter = 0;
    player->fade_interval = 0;
    index = 0;
    track = player->tracks;
    for (; index < song->track_count && index < player->track_count;
         index++, track++) {
        func_08144D94(player, track);
        track->flags = 0xC0;
        track->channel = 0;
        track->commands = song->parts[index];
    }
    for (; index < player->track_count; index++, track++) {
        func_08144D94(player, track);
        track->flags = 0;
    }
    if (song->reverb & 0x80)
        func_081456AC(song->reverb);
    player->signature = 0x68736D53;
}
