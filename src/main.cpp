#include <iostream>

void initialize()
{
}

void mainLoop()
{
    char c;
    while(!std::cin.eof())
    {
        std::cin >> c;
        std::cout << static_cast<int>(c) << std::endl;
    }
    std::cout << "done" << std::endl;
}

void shutDown()
{
}
int main(int argv, char **argc)
{


    return EXIT_SUCCESS;
}