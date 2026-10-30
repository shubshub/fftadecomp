#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAC];
    u8 count;
    u8 unknown_AD;
    u8 flags;
} InputState080C76C4;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 ticks;
} SystemState080C76C4;

typedef struct {
    u32 value;
    u8 queue[0x60];
    u16 phase;
    u8 unknown_66[0x46];
} State080C76C4;

typedef void (*BufferCopier080C76C4)(void *destination,
                                    const void *source, u32 size);

extern InputState080C76C4 data_02015738;
extern SystemState080C76C4 data_030028A0;
extern State080C76C4 data_020158B0;
extern u8 data_02015960[];
typedef struct {
    u8 unknown_00[0x3C32];
    u8 byte_3C32;
    u8 byte_3C33;
    u8 bytes_3C34[8];
} SnapshotState080C76C4;

extern SnapshotState080C76C4 g_state_02000000;
extern BufferCopier080C76C4 const data_0836D4BC[];

extern s32 func_08004D68(void);
extern u8 func_080C5F94(void *context);

static inline u8 input_blocked(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }
    if (((data_02015738.flags & 0x20) || data_02015738.count > 13) &&
        (data_030028A0.busy != 0 ||
         (data_030028A0.mode != 3 && data_030028A0.ticks > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

/* Complete [0x080C76C4, 0x080C779C), 216 bytes.
 * Target: 30b50a4c0a49081cae3002784020104000280fd08020104000282fd03df742fb0121484041420143c90f28e0b45801023857010220201040002804d1081cac3000780d280fd90c4a90235b00d018008800280fd19078032805d091256d0050190088102806d8081cae30017808200840002803d0012102e0a02800030021002901d0022002e0201cfef722fc0006000e041c002c11d10b480b490b780b4d421913704b78013542191370094a094bc0180231136808227af069fd201c30bc02bc084700000000000260590102323c0000bcd43608343c0000
 */
u8 func_080C76C4(void)
{
    void *queue = data_020158B0.queue;
    u32 status;
    u8 result;

    if (!input_blocked())
        status = func_080C5F94(queue);
    else
        status = 2;
    result = (u8)status;
    if (result == 0) {
        SnapshotState080C76C4 *state = &g_state_02000000;
        u8 *saved = data_02015960;

        state->byte_3C32 = saved[0];
        state->byte_3C33 = saved[1];
        data_0836D4BC[0](state->bytes_3C34, saved + 2, 8);
    }
    return result;
}
