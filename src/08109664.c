typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* Target: complete [0x08109664, 0x0810973C), 216 bytes, 97 instructions.
 * Local offset views do not establish original types or storage extents.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0c];
    u16 mode;
    u16 selector;
} Descriptor08109664;

typedef struct {
    u8 mode;
    u8 selector;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *actor;
    void *coordinate_result;
    u8 unknown_10[0x0c];
    void *coordinate_task;
    void *object_task;
} Payload08109664;

/* Address bindings only; original data declarations and extents are unknown. */
extern const u8 data_083A17C4[];
extern const u8 data_083A1810[];

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08109664(void *task, Descriptor08109664 *descriptor,
                  Payload08109664 *payload)
{
    u16 mode;

    switch (descriptor->phase) {
    case 0: {
        void *actor = descriptor->actor;
        payload->actor = actor;
        payload->mode = descriptor->mode;
        payload->selector = descriptor->selector;
        payload->coordinate_result = func_080DD748(actor,
            &payload->x, &payload->y, 0);
        break;
    }
    case 0x100:
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 3, payload->unknown_10, data_083A17C4, task);
        mode = (payload->mode & 1) ? 4 : 2;
        payload->object_task = func_080DCFE4(payload->actor,
            data_083A1810 + 20 * payload->selector, 12, 32, mode | 8, task, 32);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task == 0)
            descriptor->phase++;
        break;
    case 0x102:
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
