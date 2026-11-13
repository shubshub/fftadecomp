// 0x0811EC30: complete 160-byte function, including the literal pool.
// f0b581b0041c6d4601356846291cfff6e7fc002000210022231cbbf79bff061c1e4f391c
// 3b310878002008703a1c3a3211781070053211781070391c3e310878a020087068460078
// e4f6aafc041c2878e4f6a6fc04433f25281ca0433a1c4232117810700220e4f69bfc041c
// 0320e4f697fc0443a543381c443001780570398880229201101c08433880301c0121baf7
// 73ff301c01b0f0bc02bc084740090003
#include "control_flags.h"

extern void func_0801E610(u8 *first, u8 *second);
extern void *func_080DAB84(int, int, int, void *);
extern void func_080D9BA8(void *, int);
extern int func_080035D0(int);

void *func_0811EC30(void *owner)
{
    u8 first;
    u8 second;
    void *sprite;

    func_0801E610(&first, &second);
    sprite = func_080DAB84(0, 0, 0, owner);
    g_control_flags_03000940.win0h_hi = 0;
    g_control_flags_03000940.win0h_lo = 0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0v_lo = 0xa0;
    g_control_flags_03000940.winin_lo =
        0x3f & ~(func_080035D0(first) | func_080035D0(second));
    g_control_flags_03000940.winout_lo =
        0x3f & ~(func_080035D0(2) | func_080035D0(3));
    g_control_flags_03000940.display |= 0x2000;
    func_080D9BA8(sprite, 1);
    return sprite;
}
