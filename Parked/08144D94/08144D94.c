#include "ffta.h"

typedef void (*StopChannel)(u32 channel_type);

typedef struct {
    u8 unknown_00[0x2C];
    StopChannel stop_channel;
} SoundDriver;

typedef struct SoundChannel SoundChannel;
struct SoundChannel {
    u8 flags;
    u8 type;
    u8 unknown_02[0x2A];
    void *owner;
    u8 unknown_30[4];
    SoundChannel *next;
};

typedef struct {
    u8 flags;
    u8 unknown_01[0x1F];
    SoundChannel *channels;
} SoundTrack;

extern SoundDriver *data_03007FF0;

void func_08144D94(void *player, SoundTrack *track)
{
    if (track->flags & 0x80)
    {
        SoundChannel *channel = track->channels;

        while (channel)
        {
            if (channel->flags)
            {
                u32 type = channel->type & 7;
                if (type)
                    data_03007FF0->stop_channel(type);
                channel->flags = 0;
            }
            channel->owner = 0;
            channel = channel->next;
        }
        track->channels = channel;
    }
}
