void func_08011614(void);
void func_0800C70C(void);
void func_0800C2FC(void);
void func_0800718C(void *owner);

void func_0800A61C(void)
{
    func_08011614();
    func_0800C70C();
    func_0800C2FC();
    func_0800718C(*(void **)0x02008FF4);
    *(void **)0x02008FF4 = 0;
}
