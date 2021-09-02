#pragma once

#include <iostream>

class BulkHandler
{
public:
    BulkHandler(int bulkSize) :
        m_bulkSize(bulkSize)
    {}

    void process(std::istream& in);

private:
    int m_bulkSize = 0;
    int m_dynamicBlockDepth = 0;
};
