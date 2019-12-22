#include <iostream>
#include <string>


void initialize()
{
}

void prompt()
{
    std::cout << "$ ";
}

void parseLine(const std::string& line)
{

}

void mainLoop()
{
    std::string line;
    while(!std::cin.eof())
    {
        prompt();
        std::getline(std::cin, line);
        parseLine(line);
    }
}

void shutDown()
{
}

int main(int argv, char **argc)
{
    initialize();

    mainLoop();

    shutDown();

    return EXIT_SUCCESS;
}