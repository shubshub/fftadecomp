typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* Target: complete [0x080F9094, 0x080F9166), 210 bytes.
 * f0b584b0061c0d1c141c298801295bd0012902dc002908d056e08020400081420ed00130814241d04ee0a88a20706868a060a11c221d0023e4f73cfbe06043e0a068e4f753fa0006002810d00221605e0422a15e01220092221c10320192114a0292039600220123dcf7ccff606121780127381c08400223002800d00423a06809490822134300930196002202920c220023e3f75dffa0612178381c08402888013010e010c4390828c439086069dcf7f7ff6061002807d1a069e2f785fca061002801d102202880002004b0f0bc02bc0847
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080F9094;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *coordinate_result;
    u32 unknown_10;
    void *coordinate_child;
    void *object_child;
    u32 unknown_1C;
} Payload080F9094;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080F9094(void *task, Descriptor080F9094 *descriptor,
                  Payload080F9094 *payload)
{
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        if (func_080DD580(payload->object))
            payload->coordinate_child = func_080D6098(payload->x, payload->y,
                0, 1, 1, &payload->unknown_10, (const void *)0x0839C410, task);
        flags = (payload->selector & 1) ? 4 : 2;
        payload->object_child = func_080DCFE4(payload->object,
            (const void *)0x0839C428, 12, 0, flags | 8, task, 0);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
