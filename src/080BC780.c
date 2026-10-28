typedef unsigned short u16;

struct Context;

extern struct Context data_02010060;
extern void func_080BAB90(struct Context *context, void *object, u16 value);

/* Target: 080BC780..080BC798, 24 bytes. */
void func_080BC780(void *object, u16 value)
{
    func_080BAB90(&data_02010060, object, value);
}
