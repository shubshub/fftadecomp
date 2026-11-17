#include "ffta.h"

/* Target: complete [0x08115D74, 0x081160E2), 878 bytes including literals:
 * f0b593b0071c0e1c141c318881204000814200d1f2e081420fdc012964d0012902dc002924d09de18020400081425ed0
 * 0130814200d1bae094e10748814200d146e181420adc0238814200d1ece00130814200d128e185e10501000083204000
 * 814200d152e10130814200d166e179e1a171e17100231420315e0348814205d10120a07109e000003b01000007488142
 * 03d10120a071e0710723e079002807d1f08a20727068206204e00000870100007068e0600525207a002800d00025206a
 * 06490022009201972a1ccaf7dbfa60620348e2300349018044e100006c3d3a0860380003ce390000bdf72afd3ae1606a
 * caf7bafb051c6562002d00d032e1e079002837d1206abdf76bfe0006002800d026e1206ac7f7f8fae0600725a1790129
 * 0ed112480091062100220123bef796fbe068c7f71bfc0004000c0d2800d11025206a211c0c3180231b021a1c1543221c
 * 09320092064a0192052202920022039204972a1c0223c8f745f817e0b8ab8e08ec3d3a08e0680221c7f718fce0680721
 * 2d22c8f72bf9e068211c0931009501950295039703220223c8f7d0fa6063e068a21c211cc5f756ff30880130d9e0607a
 * 002800d1d6e00021605e0222a15e01220092221c283201920a4a0292039700220123c0f7a7f8e0620748009701210422
 * 0023c9f719ffa0631820a08030880130b7e00000c03d3a08043e3a08e079002804d0e06ac0f7dcf8e062a7e0a0880138
 * a0800004002800d0a4e0206a0021c6f733f8308801309ce0a07a002800d199e0c2f7d2fd0006002800d093e0e06ac0f7
 * bff8e062002800d08ce0206a0021c2f749fc0006002800d182e0206a0690201c0b3007900e48202105aa3b1ceff6c4fd
 * a061206a0021c7f75bfa6061a21c211c0023c7f7a7fb206106480097022104220023c9f7c1fea0633088013061e00000
 * 6d5b1108f43d3a08e07a00285ad00caa206a5060201c0b309060044814213b1ceff69afde061308801304ae0e55c1108
 * e07a002846d0a069eff684fd0020a0610023e05e0222a15e01220092221c28320192054a0292039700220123c0f712f8
 * e062308801302ce0a83d3a08e06ac0f757f8031ce362002b24d16069064904220092019702930c220023c6f7a1ff2063
 * 3088013015e00000d83d3a08e069caf733fae06100280dd1e068c8f797f80006002807d0206bc5f7c7fc2063002801d1
 * 02203080002013b0f0bc02bc0847
 */

typedef u32 (*TaskCallback08115D74)(void *, void *, void *);

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    s16 selector;
    u16 mode;
} Descriptor08115D74;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 variant;
    u8 alternate;
    u8 mode;
    u8 ready;
    u8 unknown_0a;
    u8 done;
    void *object;
    void *coordinate_result;
    void *unit;
    void *first_task;
    void *second_task;
    void *source;
    void *initial_child;
    u8 unknown_28[4];
    void *coordinate_child;
    void *object_child;
    void *animation_child;
    void *record_child;
} Payload08115D74;

typedef struct {
    u32 unknown_00;
    void *source;
    u8 *done;
    u8 unknown_0c[0x10];
} Request08115D74;

extern const u8 data_083A3D6C[];
extern const u8 data_083A3DEC[];
extern const u8 data_088EABB8[];
extern const u8 data_083A3DC0[];
extern const u8 data_083A3E04[];
extern const u8 data_083A3DF4[];
extern const u8 data_083A3DA8[];
extern const u8 data_083A3DD8[];
extern u16 data_03003860[];
extern void *func_08005B6C(TaskCallback08115D74, u16, void *, void *);
extern void func_08005B58(void *);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern u16 func_080DD6E0(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                           u16, u16, void *);
extern void func_080DD720(void *, u32);
extern void func_080DE150(void *, u16, u16);
extern void *func_080DE4B0(void *, u8 *, u8, s8, s8, u8, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *,
                           void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080E051C(void *);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);
extern u32 func_08115B6C(void *, void *, void *);
extern u32 func_08115CE4(void *, void *, void *);

u32 func_08115D74(void *task, Descriptor08115D74 *descriptor,
                  Payload08115D74 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        /* func_080E03F8 narrows both to u8 (0x080E0402-0x080E0408). */
        u8 kind;
        u8 priority;

        payload->variant = 0;
        payload->alternate = 0;
        priority = 0;
        if (descriptor->selector == 0x13B) {
            payload->variant = 1;
        } else if (descriptor->selector == 0x187) {
            payload->variant = 1;
            payload->alternate = 1;
            priority = 7;
        }
        if (payload->alternate == 0) {
            payload->mode = descriptor->mode;
            payload->source = descriptor->object;
        } else {
            payload->object = descriptor->object;
        }
        kind = 5;
        if (payload->mode != 0)
            kind = 0;
        payload->initial_child = func_080E03F8(payload->source, data_083A3D6C,
                                               kind, priority, 0, task);
        data_03003860[0x71] = 0x39CE;
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (payload->alternate == 0) {
            u16 code;

            if (func_080D3B54(payload->source)) {
                descriptor->phase = 2;
                break;
            }
            payload->object = func_080DD47C(payload->source);
            code = 7;
            if (payload->variant == 1) {
                func_080D45D0(data_088EABB8, 6, 0, 1, 1);
                if (func_080DD6E0(payload->object) == 0xD)
                    code = 0x10;
            }
            payload->animation_child = func_080DDF68(payload->source,
                &payload->object, code | 0x8000, 2, &payload->ready,
                data_083A3DEC, 5, 0, task);
        } else {
            func_080DD720(payload->object, 2);
            func_080DE150(payload->object, 7, 0x2D);
            payload->animation_child = func_080DE4B0(payload->object,
                &payload->ready, 3, 2, 0, 0, 0, task);
        }
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->unknown_28, data_083A3DC0, task);
        payload->record_child = func_080DFD8C(data_083A3E04, 1, 4, 0, task);
        payload->countdown = 0x18;
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->alternate != 0) {
            payload->coordinate_child = func_080D6134(payload->coordinate_child);
            if (payload->coordinate_child == 0)
                descriptor->phase = 2;
            break;
        }
        if (--payload->countdown != 0)
            break;
        func_080DBFFC(payload->source, 0);
        descriptor->phase++;
        break;
    case 0x103: {
        Request08115D74 request;

        if (payload->unknown_0a == 0)
            break;
        if (func_080D8B4C())
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        if (func_080D8858(payload->source, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        request.source = payload->source;
        request.done = &payload->done;
        payload->first_task = func_08005B6C(func_08115B6C, 0x20, &request,
                                            task);
        payload->unit = func_080DD4A4(payload->source, 0);
        payload->coordinate_result = func_080DD748(payload->unit, &payload->x,
                                                   &payload->y, 0);
        payload->record_child = func_080DFD8C(data_083A3DF4, 2, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x104: {
        Request08115D74 request;

        if (payload->done == 0)
            break;
        request.source = payload->source;
        request.done = &payload->done;
        payload->second_task = func_08005B6C(func_08115CE4, 0x14, &request,
                                             task);
        descriptor->phase++;
        break;
    }
    case 0x105:
        if (payload->done == 0)
            break;
        func_08005B58(payload->first_task);
        payload->first_task = 0;
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->unknown_28, data_083A3DA8, task);
        descriptor->phase++;
        break;
    case 0x106:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->object_child = func_080DCFE4(payload->unit, data_083A3DD8,
                                              12, 0, 4, task, 0);
        descriptor->phase++;
        break;
    case 0x107:
        payload->second_task = func_080E051C(payload->second_task);
        if (payload->second_task != 0)
            break;
        if (func_080DE1F0(payload->object) == 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
