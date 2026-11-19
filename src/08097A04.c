#include "ffta.h"

typedef struct {
    u8 unknown_00[0xfd];
    u8 movement;
} Unit08097A04;

typedef struct {
    void *sprite;
    s16 x;
    s16 y;
    s16 z;
    u8 flags;
    u8 elapsed;
    u8 frame;
    u8 unknown_0D[3];
} AnimationSlot08097A04;

typedef struct {
    u8 unknown_00[0x24];
    u32 flags;
    u8 unknown_28[0x394 - 0x28];
    AnimationSlot08097A04 slots[2];
} Scene08097A04;

typedef struct {
    Unit08097A04 *unit;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0E[6];
    s16 column;
    s16 level;
    s16 row;
    u8 unknown_1A[4];
    u8 palette;
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
    u16 sprite;
    u16 animation;
    u8 unknown_38[0xC];
    void *display;
    void *marker;
    u8 unknown_4C[0x28];
    s8 status;
    s8 marker_kind;
    u8 unknown_76[3];
    u8 marker_palette;
    s16 marker_x;
    s16 marker_y;
    s16 marker_size;
    Scene08097A04 *scene;
} Object08097A04;

typedef struct {
    s32 x : 16;
    s32 height : 16;
    s32 y : 16;
} Position08097A04;

extern const u8 data_08391624[];

/* The result is tested at full width, with no narrowing after the call
 * (0x08097A32-0x08097A36). */
extern s32 func_0809F938(Unit08097A04 *unit, s8 *status);
extern u16 func_0809F958(u32 index);
extern u32 func_08021DA0(void *object, const void *value);
extern void func_08021DE4(void *object, u16 clear, u16 set);
extern void func_08021D0C(void *object, u16 x, u16 y);
extern void func_08021C84(void *object, u16 first, s32 second);
extern void func_08021D40(void *object, s16 x, s16 y);
extern void func_08021E64(void *object, u8 value);
extern u16 func_08021DE0(const void *object);
extern u8 func_0801CC7C(u8 column, u8 row);
extern u8 func_0801CD08(u8 column, u8 row);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0809A304(Object08097A04 *object);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_0809A530(Object08097A04 *object, u32 value);
extern void func_0809A570(Object08097A04 *object, u32 clear, u32 set);
extern u32 func_0809A53C(Object08097A04 *object);
extern void func_080975DC(Object08097A04 *object, u16 value, s8 adjustment, s32 mode);

/* An inlined copy of func_0809995C (src/0809995C.c).  The ROM holds two
 * copies, at 0x08097BEC-0x08097C9A and 0x08097D48-0x08097DF2. */
static inline u8 inlined_0809995C(Object08097A04 *context)
{
    Position08097A04 position;

    position.height = context->height >> 4;
    position.x = context->x >> 5;
    position.y = context->y >> 5;
    if (context->unit->movement != 2)
        return 0;
    if (position.x < 0 || position.y < 0 || position.x > 15 || position.y > 15)
        return 0;
    if (!func_0801CC7C((u16)position.x, (u16)position.y))
        return 0;
    if (!(func_0801CD08((u16)position.x, (u16)position.y) & 2))
        return 0;
    if ((s8)func_0801CC18((u16)position.x, (u16)position.y) <= position.height)
        return 0;
    return 1;
}

/* Starts an animation in a free slot, centred on a tile.  The column
 * and row cross a call boundary as s8: each is sign-extended from bit 12
 * when passed (0x08097E3A, 0x08097E40) and extended again at each use
 * (0x08097E54, 0x08097E5E), and the slot pointer is formed once, after the
 * arguments (0x08097E44-0x08097E48).  Both slot searches call it; the ROM
 * keeps one copy at 0x08097E38. */
static inline void start_slot(AnimationSlot08097A04 *slot, s8 column, s8 row)
{
    slot->elapsed = 0;
    slot->flags |= 1;
    slot->x = column * 32 + 16;
    slot->z = row * 32 + 16;
    slot->y = func_0801CC18(column, row) * 16;
    slot->frame = 0;
}

/* Complete [0x08097A04, 0x08097F04): 1280 bytes, 576 instructions.
 * Target:
 * f0b54f464646c0b484b0061c8946306b01273840002800d095e0b06c002800d1
 * 91e03068341c7434211c07f083ff051c221c002d74d0316b1020014075208019
 * 8046002906d1007800060016172801d143461970301c80300068406a01210840
 * 002805d000201056032801d104201070414600200856002809d1b06c00218af7
 * 8df9b06c402100228af7aaf95be0b06c21498af783f9b56c371c7e370022b85e
 * 07f058ff041c2404240c0023f85e07f051ff021c1204120c281c211c8af724f9
 * b06c8422120100218af78af9b06c4246002151568904114bc918090c00228af7
 * cff82023414600200856172800d11c23b06c311c7a310022895e321c7c321288
 * d21a120412148af719f9b06c311c793109788af7a5f916e02416390800004301
 * b06c402100228af75bf9301c80300068406a3840002801d0257004e000202056
 * 002800d12770726c002a1dd04b46596a11200840002804d0b17f101c8af780f9
 * 12e00420014000290ad0306b8021c9010840002804d0101c0d218af771f903e0
 * b17f101c8af76cf9308901041423f25e4915031c8a420ed1708900041622b15e
 * 0015814207d1b08900041822b15e4015814200d199e1316b8020400208400028
 * 0cd0802000020840002800d18de102480140316389e10000ff7fffff80200002
 * 0140002900d1ade070890004001500042649009b194001430091308900044015
 * 0004000c224a904643460b40034398460093b089000440150004000c01990a40
 * 024301923068fd300778022f2bd1009a10040114002926db019b180400140028
 * 21db0f291fdc0f281ddc00990806050e019a1006040e281c211c85f70df80006
 * 002810d0281c211c85f74cf80740002f09d0281c211c84f7cdff000600164346
 * 1914884206dc002005e00000ffff00000000ffff0120002800d01ae1301c02f0
 * 2ffb306b0c490840306340210840002814d01f22b256301c0121002300f054fb
 * 301c012102f032fc80221202301c002102f04cfc1ce00000ff7fffff301c02f0
 * 2bfc051c706c8af779f8041c2404240cf18e1f22b256301c0123fff76dfc301c
 * 291c02f013fc301c0021221c02f02efc4946486a20210840002800d1d9e00025
 * 0123074949444c4608781a1c0240002a00d17fe0103110340135012df4ddc8e0
 * 9e03000070890004001500042549029a114001430291180440150004000c224a
 * 904643460b40034398460293b089000440150004000c03990a40024303923068
 * fd300778022f2bd1029a10040114002926db039b18040014002821db0f291fdc
 * 0f281ddc02990806050e039a1006040e281c211c84f760ff0006002810d0281c
 * 211c84f79fff0740002f09d0281c211c84f720ff0006001643461914884205dc
 * 002004e0ffff00000000ffff012000287bd0f08e402878d0306b802424022043
 * 3063301c02f07cfa306b40210840002830d01f22b256301c0121002300f0a4fa
 * 301c012102f082fb301c0021221c02f09dfb39e03089c0040016b189c9040916
 * e5239b00e418e272a27a01231a43a2720006c21410320025a2800906ca141032
 * 2281000e090e84f7d5fe0006000de08025732ee0301c02f05ffb051c706c89f7
 * adff041c2404240cf18e1f22b256301c0123fff7a1fb301c291c02f047fb301c
 * 0021221c02f062fb4946486a2021084000280ed000250123104949444c460878
 * 1a1c0240002ab5d0103110340135012df5dd308900044015b082708900040015
 * f082b089000440153083012004b018bc9846a146f0bc02bc084700009e030000
 */
u32 func_08097A04(Object08097A04 *object, Scene08097A04 *scene)
{
    /* One local holds the marker test result and both slot-search counters:
     * the ROM keeps all three in r5 (0x08097A32, 0x08097D22, 0x08097EB8). */
    int i;

    if (!(object->flags & 1) && object->marker) {
        i = func_0809F938(object->unit, &object->status);
        if (i) {
            if (!(object->flags & 0x10) && object->marker_kind == 0x17)
                object->marker_kind = 0;
            if ((object->scene->flags & 1) && object->status == 3)
                object->status = 4;
            if (object->marker_kind == 0) {
                func_08021DA0(object->marker, 0);
                func_08021DE4(object->marker, 0x40, 0);
            } else {
                s32 offset;

                func_08021DA0(object->marker, data_08391624);
                /* Two lookups of the same entry (0x08097AA4, 0x08097AB2). */
                func_08021D0C(object->marker, func_0809F958(object->marker_size),
                              func_0809F958(object->marker_size));
                func_08021DE4(object->marker, 0, 0x840);
                func_08021C84(object->marker, object->marker_kind * 4 + 0x143, 0);
                offset = 0x20;
                if (object->marker_kind == 0x17)
                    offset = 0x1C;
                func_08021D40(object->marker, object->marker_x, object->marker_y - offset);
                func_08021E64(object->marker, object->marker_palette);
            }
        } else {
            func_08021DE4(object->marker, 0x40, 0);
            if (object->scene->flags & 1)
                object->status = 0;
            else if (object->status == 0)
                object->status = 1;
        }
    }

    if (object->display) {
        if (scene->flags & 0x11)
            func_08021E64(object->display, object->palette);
        else if ((scene->flags & 4) && (object->flags & 0x4000))
            func_08021E64(object->display, 13);
        else
            func_08021E64(object->display, object->palette);
    }

    if (object->column == object->x >> 5 && object->level == object->height >> 4
        && object->row == object->y >> 5)
        return 1;

    if (object->flags & 0x10000) {
        if (object->flags & 0x8000)
            object->flags &= ~0x8000;
        return 1;
    }

    /* Each arm commits the new tile position itself; the ROM keeps one copy
     * of the stores (0x08097ED6), and the first search jumps to the found-slot
     * block at 0x08097E38 with the second search's registers. */
    if (object->flags & 0x8000) {
        if (!inlined_0809995C(object)) {
            func_0809A304(object);
            object->flags &= ~0x8000;
            if (object->flags & 0x40) {
                func_0809836C(object, 1, object->direction, 0);
                func_0809A530(object, 1);
                func_0809A570(object, 0, 0x8000);
            } else {
                u32 frame = func_0809A53C(object);
                u16 display_flags = func_08021DE0(object->display);

                func_080975DC(object, object->animation, object->direction, 1);
                func_0809A530(object, frame);
                func_0809A570(object, 0, display_flags);
            }
            if (scene->flags & 0x20) {
                for (i = 0; i < 2; i++) {
                    if (!(scene->slots[i].flags & 1)) {
                        start_slot(&scene->slots[i], object->x >> 5, object->y >> 5);
                        break;
                    }
                }
            }
        }
        object->column = object->x >> 5;
        object->level = object->height >> 4;
        object->row = object->y >> 5;
    } else if (inlined_0809995C(object) && object->animation != 0x40) {
        object->flags |= 0x8000;
        func_0809A304(object);
        if (object->flags & 0x40) {
            func_0809836C(object, 1, object->direction, 0);
            func_0809A530(object, 1);
            func_0809A570(object, 0, 0x8000);
        } else {
            u32 frame = func_0809A53C(object);
            u16 display_flags = func_08021DE0(object->display);

            func_080975DC(object, object->animation, object->direction, 1);
            func_0809A530(object, frame);
            func_0809A570(object, 0, display_flags);
        }
        if (scene->flags & 0x20) {
            for (i = 0; i < 2; i++) {
                if (!(scene->slots[i].flags & 1)) {
                    start_slot(&scene->slots[i], object->x >> 5, object->y >> 5);
                    break;
                }
            }
        }
        object->column = object->x >> 5;
        object->level = object->height >> 4;
        object->row = object->y >> 5;
    }
    return 1;
}
