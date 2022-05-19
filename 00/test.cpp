#include <iostream>

class A
{
    private:
    int q = 0;
    public:
    int w = 1;
    A() {};
    void getQ(){std::cout << q << "\n";}
    void Change()
    {q = 3; w = 4;}
};

int main()
{
    A q;
    q.getQ();
    q.Change();
    q.getQ();
    return 0;

}