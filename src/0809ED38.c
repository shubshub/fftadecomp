#include "ffta.h"

/* Complete [0x0809ED38, 0x0809F78A): 2642 bytes, 1109 instructions,
 * including the 42-entry jump table at 0x0809ED60 and the literal pools.
 * Steps the context func_0809EA60 (src/0809EA60.c) sets up.
 * f0b557464e464546e0b481b0071ccc300088292801d900f013fd800001494018
 * 0068874660ed0908bef10908f4f20908faf2090840f70908e4f30908aef40908
 * 42f50908a4f309084ef1090898f1090862ee09087eee09089aee0908b6ee0908
 * d2ee0908eeee09080aef090828ef090846ef090864ef090882ef09081cf00908
 * 48f009087ef00908a0f00908c4f00908def00908aeef0908beef090804f00908
 * 98f4090884f4090800f1090830f1090828f00908bef309084cee09085cee0908
 * 0cf0090856f7090808ee090830ee0908381c6830391c6431064a1278d2080123
 * 9343042228f0d2fa391ccc312920088000f0a6fca02800033c1c6834201c28f0
 * cffa0006002801d000f09afc201c28f011fb8ee30af010fa391ccc3125200880
 * 00f08efc0af01cfa83e33a68906a06210840002800d17ce31068002129f016f8
 * 021c16208fe03a68906a08210840002800d16ee31068002129f008f8021c1720
 * 81e03a68906a10210840002800d160e31068002128f0faff021c182073e03a68
 * 906a20210840002800d152e31068002128f0ecff021c192065e03a68906a4021
 * 0840002800d144e31068002128f0deff021c1a2057e03a68906a802108400028
 * 00d136e31068002128f0d0ff021c1b2049e03a68906ac02189000840002800d1
 * 27e31068002128f0c1ff021c1c203ae03a68906a8021c9000840002800d118e3
 * 1068002128f0b2ff021c1d202be03a68906a802109010840002800d109e31068
 * 002128f0a3ff021c1e201ce03a68906a802149010840002800d1fae210680021
 * 28f094ff021c1f200de03a68906a8021c9010840002800d1ebe21068002128f0
 * 85ff021c2420002186f772fb391ccc311b200880e4e3391c6031002008806c31
 * 1c200880dce3391c6031088801300880000400140c1c0f2807dd0b48c18a0320
 * 0840002801d07820208086f73ffa0021605e772800dcc3e38af790fa391ccc31
 * 1d200880bce3000090f3000286f72efa000434e00af01cfa002800d0b0e30af0
 * 41f9a6e2b86809f0ddfb0020b860a0e23868803000680021fbf716f938688030
 * 0068fbf7e3f80006002800d098e390e23c1cc834217801200840002806d134f0
 * 89fb217801200843207089e334f0c8fb0006002800d07ce234f09efc00060028
 * 00d17de375e23a1cc832117802200840002801d004326ee2022008431070ab20
 * 40000021012252e33a1cc832117802200840002801d104325de2fd2008401070
 * 01480021012242e357010000786834f0d7fb0006002800d152e3786834f0c6fb
 * 0020786045e23c1cc834217801200840002806d034f05efb2178fe2008402070
 * 3ee334f063fbb9e7381c10303c6808490a684c21a3f09ef83c613a68906a0549
 * 08409062391ccc312120088028e30000b8d43608ff7fffff381c1030fff7e0fb
 * 0006002800d01be33a68106b21214942084010630de211483a68002134f0d8f9
 * 786038680068142128f0a0fe39680968400808838f20a2f0d7f93a1ccc320923
 * 13805188481c50800904c90b381cd0304018038019201080f2e200005d010000
 * 3b681868008b4042000400140822995e5a893032120412140c241b5f00240094
 * 0af094f8d5e13b68996a01208046081c42461040002800d1cbe1022040420140
 * 99621868f83000228256181c09210023f9f7c0f809f0e2fa041cbc603e680121
 * 09f002fb201c09f005fb051c201c002109f002fb3168f63109780023a9723168
 * f7310978e9722e60066082898021114381813868836200680383b868002109f0
 * ebfa017d012211430175016980229201114301613a68106b1021084310631068
 * 2ef038fb041c2406240e3868faf7a2fc38680068211c2ef067fd3a1ccc325488
 * 611e51800804c00b3b1cd03318180088108054800904c90b591808801f241480
 * 5088411c51800004c00b18180480152414805088411c51800004c00b18180480
 * 444614805088411c51800004c00b18180480172414805088411c51800004c00b
 * 18180480162414805088411c51800004c00b1b181c802220108041e2b9683d20
 * 24e2386800682ef0f1fa0006002800d12fe1391cc931202008700d202af048f9
 * 0006002803d063f787fa796e01603868006891f067f840423d1c5c35288063f7
 * 7bfa0068786638680268108b2988401a108338680068132128f0a8fd041c3868
 * 0068142128f0a2fd844207d938680068142128f09bfd3968096808830021685e
 * 3b680822995e5a893032120412140c241b5f0024009409f0a9ff391ccc310720
 * 0880386809f0e4faf860e9e1f86808f079fc0006040e002c00d0e1e1f86809f0
 * ebfafc60bce0391cc9310a7800200856002808dc3a1ccc325088013850800004
 * c00b0731cee0501e0870c9e13868006828f04aff0006002800d1bae03868006b
 * 10210840002800d0b3e03d1ccc356888013868800004c00b3e1cd03630180088
 * 2880386800682ef055fa041c2406240e3868faf7bffb38680068211c2ef084fc
 * 6888411c69800004c00b3018298801801f222a806888411c69800004c00b3018
 * 02801e222a806888411c69800004c00b3018028016222a806888411c69800004
 * c00b361832802220288079e138680168f83100228a560a210023f8f76bff68e0
 * ae2040003a68002134f032f878603968002088624ee1386800682ef05ffa0006
 * 002856d0391cc931202008700d202af06ff80006002803d063f7aef9796e0160
 * 3868006890f066ff3c1c5e34208063f7a3f90068786638680268118b0023e05e
 * 091a002900dc002111830021605e3b680822995e5a893032120412140c241b5f
 * 0024009409f0e2fe38680168f83100228a5605210023f8f71dff8920a1f0f4ff
 * 391ccc31232008801ae1386800688ff019fe0006002804d039680868008b0028
 * 14d039680868008b002802d1081cfaf721fb3a1ccc325088013850800004c00b
 * 391cd031091808881080f9e0081cfaf711fbcc20c0198046d021c9198a4603e0
 * 006800212ef008fe3968081c80300068f9f774ff0028f3d13868006800212ef0
 * c3fb09f0fbf8041cbc603e68012109f01bf9201c09f01ef9051c201c002109f0
 * 1bf93168f6310978a9723168f7310978e9722e6006608289802111438181b868
 * 002109f009f9061c0520002100228ff04dfe494a396808681060086850600023
 * 994600208ff096fe4c462006000e8ff07ffe91f0c7fc0006002843d048468ff0
 * b1fe386800688ff085fe92f06dfa051c38680168088b441b002c00da0024081c
 * 142128f023fc844205d338680068142128f01cfc041c386800680483f583b089
 * 01210843b08130698021c901084330614846012803dc4000284940180580284d
 * 341c1434274a1368281c211c0422a2f0d3fd94f0eff823480368201c291c0422
 * a2f0cafd012189444a46022aa9dd43465a88511e59800804c00b504400881880
 * 5a800904c90b5144088015221a805888411c59800004c00b5044028003221a80
 * 5888411c59800004c00b5044028017221a805888411c59800004c00b50440280
 * 16221a805888411c59800004c00b504402802220188023e0f0f3000210f40002
 * 00f40002bcd43608b9680620002233f0dffe7860391ccc311920088010e03868
 * 803000680121faf77ffd38680168f83100228a560a210023f8f7fcfd002000e0
 * 012001b038bc9846a146aa46f0bc02bc0847
 */

typedef struct {
    u8 unknown_00[0x18];
    u16 hp;
    u8 unknown_1A[0xDC];
    u8 tile_x;
    u8 tile_z;
    s8 direction;
} Unit0809ED38;

typedef struct {
    Unit0809ED38 *unit;
    u8 unknown_04[4];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x1A];
    u32 events;
    u8 unknown_2C[4];
    u32 flags;
    u8 unknown_34[0x4C];
    void *scene;
} Subject0809ED38;

/* The 0x2C4-byte group of func_080A87B4 (src/080A87B4.c): func_080A880C
 * returns the group itself, func_080A8810 one of its 0x2C-byte entries. */
typedef struct Group0809ED38 Group0809ED38;

typedef struct {
    Subject0809ED38 *subject;
    u8 unknown_04[6];
    u8 tile_x;
    u8 tile_z;
} Header0809ED38;

/* The four bytes func_0813388C works on, copied through data_0200F3F0. */
typedef struct {
    u32 unknown_0 : 1;
    u32 unknown_1 : 31;
} Status0809ED38;

typedef struct {
    Subject0809ED38 *subject;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0E[2];
    u32 state;
    Status0809ED38 status;
    u8 unknown_18[6];
    u16 damage;
    u8 unknown_20[0xC];
} Entry0809ED38;

typedef struct {
    Subject0809ED38 *subject;
    u8 unknown_04[0x48];
} Action0809ED38;

typedef struct {
    u16 current;
    u16 depth;
    u16 history[34];
} Sequence0809ED38;

/* The context func_0809EA60 (src/0809EA60.c) clears and fills. */
typedef struct {
    Subject0809ED38 *source;
    void *task;
    Group0809ED38 *group;
    void *effect;
    Action0809ED38 action;
    s16 recovery;
    s16 damage;
    s16 timer;
    u8 unknown_62[2];
    u32 timestamp;
    u8 link[0x60];
    u8 flags;
    s8 delay;
    u8 unknown_CA[2];
    Sequence0809ED38 sequence;
} Context0809ED38;

typedef struct {
    Unit0809ED38 *source;
    Unit0809ED38 *target;
    u8 unknown_08[8];
    Status0809ED38 status;
    u8 unknown_14[0xC];
    u16 damage[2];
} ActionState0809ED38;

typedef struct {
    u8 unknown_00[0x16];
    u16 filtered_pressed;
} InputState0809ED38;

typedef struct {
    u8 flags;
} Mode0809ED38;

typedef void (*BufferInitializer0809ED38)(void *destination, u32 size);
typedef void (*BufferCopier0809ED38)(void *destination, const void *source,
                                     u32 size);

extern Mode0809ED38 data_030028A0;
extern InputState0809ED38 g_state_0200F390;
extern ActionState0809ED38 data_0200F3F0;
extern BufferInitializer0809ED38 g_callbacks_0836D4B8[];
extern BufferCopier0809ED38 data_0836D4BC[];

extern u32 *func_08002830(void);
extern s32 func_08025464(void);
extern void func_08025688(u16 identifier, u16 value, const void *argument);
extern void func_08029514(void);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern Subject0809ED38 *func_08099494(void *owner, Subject0809ED38 *state);
extern void func_08099BAC(void *state);
extern u8 func_0809A204(void *scene);
extern void func_0809A260(void *scene, u32 value);
extern u8 func_0809E8F8(Action0809ED38 *action);
extern u8 func_080A7C9C(void *task);
extern Group0809ED38 *func_080A87B4(void);
extern void func_080A87DC(Group0809ED38 *group);
extern void func_080A8800(Group0809ED38 *group, u8 count);
extern Header0809ED38 *func_080A880C(Group0809ED38 *group);
extern Entry0809ED38 *func_080A8810(Group0809ED38 *group, s32 index);
extern void *func_080A8968(void *context);
extern void func_080A8990(void *object);
extern void func_080A9270(void);
extern void func_080A9298(void);
extern void func_080A929C(void);
extern void func_080A92E4(s16 mode, s16 x, s16 y, s16 z, u32 effect);
extern s32 func_080A9448(void);
extern void func_080C73C4(void *link, void *value, u16 width, u8 mode);
extern u8 func_080C73D8(void *link);
extern void func_080C746C(void *link);
extern u32 func_080C7EA4(const void *object, u32 selector);
extern u8 func_080C8280(const void *unit);
extern u8 func_080C95A8(u16 index);
extern u8 func_080CD8CC(const void *object);
extern u8 func_080CD8E4(const void *object);
extern u8 func_080CD974(const void *object);
extern void func_080CDD40(void *object, u8 enabled);
extern void func_080CE1B0(void *object, u8 enabled);
extern void *func_080D3508(u16 id, void *object, u32 arg);
extern void func_080D3864(void *task);
extern u8 func_080D3878(const void *task);
extern void func_080D376C(void);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);
extern u8 func_080D37F8(void);
extern u8 func_080D39B0(void);
extern u8 func_0812F17C(void *unit);
extern void func_0812F2A4(u16 action, u16 equipment, u8 kind);
extern void func_0812F328(u8 index);
extern void func_0812F34C(u32 value);
extern void func_0812F39C(s32 index);
extern s16 func_081303AC(const void *object);
extern s16 func_081303FC(const void *object);
extern u8 func_08130FBC(void);
extern s32 func_08131B20(void);
extern void func_0813388C(void);
extern void func_08141520(u16 sound);

/* The two halves of the state stack: push_state as in src/0809EA60.c, and
 * pop_state, whose one shared copy is the tail at 0x0809F56A-0x0809F582. */
static inline void push_state(Sequence0809ED38 *sequence)
{
    sequence->history[sequence->depth++] = sequence->current;
}

static inline void pop_state(Sequence0809ED38 *sequence)
{
    sequence->current = sequence->history[--sequence->depth];
}

/* Clears the action and gives it its subject, as func_080A8968
 * (src/080A8968.c) does for the 0x50-byte effect state. */
static inline void start_action(Action0809ED38 *action,
                                Subject0809ED38 *subject)
{
    g_callbacks_0836D4B8[0](action, sizeof(*action));
    action->subject = subject;
}

/* Gives a fresh group one entry for the subject: the ROM has it twice, at
 * 0x0809F1F4-0x0809F22A and 0x0809F5C2-0x0809F5F4. */
static inline void attach_subject(Group0809ED38 *group,
                                  Subject0809ED38 *subject)
{
    Header0809ED38 *header;
    Entry0809ED38 *entry;

    func_080A8800(group, 1);
    header = func_080A880C(group);
    entry = func_080A8810(group, 0);
    header->tile_x = subject->unit->tile_x;
    header->tile_z = subject->unit->tile_z;
    header->subject = subject;
    entry->subject = subject;
    entry->flags |= 0x80;
}

/* Refreshes the subject but keeps the flag func_080CD8CC reads: twice in
 * the ROM, at 0x0809F256-0x0809F270 and 0x0809F41A-0x0809F436. */
static inline void refresh_subject(Context0809ED38 *context)
{
    u8 enabled = func_080CD8CC(context->source->unit);

    func_08099BAC(context->source);
    func_080CDD40(context->source->unit, enabled);
}

u32 func_0809ED38(Context0809ED38 *context)
{
    switch (context->sequence.current) {
    case 0x28:
        func_080C73C4(context->link, &context->timestamp, 4,
                      !(data_030028A0.flags & 8));
        context->sequence.current = 0x29;
        break;
    case 0x29:
        if (func_080C73D8(context->link))
            break;
        func_080C746C(context->link);
        pop_state(&context->sequence);
        break;
    case 0x24:
        func_080A9270();
        context->sequence.current = 0x25;
        break;
    case 0x25:
        func_080A9298();
        pop_state(&context->sequence);
        break;
    case 0xA:
        if (context->source->events & 6) {
            func_08025688(0x16, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0xB:
        if (context->source->events & 8) {
            func_08025688(0x17, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0xC:
        if (context->source->events & 0x10) {
            func_08025688(0x18, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0xD:
        if (context->source->events & 0x20) {
            func_08025688(0x19, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0xE:
        if (context->source->events & 0x40) {
            func_08025688(0x1A, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0xF:
        if (context->source->events & 0x80) {
            func_08025688(0x1B, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0x10:
        if (context->source->events & 0x300) {
            func_08025688(0x1C, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0x11:
        if (context->source->events & 0x400) {
            func_08025688(0x1D, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0x12:
        if (context->source->events & 0x800) {
            func_08025688(0x1E, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0x13:
        if (context->source->events & 0x1000) {
            func_08025688(0x1F, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0x14:
        if (context->source->events & 0x4000) {
            func_08025688(0x24, 0,
                          (const void *)func_080C7EA4(context->source->unit, 0));
            context->sequence.current = 0x1B;
            break;
        }
        pop_state(&context->sequence);
        break;
    case 0x1B:
        context->timer = 0;
        context->sequence.current = 0x1C;
        break;
    case 0x1C:
        if (++context->timer > 15 && (g_state_0200F390.filtered_pressed & 3))
            context->timer = 120;
        func_08025464();
        if (context->timer > 119) {
            func_08029514();
            context->sequence.current = 0x1D;
        }
        break;
    case 0x1D:
        if ((u16)func_08025464())
            pop_state(&context->sequence);
        break;
    case 0x26:
        if (func_080A9448() != 0)
            break;
        func_080A929C();
        pop_state(&context->sequence);
        break;
    case 0x15:
        func_080A87DC(context->group);
        context->group = 0;
        pop_state(&context->sequence);
        break;
    case 0x22:
        func_0809A260(context->source->scene, 0);
        if (func_0809A204(context->source->scene))
            break;
        pop_state(&context->sequence);
        break;
    case 0x16:
        if (!(context->flags & 1)) {
            func_080D376C();
            context->flags |= 1;
        } else if (func_080D37F8() || func_080D39B0()) {
            pop_state(&context->sequence);
        }
        break;
    case 0x17:
        if (context->flags & 2) {
            pop_state(&context->sequence);
        } else {
            context->flags |= 2;
            context->task = func_080D3508(0x156, 0, 1);
            context->sequence.current = 0x19;
        }
        break;
    case 0x18:
        if (!(context->flags & 2)) {
            pop_state(&context->sequence);
        } else {
            context->flags &= ~2;
            context->task = func_080D3508(0x157, 0, 1);
            context->sequence.current = 0x19;
        }
        break;
    case 0x19:
        if (!func_080D3878(context->task))
            break;
        func_080D3864(context->task);
        context->task = 0;
        pop_state(&context->sequence);
        break;
    case 0x1A:
        if (context->flags & 1) {
            func_080D37AC();
            context->flags &= ~1;
        } else if (func_080D37C4()) {
            pop_state(&context->sequence);
        }
        break;
    case 0x20:
        start_action(&context->action, context->source);
        context->source->events &= ~0x8000;
        context->sequence.current = 0x21;
        break;
    case 0x21:
        if (func_0809E8F8(&context->action))
            break;
        context->source->flags &= ~0x20;
        pop_state(&context->sequence);
        break;
    case 8:
        context->task = func_080D3508(0x15D, 0, (u32)context->source);
        context->source->unit->hp =
            func_080C7EA4(context->source->unit, 0x14) >> 1;
        func_08141520(0x8F);
        context->sequence.current = 9;
        push_state(&context->sequence);
        context->sequence.current = 0x19;
        break;
    case 9:
        func_080A92E4(-context->source->unit->hp, context->source->x,
                      context->source->y + 0x30, context->source->z, 0);
        pop_state(&context->sequence);
        break;
    case 0: {
        Entry0809ED38 *entry;

        if (!(context->source->events & 1)) {
            pop_state(&context->sequence);
            break;
        }
        context->source->events &= ~1;
        func_0809836C(context->source, 9, context->source->unit->direction, 0);
        context->group = func_080A87B4();
        attach_subject(context->group, context->source);
        context->source->events = 0;
        context->source->unit->hp = 0;
        entry = func_080A8810(context->group, 0);
        entry->status.unknown_0 = 1;
        entry->state |= 0x2000;
        context->source->flags |= 0x10;
        refresh_subject(context);
        pop_state(&context->sequence);
        push_state(&context->sequence);
        context->sequence.current = 0x1F;
        push_state(&context->sequence);
        context->sequence.current = 0x15;
        push_state(&context->sequence);
        context->sequence.current = 1;
        push_state(&context->sequence);
        context->sequence.current = 0x17;
        push_state(&context->sequence);
        context->sequence.current = 0x16;
        push_state(&context->sequence);
        context->sequence.current = 0x22;
        break;
    }
    case 1:
        context->task = func_080D3508(0x3D, context->group, 0);
        context->sequence.current = 0x19;
        break;
    case 2:
        if (!func_080CD8E4(context->source->unit)) {
            pop_state(&context->sequence);
            break;
        }
        context->delay = 0x20;
        if (func_080C95A8(0xD))
            *func_08002830() = context->timestamp;
        context->recovery = -func_081303FC(context->source->unit);
        context->timestamp = *func_08002830();
        context->source->unit->hp -= context->recovery;
        if (func_080C7EA4(context->source->unit, 0x13) >
            func_080C7EA4(context->source->unit, 0x14))
            context->source->unit->hp =
                func_080C7EA4(context->source->unit, 0x14);
        func_080A92E4(context->recovery, context->source->x,
                      context->source->y + 0x30, context->source->z, 0);
        context->sequence.current = 7;
        context->effect = func_080A8968(context->source);
        break;
    case 7:
        if (func_080A7C9C(context->effect))
            break;
        func_080A8990(context->effect);
        context->effect = 0;
        context->sequence.current = 0x23;
        break;
    case 0x23:
        if (context->delay <= 0)
            pop_state(&context->sequence);
        else
            context->delay--;
        break;
    case 4:
        if (!func_080C8280(context->source->unit) ||
            (context->source->flags & 0x10)) {
            pop_state(&context->sequence);
            break;
        }
        pop_state(&context->sequence);
        refresh_subject(context);
        push_state(&context->sequence);
        context->sequence.current = 0x1F;
        push_state(&context->sequence);
        context->sequence.current = 0x1E;
        push_state(&context->sequence);
        context->sequence.current = 0x16;
        push_state(&context->sequence);
        context->sequence.current = 0x22;
        break;
    case 0x1F:
        func_0809836C(context->source, 10, context->source->unit->direction, 0);
        pop_state(&context->sequence);
        break;
    case 0x1E:
        context->task = func_080D3508(0x15C, 0, (u32)context->source);
        context->source->events = 0;
        context->sequence.current = 0x19;
        break;
    case 5: {
        s32 hp;

        if (!func_080CD974(context->source->unit)) {
            pop_state(&context->sequence);
            break;
        }
        context->delay = 0x20;
        if (func_080C95A8(0xD))
            *func_08002830() = context->timestamp;
        context->damage = func_081303AC(context->source->unit);
        context->timestamp = *func_08002830();
        hp = context->source->unit->hp - context->damage;
        if (hp <= 0)
            hp = 0;
        context->source->unit->hp = hp;
        func_080A92E4(context->damage, context->source->x,
                      context->source->y + 0x30, context->source->z, 0);
        func_0809836C(context->source, 5, context->source->unit->direction, 0);
        func_08141520(0x89);
        context->sequence.current = 0x23;
        break;
    }
    case 6: {
        Subject0809ED38 *member;
        Entry0809ED38 *entry;
        s32 i;
        s32 damage;
        s32 hp;

        if (!func_0812F17C(context->source->unit) ||
            context->source->unit->hp != 0) {
            if (context->source->unit->hp == 0)
                func_08099BAC(context->source);
            pop_state(&context->sequence);
            break;
        }
        func_08099BAC(context->source);
        while ((member = func_08099494(context->source->scene,
                                       context->source)) != 0)
            func_080CE1B0(member->unit, 0);
        func_080CDD40(context->source->unit, 0);
        context->group = func_080A87B4();
        attach_subject(context->group, context->source);
        entry = func_080A8810(context->group, 0);
        func_0812F2A4(5, 0, 0);
        data_0200F3F0.source = context->source->unit;
        data_0200F3F0.target = context->source->unit;
        for (i = 0; i < 3; i++) {
            func_0812F34C(0);
            func_0812F328(i);
            if (func_08130FBC()) {
                func_0812F39C(i);
                func_0812F34C((u32)context->source->unit);
                damage = func_08131B20();
                hp = context->source->unit->hp - damage;
                if (hp < 0)
                    hp = 0;
                if (hp >= func_080C7EA4(context->source->unit, 0x14))
                    hp = func_080C7EA4(context->source->unit, 0x14);
                context->source->unit->hp = hp;
                entry->damage = damage;
                entry->flags |= 1;
                entry->state |= 0x4000;
                if (i < 2)
                    data_0200F3F0.damage[i] = damage;
                data_0836D4BC[0](&data_0200F3F0.status, &entry->status,
                                 sizeof(entry->status));
                func_0813388C();
                data_0836D4BC[0](&entry->status, &data_0200F3F0.status,
                                 sizeof(entry->status));
            }
        }
        pop_state(&context->sequence);
        push_state(&context->sequence);
        context->sequence.current = 0x15;
        push_state(&context->sequence);
        context->sequence.current = 3;
        push_state(&context->sequence);
        context->sequence.current = 0x17;
        push_state(&context->sequence);
        context->sequence.current = 0x16;
        push_state(&context->sequence);
        context->sequence.current = 0x22;
        break;
    }
    case 3:
        context->task = func_080D3508(6, context->group, 0);
        context->sequence.current = 0x19;
        break;
    case 0x27:
        func_0809A260(context->source->scene, 1);
        func_0809836C(context->source, 10, context->source->unit->direction, 0);
        return 0;
    }
    return 1;
}
