/* 0x080ED044: 708 bytes, through 0x080ED308 including literal pools. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u16 phase;
    u16 unknown_02;
    u16 *offsets;
} Descriptor;

typedef struct {
    u16 angle;
    u16 unknown_02;
    s32 ordinate;
} Motion;

typedef struct {
    u16 counter;
    u16 unknown_02;
    u16 *offsets;
    void *objects[15];
    Motion motion[15];
} Payload;

typedef struct {
    u8 time;
    u8 kind;
    u8 x;
    u8 y;
    u8 xAmplitude;
    u8 yAmplitude;
    u8 angle;
    u8 flag;
    u16 angleStep;
    s16 ordinateStep;
} Event;

extern const Event g_events_083992F8[];
extern void func_080D5F74(void **objects, u16 count);
extern void *func_080D5CC0(const void *, u16, s16, s16, s16, u8, u8, u8);
extern s16 func_08007A60(u8);
extern s32 func_08007A4C(u8);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_08011138(void *, u8);
extern void func_08011428(void *);

#define SCALE_WAVE(sample, amplitude) \
    if ((amplitude) != 0x100) { \
        if ((amplitude) == 0xC0) \
            (sample) = ((s16)(sample) >> 1) + ((s16)(sample) >> 2); \
        else if ((amplitude) == 0xA0) \
            (sample) = ((s16)(sample) >> 1) + ((s16)(sample) >> 3); \
        else if ((amplitude) == 0x80) \
            (sample) >>= 1; \
        else if ((amplitude) == 0x60) \
            (sample) = ((s16)(sample) >> 2) + ((s16)(sample) >> 3); \
        else if ((amplitude) == 0x40) \
            (sample) >>= 2; \
        else if ((amplitude) == 0x30) \
            (sample) = ((s16)(sample) >> 3) + ((s16)(sample) >> 4); \
        else if ((amplitude) == 0x20) \
            (sample) >>= 3; \
        else if ((amplitude) == 0x18) \
            (sample) = ((s16)(sample) >> 4) + ((s16)(sample) >> 5); \
        else if ((amplitude) == 0x10) \
            (sample) >>= 4; \
        else if ((amplitude) == 0x0C) \
            (sample) = ((s16)(sample) >> 5) + ((s16)(sample) >> 6); \
        else if ((amplitude) == 8) \
            (sample) >>= 5; \
        else \
            (sample) = 0; \
    }

u32 func_080ED044(void *task, Descriptor *descriptor, Payload *payload)
{
    u16 i;
    s32 coordinate;
    u32 angle;
    u16 wave;
    s32 ordinate;
    u32 x;
    u32 y;
    const Event *events = g_events_083992F8;

    switch (descriptor->phase) {
    case 0:
        payload->offsets = descriptor->offsets;
        break;
    case 1:
        func_080D5F74(payload->objects, 15);
        break;
    case 0x100:
        for (i = 0; i < 15; i++) {
            if (payload->objects[i] == 0) {
                if (payload->counter == events[i].time) {
                    payload->objects[i] = func_080D5CC0((const void *)0x084F71D8,
                        events[i].kind, events[i].x + events[i].xAmplitude,
                        events[i].y + events[i].yAmplitude, 0x3CC, 6, 0, 0);
                    payload->motion[i].angle = events[i].angle << 8;
                    payload->motion[i].ordinate = events[i].y << 8;
                }
                if (payload->objects[i] == 0)
                    continue;
            }
            payload->motion[i].angle += events[i].angleStep;
            payload->motion[i].ordinate += events[i].ordinateStep;
            angle = payload->motion[i].angle >> 8;
            ordinate = (u16)((payload->motion[i].ordinate >> 8) + events[i].y);
            {
                u32 sample = (s16)func_08007A60(angle);
                u16 amplitude = events[i].xAmplitude;
                SCALE_WAVE(sample, amplitude);
                wave = sample;
            }
            x = (u16)(wave + events[i].x);
            {
                u32 sample = (s16)func_08007A4C(angle);
                u16 amplitude = events[i].yAmplitude;
                SCALE_WAVE(sample, amplitude);
                wave = sample;
            }
            coordinate = (s16)wave;
            ordinate = (s16)ordinate;
            coordinate += ordinate;
            y = (u16)coordinate;
            if (events[i].flag == 0 && (u16)ordinate <= 159) {
                coordinate = (s16)x;
                coordinate -= payload->offsets[(s16)ordinate];
                x = (u16)coordinate;
            }
            func_080107D4(payload->objects[i], (s16)x, (s16)y, 0);
            func_08011138(payload->objects[i], (u8)(angle - 0x40) >> 7);
            if ((s16)y < -16) {
                func_08011428(payload->objects[i]);
                payload->objects[i] = 0;
            }
        }
        payload->counter++;
        break;
    }
    return 0;
}
