typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

/* Target: complete [0x08109214, 0x081092FE), 234 bytes, 103 instructions.
 * These local offset views do not establish original storage extents or types.
 */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 mode;
} Descriptor08109214;

typedef struct {
    u8 mode;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *actor;
    void *coordinate_result;
    u8 unknown_10[4];
    void *coordinate_task;
    void *object_task;
    void *output_task;
} Payload08109214;

extern const u8 data_083A16D4[];
extern const u8 data_083A1708[];
extern const u8 data_083A16EC[];

extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_08109214(void *task, Descriptor08109214 *descriptor,
                  Payload08109214 *payload)
{
    u16 mode;
    void *actor;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        actor = descriptor->actor;
        payload->actor = actor;
        payload->coordinate_result = func_080DD748(actor,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        if (func_080DD580(payload->actor) != 0) {
            payload->coordinate_task = func_080D6098(payload->x, payload->y,
                0, 1, 1, payload->unknown_10, data_083A16D4, task);
            mode = (payload->mode & 1) ? 16 : 8;
            payload->output_task = func_080DFD8C(data_083A1708, 1,
                mode | 4, 0, task);
        }
        mode = (payload->mode & 1) ? 4 : 2;
        payload->object_task = func_080DCFE4(payload->actor, data_083A16EC,
            12, 10, mode, task, 10);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
