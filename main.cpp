#include <iostream>
#include <string>

#include "bulk_handler.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "invalid input";
        std::terminate();
    }
    
    int bulkSize = std::stoi(argv[1]);
    BulkHandler handler{ bulkSize };
    handler.process(std::cin);

    system("pause");
    return 0;
}
