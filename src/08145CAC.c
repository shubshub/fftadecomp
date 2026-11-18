#include "ffta.h"

/* Complete target [0x08145CAC, 0x081460F6), 1098 bytes.
 * MusicPlayer2000 CgbSound, from SAT-R/sa2 src/lib/m4a/m4a.c. */
#define TONEDATA_TYPE_FIX 0x08

#define SOUND_CHANNEL_SF_START       0x80
#define SOUND_CHANNEL_SF_STOP        0x40
#define SOUND_CHANNEL_SF_IEC         0x04
#define SOUND_CHANNEL_SF_ENV         0x03
#define SOUND_CHANNEL_SF_ENV_ATTACK  0x03
#define SOUND_CHANNEL_SF_ENV_DECAY   0x02
#define SOUND_CHANNEL_SF_ENV_SUSTAIN 0x01
#define SOUND_CHANNEL_SF_ENV_RELEASE 0x00
#define SOUND_CHANNEL_SF_ON          (SOUND_CHANNEL_SF_START | SOUND_CHANNEL_SF_STOP | SOUND_CHANNEL_SF_IEC | SOUND_CHANNEL_SF_ENV)

#define CGB_CHANNEL_MO_PIT 0x02
#define CGB_CHANNEL_MO_VOL 0x01

#define CGB_NRx2_ENV_DIR_DEC 0x00
#define CGB_NRx2_ENV_DIR_INC 0x08

struct MixerSource {
    u8 status;
    u8 type;
    u8 rightVol;
    u8 leftVol;

    /* The mixer also overlays PCM state here. This routine uses the CGB view. */
    union {
        struct {
            u8 attack;
            u8 decay;
            u8 sustain;
            u8 release;
            u8 key;
            u8 envelopeVol;

            u8 envelopeGoal;
            u8 envelopeCtr;

            u8 echoVol;
            u8 echoLen;
            u8 padding1;
            u8 padding2;
            u8 gateTime;
            u8 untransposedKey;
            u8 velocity;
            u8 priority;
            u8 rhythmPan;
            u8 padding3;
            u8 padding4;
            u8 padding5;

            u8 padding6;
            u8 sustainGoal;
            u8 nrx4;
            u8 pan;

            u8 panMask;
            u8 cgbStatus;
            u8 length;
            u8 sweep;

            u32 freq;
        } cgb;
    } data;

    void *wav; // The next piece of data to be loading
    void *current; // The working pointer from wav

    struct MP2KTrack *track;
    struct MixerSource *prev;
    struct MixerSource *next;
    u32 padding7; // d4
    u32 blockCount; // bdpcm block count
};

struct SoundMixerState {
    u8 unknown_00[0xA];
    u8 cgbCounter15;
    u8 unknown_0B[0x11];
    struct MixerSource *cgbChans;
};

extern struct SoundMixerState *data_03007FF0;
extern const u8 data_0836D2FC[];
extern void func_08145C44(struct MixerSource *channels);
extern void func_08145BF4(u8 ch);

void func_08145CAC(void)
{
    s32 ch;
    struct MixerSource *channels;
    s32 prevC15;
    struct SoundMixerState *soundInfo = data_03007FF0;
    /* plausible: Each hardware channel selects five byte-wide GBA sound registers. */
    volatile u8 *nrx0ptr;
    volatile u8 *nrx1ptr;
    volatile u8 *nrx2ptr;
    volatile u8 *nrx3ptr;
    volatile u8 *nrx4ptr;
    s32 envelopeStepTimeAndDir;

    // Most comparison operations that cast to s8 perform 'and' by 0xFF.
    int mask = 0xff;

    if (soundInfo->cgbCounter15)
        soundInfo->cgbCounter15--;
    else
        soundInfo->cgbCounter15 = 14;

    for (ch = 1, channels = soundInfo->cgbChans; ch <= 4; ch++, channels++) {
        if (!(channels->status & SOUND_CHANNEL_SF_ON))
            continue;

        /* 1. determine hardware channel registers */
        switch (ch) {
            case 1:
                nrx0ptr = (volatile u8 *)0x04000060;
                nrx1ptr = (volatile u8 *)0x04000062;
                nrx2ptr = (volatile u8 *)0x04000063;
                nrx3ptr = (volatile u8 *)0x04000064;
                nrx4ptr = (volatile u8 *)0x04000065;
                break;
            case 2:
                nrx0ptr = (volatile u8 *)0x04000061;
                nrx1ptr = (volatile u8 *)0x04000068;
                nrx2ptr = (volatile u8 *)0x04000069;
                nrx3ptr = (volatile u8 *)0x0400006C;
                nrx4ptr = (volatile u8 *)0x0400006D;
                break;
            case 3:
                nrx0ptr = (volatile u8 *)0x04000070;
                nrx1ptr = (volatile u8 *)0x04000072;
                nrx2ptr = (volatile u8 *)0x04000073;
                nrx3ptr = (volatile u8 *)0x04000074;
                nrx4ptr = (volatile u8 *)0x04000075;
                break;
            default:
                nrx0ptr = (volatile u8 *)0x04000071;
                nrx1ptr = (volatile u8 *)0x04000078;
                nrx2ptr = (volatile u8 *)0x04000079;
                nrx3ptr = (volatile u8 *)0x0400007C;
                nrx4ptr = (volatile u8 *)0x0400007D;
                break;
        }

        prevC15 = soundInfo->cgbCounter15;
        envelopeStepTimeAndDir = *nrx2ptr;

        /* 2. calculate envelope volume */
        if (channels->status & SOUND_CHANNEL_SF_START) {
            if (!(channels->status & SOUND_CHANNEL_SF_STOP)) {
                channels->status = SOUND_CHANNEL_SF_ENV_ATTACK;
                channels->data.cgb.cgbStatus = CGB_CHANNEL_MO_PIT | CGB_CHANNEL_MO_VOL;
                func_08145C44(channels);
                switch (ch) {
                    case 1:
                        *nrx0ptr = channels->data.cgb.sweep;
                        // fallthrough
                    case 2:
                        *nrx1ptr = ((s32)channels->wav << 6) + channels->data.cgb.length;
                        goto init_env_step_time_dir;
                    case 3:
                        if (channels->wav != channels->current) {
                            *nrx0ptr = 0x40;
                            (*(volatile u32 *)0x04000090) = ((u32 *)channels->wav)[0]; /* plausible: Wave RAM word 0. */
                            (*(volatile u32 *)0x04000094) = ((u32 *)channels->wav)[1]; /* plausible: Wave RAM word 1. */
                            (*(volatile u32 *)0x04000098) = ((u32 *)channels->wav)[2]; /* plausible: Wave RAM word 2. */
                            (*(volatile u32 *)0x0400009C) = ((u32 *)channels->wav)[3]; /* plausible: Wave RAM word 3. */
                            channels->current = channels->wav;
                        }
                        *nrx0ptr = 0;
                        *nrx1ptr = channels->data.cgb.length;
                        if (channels->data.cgb.length)
                            channels->data.cgb.nrx4 = 0xC0;
                        else
                            channels->data.cgb.nrx4 = 0x80;
                        break;
                    default:
                        *nrx1ptr = channels->data.cgb.length;
                        *nrx3ptr = (s32)channels->wav << 3;
                    init_env_step_time_dir:
                        envelopeStepTimeAndDir = channels->data.cgb.attack + CGB_NRx2_ENV_DIR_INC;
                        if (channels->data.cgb.length)
                            channels->data.cgb.nrx4 = 0x40;
                        else
                            channels->data.cgb.nrx4 = 0x00;
                        break;
                }
                channels->data.cgb.envelopeCtr = channels->data.cgb.attack;
                if ((s8)(channels->data.cgb.attack & mask)) {
                    channels->data.cgb.envelopeVol = 0;
                    goto envelope_step_complete;
                } else {
                    // skip attack phase if attack is instantaneous (=0)
                    goto envelope_decay_start;
                }
            } else {
                goto oscillator_off;
            }
        } else if (channels->status & SOUND_CHANNEL_SF_IEC) {
            channels->data.cgb.echoLen--;
            if ((s8)(channels->data.cgb.echoLen & mask) <= 0) {
            oscillator_off:
                func_08145BF4(ch);
                channels->status = 0;
                goto channel_complete;
            }
            goto envelope_complete;
        } else if ((channels->status & SOUND_CHANNEL_SF_STOP) && (channels->status & SOUND_CHANNEL_SF_ENV)) {
            channels->status &= ~SOUND_CHANNEL_SF_ENV;
            channels->data.cgb.envelopeCtr = channels->data.cgb.release;
            if ((s8)(channels->data.cgb.release & mask)) {
                channels->data.cgb.cgbStatus |= CGB_CHANNEL_MO_VOL;
                if (ch != 3)
                    envelopeStepTimeAndDir = channels->data.cgb.release | CGB_NRx2_ENV_DIR_DEC;
                goto envelope_step_complete;
            } else {
                goto envelope_pseudoecho_start;
            }
        } else {
        envelope_step_repeat:
            if (channels->data.cgb.envelopeCtr == 0) {
                if (ch == 3)
                    channels->data.cgb.cgbStatus |= CGB_CHANNEL_MO_VOL;

                func_08145C44(channels);
                if ((channels->status & SOUND_CHANNEL_SF_ENV) == SOUND_CHANNEL_SF_ENV_RELEASE) {
                    channels->data.cgb.envelopeVol--;
                    if ((s8)(channels->data.cgb.envelopeVol & mask) <= 0) {
                    envelope_pseudoecho_start:
                        channels->data.cgb.envelopeVol = ((channels->data.cgb.envelopeGoal * channels->data.cgb.echoVol) + 0xFF) >> 8;
                        if (channels->data.cgb.envelopeVol) {
                            channels->status |= SOUND_CHANNEL_SF_IEC;
                            channels->data.cgb.cgbStatus |= CGB_CHANNEL_MO_VOL;
                            if (ch != 3)
                                envelopeStepTimeAndDir = 0 | CGB_NRx2_ENV_DIR_INC;
                            goto envelope_complete;
                        } else {
                            goto oscillator_off;
                        }
                    } else {
                        channels->data.cgb.envelopeCtr = channels->data.cgb.release;
                    }
                } else if ((channels->status & SOUND_CHANNEL_SF_ENV) == SOUND_CHANNEL_SF_ENV_SUSTAIN) {
                envelope_sustain:
                    channels->data.cgb.envelopeVol = channels->data.cgb.sustainGoal;
                    channels->data.cgb.envelopeCtr = 7;
                } else if ((channels->status & SOUND_CHANNEL_SF_ENV) == SOUND_CHANNEL_SF_ENV_DECAY) {
                    int envelopeVol, sustainGoal;

                    channels->data.cgb.envelopeVol--;
                    envelopeVol = (s8)(channels->data.cgb.envelopeVol & mask);
                    sustainGoal = (s8)(channels->data.cgb.sustainGoal);
                    if (envelopeVol <= sustainGoal) {
                    envelope_sustain_start:
                        if (channels->data.cgb.sustain == 0) {
                            channels->status &= ~SOUND_CHANNEL_SF_ENV;
                            goto envelope_pseudoecho_start;
                        } else {
                            channels->status--;
                            channels->data.cgb.cgbStatus |= CGB_CHANNEL_MO_VOL;
                            if (ch != 3)
                                envelopeStepTimeAndDir = 0 | CGB_NRx2_ENV_DIR_INC;
                            goto envelope_sustain;
                        }
                    } else {
                        channels->data.cgb.envelopeCtr = channels->data.cgb.decay;
                    }
                } else {
                    channels->data.cgb.envelopeVol++;
                    if ((u8)(channels->data.cgb.envelopeVol & mask) >= channels->data.cgb.envelopeGoal) {
                    envelope_decay_start:
                        channels->status--;
                        channels->data.cgb.envelopeCtr = channels->data.cgb.decay;
                        if ((u8)(channels->data.cgb.envelopeCtr & mask)) {
                            channels->data.cgb.cgbStatus |= CGB_CHANNEL_MO_VOL;
                            channels->data.cgb.envelopeVol = channels->data.cgb.envelopeGoal;
                            if (ch != 3)
                                envelopeStepTimeAndDir = channels->data.cgb.decay | CGB_NRx2_ENV_DIR_DEC;
                        } else {
                            goto envelope_sustain_start;
                        }
                    } else {
                        channels->data.cgb.envelopeCtr = channels->data.cgb.attack;
                    }
                }
            }
        }

    envelope_step_complete:
        // every 15 frames, envelope calculation has to be done twice
        // to keep up with the hardware envelope rate (1/64 s)
        channels->data.cgb.envelopeCtr--;
        if (prevC15 == 0) {
            prevC15--;
            goto envelope_step_repeat;
        }

    envelope_complete:
        /* 3. apply pitch to HW registers */
        if (channels->data.cgb.cgbStatus & CGB_CHANNEL_MO_PIT) {
            if (ch < 4 && (channels->type & TONEDATA_TYPE_FIX)) {
                int dac_pwm_rate = (*(volatile u8 *)0x04000089); /* plausible: SOUNDBIAS PWM rate. */

                if (dac_pwm_rate < 0x40) // if PWM rate = 32768 Hz
                    channels->data.cgb.freq = (channels->data.cgb.freq + 2) & 0x7fc;
                else if (dac_pwm_rate < 0x80) // if PWM rate = 65536 Hz
                    channels->data.cgb.freq = (channels->data.cgb.freq + 1) & 0x7fe;
            }

            if (ch != 4)
                *nrx3ptr = channels->data.cgb.freq;
            else
                *nrx3ptr = (*nrx3ptr & 0x08) | channels->data.cgb.freq;
            channels->data.cgb.nrx4 = (channels->data.cgb.nrx4 & 0xC0) + (*((u8 *)(&channels->data.cgb.freq) + 1));
            *nrx4ptr = (s8)(channels->data.cgb.nrx4 & mask);
        }

        /* 4. apply envelope & volume to HW registers */
        if (channels->data.cgb.cgbStatus & CGB_CHANNEL_MO_VOL) {
            (*(volatile u8 *)0x04000081) = ((*(volatile u8 *)0x04000081) & ~channels->data.cgb.panMask) | channels->data.cgb.pan; /* plausible: NR51 routes channels to the two outputs. */
            if (ch == 3) {
                *nrx2ptr = data_0836D2FC[channels->data.cgb.envelopeVol];
                if (channels->data.cgb.nrx4 & 0x80) {
                    *nrx0ptr = 0x80;
                    *nrx4ptr = channels->data.cgb.nrx4;
                    channels->data.cgb.nrx4 &= 0x7f;
                }
            } else {
                u32 envMask = 0xF;
                *nrx2ptr = (envelopeStepTimeAndDir & envMask) + (channels->data.cgb.envelopeVol << 4);
                *nrx4ptr = channels->data.cgb.nrx4 | 0x80;
                if (ch == 1 && !(*nrx0ptr & 0x08))
                    *nrx4ptr = channels->data.cgb.nrx4 | 0x80;
            }
        }

    channel_complete:
        channels->data.cgb.cgbStatus = 0;
    }
}
