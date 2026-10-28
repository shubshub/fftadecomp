#include "ffta.h"

/* Target: complete [0x08144E08, 0x08145008), 512 bytes. */
typedef struct Track Track;
typedef struct Channel Channel;

typedef struct {
    u8 type;
    u8 key;
    u8 length;
    u8 sweep;
    const void *wave;
    union {
        u32 envelope;
        const u8 *keys;
    } data;
} Tone;

struct Channel {
    u8 status;
    u8 type;
    u8 left;
    u8 right;
    u32 envelope;
    u8 key;
    u8 unknown_09[3];
    u16 tune;
    u8 unknown_0E[2];
    u8 gate_time;
    u8 original_key;
    u8 velocity;
    u8 priority;
    s8 pan;
    u8 unknown_15[9];
    u8 length;
    u8 sweep;
    u32 frequency;
    const void *wave;
    u8 unknown_28[4];
    Track *track;
    Channel *previous;
    Channel *next;
    u8 unknown_38[8];
};

struct Track {
    u8 flags;
    u8 unknown_01[3];
    u8 gate_time;
    u8 key;
    u8 velocity;
    u8 unknown_07;
    s8 key_shift;
    u8 pitch;
    u8 unknown_0A[0x11];
    u8 modulation_delay;
    u8 modulation_delay_count;
    u8 priority;
    u16 tune;
    Channel *channel;
    Tone tone;
    u8 unknown_30[0x10];
    const u8 *command;
};

typedef struct {
    u8 unknown_00[9];
    u8 priority;
} Player;

typedef u32 (*FrequencyFunction)(u32, u32, u32);

typedef struct {
    u8 unknown_00[6];
    u8 channel_count;
    u8 unknown_07[0x15];
    Channel *hardware_channels;
    u8 unknown_20[0x10];
    FrequencyFunction frequency;
    u8 unknown_34[0x1c];
    Channel channels[12];
} SoundInfo;

extern SoundInfo *data_03007FF0;
extern const u8 data_0836D30C[];
extern void func_08145514(Channel *);
extern void func_08145048(u32, Track *);
extern void func_08145A98(Player *, Track *);
extern void func_08144DD8(Channel *, Track *);
extern u32 func_08144D84(u32, u32, u32, FrequencyFunction);
extern u32 func_08145098(const void *, u32, u32);

void func_08144E08(u32 clock, Player *player, Track *track)
{
    SoundInfo *sound = data_03007FF0;
    const u8 *command;
    const Tone *tone;
    Channel *channel;
    u32 key;
    s32 pan = 0;
    u32 priority;
    u32 hardware;
    const void *wave;
    s32 shifted_key;

    track->gate_time = data_0836D30C[clock];
    command = track->command;
    if (*command < 0x80) {
        track->key = *command++;
        if (*command < 0x80) {
            track->velocity = *command++;
            if (*command < 0x80)
                track->gate_time += *command++;
        }
        track->command = command;
    }

    if (track->tone.type & 0xc0) {
        key = track->key;
        tone = (const Tone *)track->tone.wave;
        if (track->tone.type & 0x40)
            tone += track->tone.data.keys[key];
        else
            tone += key;
        if (tone->type & 0xc0)
            return;
        if (track->tone.type & 0x80) {
            if (tone->sweep & 0x80)
                pan = (tone->sweep - 0xc0) * 2;
            key = tone->key;
        }
    } else {
        tone = &track->tone;
        key = track->key;
    }

    priority = player->priority + track->priority;
    if (priority > 255)
        priority = 255;
    hardware = tone->type & 7;
    if (hardware) {
        channel = sound->hardware_channels;
        if (channel == 0)
            return;
        channel += hardware - 1;
        if ((channel->status & 0xc7) && !(channel->status & 0x40)) {
            if (channel->priority > priority)
                return;
            if (channel->priority == priority && channel->track < track)
                return;
        }
    } else {
        u32 best_priority = priority;
        Track *best_track = track;
        u32 releasing = 0;
        Channel *best = 0;
        s32 remaining = sound->channel_count;

        channel = sound->channels;
        do {
            if (!(channel->status & 0xc7))
                goto selected;
            if (channel->status & 0x40) {
                if (!releasing) {
                    releasing++;
                    best_priority = channel->priority;
                    best_track = channel->track;
                    best = channel;
                    goto next_channel;
                }
            } else if (releasing) {
                goto next_channel;
            }
            if (channel->priority < best_priority) {
                best_priority = channel->priority;
                best_track = channel->track;
                best = channel;
            } else if (channel->priority == best_priority) {
                if (channel->track > best_track) {
                    best_track = channel->track;
                    best = channel;
                } else if (channel->track == best_track) {
                    best = channel;
                }
            }
next_channel:
            channel++;
        } while (--remaining > 0);
        channel = best;
        if (channel == 0)
            return;
    }

selected:
    func_08145514(channel);
    channel->previous = 0;
    channel->next = track->channel;
    if (track->channel)
        track->channel->previous = channel;
    track->channel = channel;
    channel->track = track;
    track->modulation_delay_count = track->modulation_delay;
    if (track->modulation_delay_count)
        func_08145048(track->modulation_delay_count, track);
    func_08145A98(player, track);
    *(u32 *)&channel->gate_time = *(u32 *)&track->gate_time;
    channel->priority = priority;
    channel->key = key;
    channel->pan = pan;
    channel->type = tone->type;
    wave = tone->wave;
    channel->wave = wave;
    channel->envelope = tone->data.envelope;
    channel->tune = track->tune;
    func_08144DD8(channel, track);
    shifted_key = channel->key + track->key_shift;
    if (shifted_key < 0)
        shifted_key = 0;
    if (hardware) {
        u32 sweep = tone->sweep;

        channel->length = tone->length;
        if ((sweep & 0x80) || !(sweep & 0x70))
            sweep = 8;
        channel->sweep = sweep;
        channel->frequency = func_08144D84(hardware, shifted_key,
                                          track->pitch, sound->frequency);
    } else {
        channel->frequency = func_08145098(wave, shifted_key, track->pitch);
    }
    channel->status = 0x80;
    track->flags &= 0xf0;
}
