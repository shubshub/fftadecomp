/* 0x08009414..0x080094BC: 168 target bytes, including trailing literals. */
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x10];
    u8 *buffer;
} Display08009414;

typedef struct {
    u16 unknown_00;
    u16 row;
    u8 unknown_04[0x14];
    Display08009414 *display;
    u8 unknown_1C[8];
    u8 renderer[0x33c];
    u8 descriptor[0x80];
    u8 scratch[0x2e8];
    u8 work[0xb00];
} State08009414;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern const u8 g_table_084E8FD4[];

u16 func_08013E9C(void *destination, const u8 *resource, void *scratch,
                u16 index, u8 *flag, u8 *attribute);
void func_080154D8(void *renderer, void *destination, const void *descriptor,
                   u8 width, u8 first, u8 second, u8 third, u32 fourth, u16 flags);
void func_0814186C(const void *source, void *destination, u32 control);

void func_08009414(u8 index)
{
    State08009414 **current = (State08009414 **)0x02009188;
    u8 *destination = (*current)->display->buffer + (*current)->row * 32 + 0x2680;
    u8 *descriptor;

    g_callbacks_0836D4B8[0]((*current)->work, 0xb00);
    descriptor = (*current)->descriptor;
    func_08013E9C(descriptor, g_table_084E8FD4, (*current)->scratch, index, 0, 0);
    func_080154D8((*current)->renderer, (*current)->work, descriptor, 22,
                   0, 0, 0, 0, 0);
    func_0814186C((*current)->work, destination, 0x580);
}
