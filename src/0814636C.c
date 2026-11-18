#include "ffta.h"

typedef struct MusicPlayer {
    u8 unknown_00[0x18];
    u8 *memAccArea;
} MusicPlayer;

typedef struct MusicTrack {
    u8 unknown_00[0x40];
    const u8 *cmdPtr;
} MusicTrack;

typedef void (*CommandHandler)(MusicPlayer *, MusicTrack *);
extern CommandHandler data_02008E60[];

/* Complete target: [0x0814636C, 0x081464C4), 344 bytes.
 * MusicPlayer2000 MP2K_event_memacc, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Reads a memory operation, byte index and value from the track command stream.
 * Conditional operations invoke the jump handler or skip its four-byte argument. */

#define MEMACC_COND_JUMP(cond)                                                                                                             \
    if (cond)                                                                                                                              \
        goto cond_true;                                                                                                                    \
    else                                                                                                                                   \
        goto cond_false;

void func_0814636C(struct MusicPlayer *mplayInfo, struct MusicTrack *track)
{
    u32 op;
    u8 *addr;
    u8 data;

    op = *track->cmdPtr;
    track->cmdPtr++;

    addr = mplayInfo->memAccArea + *track->cmdPtr;
    track->cmdPtr++;

    data = *track->cmdPtr;
    track->cmdPtr++;

    switch (op) {
        case 0:
            *addr = data;
            return;
        case 1:
            *addr += data;
            return;
        case 2:
            *addr -= data;
            return;
        case 3:
            *addr = mplayInfo->memAccArea[data];
            return;
        case 4:
            *addr += mplayInfo->memAccArea[data];
            return;
        case 5:
            *addr -= mplayInfo->memAccArea[data];
            return;
        case 6:
            MEMACC_COND_JUMP(*addr == data)
            return;
        case 7:
            MEMACC_COND_JUMP(*addr != data)
            return;
        case 8:
            MEMACC_COND_JUMP(*addr > data)
            return;
        case 9:
            MEMACC_COND_JUMP(*addr >= data)
            return;
        case 10:
            MEMACC_COND_JUMP(*addr <= data)
            return;
        case 11:
            MEMACC_COND_JUMP(*addr < data)
            return;
        case 12:
            MEMACC_COND_JUMP(*addr == mplayInfo->memAccArea[data])
            return;
        case 13:
            MEMACC_COND_JUMP(*addr != mplayInfo->memAccArea[data])
            return;
        case 14:
            MEMACC_COND_JUMP(*addr > mplayInfo->memAccArea[data])
            return;
        case 15:
            MEMACC_COND_JUMP(*addr >= mplayInfo->memAccArea[data])
            return;
        case 16:
            MEMACC_COND_JUMP(*addr <= mplayInfo->memAccArea[data])
            return;
        case 17:
            MEMACC_COND_JUMP(*addr < mplayInfo->memAccArea[data])
            return;
        default:
            return;
    }

cond_true : {
    {
        void (*func)(struct MusicPlayer *, struct MusicTrack *) = *(&data_02008E60[1]);
        func(mplayInfo, track);
    }
    return;
}

cond_false:
    track->cmdPtr += 4;
}

