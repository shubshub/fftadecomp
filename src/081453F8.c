#include "ffta.h"

/* MusicPlayer2000 MPlayExtender, SAT-R/sa2 src/lib/m4a/m4a.c. */
struct MP2KPlayerState;
struct MP2KTrack;

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
    u32 lockStatus;
    u8 unknown_04[8];
    u8 maxScanlines;
    u8 unknown_0D[0xF];
    struct MixerSource *cgbChans;
    u8 unknown_20[8];
    void (*CgbSound)(void);
    void (*CgbOscOff)(u8);
    u32 (*MidiKeyToCgbFreq)(u8, u8, u8);
};

extern struct SoundMixerState *data_03007FF0;
extern void *data_02008E60[];
/* Linker absolute gMaxLines. The historical GBA MAX_LINES uses its address. */
extern char gMaxLines[];
#define MAX_LINES ((u32)gMaxLines)
extern void func_0814186C(const void *, void *, u32);
extern void func_0814636C(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_08145070(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_08145084(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_081464C4(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_08145008(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_08145608(u32);
extern void func_08144D94(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_081459D0(struct MP2KPlayerState *);
extern void func_08145A98(struct MP2KPlayerState *, struct MP2KTrack *);
extern void func_08145CAC(void);
extern void func_08145BF4(u8);
extern u32 func_08145B4C(u8, u8, u8);

void func_081453F8(struct MixerSource *cgbChans)
{
    struct SoundMixerState *soundInfo;
    u32 lockStatus;
    u32 zero;

    /* plausible: Master sound enable and channel status. */
    *(volatile u16 *)0x04000084 = 0x8F;
    /* plausible: PSG channel mix control. */
    *(volatile u16 *)0x04000080 = 0; // set master volume to zero
    /* plausible: Channel 1 envelope. */
    *(volatile u8 *)0x04000063 = 0x8;
    /* plausible: Channel 2 envelope. */
    *(volatile u8 *)0x04000069 = 0x8;
    /* plausible: Channel 4 envelope. */
    *(volatile u8 *)0x04000079 = 0x8;
    /* plausible: Channel 1 trigger. */
    *(volatile u8 *)0x04000065 = 0x80;
    /* plausible: Channel 2 trigger. */
    *(volatile u8 *)0x0400006D = 0x80;
    /* plausible: Channel 4 trigger. */
    *(volatile u8 *)0x0400007D = 0x80;
    /* plausible: Wave channel enable. */
    *(volatile u8 *)0x04000070 = 0;
    /* plausible: PSG master volume. */
    *(volatile u8 *)0x04000080 = 0x77;


    soundInfo = data_03007FF0;

    lockStatus = soundInfo->lockStatus;

    if (lockStatus != 0x68736D53)
        return;

    soundInfo->lockStatus++;

    data_02008E60[8] = func_0814636C;
    data_02008E60[17] = func_08145070;
    data_02008E60[19] = func_08145084;
    data_02008E60[28] = func_081464C4;
    data_02008E60[29] = func_08145008;
    data_02008E60[30] = func_08145608;
    data_02008E60[31] = func_08144D94;
    data_02008E60[32] = func_081459D0;
    data_02008E60[33] = func_08145A98;

    soundInfo->cgbChans = cgbChans;
    soundInfo->CgbSound = func_08145CAC;
    soundInfo->CgbOscOff = func_08145BF4;
    soundInfo->MidiKeyToCgbFreq = func_08145B4C;
    soundInfo->maxScanlines = MAX_LINES;

    zero = 0;
    func_0814186C(&zero, cgbChans, 0x05000000 | (sizeof(struct MixerSource) * 4 / sizeof(u32)));

    cgbChans[0].type = 1;
    cgbChans[0].data.cgb.panMask = 0x11;
    cgbChans[1].type = 2;
    cgbChans[1].data.cgb.panMask = 0x22;
    cgbChans[2].type = 3;
    cgbChans[2].data.cgb.panMask = 0x44;
    cgbChans[3].type = 4;
    cgbChans[3].data.cgb.panMask = 0x88;

    soundInfo->lockStatus = lockStatus;
}
