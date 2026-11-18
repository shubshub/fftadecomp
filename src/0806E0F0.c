#include "ffta.h"

/* 0806E0F0..0806E170, 128 bytes including the literal pools. */
typedef struct {
    u8 unknown_0000[0x446C];
    u8 next;
    u8 unknown_446D[0x82];
    u8 selection;
} Menu;

typedef struct {
    u8 unknown_0000[0x1F30];
    u16 items[5];
    u8 unknown_1F3A[0x2A];
    u32 funds;
} Save;

typedef struct {
    u8 unknown_00[0x18];
    u8 price_index;
    u8 unknown_19[7];
} Item;

typedef struct {
    u8 category;
    u8 text_index;
    u16 price_units;
} Price;

extern Menu *data_0200F428;
extern Save g_state_02000000;
extern const Item g_table_0851D180[];
extern const Price data_08528968[];
extern void func_08141540(u16 song_id);

void func_0806E0F0(u8 *command)
{
    u8 price_index;
    u32 price;

    func_08141540(100);
    *command = 60;
    price_index = g_table_0851D180[
        g_state_02000000.items[data_0200F428->selection]].price_index;
    price = data_08528968[price_index].price_units * 200;
    if (price <= g_state_02000000.funds)
        data_0200F428->next = 100;
    else
        data_0200F428->next = 80;
}
