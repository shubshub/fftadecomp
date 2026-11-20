/* Complete target [0x081037B0, 0x08103E12), 1634 bytes including the literal
 * pools, sha1 of the ROM bytes 699d2607f31ee206aeabbef0dc46e0a85ab00213.
 * The seven array initialisers are the ROM bytes at 0x08149DFC..0x08149E30.
 * Target bytes:
 * f0b557464e464546e0b4a3b081460f1c161c3b8882204000834200d1eae18342
 * 6edc0438834200d1a3e0834206dc002b00d185e0012b00d198e009e381204000
 * 834200d1fde0834200dd45e12a4905a8082240f0fbfd07ac2849201c082240f0
 * f5fd307c002800d1f2e2b06d0021d9f741fe7066d9f74efe306609ac6d462635
 * 0aab211c2a1cd8f7b3fa2088b08428881038f084f06dd8f71ffa0006c00d6946
 * 091814310988b28c8918b18268441c300088f38cc018f0822420315e1422b05e
 * 0d1a2623f15e1622b05e0c1a28040014210409143df0ecff0004000e8046281c
 * 04213df0edff051c201c04213df0e8ff041c012366e00000fc9d1408049e1408
 * 0748834200d1f3e183420bdc0238834200d199e10130834200d1b9e198e20000
 * 070100000548834200d11be2834200daf3e10130834200d168e289e209010000
 * f88a30707c68b46505220006002800d00022054900934b460193201c0023dcf7
 * 73fdb06674e20000e8f13908cff7caff6ee2b06edcf75afeb066002800d067e2
 * b06dd0f70ff90006040e002c00d05de2b06d311c5c31094a331c10330093084b
 * 01930523029303944b4604930123daf703fb30673888013049e2000007800000
 * 68f239089a00b218591e89007118888a40199082c88a0019d082581c0006030e
 * 032befd9404604f759f800040514a8004019c5002d12404604f75af800040414
 * a0000019c4002412012301201840002807d098003018818a491b8182c18a0919
 * 06e098003018818a49198182c18a091bc182581c0006030e032be6d938880130
 * 05e2214905a8032240f000fdf06d12ac6d464a3513ab211c2a1cd8f7c9f92288
 * 1a49219808401043219029880c390904174a1040084321900ba921a84860301c
 * 1430886000242820801980460d1c201c09303018e860ac826846001914300078
 * e8820c48902149002a1c4b4602f786f8a10041440860601c0006040e022ce6d9
 * 38880130c3e100000c9e14080000ffffffff0000ad3110083f4905a8082240f0
 * b5fc07ac3d49201c082240f0affc14a98a463b495046082240f0a8fc6a465832
 * 22923849101c082240f0a0fc707a002800d19de1b07a002800d199e1f07a0028
 * 00d195e1f06d0021daf770fcf06d18ac6d46623519ab211c2a1cd8f759f9f06d
 * d8f7caf80006000e8046274841464b005246d1180a8824881219120412142299
 * cb181b882d885b191b041b141f49009106210191002102910b21d2f753f97064
 * 1b484a460092022104220023dcf726f970670021321c0932022350180370481c
 * 0006010e0229f8d9434659006846401814300088b28c80180004001469441c31
 * 0988f68c8919090409143c2217f7c6ff388801303be10000109e1408189e1408
 * 209e1408289e1408102a5008930300007cf23908706c0df76dfc041c7464002c
 * 00d025e1707a032800d021e10c481423f25e1621735e0b490091062101910294
 * 0b21d2f7fff87064ff210df7adfa706c0df7dafa142070803888013007e10000
 * 102a5008930300007088013870800004040c002c00d0fbe00b481423f25e1621
 * 735e0a4900910621019102940c21d2f7d9f8b064ff210df787fab06c0df7b4fa
 * 38880130e3e00000102a50089303000000203072351c34351aac307aa082307a
 * 8000143030186060307a800018303018a060307a0c303018e0600c484821221c
 * 4b4601f77bff317a890069180860307a013030720006000e0328ded900203072
 * 1820708038880130b1e00000113510087088002805d0013870800004002800d0
 * a6e0307b002800d1a2e002203073307a013030723888013099e0317a321c0c32
 * 53181878012809d8481e10180078032804d102201870307a01303072301c3430
 * 0421dcf73dfc307a032800d880e0301c44300221d2f70ef90006002878d03888
 * 013074e0301c28300321dcf729fc000600286dd0f07b02286ad9b06d0021d4f7
 * 93fd0006002802d1852040005fe0706e311db21d0023d9f7fffc30660422b05e
 * 0623f15e02220092321c44320192134a02924a46039200220123d2f795f93065
 * 0f484946d0f7c6fc70650422706e0d4900924b460193142202920c221423d9f7
 * 29f9f066084849460091012114220023dbf7f4ff70673888013028e024f23908
 * dc92940854f2390874f23908301c34300421dcf7d5fb0006002819d0706dd0f7
 * d1fc7065002813d1306dd2f7abf9306500280dd1f06ddaf72dfa0006002807d0
 * f06ed7f733fef066002801d102203880002023b038bc9846a146aa46f0bc02bc
 * 0847
 */
#include "ffta.h"

typedef struct {
    s16 x, y;
} Point;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0xE];
    u16 flag;
} Descriptor;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Point *start;
    Point *end;
    u8 *status;
    u8 unknown_10[4];
    u16 index;
    u16 delay;
    u8 unknown_18[4];
} ChildDescriptor;

typedef struct {
    u8 flag;
    u8 unknown_01;
    u16 timer;
    s16 x;
    s16 y;
    u8 index;
    u8 arrow_status[3];
    u8 segment_status[4];
    u8 ready;
    u8 unknown_11[3];
    Point points[5];
    void *arrows[3];
    void *segments[4];
    void *sprites[2];
    void *unknown_4C;
    void *animation;
    void *resource;
    void *actor;
    void *object;
    void *coordinates;
    void *child;
    void *initial;
    void *record;
    void *preparation;
    void *effect;
} Payload;

typedef u32 (*TaskCallback)(void *, ChildDescriptor *, void *);

extern const u8 data_0839F1E8[];
extern const u8 data_0839F224[];
extern const u8 data_0839F254[];
extern const u8 data_0839F268[];
extern const u8 data_0839F274[];
extern const u8 data_0839F27C[];
extern const u8 data_08502A10[];
extern const u8 data_089492DC[];

/* Called by the compiler for the seven array initialisers (0x08103802,
 * 0x0810380E, 0x081039F8, 0x08103A8E, 0x08103A9A, 0x08103AA8, 0x08103AB8). */
extern void *memcpy(void *, const void *, unsigned long);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16,
                           u16, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern void func_080DBDA0(void *, s16 *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern s32 func_08141870(s32 numerator, s32 denominator);
extern s32 func_08007A4C(u8 angle);
extern s16 func_08007A60(u8 angle);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           ChildDescriptor *descriptor, void *parent);
extern u32 func_081031AC(void *, ChildDescriptor *, void *);
extern u32 func_08103510(void *, ChildDescriptor *, void *);
extern void func_080DE3BC(void *, u8);
extern void *func_080D5DD4(const void *header, u16 index, s16 x, s16 y,
                           u16 height, u8 mode, u8 palette);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u16 func_0801BB0C(s16, s16, u16);
extern void *func_08011484(void *);
extern void func_08011138(void *, u8);
extern void func_08011198(void *);
extern u8 func_080E0570(void **, int);
extern u8 func_080D5F24(void **, u16);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *,
                           void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080D6134(void *);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_081037B0(void *task, Descriptor *d, Payload *p)
{
    u8 mode;
    u16 flags;

    switch (d->phase) {
    case 0:
        p->flag = d->flag;
        p->actor = d->actor;
        mode = 5;
        if (p->flag != 0)
            mode = 0;
        p->initial = func_080E03F8(p->actor, data_0839F1E8, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        p->initial = func_080E05DC(p->initial);
        if (p->initial != 0)
            break;
        if (func_080D3B54(p->actor) != 0) {
            d->phase = 2;
            break;
        }
        p->preparation = func_080DDF68(p->actor, &p->object, 0x8007, 1,
                                       &p->ready, data_0839F268, 5, 0, task);
        d->phase++;
        break;
    case 0x101: {
        s16 x_offsets[4] = {144, 144, -144, -144};
        s16 y_offsets[4] = {-96, 96, 96, -96};
        s16 x, y, z;
        u8 facing;
        u8 angle;
        int dx, dy;
        u8 i;

        if (p->ready == 0)
            break;
        p->child = func_080DD4A4(p->actor, 0);
        p->coordinates = func_080DD4C4(p->child);
        func_080DBDA0(p->coordinates, &x, &y, &z);
        p->points[4].x = x;
        p->points[4].y = y - 16;
        facing = func_080DBC88(p->object);
        p->points[0].x = p->points[4].x + x_offsets[facing];
        p->points[0].y = p->points[4].y + y_offsets[facing];
        dx = p->points[4].x - p->points[0].x;
        dy = p->points[4].y - p->points[0].y;
        angle = func_08141860(dx, dy) >> 8;
        dx = func_08141870(dx, 4);
        dy = func_08141870(dy, 4);
        for (i = 1; i < 4; i++) {
            p->points[i].x = p->points[i - 1].x + dx;
            p->points[i].y = p->points[i - 1].y + dy;
        }
        /* Three assignments each: the sine is in r5 (0x0810399C), the
         * product goes back to r5 (0x081039A2) and the shift stays apart
         * (0x081039A4).  One expression folds to an asrs #5. */
        dx = (s16)func_08007A4C(angle);
        dx *= 40;
        dx >>= 8;
        dy = func_08007A60(angle);
        dy *= 40;
        dy >>= 8;
        for (i = 1; i < 4; i++) {
            if (i & 1) {
                p->points[i].x -= dx;
                p->points[i].y += dy;
            } else {
                p->points[i].x += dx;
                p->points[i].y -= dy;
            }
        }
        d->phase++;
        break;
    }
    case 0x102: {
        u8 delays[3] = {3, 0, 6};
        ChildDescriptor child;
        s16 x, y, z;
        Point position;
        u8 i;

        func_080DBDA0(p->object, &x, &y, &z);
        position.x = x;
        position.y = y - 12;
        child.start = &position;
        child.end = &p->points[0];
        for (i = 0; i < 3; i++) {
            child.status = &p->arrow_status[i];
            child.index = i;
            child.delay = delays[i];
            p->arrows[i] = func_08005B6C(func_081031AC, 0x120, &child, task);
        }
        d->phase++;
        break;
    }
    case 0x103: {
        s16 target_x[4] = {-64, -64, -176, -176};
        s16 target_y[4] = {-112, -48, -48, -112};
        s16 sprite_x[4] = {-4, -4, 4, 4};
        s16 sprite_y[4] = {-10, -14, -14, -10};
        s16 x, y, z;
        u8 facing;
        u8 i;

        if (p->arrow_status[0] == 0 || p->arrow_status[1] == 0 ||
            p->arrow_status[2] == 0)
            break;
        func_080DE3BC(p->object, 0);
        func_080DBDA0(p->object, &x, &y, &z);
        facing = func_080DBC88(p->object);
        p->sprites[0] = func_080D5DD4(data_08502A10, 11, x + sprite_x[facing],
                                      y + sprite_y[facing], 0x393, 6, 0);
        p->effect = func_080DFD8C(data_0839F27C, 2, 4, 0, task);
        for (i = 0; i < 3; i++)
            p->arrow_status[i] = 2;
        func_0801BB0C(p->points[4].x + target_x[facing],
                      p->points[4].y + target_y[facing], 60);
        d->phase++;
        break;
    }
    case 0x104:
        p->sprites[0] = func_08011484(p->sprites[0]);
        if (p->sprites[0] != 0)
            break;
        if (p->arrow_status[0] != 3)
            break;
        p->sprites[0] = func_080D5DD4(data_08502A10, 11, p->points[0].x,
                                      p->points[0].y, 0x393, 6, 0);
        func_08011138(p->sprites[0], 0xFF);
        func_08011198(p->sprites[0]);
        p->timer = 20;
        d->phase++;
        break;
    case 0x105:
        if (--p->timer != 0)
            break;
        p->sprites[1] = func_080D5DD4(data_08502A10, 12, p->points[0].x,
                                      p->points[0].y, 0x393, 6, 0);
        func_08011138(p->sprites[1], 0xFF);
        func_08011198(p->sprites[1]);
        d->phase++;
        break;
    case 0x106: {
        ChildDescriptor child;

        for (p->index = 0; p->index < 4; p->index++) {
            child.index = p->index;
            child.start = &p->points[p->index];
            child.end = &p->points[p->index + 1];
            child.status = &p->segment_status[p->index];
            p->segments[p->index] = func_08005B6C(func_08103510, 0x48, &child,
                                                  task);
        }
        p->index = 0;
        p->timer = 24;
        d->phase++;
        break;
    }
    case 0x107:
        if (p->timer != 0 && --p->timer != 0)
            break;
        if (p->segment_status[0] == 0)
            break;
        p->segment_status[0] = 2;
        p->index++;
        d->phase++;
        break;
    case 0x108:
        /* BUG (possible, not reproduced): nothing bounds p->index here.  The
         * index reaches 4 in this phase (0x08103CF6..0x08103CFC).  If
         * func_080D5F24 has not reported both sprites done on the frame the
         * index reaches 4, this phase runs again and the loads at 0x08103CD2
         * and 0x08103CDC read segment_status[4], which is p->ready; the store
         * at 0x08103CE4 can set it to 2.  Not reproduced. */
#ifdef BUGFIX
        if (p->index < 4 && p->segment_status[p->index] <= 1 &&
            p->segment_status[p->index - 1] == 3) {
#else
        if (p->segment_status[p->index] <= 1 &&
            p->segment_status[p->index - 1] == 3) {
#endif
            p->segment_status[p->index] = 2;
            p->index++;
        }
        func_080E0570(p->segments, 4);
        if (p->index <= 3)
            break;
        if (func_080D5F24(p->sprites, 2))
            d->phase++;
        break;
    case 0x109:
        if (!func_080E0570(p->arrows, 3))
            break;
        if (p->segment_status[3] <= 2)
            break;
        if (func_080D8858(p->actor, 0) == 0) {
            d->phase = 0x10A;
            break;
        }
        p->coordinates = func_080DD748(p->child, &p->x, &p->y, 0);
        p->animation = func_080D6098(p->x, p->y, 0, 1, 2, p->sprites,
                                     data_0839F224, task);
        p->resource = func_080D4704(data_089492DC, task);
        /* The 4 is loaded at 0x08103D7A, ahead of the first argument
         * (0x08103D7C); a literal argument is loaded after the second
         * (it compiles to ldr r0; ldr r1; movs r2,#4). */
        flags = 4;
        p->record = func_080DCFE4(p->child, data_0839F254, 12, 20, flags, task,
                                  20);
        p->effect = func_080DFD8C(data_0839F274, 1, 20, 0, task);
        d->phase++;
        break;
    case 0x10A:
        if (!func_080E0570(p->segments, 4))
            break;
        p->resource = func_080D4774(p->resource);
        if (p->resource != 0)
            break;
        p->animation = func_080D6134(p->animation);
        if (p->animation != 0)
            break;
        if (!func_080DE244(p->object))
            break;
        p->record = func_080DBA5C(p->record);
        if (p->record == 0)
            d->phase = 2;
        break;
    }
    return 0;
}
