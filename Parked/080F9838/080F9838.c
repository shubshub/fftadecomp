typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 selector;
} Descriptor080F9838;

typedef struct {
    u8 selector;
    u8 unknown_01;
    u16 unknown_02;
    s16 x;
    s16 y;
    void *object;
    void *coordinate_result;
    u32 unknown_10;
    void *coordinate_child;
    void *object_child;
    u32 unknown_1C;
} Payload080F9838;

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

/* Target: complete [0x080F9838, 0x080F990A), 210 bytes, comprising
 * 202 code bytes and eight literal bytes. The address at +10 is passed
 * without an inferred pointee type or extent. */
u32 func_080F9838(void *task, Descriptor080F9838 *descriptor,
                  Payload080F9838 *payload)
{
    u16 object_flags;

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
                0, 1, 1, &payload->unknown_10, (const void *)0x0839C518, task);
        object_flags = payload->selector & 1 ? 4 : 2;
        payload->object_child = func_080DCFE4(payload->object,
            (const void *)0x0839C530, 12, 0, object_flags | 8, task, 0);
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
