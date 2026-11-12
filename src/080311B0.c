/* 0x080311B0: 180 target bytes, including literal pool. */
#include "ffta.h"
typedef struct {
    u8 unknown_00[0x78];
    u32 heap;
    u8 unknown_7c[0x1c];
    void *buffer;
    u8 unknown_9c[0xb6c];
    void *tail;
} State;
typedef struct {
    u32 unknown_00;
    void *buffer;
} Other;
extern u8 g_state_0200F390[];
extern void *data_0200F38C;
extern State *g_state_03002810;
extern Other data_03000E30;
extern void *func_080070C8(void *, u32);
extern void *func_08007138(void *, u32);
extern void func_0800717C(void *, void *);
extern void func_0814186C(const void *, void *, u32);
void func_080311B0(void)
{
    u16 first, second, third;
    void *buffer;
    void **heap;
    State **state;
    Other *other;
    data_0200F38C = func_080070C8(g_state_0200F390, 0xB880);
    heap = &data_0200F38C;
    state = &g_state_03002810;
    buffer = func_08007138(*heap, 0x7570);
    *state = buffer;
    {
        u16 *source = &first;
        *source = 0;
        func_0814186C(source, buffer, 0x01003AB8);
    }
    (*state)->heap = (u32)*heap;
    buffer = func_08007138(*heap, 0x1840);
    (*state)->buffer = buffer;
    {
        u16 *source = &second;
        *source = 0;
        func_0814186C(source, buffer, 0x01000C20);
    }
    buffer = func_08007138(*heap, 0x740);
    other = &data_03000E30;
    other->buffer = buffer;
    {
        u16 *source = &third;
        *source = 0;
        func_0814186C(source, buffer, 0x010003A0);
    }
    (*state)->tail = func_08007138(*heap, 0xF68);
    func_0800717C((void *)(*state)->heap, (*state)->buffer);
}
