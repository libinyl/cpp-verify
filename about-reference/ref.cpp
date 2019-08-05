class A
{
    int v = 1;
};

void callee(A& a)
{

}

void caller()
{
    A _a;
    callee(_a);
}