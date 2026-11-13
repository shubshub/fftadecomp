typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Target: complete [0x0811DA64, 0x0811DBCC), 360 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
    void **effect;
    u8 unknown_0C[16];
} Descriptor;
typedef struct {
    u8 unknown_00[8];
    void *value;
    void *effect;
    void *initial_task;
    void *first_child;
    void *second_child;
    void *third_child;
} Payload;
typedef u32 (*Callback)(void *, Descriptor *, void *);
extern const u8 data_083A6EB4[];
extern u8 data_0600D7C0[];
extern u8 data_06005000[];
extern void *func_080D7A70(const void *, u8, void *);
extern void func_080D35D8(void);
extern void *func_080D7ABC(void *);
extern void *func_08005B6C(Callback, u16, Descriptor *, void *);
extern void *func_080E051C(void *);
extern void func_080DE390(void *);
extern u8 func_080DE488(void *);
extern void *func_080DFA70(void *, u32, u32, u32, u32, u32, void *, void *, u32, u32, void *);
extern u32 func_0811D5FC(void *, Descriptor *, void *);
extern u32 func_0811D73C(void *, Descriptor *, void *);
extern u32 func_0811D8A4(void *, Descriptor *, void *);

u32 func_0811DA64(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        payload->initial_task = func_080D7A70(data_083A6EB4, 10, task);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100: {
        Descriptor request;
        payload->initial_task = func_080D7ABC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        request.value = payload->value;
        payload->first_child = func_08005B6C(func_0811D5FC, 0x24, &request, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->first_child = func_080E051C(payload->first_child);
        if (payload->first_child != 0)
            break;
        func_080DE390(payload->value);
        descriptor->phase++;
        break;
    case 0x102: {
        Descriptor request;
        if (!func_080DE488(payload->value))
            break;
        payload->effect = func_080DFA70(payload->value, 3, 7, 6,
            0x372, 0x36b, data_0600D7C0, data_06005000, 0, 127, task);
        request.value = payload->value;
        request.effect = &payload->effect;
        payload->second_child = func_08005B6C(func_0811D73C, 0x44, &request, task);
        descriptor->phase++;
        break;
    }
    case 0x103: {
        Descriptor request;
        payload->second_child = func_080E051C(payload->second_child);
        if (payload->second_child != 0)
            break;
        request.value = payload->value;
        request.effect = &payload->effect;
        payload->third_child = func_08005B6C(func_0811D8A4, 0x4c, &request, task);
        descriptor->phase++;
        break;
    }
    case 0x104:
        payload->third_child = func_080E051C(payload->third_child);
        if (payload->third_child == 0)
            descriptor->phase++;
        break;
    case 0x105:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
