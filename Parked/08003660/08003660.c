#include "ffta.h"

/* 08003660 .. 08003888: 552 bytes. */
typedef void (*SceneCallback)(void *, u8 *);

typedef struct SceneRecord {
    struct SceneRecord *previous;
    u16 scene;
    u16 unknown_06;
} SceneRecord;

extern SceneCallback data_03000830[12];
extern SceneRecord *data_030034B8;
extern SceneRecord data_030034C0[];
extern u8 data_030034D0;
extern u8 data_030034D1;
extern u16 data_030034D2;
extern u16 data_030034D4;
extern u8 data_03000E10[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);

extern void func_08002800(void *, u8 *);
extern void func_08030200(void *, u8 *);
extern void func_08023F00(void *, u8 *);
extern void func_08070414(void *, u8 *);
extern void func_08070604(void *, u8 *);
extern void func_08135890(void *, u8 *);
extern void func_08138EFC(void *, u8 *);
extern void func_08139C70(void *, u8 *);
extern void func_0804C888(void *, u8 *);
extern void func_0813BF5C(void *, u8 *);
extern void func_08070C94(void *, u8 *);
extern void func_0813BCF0(void *, u8 *);
extern void func_08006AF8(void *, s32, SceneCallback, u32);
extern void func_08006B8C(void *, s32);
extern void func_08009964(void);
extern void func_08009990(void);

void func_08003660(void *context, u8 *stage)
{
    SceneRecord *record;

    switch (*stage) {
    case 0:
        data_03000830[0] = func_08002800;
        data_03000830[1] = func_08030200;
        data_03000830[2] = func_08023F00;
        data_03000830[3] = func_08070414;
        data_03000830[4] = func_08070604;
        data_03000830[5] = func_08135890;
        data_03000830[6] = func_08138EFC;
        data_03000830[7] = func_08139C70;
        data_03000830[8] = func_0804C888;
        data_03000830[9] = func_0813BF5C;
        data_03000830[10] = func_08070C94;
        data_03000830[11] = func_0813BCF0;
        data_030034D0 = 1;
        data_030034B8 = data_030034C0;
        g_callbacks_0836D4B8[0](data_030034B8, sizeof(SceneRecord));
        data_030034B8->scene = 11;
        data_030034D1 = 0;
        *stage = 1;
        break;
    case 1:
        if (data_030034B8->scene == 11) {
            data_030034D0 = 1;
            data_030034B8 = data_030034C0;
            g_callbacks_0836D4B8[0](data_030034B8, sizeof(SceneRecord));
            data_030034B8->scene = 11;
        }
        data_030034D4 = data_030034B8->scene <= 11 ?
                          data_030034B8->scene : 0;
        func_08006AF8(data_03000E10, 1, data_03000830[data_030034D4],
                      data_030034D1);
        func_08009964();
        data_030034D2 = 0xFFFF;
        *stage = 2;
        break;
    case 2:
        if (data_030034D2 == 0xFFFF)
            break;
        if (data_030034D2 == 0xFFFE && data_030034B8->previous == 0) {
            data_030034D2 = 0xFFFF;
            break;
        }
        func_08006B8C(data_03000E10, 1);
        func_08006B8C(data_03000E10, 2);
        func_08009990();
        if (data_030034D2 == 0xFFFE) {
            record = data_030034B8;
            if (record->previous != 0) {
                data_030034D2 = record->scene;
                data_030034B8 = record->previous;
                data_030034D0--;
            } else {
                record->scene = 0;
            }
        } else if (data_030034D2 & 0x8000) {
            data_030034D2 &= 0x7FFF;
            data_030034B8->scene = data_030034D2;
        } else {
            record = data_030034B8;
            data_030034B8 = &data_030034C0[data_030034D0++];
            g_callbacks_0836D4B8[0](data_030034B8, sizeof(SceneRecord));
            data_030034B8->previous = record;
            data_030034B8->scene = data_030034D2;
        }
        *stage = 1;
        break;
    }
}
