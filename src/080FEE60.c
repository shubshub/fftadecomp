#include "ffta.h"

// Target 0x080FEE60..0x080FF17E (798 bytes, complete span with literal pools):
// f0b58cb0061c0d1c141c298880204000814242d0814204dc00290ed0012939d078e181204000814200d17de081424fdb
// 0130814200d14de16ce1a171aa8a1420295e074881420dd1082020710122a271e86802210840002807d0e27105e00000
// 07010000101c60302071e88a60716b68636103220006002800d000220449002000900196181c0023e1f786fae06141e1
// 1cdf3908d4f7defc3ce1e069e1f76efbe061002800d035e107492279900040180068064952181178321cd8f7a9fd2062
// 2888013025e10000c4df3908e8df3908206ad8f7c3fd2062002800d01ae16069d4f708fe0006002800d011e12823a079
// 012803d1e079002800d15c236069211c0c31221c08320092064a019200220292039204961a1c0223def7f6ff60652888
// 0130f6e0b4e13908207a002800d1f1e060690021d9f760fc0006002800d1e7e060690021def77efa071ca21c211c0023
// def7cafb2061381cdef7e2fa0006002800d191e011480096012104220023e0f7ddfea065207908282ad00021605e0222
// a15e03220092221c24320192084a0292039600220123d7f74ff8e063207905280ad10448009601213de00000bce13908
// f4df3908c4e1390806380006000e012836d80248009601212de00000cce139080021605e0222a15e06220092221c2432
// 01921a4a0292039600220123d7f724f8e06320690690e0680790a079012804d160690121def71efa089005a9a0798882
// 0f489621490005aa331c06f777fda0610c480096022104220023e0f77ffee0652079052812d10021605e0222a15e0122
// 0092221c40320192034a16e03ce03908ddeb0f08d4e13908cce0390806380006000e012810d80021605e0222a15e0122
// 0092221c40320192134a0292039600220123d6f7d9ffe06421791823082900d10623a079012802d1481c0006010e0b48
// 081800788100091889000948091804200090019618200290381c0c22ddf762ff20652888013024e0e4e03908a8e13908
// 44e13908e068dff75bf80006002819d0e06bd6f7f7ffe063002813d1e06cd6f7f1ffe06400280dd1a069e1f7dff9a061
// 002807d1206ddcf779fc2065002801d10220288000200cb0f0bc02bc0847

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *actor;
    u8 unknown_08[4];
    u32 flags;
    u8 unknown_10[4];
    s16 classifier;
    u16 selection;
} Command080FEE60;

typedef struct {
    s16 x;
    s16 y;
    u8 kind;
    u8 selection;
    u8 flag;
    u8 flag_07;
    u8 status;
    u8 unknown_09[3];
    void *status_handle;
    void *coordinate_result;
    void *actor;
    void *task;
    void *opening;
    void *load_handle;
    u8 outputs_24[24];
    void *position_task;
    u8 outputs_40[12];
    void *aux_task;
    void *actor_effect;
    void *status_result;
    void *effect_58;
    void *effect_5c;
} Work080FEE60;

typedef struct {
    u8 unknown_00[4];
    void *value_04;
    void *value_08;
    void *value_0C;
    u8 unknown_10[4];
    u16 flag;
    u8 unknown_16[6];
} Descriptor080FEE60;

typedef u32 (*Callback080FEE60)(void *task, void *descriptor, void *payload);

extern const u8 data_0839DF1C[];
extern const void *const data_0839DFC4[];
extern const u8 data_0839DFE8[];
extern const u8 data_0839E1B4[];
extern const u8 data_0839E1BC[];
extern const u8 data_0839DFF4[];
extern const u8 data_0839E1C4[];
extern const u8 data_0839E1CC[];
extern const u8 data_0839E03C[];
extern const u8 data_0839E1D4[];
extern const u8 data_0839E0CC[];
extern const u8 data_0839E0E4[];
extern const u8 data_0839E1A8[];
extern const u8 data_0839E144[][20];

extern void func_080D38B4(void);
extern u8 func_080D3B54(void *actor);
extern void *func_080E03F8(void *actor, const void *script, u8 mode,
                           u8 variant, u32 value, void *parent);
extern void *func_080E05DC(void *task);
extern void *func_080D7A70(const void *resource, u8 palette, void *parent);
extern void *func_080D7ABC(void *handle);
extern void *func_080DDF68(void *actor, void *handle, u16 flags, u8 mode,
                           void *status, const void *script, u16 first,
                           u16 second, void *parent);
extern u8 func_080D8858(void *actor, u16 flags);
extern void *func_080DD4A4(void *actor, u8 index);
extern void *func_080DD748(void *helper, s16 *x, s16 *y, u32 value);
extern u8 func_080DD580(void *helper);
extern void *func_080DFD8C(const void *script, u8 mode, u16 flags,
                           u16 value, void *parent);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, s16 count,
                           void *outputs, const void *script, void *parent);
extern void *func_08005B6C(Callback080FEE60 callback, u16 size,
                           void *descriptor, void *parent);
extern u32 func_080FEBDC(void *task, void *descriptor, void *payload);
extern void *func_080DCFE4(void *object, const void *script, u8 mode,
                           u16 first, u16 count, void *parent, s16 value);
extern u8 func_080DE1F0(void *object);
extern void *func_080D6134(void *task);
extern void *func_080E051C(void *task);
extern void *func_080DBA5C(void *task);

u32 func_080FEE60(void *parent, Command080FEE60 *command, Work080FEE60 *work)
{
    switch (command->state) {
    case 0: {
        void *actor;
        u8 mode;

        work->flag = 0;
        if (command->classifier == 0x107) {
            work->kind = 8;
            work->flag = 1;
            if (command->flags & 2)
                work->flag_07 = 1;
        } else {
            work->kind = command->classifier + 0x60;
        }
        work->selection = command->selection;
        actor = command->actor;
        work->actor = actor;
        mode = 3;
        if (work->selection)
            mode = 0;
        work->opening = func_080E03F8(actor, data_0839DF1C, mode, 0, 0, parent);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->opening = func_080E05DC(work->opening);
        if (work->opening != 0)
            break;
        work->load_handle = func_080D7A70(data_0839DFC4[work->kind],
                                          data_0839DFE8[work->kind], parent);
        command->state++;
        break;
    case 0x101: {
        u8 flags;

        work->load_handle = func_080D7ABC(work->load_handle);
        if (work->load_handle != 0)
            break;
        if (func_080D3B54(work->actor)) {
            command->state = 2;
            break;
        }
        flags = 0x28;
        if (work->flag == 1) {
            if (work->flag_07 == 0)
                flags = 0x5c;
        }
        work->status_result = func_080DDF68(work->actor, &work->status_handle,
                                            flags, 2, &work->status,
                                            data_0839E1B4, 0, 0, parent);
        command->state++;
        break;
    }
    case 0x102: {
        void *helper;
        u16 count;

        if (work->status == 0)
            break;
        if (!func_080D8858(work->actor, 0)) {
            command->state = 2;
            break;
        }
        helper = func_080DD4A4(work->actor, 0);
        work->coordinate_result = func_080DD748(helper, &work->x, &work->y, 0);
        if (func_080DD580(helper)) {
            work->effect_58 = func_080DFD8C(data_0839E1BC, 1, 4, 0, parent);
            if (work->kind != 8) {
                work->position_task = func_080D6098(work->x, work->y, 0, 1, 3,
                                                   work->outputs_24,
                                                   data_0839DFF4, parent);
                if (work->kind == 5)
                    work->effect_5c = func_080DFD8C(data_0839E1C4, 1, 4, 0, parent);
                else if (work->kind == 6 || work->kind == 7)
                    work->effect_5c = func_080DFD8C(data_0839E1CC, 1, 4, 0, parent);
            } else {
                Descriptor080FEE60 descriptor;

                work->position_task = func_080D6098(work->x, work->y, 0, 1, 6,
                                                   work->outputs_24,
                                                   data_0839E03C, parent);
                descriptor.value_04 = work->coordinate_result;
                descriptor.value_08 = work->status_handle;
                if (work->flag == 1)
                    descriptor.value_0C = func_080DD4A4(work->actor, 1);
                descriptor.flag = work->flag;
                work->task = func_08005B6C(func_080FEBDC,
                                           0x12C, &descriptor, parent);
                work->effect_5c = func_080DFD8C(data_0839E1D4, 2, 4, 0, parent);
            }
            if (work->kind == 5)
                work->aux_task = func_080D6098(work->x, work->y, 0, 1, 1,
                                              work->outputs_40,
                                              data_0839E0CC, parent);
            else if (work->kind == 6 || work->kind == 7)
                work->aux_task = func_080D6098(work->x, work->y, 0, 1, 1,
                                              work->outputs_40,
                                              data_0839E0E4, parent);
        }
        {
            u8 index = work->kind;

            count = 0x18;
            if (index == 8)
                count = 6;
            if (work->flag == 1)
                index = index + 1;
            work->actor_effect = func_080DCFE4(helper,
                                              data_0839E144[data_0839E1A8[index]],
                                              12, count, 4, parent, 0x18);
        }
        command->state++;
        break;
    }
    case 0x103:
        if (!func_080DE1F0(work->status_handle))
            break;
        work->position_task = func_080D6134(work->position_task);
        if (work->position_task != 0)
            break;
        work->aux_task = func_080D6134(work->aux_task);
        if (work->aux_task != 0)
            break;
        work->task = func_080E051C(work->task);
        if (work->task != 0)
            break;
        work->actor_effect = func_080DBA5C(work->actor_effect);
        if (work->actor_effect == 0)
            command->state = 2;
        break;
    }
    return 0;
}
