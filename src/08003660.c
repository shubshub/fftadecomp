#include "ffta.h"

// Target 0x08003660..0x08003888, 552 bytes including literal pools:
// f0b50f1c3978012958d0012902dc002904d0fde0022900d190e0f9e01549164808601648
// 4860164888601648c8601648086116484861164888611648c86116480862164848621648
// 88621648c8621648164c012505701648206016490a6808213ef1c4fd216800220b208880
// 124802703d70cde0300800030128000801020308013f0208150407080506070891581308
// fd8e1308719c130889c804085dbf1308950c0708f1bc1308d0340003b8340003c0340003
// b8d43608d1340003154c206885880b2d0ad1144801701448206014490a6808213ef18afd
// 20688580114b2068808800210b2800d8011c19800e480f4a1988890089180a680d490b78
// 012103f0cbf906f0fff80b490b4a101c088002207de00000b8340003d0340003c0340003
// b8d43608d4340003100e000330080003d1340003d2340003ffff0000074a1088074b9842
// 64d01188064881420ed1064800680068002809d1138059e0d2340003ffff0000feff0000
// b83400030e4c201c012103f0dbf9201c022103f0d7f906f0d7f80a4e31880a48814219d1
// 094a15682968002912d0a88830801160064908780138087032e00000100e0003d2340003
// feff0000b8340003d0340003a98025e0318880200002084000280bd03188034808403080
// 0248016816e00000ff7f0000b83400030c4c25680c4a1078411c11700006400d0a494018
// 20600a490a6808213ef1f4fc21680d603088888001203870f0bc01bc00470000b8340003
// d0340003c0340003b8d43608

typedef void (*SceneCallback)(u8 index, u8 *phase);

typedef struct SceneRecord {
    struct SceneRecord *previous;
    u16 scene;
} SceneRecord;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer g_callbacks_0836D4B8[];
extern SceneCallback data_03000830[12];
extern SceneRecord *data_030034B8;
extern SceneRecord data_030034C0[2];
extern u8 data_030034D0;
extern u8 data_030034D1;
/* The scene request word.  The ROM re-reads it with no store or call
 * between: ldrh at 0x080037A6 after 0x0800379E, at 0x08003820 after
 * 0x080037E4 and at 0x0800382C after 0x08003820; a plain declaration
 * drops or merges all three.  The reviewed-ram entry for it in the kit's
 * volatile_objects.json holds this evidence (user ruling, 2026-11-26). */
extern volatile u16 data_030034D2;
extern u16 data_030034D4;
extern Table data_03000E10;

extern void func_08002800(u8, u8 *);
extern void func_08030200(u8, u8 *);
extern void func_08023F00(u8, u8 *);
extern void func_08070414(u8, u8 *);
extern void func_08070604(u8, u8 *);
extern void func_08135890(u8, u8 *);
extern void func_08138EFC(u8, u8 *);
extern void func_08139C70(u8, u8 *);
extern void func_0804C888(u8, u8 *);
extern void func_0813BF5C(u8, u8 *);
extern void func_08070C94(u8, u8 *);
extern void func_0813BCF0(u8, u8 *);
extern void func_08006AF8(Table *, u8, SceneCallback, u8);
extern void func_08006B8C(Table *, u8);
extern void func_08009964(void);
extern void func_08009990(void);

// The same text is the body of func_08003888 after its whole-array clear.
static inline void reset_scene_stack(void)
{
    u8 *count;
    SceneRecord **selected;

    count = &data_030034D0;
    selected = &data_030034B8;
    *count = 1;
    *selected = &data_030034C0[0];
    g_callbacks_0836D4B8[0](*selected, sizeof(**selected));
    (*selected)->scene = 11;
}

void func_08003660(u8 index, u8 *phase)
{
    SceneRecord *record;

    switch (*phase) {
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
        reset_scene_stack();
        data_030034D1 = 0;
        *phase = 1;
        break;
    case 1:
        if (data_030034B8->scene == 11)
            reset_scene_stack();
        data_030034D4 = data_030034B8->scene <= 11 ? data_030034B8->scene : 0;
        func_08006AF8(&data_03000E10, 1, data_03000830[data_030034D4],
                      data_030034D1);
        func_08009964();
        data_030034D2 = 0xFFFF;
        *phase = 2;
        break;
    case 2:
        if (data_030034D2 == 0xFFFF)
            break;
        if (data_030034D2 == 0xFFFE && data_030034B8->previous == 0) {
            data_030034D2 = 0xFFFF;
            break;
        }
        func_08006B8C(&data_03000E10, 1);
        func_08006B8C(&data_03000E10, 2);
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
        *phase = 1;
        break;
    }
}
