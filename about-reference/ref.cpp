class C
{
public:
    int buf[10000] = {0};
};


int test2(C a)
{

}

int test1(C a)
{
    test2(a);
}