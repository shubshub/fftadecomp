// Complete target [0x080F72B0, 0x080F7720): 1136 bytes.
// Target bytes: f0b5474680b485b0061c8846151c0b8881204000834200d1e4e083420fdc012b34d0012b02dc002b1ad01ae28020400083422ed00130834200d1a3e011e282204000834200d167e1834200da04e10130834200d1d0e10130834200d1ece100e24146c88aa8704c68ac6006220006002800d00022044900930196201c0723e9f763f8a864ede1000048bb3908dcf7bafae7e1a86ce9f74af9041cac64002c00d0dfe1a8680021e1f77ffa0006002801d1022092e0a8680021e6f79cf8e860291daa1d0023e6f7e8f928612648311cddf7c1f928622448311cdcf788fde862234804216b5e0622a95e0091019400210222dff73eff0423e85e0622a95e012200922a1c143201921a4a0292039600220123def76afee8611748311c1e22ddf7aaf9a8620224e868e6f7d3f8000600280cd0286911490091114901910296002100220623e4f7f9fe686403240d480096211c04220023e8f7c2fc28654346188801307ee10000e4a394089cd69408f0468f0890bb3908a0ab9408c0f8000600500006d8bb3908286addf79df92862002800d067e1e86adcf760fde862002800d060e1e869def76ffee861002800d059e1e868e6f78ef8000600280ed02869009602210c220023e4f74efb28640a202880414608880130088044e101484246108040e1030100002888013828800004002800d037e1686ce4f7dafa6864002800d030e113480cf7dffa041c12480cf7e1fa04432404240c201c03210bf7f6ff28690423e95e0623ea5e6c461234009404abe4f7a1fe04a80021405e03210cf70df80022a05e03210cf730f843461888013007e10050000600800006286ce4f7a7fa071c2f64002f00d0fce0002000210022331ce3f730fb28630121e2f73efb02200cf74ff8234e3f24211c8143081c321c42321178107003200cf743f88443301c443001780470311c3b3108780f700139ff200870053108780f7001390878012040420870318880229201101c084330801149081c1022082350f0a5fe03200cf734f8321c4a32117808431178107003200cf703f8318801433180281c3430002118223c23e9f729f8434618880130a8e0000040090003203900032c1c3434201ce9f73df8286b0422a95eea88083a12041214ab8ee3f72dfb201ce9f752f80006002800d18ee0286be2f7b5fa286302200bf7d3ff1e4c218881431d4801402180e868e5f7b6ff0006020e002a35d003200bf7d7ff3f218143221c453210781170211c443108783f200870208880231b02191c0843208028690021e4f734fc0421685e0622a95e022200922a1c14320192094a0292039600220123def716fde861462028804346188801304ae0000040090003ffdf0000a8bb3908e868022100910196029200210c220023e5f7a4fce864832040004146088034e0288800280dd0013828800004002808d103200bf775ff084a11888143074801401180e869def732fde86100281dd1424610880130108018e040090003ff7f0000a86addf743f8a86200280ed1286be2f735fa2863002808d1e86ce4f7abf9e864002802d1022043461880002005b008bc9846f0bc02bc0847
#include "ffta.h"
#include "control_flags.h"
#include "effect_task.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080F72B0;

typedef struct {
    u16 value;
    u16 unknown_02;
    u32 unknown_04;
    u32 unknown_08;
} Interpolation080F72B0;

typedef struct {
    u16 counter;
    u8 flag;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *actor;
    void *actor_state;
    void *position;
    void *outputs;
    u32 unknown_18;
    void *window;
    void *first_text;
    u32 unknown_24;
    void *second_text;
    void *image;
    void *sprite;
    Interpolation080F72B0 fade;
    void *blink_child;
    void *tile_child;
    void *initial_child;
    void *transition_child;
    void *sequence;
} Payload080F72B0;

extern u16 data_03003920[];
extern u8 data_088F46F0[], data_0894A3E4[], data_0894ABA0[], data_0894D69C[];
extern u8 data_0839BB48[], data_0839BB90[], data_0839BBA8[], data_0839BBD8[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern u8 func_080DD580(const void *);
extern void *func_080DC1E8(void *, u8, u8, u8, void *, void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern void *func_080D6134(void *);
extern void *func_080DBB14(void *, u8, u8, u16, void *);
extern void *func_080DBA5C(void *);
extern u32 func_08003A74(u32);
extern u32 func_08003A80(u32);
extern void func_080034B8(u16, u8);
extern void func_080DC224(void *, s16, s16, s16 *, s16 *);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080D9BA8(void *, u8);
extern u16 func_080035D0(u8);
extern void func_081482D4(const u16 *, u16 *, u16, u8);
extern u16 func_080035F8(u8);
extern u16 func_080035A8(u8);
extern void func_080E0608(Interpolation080F72B0 *, s16, s16, s16);
extern void func_080E064C(Interpolation080F72B0 *);
extern void func_080DAC40(void *, s16, s16, u16);
extern u8 func_080E0690(Interpolation080F72B0 *);
extern void *func_080D9B64(void *);
extern void func_080DBEB4(void *, u8);

u32 func_080F72B0(void *task, Descriptor080F72B0 *descriptor,
                  Payload080F72B0 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;
        void *actor;

        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 6;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(actor,
            data_0839BB48, mode, 7, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 count;

        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (!func_080D8858(payload->actor, 0)) {
            descriptor->phase = 2;
            break;
        }
        payload->actor_state = func_080DD4A4(payload->actor, 0);
        payload->position = func_080DD748(payload->actor_state,
            &payload->x, &payload->y, 0);
        payload->first_text = func_080D4704(data_0894A3E4, task);
        payload->image = func_080D3E9C(data_0894D69C, task);
        func_080D7220(data_088F46F0, 0, 2, payload->x, payload->y, 0);
        payload->window = func_080D6098(payload->x, payload->y, 0, 1, 1,
            &payload->outputs, data_0839BB90, task);
        payload->second_text = func_080D4724(data_0894ABA0, task, 30);
        count = 2;
        if (func_080DD580(payload->actor_state)) {
            payload->tile_child = func_080DC1E8(payload->position, 0, 0, 6,
                (void *)0x0600F8C0, (void *)0x06005000, task);
            count = 3;
        }
        payload->sequence = func_080DFD8C(data_0839BBD8, count, 4,
            0, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->first_text = func_080D4774(payload->first_text);
        if (payload->first_text != 0)
            break;
        payload->image = func_080D3F08(payload->image);
        if (payload->image != 0)
            break;
        payload->window = func_080D6134(payload->window);
        if (payload->window != 0)
            break;
        if (func_080DD580(payload->actor_state)) {
            payload->blink_child = func_080DBB14(payload->position, 2, 12, 0,
                task);
            payload->counter = 10;
            descriptor->phase++;
        } else {
            descriptor->phase = 0x103;
        }
        break;
    case 0x102: {
        s16 x;
        s16 y;

        if (--payload->counter != 0)
            break;
        payload->tile_child = func_080DBA5C(payload->tile_child);
        if (payload->tile_child != 0)
            break;
        func_080034B8(func_08003A74(0x06005000)
                      | func_08003A80(0x06008000), 3);
        func_080DC224(payload->position, payload->x, payload->y, &x, &y);
        func_08003508(x, 3);
        func_08003558(y, 3);
        descriptor->phase++;
        break;
    }
    case 0x103:
        /* On the no-tile path blink_child is still NULL (the scheduler
         * zero-fills the payload), and func_080DBA5C(NULL) returns NULL. */
        payload->blink_child = func_080DBA5C(payload->blink_child);
        if (payload->blink_child != 0)
            break;
        payload->sprite = func_080DAB84(0, 0, 0, task);
        func_080D9BA8(payload->sprite, 1);
        g_control_flags_03000940.winin_lo = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(3);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 255;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 255;
        g_control_flags_03000940.display |= 0x2000;
        func_081482D4(data_03003920, data_03003920, 16, 8);
        g_control_flags_03000940.bldcnt_lo |= func_080035F8(3);
        g_control_flags_03000940.display |= func_080035A8(3);
        func_080E0608(&payload->fade, 0, 24, 60);
        descriptor->phase++;
        break;
    case 0x104:
        func_080E064C(&payload->fade);
        func_080DAC40(payload->sprite, payload->x, payload->y - 8,
                      payload->fade.value);
        if (!func_080E0690(&payload->fade))
            break;
        payload->sprite = func_080D9B64(payload->sprite);
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.display &= 0xdfff;
        if (func_080DD580(payload->actor_state)) {
            g_control_flags_03000940.winout_hi = 0x3f & ~func_080035D0(3);
            g_control_flags_03000940.winout_lo = 0x3f;
            g_control_flags_03000940.display |= 0x8000;
            func_080DBEB4(payload->position, 0);
            payload->window = func_080D6098(payload->x, payload->y, 0, 1, 2,
                &payload->outputs, data_0839BBA8, task);
            payload->counter = 70;
            descriptor->phase++;
        } else {
            payload->transition_child = func_080DCFE4(payload->actor_state,
                0, 12, 0, 2, task, 0);
            descriptor->phase = 0x106;
        }
        break;
    case 0x105:
        if (payload->counter != 0) {
            if (--payload->counter == 0) {
                g_control_flags_03000940.display &= ~func_080035A8(3);
                g_control_flags_03000940.display &= 0x7fff;
            }
        }
        payload->window = func_080D6134(payload->window);
        if (payload->window == 0)
            descriptor->phase++;
        break;
    case 0x106:
        payload->second_text = func_080D4774(payload->second_text);
        if (payload->second_text != 0)
            break;
        payload->sprite = func_080D9B64(payload->sprite);
        if (payload->sprite != 0)
            break;
        payload->transition_child = func_080DBA5C(payload->transition_child);
        if (payload->transition_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
