#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

typedef struct {
    u8 state;
} State0806FE14;

typedef struct {
    u16 field_00;
    u8 field_02;
    u8 field_03;
} Record0806D428;

typedef struct {
    u8 unknown_0000[0x14C0];
    ClampState08017B68 clamp;
    u8 unknown_14DC[0x15];
    u8 field_14F1;
    u8 unknown_14F2[0x596];
    State0806FE14 state_1A88;
    u8 unknown_1A8C[0x29E0];
    u8 saved_command;
    u8 unknown_446D[3];
    u8 vector_4470[0];
    u8 unknown_4470[0x7C];
    u16 field_44EC;
    u8 selection;
    u8 unknown_44EF;
    u8 field_44F0;
    u8 values_44F1[0];
    u8 unknown_44F1[6];
    u8 values_44F7[0];
    u8 unknown_44F7[0xD];
    Record0806D428 records[0];
    u8 unknown_4504[0x6FC];
    u8 field_4C00;
    u8 field_4C01;
} Context0806D428;

extern Context0806D428 *data_0200F428;
extern u16 func_08017B68(ClampState08017B68 *state, u32 index);
extern u8 func_0806EFE4(const u8 *data);
extern void func_08141540(u16 song_id);
extern u8 func_0806FE14(const State0806FE14 *object);

/* Complete [0x0806D428, 0x0806D58E): 358 bytes, 142 reached instructions,
 * 52 literal bytes and 4 zero-alignment bytes. Zero-length array views mark
 * observed byte/table offsets without assigning unknown capacities.
 * Target bytes:
 * f0b5474680b480463b4f3868a72676018119a62252018018497c09060916aaf7
 * 8ffb3968354d4919087038684119097889004118324bc9180a88183bc1180a80
 * 304c001901f0bafd3a680006000e2e4bd11809182d4812181088087038680019
 * 01f0acfd3a680006000e294bd11809189219507c08703868011909789822d201
 * 801801703868001901f098fd3968214bc91808703a6855192878800010181e4b
 * c1180133c01809780078814238d9101901f084fd3968194a8918087038680019
 * 01f07cfd3a680006000e114bd11809180e481218108808703868001901f06efd
 * 3a680006000e0a4bd11809189219507c0870282418e0000028f40002ee440000
 * 0445000070440000f1440000da140000f7440000014c000006450000f0440000
 * 6420d3f0f9ff7824084d28680849401802f05cfc0006000e01280dd13e204246
 * 10702868034bc01807e0000028f40002881a00006c4400004046047008bc9846
 * f0bc01bc0047
 */
void func_0806D428(u8 *command)
{
    u8 next_command;

    data_0200F428->selection = func_08017B68(
        &data_0200F428->clamp, (s8)data_0200F428->field_14F1);
    data_0200F428->field_44EC =
        data_0200F428->records[data_0200F428->selection].field_00;

    data_0200F428->values_44F1[
        func_0806EFE4(data_0200F428->vector_4470)] =
        data_0200F428->clamp.field_1A;
    data_0200F428->values_44F7[
        func_0806EFE4(data_0200F428->vector_4470)] =
        data_0200F428->field_14F1;
    data_0200F428->field_4C00 = data_0200F428->vector_4470[0];
    data_0200F428->field_4C01 =
        func_0806EFE4(data_0200F428->vector_4470);

    if (data_0200F428->records[data_0200F428->selection].field_02 >
        data_0200F428->records[data_0200F428->selection].field_03) {
        data_0200F428->field_44F0 =
            func_0806EFE4(data_0200F428->vector_4470);
        data_0200F428->values_44F7[
            func_0806EFE4(data_0200F428->vector_4470)] =
            data_0200F428->clamp.field_1A;
        data_0200F428->values_44F7[
            func_0806EFE4(data_0200F428->vector_4470)] =
            data_0200F428->field_14F1;
        next_command = 0x28;
    } else {
        func_08141540(100);
        next_command = 0x78;
    }

    if (func_0806FE14(&data_0200F428->state_1A88) == 1) {
        *command = 0x3E;
        data_0200F428->saved_command = next_command;
    } else {
        *command = next_command;
    }
}
