#include <iostream>

int main()
{
    int i = 0;
    int a;
    int b = 0;
    std::cin >> a;
    while(b != 2*a)
    {
        ++i;
        std::cout << i << " ";
        if(a != 2)
        {
            if(a == 5)
            {
                b += a;
                std::cout << "first" << "\n";
                continue;
            }
            if(a == 5)
            {
                std::cout << "second" << "\n";
            }
        }
        std::cout << "third";
    }
}