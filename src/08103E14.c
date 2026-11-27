#include "ffta.h"

/* 0x08103E14..0x081042C8, 1204 bytes (602 halfwords, complete span including
 * literal pools), phase handler shared by entries 0xDC..0xDE of the table at
 * 0x083947D8 (words at 0x08394EB0/EB8/EC0; src/080D3B98.c indexes it by
 * entry - 1), sha1 of the ROM bytes d0208e027ef555f59578aae081714435d97e2125.
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u8 effect;
    u8 unknown_15;
    u16 flag;
} Descriptor08103E14;

typedef struct {
    u8 flag;
    u8 kind;
    u16 countdown;
    u8 facing;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_0B;
    void *sprite;
    void *second_sprite;
    void *outputs[2];
    void *animation;
    void *second_outputs[2];
    void *second_animation;
    void *third_outputs[1];
    void *third_animation;
    void *resource;
    void *actor;
    void *object;
    void *coordinates;
    void *child;
    void *initial;
    void *record;
    void *preparation;
    void *effect;
} Payload08103E14;

extern const u8 data_0839F31C[];
extern const s16 data_08149E30[];
extern u8 data_06017C00[];
extern const u8 data_085028E0[];
extern const u8 data_08502630[];
extern const u8 data_0839F370[];
extern const u8 data_0839F428[];
extern const u8 data_0839F424[];
extern const u8 data_0894A76C[];
extern const u8 data_0839F430[];
extern const u8 data_0839F3A0[];
extern const u8 data_0839F3D0[];
extern const u8 data_0839F438[];
extern const u8 data_0839F3E8[][20];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void func_080DE390(void *);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080DD4A4(void *, u8);
extern s8 func_080DBC88(void *);
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern s16 func_080DD56C(void *);
extern void *func_080D5FD8(u16 id, u8 layer, s16 x, s16 y, u16 width,
                           u32 tiles, u8 bank, void *parent);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011118(void *, u8);
extern void func_08011058(void *, s16);
extern void func_080111A8(void *, u8);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void *buffer, const void *records, void *parent);
extern void func_080D6194(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void func_0801115C(void *, u8);
extern void func_08011428(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                           u16, u16, void *);
extern void func_080DC12C(void *, u8, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD580(void *);
extern void func_080107D4(void *, s16, s16, u8);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D4774(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_08103E14(void *task, Descriptor08103E14 *descriptor,
                  Payload08103E14 *payload)
{
    u8 mode;
    s16 x, y;

    switch (descriptor->phase) {
    case 0:
        payload->kind = descriptor->effect - 0xDC;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 7;
        if (payload->flag != 0)
            mode = 0;
        payload->initial = func_080E03F8(payload->actor, data_0839F31C, mode,
                                         0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial = func_080E05DC(payload->initial);
        if (payload->initial != 0)
            break;
        if (func_080D3B54(payload->actor) != 0) {
            descriptor->phase = 2;
            break;
        }
        payload->object = func_080DD47C(payload->actor);
        func_080DE390(payload->object);
        func_080DBDC8(payload->object, &x, &y);
        payload->child = func_080DD4A4(payload->actor, 0);
        payload->facing = func_080DBC88(payload->object);
        {
            /* One copy at sp+0x18, above x/y at sp+0x14/0x16; each arm
             * fills it (calls at 0x08103F1C and 0x08103F6C). */
            s16 offsets[4];

            if (payload->kind != 2) {
                func_081443FC(offsets, data_08149E30, sizeof(offsets));
                payload->sprite = func_080D5FD8(func_080DD56C(payload->child),
                                                0, x + offsets[payload->facing],
                                                y - 0x23, 0,
                                                (u32)data_06017C00, 8, task);
            } else {
                func_081443FC(offsets, data_08149E30, sizeof(offsets));
                payload->sprite = func_080D5CC0(data_085028E0, 0,
                                                x + offsets[payload->facing],
                                                y - 0x23, 0x3E0, 8, 0, 0);
            }
        }
        payload->second_sprite = func_080D5CC0(data_08502630, 0, x, y, 0x3EF,
                                               6, 0, 0);
        if (payload->facing > 1)
            func_08011118(payload->second_sprite, 1);
        func_08011058(payload->sprite, 1);
        func_08011058(payload->second_sprite, 2);
        func_080111A8(payload->sprite, 1);
        func_080111A8(payload->second_sprite, 1);
        payload->animation = func_080D6098(x, y, 0, 1, 2, payload->outputs,
                                           data_0839F370, task);
        if (payload->facing > 1)
            func_080D6194(payload->animation, 1);
        payload->effect = func_080DFD8C(data_0839F428, 1, 4, 0, task);
        payload->countdown = 6;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->countdown != 0 && --payload->countdown == 0) {
            func_080111A8(payload->sprite, 0);
            func_080111A8(payload->second_sprite, 0);
        }
        payload->animation = func_080D6134(payload->animation);
        if (payload->animation != 0)
            break;
        func_080111A8(payload->sprite, 1);
        func_080111A8(payload->second_sprite, 1);
        payload->countdown = 6;
        descriptor->phase++;
        break;
    case 0x102:
        if (--payload->countdown != 0)
            break;
        func_080111A8(payload->sprite, 0);
        func_0801115C(payload->sprite, 0);
        func_08011428(payload->second_sprite);
        payload->second_sprite = 0;
        payload->preparation = func_080DDF68(payload->actor, 0, 0x8007, 1,
                                             &payload->ready, data_0839F424,
                                             5, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (payload->ready == 0)
            break;
        func_080DC12C(payload->actor, 0, 0);
        payload->countdown = 10;
        descriptor->phase++;
        /* Fall through to the timer phase. */
    case 0x104:
        if (payload->countdown != 0 && --payload->countdown != 0)
            break;
        if (func_080D8B4C() != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            func_08011428(payload->sprite);
            payload->sprite = 0;
            descriptor->phase = 2;
            break;
        }
        payload->coordinates = func_080DD748(payload->child, &payload->x,
                                             &payload->y, 0);
        if (func_080DD580(payload->child) == 0) {
            func_08011428(payload->sprite);
            payload->sprite = 0;
            descriptor->phase = 0x106;
            break;
        }
        func_0801115C(payload->sprite, 1);
        func_080107D4(payload->sprite, payload->x, payload->y - 0x20, 0);
        payload->resource = func_080D4724(data_0894A76C, task, 0x14);
        payload->effect = func_080DFD8C(data_0839F430, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        payload->resource = func_080D4774(payload->resource);
        if (payload->resource != 0)
            break;
        func_08011428(payload->sprite);
        payload->sprite = 0;
        payload->second_animation = func_080D6098(payload->x, payload->y, 0, 1,
                                                  2, payload->second_outputs,
                                                  data_0839F3A0, task);
        if (payload->kind == 2 && func_080DD580(payload->child) != 0) {
            payload->third_animation = func_080D6098(payload->x, payload->y,
                                                     0, 1, 1,
                                                     payload->third_outputs,
                                                     data_0839F3D0, task);
            payload->effect = func_080DFD8C(data_0839F438, 1, 4, 0, task);
        }
        descriptor->phase++;
        break;
    case 0x106:
        payload->second_animation = func_080D6134(payload->second_animation);
        if (payload->second_animation != 0)
            break;
        payload->third_animation = func_080D6134(payload->third_animation);
        if (payload->third_animation != 0)
            break;
        payload->record = func_080DCFE4(payload->child,
                                        data_0839F3E8[payload->kind], 12, 0,
                                        12, task, 0);
        descriptor->phase++;
        break;
    case 0x107:
        if (func_080DE244(payload->object) == 0)
            break;
        payload->record = func_080DBA5C(payload->record);
        if (payload->record == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
