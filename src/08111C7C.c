typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Descriptor {
    u16 phase;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 counter;
    u8 unknown_02[6];
    void *object;
    struct InterpolationState y_motion;
};

extern const u8 data_08504D8C[];
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_080107D4(void *, s16, s16, u8);
extern void func_080E064C(struct InterpolationState *);
extern void func_08011428(void *);

/* Target: complete [0x08111C7C, 0x08111D50), 212 bytes, 94 instructions. */
u32 func_08111C7C(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->counter = 5;
        break;
    case 1:
        break;
    case 0x100:
        if (--payload->counter == 0) {
            func_080E0608(&payload->y_motion, 136, 172, 7);
            payload->object = func_080D5CC0(data_08504D8C, 3, 120,
                                           payload->y_motion.current, 779, 8, 0, 0);
            descriptor->phase++;
        }
        break;
    case 0x101: {
        u32 cycle = payload->counter & 3;
        s16 x = 120;
        s16 y = payload->y_motion.current;

        if (cycle == 1)
            y += 2;
        else if (cycle == 3)
            y -= 2;
        func_080107D4(payload->object, x, y, 0);
        func_080E064C(&payload->y_motion);
        if (payload->counter <= 7) {
            payload->counter++;
        } else {
            func_08011428(payload->object);
            payload->object = 0;
            descriptor->phase = 2;
        }
        break;
    }
    }
    return 0;
}
