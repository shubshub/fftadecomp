typedef unsigned char u8;

void func_08024860(void *state);
void *func_08096D7C(void);
void func_0809A48C(void *state);
void func_080A9420(void);
void func_0808F638(void);

void func_080231F4(u8 index, u8 *flag)
{
    func_08024860((void *)0x0200F3AC);
    if (func_08096D7C() != 0)
        func_0809A48C(func_08096D7C());
    func_080A9420();
    func_0808F638();
}
