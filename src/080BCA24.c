struct Context;

extern void *func_08022840(unsigned int size);
extern void func_080BC4BC(struct Context *context, void *argument);

/* Target: 080BCA24..080BCA3E, 26 bytes. */
struct Context *func_080BCA24(void *argument)
{
    struct Context *context = func_08022840(0x88);

    func_080BC4BC(context, argument);
    return context;
}
