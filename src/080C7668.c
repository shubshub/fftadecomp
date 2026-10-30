#include "ffta.h"

typedef struct {
    void *context;
    u8 unknown_04[4];
    void *buffer;
    u8 unknown_0C[4];
    u16 width;
    u16 mode;
    u8 unknown_14;
    u8 index;
    u8 blocks;
    u8 unknown_17;
    u16 command;
    u16 count;
    u16 commands[34];
} CommandQueue080C5D60;

typedef struct {
    u32 value;
    CommandQueue080C5D60 queue;
    u16 phase;
    u8 unknown_66[0x46];
} State080C7668;

typedef void (*BufferCopier080C7668)(void *destination,
                                    const void *source, u32 size);

extern State080C7668 data_020158B0;
extern u8 data_02015960[];
extern u8 g_state_02000000[];
extern BufferCopier080C7668 const data_0836D4BC[];

extern void func_080C5D60(CommandQueue080C5D60 *queue, void *context,
                         u16 width, u8 mode);

/* Complete [0x080C7668, 0x080C76C4), 92 bytes.
 * Target: 30b5041c2406240e0e4d0f490f4a8818007828700e4bc818007868700d4aa81c0133c918136808227af0defd0023002c00d101230848291c0c22fef75dfb30bc01bc00476059010200000002323c0000333c0000bcd43608b4580102
 */
void func_080C7668(u8 mode)
{
    u8 *saved = data_02015960;
    u8 *state = g_state_02000000;
    s32 queue_mode;

    saved[0] = state[0x3C32];
    saved[1] = state[0x3C33];
    data_0836D4BC[0](saved + 2, state + 0x3C34, 8);
    queue_mode = 0;
    if (mode == 0)
        queue_mode = 1;
    func_080C5D60(&data_020158B0.queue, saved, 12, queue_mode);
}
