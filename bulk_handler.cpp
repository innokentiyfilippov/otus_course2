#include "bulk_handler.h"

#include <string>
#include <fstream>
#include <chrono>

class Bulk
{
public:
    void append(const std::string& str);
    void release();
    void clear();

    std::string asString() const;
    int size() const;
    bool isEmpty() const;

private:
    std::string m_strRepresentation;
    int m_size = 0;
    long long m_time = 0;
};

void Bulk::append(const std::string& str)
{
    if (m_strRepresentation.empty())
    {
        m_strRepresentation = "bulk: ";
        
        auto curTime = std::chrono::system_clock::now().time_since_epoch();
        auto numSeconds = std::chrono::duration_cast<std::chrono::seconds>(curTime);
        m_time = numSeconds.count();
    }
    else
    {
        m_strRepresentation += ", ";
    }
    m_strRepresentation += str;
    m_size++;
}

void Bulk::release()
{
    std::string fileName = "bulk" + std::to_string(m_time) + ".log";
    std::ofstream out(fileName);
    out << m_strRepresentation;
    clear();
}

void Bulk::clear()
{
    m_strRepresentation.clear();
    m_size = 0;
    m_time = 0;
}

std::string Bulk::asString() const
{
    return m_strRepresentation;
}

int Bulk::size() const
{
    return m_size;
}

bool Bulk::isEmpty() const
{
    return m_size == 0;
}

void BulkHandler::process(std::istream& in)
{
    Bulk bulk;
    auto releaseBulk = [&bulk]()
    {
        std::cout << bulk.asString() << std::endl;
        bulk.release();
    };
    
    std::string str;
    while (std::getline(in, str))
    {
        bool bNeedRelease = false;
        if (str == "{")
        {
            m_dynamicBlockDepth++;
            if (!bulk.isEmpty() && m_dynamicBlockDepth == 1)
                bNeedRelease = true;
        }
        else if(str == "}")
        {
            m_dynamicBlockDepth--;
            if (m_dynamicBlockDepth == 0 && !bulk.isEmpty())
                bNeedRelease = true;
        }
        else
        {
            bulk.append(str);
            if(bulk.size() == m_bulkSize && m_dynamicBlockDepth == 0)
                bNeedRelease = true;
        }

        if (bNeedRelease)
            releaseBulk();
    }

    if (m_dynamicBlockDepth == 0 && !bulk.isEmpty())
        releaseBulk();
}
