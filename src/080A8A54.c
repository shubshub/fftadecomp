/* 0x080A8A54..0x080A8A64: 16 bytes. */
typedef struct GroupList GroupList;
typedef struct OutputList OutputList;

void func_080A7A80(GroupList *source, OutputList *output);

void func_080A8A54(OutputList *output, GroupList *source)
{
    func_080A7A80(source, output);
}
