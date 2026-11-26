// Target: complete [0x081104DC, 0x08110888), 940 bytes:
// f0b557464e464546e0b485b081468a469046098880204000814231d0814202dc00290cd0b9e181
// 204000814200d1ffe0814229db0130814200d199e1ade151464868424650600a490a1c4a321078
// ef2010700a88074810400880074cc3f7defa064a8023db00211cf0f6ecfa95e1000040090003ff
// 9f0000fd63000000580006481c5346188088e1604c4a3420780025ef2020705e48009501950021
// 02220023c6f750fe0020f3f64df8207825700027bc00e419a400574824187d0108354544002022
// 5e0221635ebc2080000090062001900020029003904f48391cc5f782fb2860022100f79efd2868
// 012100f796fd2868012100f78afe2e1c01ce80225200111c002300f774fe0022a15e0423e25e30
// 1c3c23d0f70af810350220215e0623e25e281c3c23d0f701f8781c0006070e0a2fbdd90027fc00
// 384d6519e41ba400e42040002418444429786a78ab78b520800000900620019000200290039030
// 48c5f740fb261c01c6022100f75bfd69780423ea5e301c3c23cff7d8ff1034a97806202a5e201c
// 3c23cff7d0ff781c0006070e0d2fcfd91d4d291c443108783f243f2008700220f2f6a5ff844329
// 1c453108780c70298880221202101c08432880184828214a46c3f70dfcd4218900414408600df7
// 45fa14484b460093012104220023cff765fbd6218900414408600f484946c4f719f8d521890041
// 4408600621c4f77ef8514608880130c5e040090003cc468f08d82f3a08b01d5008f0303a08681e
// 5008d0d99408102f3a0818aa94080122049243461888013018800026b000801980002349451870
// 01083041460c182068002842d0271d381ccff789ff201c1030cff785ff20680422a15e1023e25e
// 002300f741f8288aa18b401800229146a08380214900aa68002a04d04346188840008018018880
// 225200eb68002b04d0424610884000c0180288a38b2068090409141204121400f79bfd381ccff7
// 7aff0006002808d0206800f740fe4b46236004e00000d82f3a0800200490701c0006060e0a2eab
// d90026f000801b8000e4214900401842461518286800281dd02c1d201ccff735ff281c1030cff7
// 31ff28680423e95e1023ea5e0023fff6edff201ccff748ff0006002805d0286800f70efe002028
// 6001e000200490701c0006060e0d2ed1d90499002927d00220f2f6befe064a1188814311804246
// 516807200870534618880130188017e0000040090003d524a40044442068c3f78eff206000280b
// d1d424a40044442068c3f74ffb2060002802d1022051460880002005b038bc9846a146aa46f0bc
// 02bc0847

#include "ffta.h"
#include "control_flags.h"

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    u8 *actor;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct RotatingObject {
    void *object;
    struct InterpolationState x_motion;
    struct InterpolationState y_motion;
    s16 rotation;
    u16 unknown_1e;
};

struct MovingObject {
    void *object;
    struct InterpolationState x_motion;
    struct InterpolationState y_motion;
};

struct Payload {
    u16 counter;
    u16 unknown_02;
    u8 *actor;
    struct RotatingObject rotating[11];
    u8 unknown_168[0x60];
    struct MovingObject moving[14];
    void *resource_task;
    void *effect_task;
    void *record_task;
};

struct RotatingDefinition {
    s16 start_x;
    s16 start_y;
    s16 end_x;
    s16 end_y;
    const s16 *x_scale;
    const s16 *y_scale;
    u16 rotation;
    u16 unknown_12;
};

struct MovingDefinition {
    u8 kind;
    u8 start_x;
    u8 start_y;
    u8 unknown_03;
    s16 end_x;
    s16 end_y;
};

extern u8 data_06005800[];
extern const u8 data_088F46CC[];
extern const struct RotatingDefinition data_083A2FD8[];
extern const u8 data_08501DB0[];
extern const struct MovingDefinition data_083A30F0[];
extern const u8 data_08501E68[];
extern const u8 data_0894D9D0[];
extern const u8 data_083A2F10[];
extern const u8 data_0894AA18[];

extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, u32, u16);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void func_08003620(u8);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011100(void *, u8);
extern void func_080110F8(void *, u8);
extern void func_080112E8(void *, u8);
extern void func_080112CC(void *, s16, s16, u16);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern u16 func_080035D0(u8);
extern void *func_080D3EC0(const void *, u16, void *);
extern void func_0801DB3C(void);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4704(const void *, void *);
extern void func_080D47DC(void *, u16);
extern void func_080E064C(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, u8);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_08011428(void *);
extern u16 func_080035A8(u8);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);

u32 func_081104DC(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    u8 index;

    switch (descriptor->phase) {
    case 0: {
        u16 entry;

        payload->actor = descriptor->actor;
        g_control_flags_03000940.bldcnt_lo = 0xEF;
        g_control_flags_03000940.display &= 0x9FFF;
        /* Map entry: palette 6, tile 0x3FD, as in merged src/080E0A8C.c: the
         * ROM loads it into r4 before the func_080D3AF8 call and copies it to
         * r1 after it (0x08110536, 0x08110542). */
        entry = 0x63FD;
        func_08000B20(func_080D3AF8(), entry, (u32)data_06005800, 0x400);
        break;
    }
    case 1:
        break;
    case 0x100:
        descriptor->phase++;
        break;
    case 0x101:
        g_control_flags_03000940.bldcnt_lo = 0xEF;
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        func_08003620(0);
        g_control_flags_03000940.bldcnt_lo = 0;
        for (index = 0; index < 11; index++) {
            const struct RotatingDefinition *definition = &data_083A2FD8[index];
            struct RotatingObject *object = &payload->rotating[index];

            object->object = func_080D5CC0(data_08501DB0, index,
                definition->start_x, definition->start_y, 0x2F0, 6, 0, 0);
            func_08011100(object->object, 2);
            func_080110F8(object->object, 1);
            func_080112E8(object->object, 1);
            func_080112CC(object->object, 0x100, 0x100, 0);
            func_080E0608(&object->x_motion, definition->start_x,
                definition->end_x, 60);
            func_080E0608(&object->y_motion, definition->start_y,
                definition->end_y, 60);
        }
        for (index = 0; index < 14; index++) {
            const struct MovingDefinition *definition = &data_083A30F0[index];
            struct MovingObject *object = &payload->moving[index];

            object->object = func_080D5CC0(data_08501E68, definition->kind,
                definition->start_x, definition->start_y, 0x2D4, 6, 0, 0);
            func_08011100(object->object, 2);
            func_080E0608(&object->x_motion, definition->start_x,
                definition->end_x, 60);
            func_080E0608(&object->y_motion, definition->start_y,
                definition->end_y, 60);
        }
        g_control_flags_03000940.winout_lo = 0x3F;
        g_control_flags_03000940.winout_hi = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.display |= 0x8000;
        payload->resource_task = func_080D3EC0(data_0894D9D0, 40, task);
        func_0801DB3C();
        payload->record_task = func_080DFD8C(data_083A2F10, 1, 4, 0, task);
        payload->effect_task = func_080D4704(data_0894AA18, task);
        func_080D47DC(payload->effect_task, 6);
        descriptor->phase++;
        break;
    case 0x102: {
        u32 finished = 1;
        u8 update_index;

        /* BUG: the counter is stepped (0x08110710-0x08110716) before it
         * indexes the scale tables (0x08110768-0x08110770 and
         * 0x0811077C-0x08110784).  Every table has 60 entries (seven of
         * them back to back at 0x083A39D8-0x083A3D1F), entry 0 is the
         * scale phase 0x101 gives each object, and every motion lasts 60
         * steps.  So passes 1 to 59 read entries 1 to 59, and the 60th
         * pass, the one that unlinks the objects (0x081107A4), reads entry
         * 60: the next table's entry 0 (0x0100) or, for object 7's y
         * scale, 0x000A at 0x083A3D20, the first halfword of
         * data_083A3D20.  func_080112CC only stores it (0x08110792) and
         * the object is unlinked later in the same pass, so nothing is
         * drawn from it.  docs/bugs/081104DC/ has the case. */
        payload->counter++;
        for (update_index = 0; update_index < 11; update_index++) {
            const struct RotatingDefinition *definition = &data_083A2FD8[update_index];
            struct RotatingObject *object = &payload->rotating[update_index];
            s16 x_scale;
            s16 y_scale;
            u16 rotation;

            if (object->object == 0)
                continue;
            func_080E064C(&object->x_motion);
            func_080E064C(&object->y_motion);
            func_080107D4(object->object, object->x_motion.current,
                object->y_motion.current, 0);
            object->rotation += definition->rotation;
#ifdef BUGFIX
            if (payload->counter >= 60)
                goto check_end;
#endif
            x_scale = 0x100;
            if (definition->x_scale != 0)
                x_scale = definition->x_scale[payload->counter];
            y_scale = 0x100;
            if (definition->y_scale != 0)
                y_scale = definition->y_scale[payload->counter];
            rotation = object->rotation;
            func_080112CC(object->object, x_scale, y_scale, rotation);
#ifdef BUGFIX
        check_end:
#endif
            if (func_080E0690(&object->x_motion)) {
                func_08011428(object->object);
                object->object = 0;
            } else {
                finished = 0;
            }
        }
        for (update_index = 0; update_index < 14; update_index++) {
            struct MovingObject *object = &payload->moving[update_index];

            if (object->object == 0)
                continue;
            func_080E064C(&object->x_motion);
            func_080E064C(&object->y_motion);
            func_080107D4(object->object, object->x_motion.current,
                object->y_motion.current, 0);
            if (func_080E0690(&object->x_motion)) {
                func_08011428(object->object);
                object->object = 0;
            } else {
                finished = 0;
            }
        }
        if (finished) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            *payload->actor = 7;
            descriptor->phase++;
        }
        break;
    }
    case 0x103:
        payload->effect_task = func_080D4774(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
