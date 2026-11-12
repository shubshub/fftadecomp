typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback0800052C)(u8, u8 *);
typedef struct {
    u16 value;
    u8 count;
    u8 current;
    u8 active_count;
    u8 state;
    u8 unknown_06[2];
    Callback0800052C *callbacks;
    u8 *states;
} Runner0800052C;

extern Runner0800052C data_03000880;
extern Runner0800052C data_030027E0;
extern Runner0800052C data_03000E10;
extern Callback0800052C data_03002860[];
extern Callback0800052C data_03000E4C[];
extern Callback0800052C data_03002800[];
extern u8 data_03000EB8[];
extern u8 data_030009A8[];
extern u8 data_030027D0[];
extern void func_08006A7C(Runner0800052C *, Callback0800052C *, u8 *, u8);
extern void func_08006ADC(Runner0800052C *, u8, Callback0800052C);
extern void func_08003660(u8, u8 *);

/* Target: 0x0800052C..0x0800058C, complete 96-byte body. */
void func_0800052C(void)
{
    func_08006A7C(&data_03000880, data_03002860, data_03000EB8, 4);
    func_08006A7C(&data_030027E0, data_03000E4C, data_030009A8, 1);
    func_08006A7C(&data_03000E10, data_03002800, data_030027D0, 3);
    func_08006ADC(&data_03000E10, 0, func_08003660);
}
