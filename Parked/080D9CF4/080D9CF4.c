#include "ffta.h"

// 0x080D9CF4..0x080D9F5E: 618 bytes, including the one-word literal pool.
typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    u16 x;
    u16 y;
    u16 mode;
} SwingDescriptor;

typedef struct {
    u16 x;
    u16 y;
    u16 angle;
    u16 limit;
    u8 countdown;
    u8 speed;
    u8 mode;
    u8 mirrored;
    void *first_task;
    void *second_task;
} SwingPayload;

typedef struct {
    s16 x;
    s16 y;
    s16 first_x;
    s16 first_y;
    s16 second_x;
    s16 second_y;
} SwingPoints;

extern void *func_080DAB84(u8 first, u8 second, u8 third, void *parent);
extern void func_080DADFC(void *task);
extern void func_080DAD74(void *task, SwingPoints *points);
extern void func_080D9B98(void *task);
extern void *func_080D9B64(void *task);
extern s16 func_08007A60(u8 angle);
extern s16 func_08007A4C(u8 angle);
extern s32 func_08141870(s32 numerator, s32 denominator);

u32 func_080D9CF4(void *task, SwingDescriptor *descriptor, SwingPayload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        payload->mode = descriptor->mode;
        break;
    case 0x100:
        payload->angle = 0xA0;
        payload->limit = 0xA0;
        payload->countdown = 4;
        payload->speed = 1;
        payload->first_task = func_080DAB84(0, 0, 0, task);
        payload->second_task = func_080DAB84(1, 0, 0, task);
        payload->angle += 4;
        payload->limit += payload->speed;
        descriptor->phase++;
        break;
    case 0x101: {
        u8 first_angle;
        u8 second_angle;
        s32 first_x = 0;
        s32 second_x = 0;
        s32 first_y = 0;
        s32 second_y = 0;
        SwingPoints points;

        payload->countdown--;
        if (payload->countdown == 0) {
            payload->speed++;
            payload->countdown = 4;
        }
        payload->angle += 4;
        payload->limit += payload->speed;
        func_080DADFC(payload->first_task);
        func_080DADFC(payload->second_task);
        first_angle = payload->angle;
        second_angle = payload->limit;
        if (payload->mirrored) {
            first_angle = ~first_angle + 1;
            second_angle = ~second_angle + 1;
        }
        if (payload->mode == 0) {
            first_x = func_08007A60(first_angle);
            first_x <<= 5;
            first_x += first_x * 4;
            first_x = func_08141870(first_x, 0x100);
            first_y = func_08007A4C(first_angle);
            first_y <<= 5;
            first_y += first_y * 4;
            first_y = func_08141870(first_y, 0x100);
            second_x = func_08007A60(second_angle);
            second_x <<= 5;
            second_x += second_x * 4;
            second_x = func_08141870(second_x, 0x100);
            second_y = func_08007A4C(second_angle);
            second_y <<= 5;
            second_y += second_y * 4;
            second_y = func_08141870(second_y, 0x100);
        } else if (payload->mode == 1) {
            first_x = func_08007A60(first_angle);
            first_x <<= 6;
            first_x += first_x * 2;
            first_x = func_08141870(first_x, 0x100);
            first_y = func_08007A4C(first_angle);
            first_y <<= 6;
            first_y += first_y * 2;
            first_y = func_08141870(first_y, 0x100);
            second_x = func_08007A60(second_angle);
            second_x <<= 6;
            second_x += second_x * 2;
            second_x = func_08141870(second_x, 0x100);
            second_y = func_08007A4C(second_angle);
            second_y <<= 6;
            second_y += second_y * 2;
            second_y = func_08141870(second_y, 0x100);
        }
        points.x = payload->x;
        points.y = payload->y;
        points.first_x = payload->x - first_x;
        points.first_y = payload->y - first_y;
        points.second_x = payload->x - second_x;
        points.second_y = payload->y - second_y;
        func_080DAD74(payload->first_task, &points);
        points.first_x = payload->x + first_x;
        points.first_y = payload->y + first_y;
        points.second_x = payload->x + second_x;
        points.second_y = payload->y + second_y;
        func_080DAD74(payload->second_task, &points);
        func_080D9B98(payload->first_task);
        func_080D9B98(payload->second_task);
        if (payload->limit >= payload->angle)
            descriptor->phase++;
        break;
    }
    case 0x102:
        if (payload->first_task != 0)
            func_080DADFC(payload->first_task);
        if (payload->second_task != 0)
            func_080DADFC(payload->second_task);
        payload->first_task = func_080D9B64(payload->first_task);
        payload->second_task = func_080D9B64(payload->second_task);
        if (payload->first_task == 0 && payload->second_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
