#include "ffta.h"

/* 0x08121A48..0x08121B64: 284 bytes.
 * 10b506480068007b01380c2800d97ae0800003494018006887460000cc5901026c1a1208f21a
 * 1208aa1a12084e1b1208bc1a1208001b12084e1b1208001b1208e41a12084e1b12084e1b1208
 * 4e1b1208281b1208a01a120844200121a7f766fd31e003f059fd0249092008704be0000090f3
 * 0002002009f773fd064c231c94331988054808400022042108431880227039e0000090f30002
 * feff000075f74af9012178f7b9fb03f0e5fd02490020087029e0000090f300020548064a8118
 * 0978054bc01801700549122008701be0000000000002902100009121000090f3000208200121
 * a7f748fd00f7b4ffa220e7f6e1ffe8f649fa07489430028880235b00191c1143018004480168
 * 0020087310bc01bc004790f30002cc590102
 */

typedef struct {
    u8 unknown_00[0x2190];
    u8 value_2190;
    u8 value_2191;
} State08121A48;

typedef struct {
    void *manager;
    void *allocation;
    void *task;
    u8 action;
} ScriptContext08121A48;

typedef struct {
    u8 mode;
    u8 unknown_01[0x93];
    u16 flags;
} ModeState08121A48;

extern State08121A48 g_state_02000000;
extern ScriptContext08121A48 *data_020159CC;
extern ModeState08121A48 g_state_0200F390;
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void func_080C95C0(u16 index, u32 value);
extern void func_08125560(void);
extern void func_0802B5A8(u32 value);
extern void *func_08096D7C(void);
extern void func_0809A260(void *object, u32 value);
extern void func_081256BC(void);
extern void func_08022A9C(void);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);

/* Complete [0x08121A48, 0x08121B64): 284 bytes. */
void func_08121A48(void)
{
    switch (data_020159CC->action) {
    case 13:
        func_080C9574(0x44, 1);
        g_state_0200F390.mode = 0x12;
        break;
    case 2:
        func_08125560();
        g_state_0200F390.mode = 9;
        break;
    case 4:
        func_0802B5A8(0);
        g_state_0200F390.flags &= ~1;
        g_state_0200F390.flags |= 4;
        g_state_0200F390.mode = 0;
        break;
    case 8:
        func_0809A260(func_08096D7C(), 1);
        func_081256BC();
        g_state_0200F390.mode = 0;
        break;
    case 1:
        g_state_0200F390.mode = 0;
        break;
    case 5:
    case 7:
        g_state_02000000.value_2191 = g_state_02000000.value_2190;
        g_state_0200F390.mode = 0x12;
        break;
    case 12:
        func_080C95C0(8, 1);
        func_08022A9C();
        func_08009AFC(0xA2);
        func_08009FD0();
        g_state_0200F390.flags |= 0x100;
        break;
    }
    data_020159CC->action = 0;
}
