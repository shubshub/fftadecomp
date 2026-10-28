typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*Callback0807E2C4)(void *, u8 *);

typedef struct {
    u8 unknown_00[8];
    Callback0807E2C4 *callbacks;
    u8 *states;
} Callbacks0807E2C4;

typedef struct {
    u8 unknown_00[6];
    u8 id;
} Record0807E2C4;

typedef struct {
    u8 unknown_0000[0x1131];
    u8 enabled;
    u8 unknown_1132;
    u8 flag;
    u8 unknown_1134[0xbd8];
    Record0807E2C4 *record;
    u8 unknown_1d10[0x1040];
    void *context;
} State0807E2C4;

typedef struct {
    u8 state;
    u8 unknown_01[0x4b];
} Entry0807E2C4;

extern State0807E2C4 *data_03002818;
extern Callbacks0807E2C4 data_03002730;
extern Entry0807E2C4 data_030009E0[];
extern u8 data_0200F23B;
extern u8 data_0200F23A;
extern void func_0807D96C(u8, u8, void *);
extern void func_0807B858(void);
extern void func_0808A604(u8, u8);
extern void func_0807C7E8(void *, u8 *);
extern void func_08006ADC(Callbacks0807E2C4 *, u8, Callback0807E2C4);

/* Complete [0x0807E2C4, 0x0807E37C): 184 bytes, 64 instructions. */
void func_0807E2C4(void *unused, u8 *state)
{
    switch (*state) {
    case 0:
        data_03002818->flag = 0;
        func_0807D96C(1, data_03002818->record->id, data_03002818->context);
        func_0807B858();
        func_0808A604(3, 5);
        data_03002818->enabled = 1;
        func_08006ADC(&data_03002730, 7, func_0807C7E8);
        *state = 16;
        break;
    case 16:
        if (data_03002730.states[7] == 18)
            *state = 18;
        break;
    case 9:
        if (data_030009E0[data_0200F23B].state == 0)
            *state = data_0200F23A;
        break;
    }
}
