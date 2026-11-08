#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x2C];
} Slot080A8AFC;

typedef struct {
    void *allocator;
    void *owner;
    void *menu;
    void *object;
    u8 transfer[0x3A];
    u16 tile;
    void *graphics;
    void *list;
    Slot080A8AFC slots[32];
    u8 unknown_5D4[8];
    u8 active;
    u8 unknown_5DD[3];
} State080A8AFC;

extern BufferInitializer g_callbacks_0836D4B8[];
extern const u8 data_083BC898[];
extern void *func_080C799C(void *owner);
extern void *func_080C7A74(void *list, void *value);
extern void *func_080C7AB4(void *list, void *value, s32 key);
extern void *func_08021B1C(void *owner);
extern s32 func_08021C90(void *owner, u32 alternate, s32 step);
extern void *func_08021B9C(void *menu);
extern void func_08021C84(void *object, u16 first, u16 second);
extern void *func_08007138(void *allocator, u32 size);
extern s32 func_08005318(const void *data, u8 *output, u16 start, u16 count);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x080A8AFC, 0x080A8BC4): 200 bytes.
 * f0b5474680b4051c0f1c90462948bc21c9000268281c99f09bfb2748291801200870381c
 * 1ef03cff28650026286d2c21341c4c4354342c19211c1ef09dff286d211c321c1ef0b8ff
 * 01361f2eeedd2f6043466b60404678f7e3ffa860686801211c2279f797f8041ca86879f7
 * 19f8e8602104090c1c2279f787f82e1c4a36348028680e495ef7dafa011ce9640c480022
 * 00235cf7c3fb281c1030e96c32885201084bd218502357f79bff08bc9846f0bc01bc0047
 * b8d43608dc0500009c15000098c83b0800000106
 */
void func_080A8AFC(State080A8AFC *state, void *allocator, void *owner)
{
    s32 i;
    s32 tile;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->active = 1;
    state->list = func_080C799C(allocator);
    for (i = 0; i < 32; i++) {
        func_080C7A74(state->list, &state->slots[i]);
        func_080C7AB4(state->list, &state->slots[i], i);
    }
    state->allocator = allocator;
    state->owner = owner;
    state->menu = func_08021B1C(owner);
    tile = func_08021C90(state->owner, 1, 0x1C);
    state->object = func_08021B9C(state->menu);
    func_08021C84(state->object, tile, 0x1C);
    state->tile = tile;
    state->graphics = func_08007138(state->allocator, 0x159C);
    func_08005318(data_083BC898, state->graphics, 0, 0);
    func_08000ADC((TransferRecord *)state->transfer, state->graphics,
                  (u8 *)0x06010000 + (state->tile << 5), 0x50);
}
