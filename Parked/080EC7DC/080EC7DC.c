#include "ffta.h"
#include "control_flags.h"

// func_080EC7DC: complete [0x080EC7DC, 0x080ECCDC), 1280 bytes, 541 instructions
// plus literal pools.  A scene effect that drops one screen column at a time:
// it captures two BG maps, opens window 0 over the column, slides it down along
// an interpolated line, shifts the column's map rows and shakes both layers.
// f0b557464e464546e0b484b0061c8a46171c098881204000814200d190e081420edc012946d0012902dc002919d00ee2
// 80204000814251d00130814268d006e282204000814200d168e1814200da15e10130814200d17ae10130814200d1b5e1
// f5e15146888af8800022fd1c391d3b1c08335024500018180480501c0006020e0a2af7d95246908af883d08a3884908a
// 0004c0147884d08a0004c0140a38b884281c31f7c7fe024bf91801200870cee158100000022016f789fe064c21888143
// 2180032016f782fe21888143024801402180bce140090003ffdf00002221785e2422b95e3c1c583400220092231c2ef7
// b1fee7f713f9054a8023db00211c14f7ddf8534618880130a0e10000005800062221785e2422b95e074bfc1800940022
// 00232ef797fee7f7f9f8044a8023db00211c14f7c3f805e158080000005000064a4901a8082257f06bfd1e22b85e2023
// f95e8822502331f707fc022016f74afe041c032016f746fe4149894604433f25281ca0434a464232117800261070f878
// 16f738fe041c387916f734fe0443a543484644300178057049463b3108780e70013908780e70053108780e7001390878
// ff2008704a46118880239b01181c0843108003ad0d2068448046281c414631f739fe284817f760f8041cc026f604301c
// 17f760f804432878400068440430008804432404240c201c022116f76ffd0020022116f793fd5020022116f7b7fd1a48
// 17f742f8041c301c17f744f8044341460878400068440430008804432404240c201c032116f752fd0020032116f776fd
// 5020032116f79afd022016f7bffd4a46118801431180032016f7b8fd4b461988014319805020f88438856be0e09c1408
// 4009000300580006005000063878002800d1e4e000203870ba7892001d48121810787870797889001b4809181b480b78
// 051c3b352c782b7049783a3003780170381c2c30797849003c1c083461180023c95e5378cb1a9278009200221af790fd
// 787840002418208838850d49b87840180078002809d00b480096012104220023f3f75ef9084ab9180860534618880130
// a4e00000609139084c913908400900034c923908449239085c1000003c1c2c34201c1af7cffdf86a3885201c1af7bafe
// 002800d18be078784000391c08310918f86a088051460888013008807fe01c4978788000401802784078c00881461949
// b878800040184078c508d0085822d2199046484517d21f23461cab420fd342004446990151186118581b800110182018
// 00880880581e0006030eab42f1d23006000e4845e7d3e6f7b9ff074a8023db00414613f783ff53461888013046e00000
// 4c9139086091390800580006434978788000401802784078c00880464049b878800040184078c508d00840451ad23d49
// 89461f23461cab4210d3420048463c18990151186118581b80011018201800880880581e0006030eab42f1d23006000e
// 4045e6d3e6f77aff2e4ab9182e4a8023db0013f743ff2d48021c3b321178002111703a30027801702948534618805046
// 018881204000814237d9264ab9180878013808700006002809d1022008700022214bf9180878002800d101220a701e49
// 781800781d4c002800d00324f88c24042414201800040014022116f76ffcf88c201800040014032116f768fc388d2018
// 00040014f97816f761fc388d2418240424143979201c16f759fc002004b038bc9846a146aa46f0bc02bc08474c913908
// 60913908580800000050000640090003030100005810000059100000fdff0000

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    s16 x;
    s16 y;
} Descriptor080EC7DC;

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u8 pending;
    u8 column;
    u8 step;
    u8 first_layer;
    u8 second_layer;
    u8 unknown_05;
    s16 unknown_06;
    s16 column_offsets[11];
    s16 x;
    s16 y;
    s16 tile_x;
    s16 tile_y;
    s16 first_offset;
    s16 second_offset;
    u8 unknown_2A[2];
    LineState line;
    u16 first_map[32][32];
    u16 second_map[32][32];
    u8 timer;
    u8 shake;
    u8 unknown_105A[2];
    void *effect;
} Payload080EC7DC;

typedef struct {
    u8 left;
    u8 right;
    u8 unknown_02[2];
} Column080EC7DC;

typedef struct {
    u8 column;
    u8 drop;
    u8 duration;
    u8 unknown_03;
} Step080EC7DC;

typedef struct TransferRecord TransferRecord;

extern const Column080EC7DC data_0839914C[];
extern const Step080EC7DC data_08399160[];
extern const u8 data_08399244[];
extern const u8 data_0839924C[];

extern void func_0801E610(u8 *first, u8 *second);
extern void func_0801E620(u8 *first, u8 *second);
extern void func_0801E144(s16 x, s16 y, s16 inset_x, s16 inset_y);
extern void func_0801B630(int x, int y, int layer, u16 *first, u16 *second);
extern TransferRecord *func_080D3AF8(void);
extern void func_08000A98(TransferRecord *entry, const void *source,
                          void *destination, u16 count);
extern u16 func_080035A8(u8 layer);
extern u16 func_080035D0(u8 layer);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 offset, u8 layer);
extern void func_08003558(s16 offset, u8 layer);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const void *state);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);

u32 func_080EC7DC(void *task, Descriptor080EC7DC *descriptor,
                  Payload080EC7DC *payload)
{
    u8 i;
    const Step080EC7DC *step;
    const Column080EC7DC *column;
    s16 offset;

    switch (descriptor->phase) {
    case 0:
        payload->unknown_06 = descriptor->x;
        for (i = 0; i < 11; i++)
            payload->column_offsets[i] = 0x50;
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        payload->tile_x = descriptor->x >> 3;
        payload->tile_y = (descriptor->y >> 3) - 10;
        func_0801E610(&payload->first_layer, &payload->second_layer);
        payload->timer = 1;
        break;
    case 1:
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.display &= ~func_080035A8(3);
        g_control_flags_03000940.display &= ~0x2000;
        break;
    case 0x100:
        func_0801B630(payload->tile_x, payload->tile_y, 0,
                      &payload->first_map[0][0], 0);
        func_08000A98(func_080D3AF8(), payload->first_map,
                      (void *)0x06005800, 0x400);
        descriptor->phase++;
        break;
    case 0x101:
        func_0801B630(payload->tile_x, payload->tile_y, 0, 0,
                      &payload->second_map[0][0]);
        func_08000A98(func_080D3AF8(), payload->second_map,
                      (void *)0x06005000, 0x400);
        descriptor->phase++;
        break;
    case 0x102: {
        u16 priorities[4] = {0, 1, 2, 3};
        u8 first;
        u8 second;

        func_0801E144(payload->x, payload->y, 0x88, 0x50);
        g_control_flags_03000940.winin_lo =
            0x3F & ~(func_080035D0(2) | func_080035D0(3));
        g_control_flags_03000940.winout_lo =
            0x3F & ~(func_080035D0(payload->first_layer)
                     | func_080035D0(payload->second_layer));
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xFF;
        g_control_flags_03000940.display |= 0x2000;
        func_0801E620(&first, &second);
        func_080034B8(func_08003A74(0x06005800) | func_08003A80(0x06000000)
                      | priorities[first], 2);
        func_08003508(0, 2);
        func_08003558(0x50, 2);
        func_080034B8(func_08003A74(0x06005000) | func_08003A80(0x06000000)
                      | priorities[second], 3);
        func_08003508(0, 3);
        func_08003558(0x50, 3);
        g_control_flags_03000940.display |= func_080035A8(2);
        g_control_flags_03000940.display |= func_080035A8(3);
        payload->first_offset = 0x50;
        payload->second_offset = 0x50;
        descriptor->phase++;
        break;
    }
    case 0x103:
        if (payload->pending == 0)
            break;
        payload->pending = 0;
        step = &data_08399160[payload->step];
        payload->column = step->column;
        column = &data_0839914C[payload->column];
        g_control_flags_03000940.win0h_hi = column->left;
        g_control_flags_03000940.win0h_lo = column->right;
        func_080075CC(&payload->line, payload->column_offsets[payload->column], 0,
                      payload->column_offsets[payload->column] - step->drop,
                      step->duration);
        payload->second_offset = payload->column_offsets[payload->column];
        if (data_0839924C[payload->step])
            payload->effect = func_080DFD8C(data_08399244, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        func_080076A0(&payload->line);
        payload->second_offset = payload->line.x;
        if (func_08007880(&payload->line)) {
            payload->column_offsets[payload->column] = payload->line.x;
            descriptor->phase++;
        }
        break;
    case 0x105: {
        u8 left;
        u8 right;
        u8 drop;
        u8 x;
        u8 y;

        left = data_0839914C[payload->column].left >> 3;
        right = data_0839914C[payload->column].right >> 3;
        drop = data_08399160[payload->step].drop >> 3;
        for (x = left; x < right; x++)
            for (y = 31; y >= drop; y--)
                payload->first_map[y][x] = payload->first_map[y - drop][x];
        func_08000A98(func_080D3AF8(), payload->first_map,
                      (void *)0x06005800, 0x400);
        descriptor->phase++;
        break;
    }
    case 0x106: {
        u8 left;
        u8 right;
        u8 drop;
        u8 x;
        u8 y;

        left = data_0839914C[payload->column].left >> 3;
        right = data_0839914C[payload->column].right >> 3;
        drop = data_08399160[payload->step].drop >> 3;
        for (x = left; x < right; x++)
            for (y = 31; y >= drop; y--)
                payload->second_map[y][x] = payload->second_map[y - drop][x];
        func_08000A98(func_080D3AF8(), payload->second_map,
                      (void *)0x06005000, 0x400);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        descriptor->phase = 0x103;
        break;
    }
    }
    if (descriptor->phase > 0x102) {
        if (--payload->timer == 0) {
            payload->timer = 2;
            payload->shake = !payload->shake;
        }
        offset = payload->shake ? 3 : -3;
        func_08003558(offset + payload->first_offset, 2);
        func_08003558(offset + payload->first_offset, 3);
        func_08003558(offset + payload->second_offset, payload->first_layer);
        func_08003558(offset + payload->second_offset, payload->second_layer);
    }
    return 0;
}
