#include "ffta.h"

/* Target: complete [0x08145CAC, 0x081460F6), 1098 bytes. */
typedef union {
    u32 value;
    struct {
        u8 low;
        u8 high;
        u8 unknown_02[2];
    } bytes;
} Frequency08145CAC;

typedef union {
    u32 value;
    const u32 *wave;
} Instrument08145CAC;

typedef struct {
    u8 status;
    u8 type;
    u8 unknown_02[2];
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 unknown_08;
    u8 envelope_volume;
    u8 envelope_goal;
    u8 envelope_counter;
    u8 echo_volume;
    u8 echo_length;
    u8 unknown_0e[11];
    u8 sustain_goal;
    u8 control;
    u8 pan;
    u8 pan_mask;
    u8 modify;
    u8 length;
    u8 sweep;
    Frequency08145CAC frequency;
    Instrument08145CAC instrument;
    const u32 *last_wave;
    u8 unknown_2c[20];
} Channel08145CAC;

typedef struct {
    u8 unknown_00[10];
    u8 counter;
    u8 unknown_0b[17];
    Channel08145CAC *channels;
} SoundInfo08145CAC;

extern SoundInfo08145CAC *data_03007FF0;
extern u8 data_04000060[];
extern u8 data_04000062[];
extern u8 data_04000063[];
extern u8 data_04000061[];
extern u8 data_04000068[];
extern u8 data_04000069[];
extern u8 data_04000070[];
extern u8 data_04000072[];
extern u8 data_04000073[];
extern u8 data_04000071[];
extern u8 data_04000078[];
extern u8 data_04000079[];
extern u32 data_04000090[];
extern u8 data_04000089[];
extern u8 data_04000081[];
extern const u8 data_0836D2FC[];
extern void func_08145C44(Channel08145CAC *);
extern void func_08145BF4(u8);

void func_08145CAC(void)
{
    s32 counter;
    SoundInfo08145CAC *info = data_03007FF0;
    Channel08145CAC *channel;
    u8 *nr0;
    u8 *nr1;
    u8 *nr2;
    u8 *nr3;
    u8 *nr4;
    u32 envelope;
    u32 flags;
    u32 stage;
    s32 number;

    if (info->counter)
        info->counter--;
    else
        info->counter = 14;

    for (number = 1, channel = info->channels; number <= 4;
         number++, channel++) {
        if (!(channel->status & 0xc7))
            continue;

        switch (number) {
        case 1:
            nr0 = data_04000060;
            nr1 = data_04000062;
            nr2 = data_04000063;
            nr3 = nr0 + 4;
            nr4 = nr2 + 2;
            break;
        case 2:
            nr0 = data_04000061;
            nr1 = data_04000068;
            nr2 = data_04000069;
            nr3 = nr0 + 11;
            nr4 = nr2 + 4;
            break;
        case 3:
            nr0 = data_04000070;
            nr1 = data_04000072;
            nr2 = data_04000073;
            nr3 = nr0 + 4;
            nr4 = nr2 + 2;
            break;
        default:
            nr0 = data_04000071;
            nr1 = data_04000078;
            nr2 = data_04000079;
            nr3 = nr0 + 11;
            nr4 = nr2 + 4;
            break;
        }

        counter = info->counter;
        envelope = *nr2;
        if (channel->status & 0x80) {
            if (channel->status & 0x40)
                goto stop_channel;
            channel->status = 3;
            channel->modify = 3;
            func_08145C44(channel);
            switch (number) {
            case 1:
                *nr0 = channel->sweep;
            case 2:
                *nr1 = channel->length + (channel->instrument.value << 6);
                break;
            case 3:
                if (channel->instrument.wave != channel->last_wave) {
                    u32 *wave;
                    const u32 *source;

                    *nr0 = 0x40;
                    wave = data_04000090;
                    source = channel->instrument.wave;
                    *wave = source[0];
                    wave++;
                    *wave = source[1];
                    wave++;
                    *wave = source[2];
                    wave++;
                    *wave = source[3];
                    channel->last_wave = source;
                }
                *nr0 = 0;
                *nr1 = channel->length;
                if (channel->length)
                    channel->control = 0xc0;
                else
                    channel->control = -128;
                goto initialize_envelope;
            default:
                *nr1 = channel->length;
                *nr3 = channel->instrument.value << 3;
                break;
            }
            envelope = channel->attack + 8;
            if (channel->length)
                channel->control = 0x40;
            else
                channel->control = 0;

initialize_envelope:
            if (!(channel->envelope_counter = channel->attack))
                goto attack_complete;
            channel->envelope_volume = 0;
            goto countdown;
        } else if (channel->status & 4) {
            if ((s8)--channel->echo_length <= 0) {
stop_channel:
                func_08145BF4((u8)number);
                channel->status = 0;
                goto clear_modify;
            }
            goto update_hardware;
        } else {
            if ((channel->status & 0x40) && (channel->status & 3)) {
                channel->status &= 0xfc;
                if (!(channel->envelope_counter = channel->release))
                    goto echo;
                {
                    flags = channel->modify;
                    channel->modify = flags | 1;
                }
                if (number != 3)
                    envelope = channel->release;
                goto countdown;
            }

envelope_step:
            if (channel->envelope_counter)
                goto countdown;
            if (number == 3) {
                flags = channel->modify;
                channel->modify = flags | 1;
            }
            func_08145C44(channel);

            stage = channel->status;
            stage &= 3;
            if (!stage) {
                if ((s8)--channel->envelope_volume <= 0)
                    goto echo;
                goto release_countdown;

echo:
                channel->envelope_volume =
                    (channel->echo_volume * channel->envelope_goal + 255) >> 8;
                if (!channel->envelope_volume)
                    goto stop_channel;
                channel->status |= 4;
                flags = channel->modify;
                channel->modify = flags | 1;
                if (number != 3)
                    envelope = 8;
                goto update_hardware;
release_countdown:
                channel->envelope_counter = channel->release;
            } else if (stage == 1) {
sustain:
                channel->envelope_volume = channel->sustain_goal;
                channel->envelope_counter = 7;
            } else if (stage == 2) {
                if ((s8)--channel->envelope_volume <= (s8)channel->sustain_goal) {
decay_complete:
                    if (!channel->sustain) {
                        channel->status &= 0xfc;
                        goto echo;
                    }
                    channel->status--;
                    {
                        flags = channel->modify;
                        channel->modify = flags | 1;
                    }
                    if (number != 3)
                        envelope = 8;
                    goto sustain;
                }
                channel->envelope_counter = channel->decay;
            } else {
                if (++channel->envelope_volume >= channel->envelope_goal) {
attack_complete:
                    channel->status--;
                    if (!(channel->envelope_counter = channel->decay))
                        goto decay_complete;
                    {
                        flags = channel->modify;
                        channel->modify = flags | 1;
                    }
                    channel->envelope_volume = channel->envelope_goal;
                    if (number != 3)
                        envelope = channel->decay;
                } else
                    channel->envelope_counter = channel->attack;
            }

countdown:
            channel->envelope_counter--;
            if (!counter) {
                counter--;
                goto envelope_step;
            }
            goto update_hardware;

        }

update_hardware:
        if (channel->modify & 2) {
            if (number <= 3 && (channel->type & 8)) {
                s32 bias = *data_04000089;
                if (bias <= 0x3f)
                    channel->frequency.value =
                        (channel->frequency.value + 2) & 0x7fc;
                else if (bias <= 0x7f)
                    channel->frequency.value =
                        (channel->frequency.value + 1) & 0x7fe;
            }
            if (number != 4)
                *nr3 = channel->frequency.value;
            else
                *nr3 = (*nr3 & 8) | channel->frequency.value;
            *nr4 = channel->control = (channel->control & 0xc0) +
                channel->frequency.bytes.high;
        }

        if (channel->modify & 1) {
            *data_04000081 = (*data_04000081 & ~channel->pan_mask) |
                channel->pan;
            if (number == 3) {
                *nr2 = data_0836D2FC[channel->envelope_volume];
                if (channel->control & 0x80) {
                    *nr0 = 0x80;
                    *nr4 = channel->control;
                    channel->control &= 0x7f;
                }
            } else {
                envelope &= 0xf;
                *nr2 = (channel->envelope_volume << 4) + envelope;
                *nr4 = channel->control | 0x80;
                if (number == 1 && !(*nr0 & 8))
                    *nr4 = channel->control | 0x80;
            }
        }

clear_modify:
        channel->modify = 0;
    }
}
