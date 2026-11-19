#include "ffta.h"

/* Complete target [0x08083FB0, 0x080845B4): 1540 bytes, 756 instructions.
 * f0b557464e464546e0b48bb08246094a1068cc2153464b43191c4018064c00190078161c0c2800d9
 * cae28000034940180068874618280003ba2c0000f03f08082440080870450808a0400808a4420808
 * 6841080870450808384308088c430808ec430808404408088444080818450808704508083068cc21
 * 52464a438018174fc019002101703068154bc1188918154c001980180268096800231068834210da
 * 956954689800c01880004019008980000019006801c1581c0004030c10688342f0db09480068cc21
 * 56464e43311c4018064fc0190221017072e20000be2c00004c2d0000d02c000018280003ba2c0000
 * 284880460068284940180021017043461a68cc2055464543244c10194019ae18234ff619006808a9
 * 0c3098c898c15019204940180088814601239c461e4c1019401901681d4fd2195219126808a80378
 * 4078009008a88078019008a8c078029008a800890390164c4c204f464743381c0019283000780490
 * 05200590604606900c200790301c93f77df908a8817a301c92f7aefd4146086840190a4a80180321
 * 017015e2182800032b040000d02c0000d42c0000b82c00009c2c0000b42c0000e0090003ba2c0000
 * 3068484bc018002101703068cc2152464a43454c01198918444fc019801803680968002218688242
 * 10da9d695c689000801880004019008980000019006801c1501c0004020c18688242f0dbcc205146
 * 414330680c18b42080012418a668607d4200a07d0025002816d008a9884657088022520491460020
 * 4346188008a8311c4a463a43bdf03efba07f400036180135a07d40008542eedb50460121fff74afb
 * 234ca046cc2057464743224ebc19404601680819783079181f4a8918497c0906091693f79dfc4346
 * 18680019783093f78bfc0004060c0025b5420eda15483c184146086800197830290609160c220b23
 * fcf786fe0135b542f2db0d4a9046cc205646464311687018b4239b01c0187118094c0919497c0906
 * 09160b220b23fcf76ffe8ae02b0400004c2d0000d02c000018280003882c0000202d000050460021
 * fff7f8fa002812d01c4acc205146414312688818b426b60180198918184fc919497c090609160b22
 * 0b23fcf749fe134a1068cc2153464b43c01812494018062101701268104c10190078002800d13be1
 * 0e4e9019c01804689818b427bf01c019002193f72dfc0004000ca2698100091889008918087cf7f7
 * dbfc25e118280003202d0000ba2c00005d090000502d00005046fff765fc0e4b1968cc2254465443
 * 221c89180b4e891908701c68a4180a4fe019058809482118281c0122fcf7c0ff07496418281c211c
 * 0122fcf7b9fffbe018280003ba2c0000b82c0000202d0000342d0000124a9046cc20564646431068
 * 3018104bc01893f743fd47463c68a4190d49601805880d4aa118281c0122fcf797ff084be418281c
 * 211c0122fcf790ff38688019064c001906210170cce0000018280003342d0000b82c0000202d0000
 * ba2c00001f4d2868cc2156464e4380191d4fc019ff2101701c483418286800194c30102193f77cf8
 * 286800199830002193f77efc28680019ac30002193f778fc28688019124940180021017028688019
 * 104a8018092101700a4dcc2054464443286820180c4bc01892f796fe0006002800d189e028680019
 * 064c0019ff21017082e0000018280003be2c0000882c0000c22c0000ba2c0000d42c00001a4c2168
 * 8726f6008a1910888030002300251080164a88180078164fc91908702068801803702068134a8118
 * 0978134bc01801702068124e81190d8080180321017010482168cc22554655434919b327bf01c919
 * 09880c4a0c4b95f7d5fa206840190b4940180b2101703fe018280003041d00002a0400003a040000
 * 3b0400000c0c0000b03c000290090003800e0003ba2c00008df7a2f90004002822d01c4a10681c4b
 * c0180a21017010681a4c011909781a4e801901701068194fc1190978184bc01801701168033c0a19
 * 108880381080cc2056464643301c0918124fc91906200870114900200880488008480068cc215246
 * 4a43111c40180b4bc01800780bb038bc9846a146aa46f0bc02bc0847182800032b0400003b040000
 * 3a0400002a040000041d0000ba2c000000000003
 *
 * The phase step of a record menu: one case per phase of
 * data_03002818->records[index], returning the new phase.  Like the other
 * record menus of this module it calls the module's inline helpers, whose
 * out-of-line copies sit after the module's last ordinary function
 * (0x0808537C, 0x080853A0, 0x08085450).
 */

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u32 unknown_04;
    u16 flags;
    u8 mode;
    u8 unknown_0B;
} Descriptor08083FB0;

typedef struct {
    u8 unknown_00[8];
    u16 value_index;
    u8 unknown_0A[0xA];
} Entry08083FB0;

typedef struct {
    s32 count;
    u32 *values;
    u8 unknown_08[4];
    Descriptor08083FB0 descriptor;
    Entry08083FB0 *entries;
} Configuration08083FB0;

typedef struct {
    u8 unknown_00[0x10];
    u8 field_10;
    u8 unknown_11[3];
} ObjectEntry08083FB0;

typedef struct {
    u8 unknown_00[0x18];
    ObjectEntry08083FB0 *entries;
} Object08083FB0;

typedef struct {
    u8 unknown_00[8];
    u16 *buffer;
    u8 unknown_0C[9];
    u8 width;
    u8 rows;
    u8 unknown_17[7];
    u8 stride;
    u8 unknown_1F;
} List08083FB0;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} Cursor08083FB0;

typedef struct {
    State08017424 window;
    List08083FB0 list;
    Cursor08083FB0 cursor;
    u8 settings[0x14];
} Menu08083FB0;

typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
    u8 unknown_18[0x14];
    u32 field_2C;
    u16 field_30;
    u8 phase;
    u8 unknown_33[3];
    u8 selection;
    u8 unknown_37;
    u16 value;
    u8 field_3A;
    u8 unknown_3B[0xD];
    Configuration08083FB0 *configuration;
    Menu08083FB0 menu;
    const void *resource;
    u32 *values;
    Object08083FB0 *object;
} Record08083FB0;

typedef struct {
    u8 unknown_0000[0x42A];
    u8 field_42A;
    u8 delay;
    u8 unknown_042C[0xC];
    u16 field_438;
    u8 field_43A;
    u8 field_43B;
    u8 unknown_043C[0x95D - 0x43C];
    u8 field_95D;
    u8 unknown_095E[0xC0C - 0x95E];
    u16 field_C0C;
    u8 unknown_0C0E[0x1D04 - 0xC0E];
    u8 field_1D04;
    u8 unknown_1D05[0x2C88 - 0x1D05];
    Record08083FB0 records[0];
} Root08083FB0;

typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource08083FB0;

typedef struct {
    u16 held;
    u16 pressed;
} Input08083FB0;

extern Root08083FB0 *data_03002818;
extern Resource08083FB0 data_030009E0[];
extern Input08083FB0 data_03000000;
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern void func_08017424(State08017424 *state, u32 value_00, u32 value_04,
                         u8 value_10, u8 value_11, u8 value_12, u8 value_13,
                         u16 value_14, u8 value_16, u16 value_18,
                         u16 value_1A, u8 value_17);
extern void func_08016C90(State08017424 *state, u8 mode);
extern void func_0814186C(const void *source, void *destination, u32 control);
/* The ROM tests this call's result as a full word: cmp r0, #0 right after the
 * bl at 0x080842AC, with no 16-bit narrowing. */
extern s32 func_0808389C(s32 index, u32 refresh);
extern u8 func_08083C08(s32 index);
extern u16 func_08017B68(List08083FB0 *list, s32 row);
extern u16 func_08017B50(List08083FB0 *list);
extern void func_08080F68(List08083FB0 *list, s8 row, u8 palette, u8 count);
extern void func_0807BCD8(u8 value);
extern void func_08017E28(void *settings);
extern void func_08017508(State08017424 *window, u8 appearance);
extern void func_08017D18(void *control, u8 flags);
extern u8 func_08017180(State08017424 *window);
extern void func_080812E8(u32 context, void *control, s32 enabled);
extern void func_08019A8C(void *data, u16 index, void *first, void *second);
extern u16 func_08011860(void);

/* As in src/08081DEC.c: the target forms the cursor's address (record + 0x98,
 * literal 0x2D20) at each of its three row reads and loads row from it at +0x11
 * (0x08084224, 0x0808427C, 0x080842C8). */
#define RECORD_CURSOR(index) (&data_03002818->records[index].menu.cursor)

/* An inlined copy of func_080853A0 (src/080853A0.c). */
static inline void inlined_080853A0(u32 index, State08017424 *state,
                                    const Configuration08083FB0 *configuration,
                                    u8 x, u8 y)
{
    Descriptor08083FB0 descriptor = configuration->descriptor;
    u16 selection = data_03002818->records[index].field_30;
    u16 enabled;

    if (x != 0xFF) {
        descriptor.x = x;
        descriptor.y = y;
    }
    enabled = 1;
    func_08017424(state, data_03002818->records[index].field_14,
                 data_03002818->records[index].field_2C,
                 descriptor.x, descriptor.y, descriptor.width, descriptor.height,
                 descriptor.flags, data_030009E0[selection].field_28, 5, enabled, 12);
    func_08016C90(state, descriptor.mode);
}

/* An inlined copy of func_0808537C (src/0808537C.c). */
static inline void inlined_0808537C(u32 context, Menu08083FB0 *object,
                                    s32 enabled)
{
    func_080812E8(context, &object->cursor, enabled);
    if (enabled)
        func_080812E8(context, object->settings, enabled);
}

/* An inlined copy of func_08085450 (src/08085450.c). */
static inline void inlined_08085450(void *unused, u32 *output,
                                    Configuration08083FB0 *list)
{
    u16 i;

    for (i = 0; i < list->count; i++)
        *output++ = list->values[list->entries[i].value_index];
}

/* fill16 and clear_window: the text of src/080817F8.c, whose ROM has the same
 * loop at 0x08081818..0x08081850 as this function at 0x080841C4..0x080841FE. */
static inline void fill16(u16 value, void *destination, u32 size)
{
    func_0814186C(&value, destination, ((size / 2) & 0x1FFFFF) | 0x01000000);
}

static inline void clear_window(List08083FB0 *window)
{
    u16 *buffer = window->buffer;
    u32 size = window->width * sizeof(u16);
    int row;

    for (row = 0; row < window->rows * 2; row++) {
        fill16(0, buffer, size);
        buffer += window->stride;
    }
}

u8 func_08083FB0(s32 index)
{
    switch (data_03002818->records[index].phase) {
    case 0: {
        u32 *values;
        Configuration08083FB0 *configuration;

        data_03002818->records[index].selection = 0;
        values = data_03002818->records[index].values;
        configuration = data_03002818->records[index].configuration;
        inlined_08085450(0, values, configuration);
        data_03002818->records[index].phase = 2;
        break;
    }
    case 2:
        data_03002818->delay = 0;
        inlined_080853A0(index, &data_03002818->records[index].menu.window,
                         data_03002818->records[index].configuration, 0xFF, 0xFF);
        data_03002818->records[index].phase = 3;
        break;
    case 4: {
        u32 *values;
        Configuration08083FB0 *configuration;
        u16 count;
        s32 row;

        data_03002818->delay = 0;
        values = data_03002818->records[index].values;
        configuration = data_03002818->records[index].configuration;
        inlined_08085450(0, values, configuration);
        clear_window(&data_03002818->records[index].menu.list);
        func_0808389C(index, 1);
        func_08017B68(&data_03002818->records[index].menu.list,
                      (s8)RECORD_CURSOR(index)->row);
        count = func_08017B50(&data_03002818->records[index].menu.list);
        for (row = 0; row < count; row++)
            func_08080F68(&data_03002818->records[index].menu.list, row, 12, 11);
        func_08080F68(&data_03002818->records[index].menu.list,
                      RECORD_CURSOR(index)->row, 11, 11);
        inlined_0808537C(data_03002818->records[index].field_30,
                         &data_03002818->records[index].menu, 1);
        data_03002818->records[index].phase = 6;
        break;
    }
    case 3:
        if (func_0808389C(index, 0))
            func_08080F68(&data_03002818->records[index].menu.list,
                          RECORD_CURSOR(index)->row, 11, 11);
        data_03002818->records[index].phase = 6;
        if (data_03002818->field_95D) {
            Object08083FB0 *object = data_03002818->records[index].object;
            u16 selected = func_08017B68(&data_03002818->records[index].menu.list, 0);

            func_0807BCD8(object->entries[selected].field_10);
        }
        break;
    case 6:
        data_03002818->records[index].phase = func_08083C08(index);
        inlined_0808537C(data_03002818->records[index].field_30,
                         &data_03002818->records[index].menu, 1);
        break;
    case 7:
        func_08017E28(data_03002818->records[index].menu.settings);
        inlined_0808537C(data_03002818->records[index].field_30,
                         &data_03002818->records[index].menu, 1);
        data_03002818->records[index].phase = 6;
        break;
    case 8:
        data_03002818->records[index].selection = 0xFF;
        func_08017508(&data_03002818->records[index].menu.window, 0x10);
        func_08017D18(&data_03002818->records[index].menu.cursor, 0);
        func_08017D18(data_03002818->records[index].menu.settings, 0);
        data_03002818->records[index].field_3A = 0;
        data_03002818->records[index].phase = 9;
        /* fall through: 0x0808443E runs on into case 9 at 0x08084440 */
    case 9:
        if (func_08017180(&data_03002818->records[index].menu.window))
            data_03002818->records[index].phase = 0xFF;
        break;
    case 10:
        data_03002818->field_438 += 0x80;
        data_03002818->field_42A = data_03002818->field_1D04;
        data_03002818->field_1D04 = 0;
        data_03002818->field_43B = data_03002818->field_43A;
        data_03002818->field_C0C = 0;
        data_03002818->field_43A = 3;
        func_08019A8C(data_02003CB0, data_03002818->records[index].value,
                      data_03000990, data_03000E80);
        data_03002818->records[index].phase = 11;
        break;
    case 11:
        if (func_08011860()) {
            data_03002818->delay = 10;
            data_03002818->field_43A = data_03002818->field_43B;
            data_03002818->field_1D04 = data_03002818->field_42A;
            data_03002818->field_438 -= 0x80;
            data_03002818->records[index].phase = 6;
        }
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        break;
    case 12:
        /* The table has 13 entries (cmp r0, #0xC at 0x08083FD4); entry 12
         * (0x08084020) goes straight to the return. */
        break;
    }
    return data_03002818->records[index].phase;
}
