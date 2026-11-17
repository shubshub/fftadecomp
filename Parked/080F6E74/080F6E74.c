#include "ffta.h"

// Target 0x080F6E74, complete [0x080F6E74, 0x080F7160), 748 bytes:
// f0b557464e464546e0b493b081468846171c0a880648824200d1bde082420edc012a00d17ae0
// 012a04dc002a16d054e10101000080204000824272d04de10648824200d1ece0824200dadae0
// 0130824200d12be141e100000301000005a92a4838c838c1006808603a7140461422815e2648
// 814201d1012038714346d88a7871596879620224a0460006002801d00025a846081ce6f7b8fa
// 041ce4f7bbfe387209ad6e4626360aab201c291c321ce4f73dff082038568000694609181431
// 28880988401a0004000c114a12991140014312910820385680006a461218143230885288801a
// 00040b4a114001431291786a094912aa00924a46019242460623e9f741fab862e9e000003c9d
// 1408490100000000ffffffff000010ba3908dcf790fcdbe0b86ae9f720fbb862002800d0d4e0
// 3979012906d10a480091062101220223ddf70cfb7b79002b0ed0786ae6f768fa78720120f872
// 034843461880bde0000030aa8e080301000034243879012800d15424786a391c2031ba1d0092
// 054a0192029303934d460495221c0223e6f7b2fff86231e050ba3908b879002800d19ce03879
// 002804d1386a4a460092022103e0386a4b46009301210c220023e4f770fd38630b484c460094
// 012104220023e8f7a3fe7863786a00211e224b46e1f768fc78720006002805d15a20b881aa30
// 72e058ba39081e20b88141460888013008806be0b889002804d00138b8810004002863d10120
// f87242461088013010805ce03c1c1034201c0421e9f768faf87a0138f8720006a24600284fd1
// 0026386908243c577b6a9c46b9890bad3b7900280ad05246701c0006060e032e04d8b0001018
// 00680028f5d1ac82e9822b830906090e6046e6f7ddf968600b4828212a1c4b460ef73afdb100
// 514408602820f872b8890130b8810004000c7f7ab8421dd1444620880130208018e0496c0f08
// 386be4f79bfc3863002810d1386ae7f789f8000600280ad0381c10300421e9f717fa00060028
// 02d0022045462880002013b038bc9846a146aa46f0bc02bc0847

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *data;
    u8 unknown_08[12];
    s16 index;
    u16 value;
    u16 mode;
    u8 unknown_1a[2];
} Descriptor;

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 flag;
    u8 ready;
    u8 unknown_07;
    s8 index;
    u8 count;
    u8 unknown_0a;
    u8 delay;
    u16 counter;
    u8 unknown_0e[2];
    void *items[4];
    void *object;
    void *data;
    void *loader;
    void *scene;
    void *output;
    void *effect;
} Payload;

typedef struct {
    u16 x, y;
} Point;

typedef struct {
    Point points[4];
} PointTable;

extern const PointTable data_08149D3C;
extern const u8 data_0839BA10[];
extern const u8 data_088EAA30[];
extern const u8 data_0839BA50[];
extern const u8 data_0839BA58[];

extern void *func_080DD47C(void *);
extern s8 func_080DBC88(void *);
extern void func_080DBDA0(void *, u16 *, u16 *, u16 *);
extern void *func_080E03F8(void *, const void *, u8, u8, Point *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                         u16, u16, void *);
extern void *func_080DBB14(void *, u8, u8, u8, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D8924(void *, u8, u8, void *);
extern u8 func_080E0570(void **, u8);
extern void *func_080DD4A4(void *, u8);
extern u32 func_080F6C48(void *, Descriptor *, void *);
extern void *func_08005B6C(void *callback, int size, Descriptor *descriptor,
                           void *owner);
extern void *func_080DBA5C(void *);
extern u8 func_080DE244(void *);

u32 func_080F6E74(void *task, Descriptor *descriptor, Payload *payload)
{
    void *object;
    u8 animation;
    u16 size;
    u8 slot;

    switch (descriptor->phase) {
    case 0: {
        PointTable table = data_08149D3C;
        u16 x, y, z;
        Point position;

        payload->mode = 0;
        if (descriptor->index == 0x149)
            payload->mode = 1;
        payload->flag = descriptor->value;
        payload->data = descriptor->data;
        animation = 2;
        if (payload->flag != 0)
            animation = 0;
        object = func_080DD47C(payload->data);
        payload->index = func_080DBC88(object);
        func_080DBDA0(object, &x, &y, &z);
        position.x = x - table.points[payload->index].x;
        position.y = y - table.points[payload->index].y;
        payload->loader = func_080E03F8(payload->data, data_0839BA10,
            animation, 6, &position, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->loader = func_080E05DC(payload->loader);
        if (payload->loader != 0)
            break;
        if (payload->mode == 1)
            func_080D45D0(data_088EAA30, 6, 1, 2, 1);
        if (payload->flag != 0) {
            payload->count = func_080DD494(payload->data);
            payload->delay = 1;
            descriptor->phase = 0x103;
            break;
        }
        size = 0x34;
        if (payload->mode == 1)
            size = 0x54;
        payload->scene = func_080DDF68(payload->data, &payload->object,
            size, 2, &payload->ready, data_0839BA50, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        if (payload->mode == 0)
            payload->output = func_080DBB14(payload->object, 2, 12, 0, task);
        else
            payload->output = func_080DBB14(payload->object, 1, 12, 0, task);
        payload->effect = func_080DFD8C(data_0839BA58, 1, 4, 0, task);
        payload->count = func_080D8924(payload->data, 0, 0x1E, task);
        if (payload->count == 0) {
            payload->counter = 0x5A;
            descriptor->phase = 0x104;
            break;
        }
        payload->counter = 0x1E;
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->counter != 0) {
            if (--payload->counter != 0)
                break;
        }
        payload->delay = 1;
        descriptor->phase++;
        break;
    case 0x103: {
        Descriptor entry;

        func_080E0570(payload->items, 4);
        if (--payload->delay != 0)
            break;
        for (slot = 0; slot < 4; slot++)
            if (payload->items[slot] == 0)
                break;
        entry.index = payload->index;
        entry.value = payload->counter;
        entry.mode = payload->mode;
        entry.data = func_080DD4A4(payload->data, payload->counter);
        payload->items[slot] = func_08005B6C(func_080F6C48, 0x28, &entry, task);
        payload->delay = 40;
        payload->counter++;
        if (payload->counter == payload->count)
            descriptor->phase++;
        break;
    }
    case 0x104:
        payload->output = func_080DBA5C(payload->output);
        if (payload->output != 0)
            break;
        if (func_080DE244(payload->object) == 0)
            break;
        if (func_080E0570(payload->items, 4) == 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
