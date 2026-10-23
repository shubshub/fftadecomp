/* 0x0800BDD0-0x0800BDF4: 36 bytes, including the trailing literal pool. */
struct ObjectFlags0800BDD0 {
    unsigned short unknown_00;
    unsigned short flags;
};

void func_0800BDD0(struct ObjectFlags0800BDD0 *object, unsigned int enabled)
{
    if (enabled)
        object->flags |= 0x2000;
    else
        object->flags &= 0xDFFF;
}
