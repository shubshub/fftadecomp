typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u8 flags;
    u8 unknown_01[0x18];
    u8 lfo_speed;
    u8 unknown_1A[0x36];
} PlayerTrack;

typedef struct {
    u8 unknown_00[8];
    u8 track_count;
    u8 unknown_09[0x23];
    PlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

extern void func_08146264(PlayerTrack *track);

/* Complete [0x081462F8, 0x0814636C): 116 bytes, including literal pools. */
void func_081462F8(MusicPlayer *player, u16 selected_tracks, u8 lfo_speed)
{
    PlayerTrack *track;
    s32 remaining;
    u32 bit;

    if (player->signature != 0x68736D53)
        return;

    player->signature++;
    remaining = player->track_count;
    track = player->tracks;
    bit = 1;
    while (remaining > 0) {
        if (selected_tracks & bit) {
            u32 active = 0x80;
            u32 flags = track->flags;
            active &= flags;

            if (active) {
                track->lfo_speed = lfo_speed;
                if (track->lfo_speed == 0)
                    func_08146264(track);
            }
        }
        remaining--;
        track++;
        bit <<= 1;
    }
    player->signature = 0x68736D53;
}
