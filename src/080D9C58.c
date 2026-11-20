#include "ffta.h"

/* Complete [0x080D9C58, 0x080D9CF4), 156 bytes including the two pool words.
 * Target bytes:
 * 30b582b00c1c151c2188012932d0012902dc002908d03ce08020400081422dd00130814233d034e0
 * 104841680068009001910f48a02149001423e25e92006a441368022232f796fb686032f7b7fc021c
 * 0023e08a51785070208b117810700232581c0004030c9f2bf3d912e02c9b140871ae0d08686832f7
 * cbfc0ae02878002807d0686832f7f0fc2088013000e002202080002002b030bc02bc0847
 */

typedef struct {
    u16 state;
    u8 unknown_02[0x12];
    s16 window;
    u16 left;
    u16 right;
} WindowEvent;

typedef struct {
    u8 finish_requested;
    u8 unknown_01[3];
    void *object;
} WindowState;

typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

typedef struct {
    u16 *registers[2];
} WindowDestinations;

typedef void (*WindowCopy)(const void *source, void *destination);

extern const WindowDestinations data_08149B2C;
extern void func_080DAE70(const void *source, void *destination);
extern void *func_0800C3CC(WindowCopy copy, u16 bytes, u16 width, u16 *destination);
extern WindowLine *func_0800C614(void *object);
extern void func_0800C668(void *object);
extern void func_0800C6C0(void *object);

u32 func_080D9C58(void *task, WindowEvent *event, WindowState *state)
{
    switch (event->state) {
    case 0: {
        WindowDestinations destinations = data_08149B2C;
        WindowLine *line;
        u16 row;

        state->object = func_0800C3CC(func_080DAE70, 320, 2, destinations.registers[event->window]);
        line = func_0800C614(state->object);
        for (row = 0; row < 160; line++, row++) {
            line->left = event->left;
            line->right = event->right;
        }
        break;
    }
    case 1:
        func_0800C668(state->object);
        break;
    case 0x100:
        if (state->finish_requested) {
            func_0800C6C0(state->object);
            event->state++;
        }
        break;
    case 0x101:
        event->state = 2;
        break;
    }
    return 0;
}
