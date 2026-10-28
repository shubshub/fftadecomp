typedef unsigned char u8;

typedef void (*Callback)(u8 index, u8 *state);

typedef struct {
    u8 unknown_00[8];
    Callback *callbacks;
    u8 *states;
} CallbackTable;

extern CallbackTable data_03000880;
extern Callback data_03002860[];
extern u8 data_03000EB8[];
extern CallbackTable data_030027E0;
extern Callback data_03000E4C[];
extern u8 data_030009A8[];
extern CallbackTable data_03000E10;
extern Callback data_03002800[];
extern u8 data_030027D0[];

extern void func_08006A7C(CallbackTable *table, Callback *callbacks,
                          u8 *states, u8 count);
extern void func_08006ADC(CallbackTable *table, u8 index, Callback callback);
extern void func_08003660(u8 index, u8 *state);

/* Complete [0x0800052C, 0x0800058C): 96 bytes, 24 instructions. */
void func_0800052C(void)
{
    func_08006A7C(&data_03000880, data_03002860, data_03000EB8, 4);
    func_08006A7C(&data_030027E0, data_03000E4C, data_030009A8, 1);
    func_08006A7C(&data_03000E10, data_03002800, data_030027D0, 3);
    func_08006ADC(&data_03000E10, 0, func_08003660);
}
