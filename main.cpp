#include <iostream>
#include <chrono>
#include <sstream>
#include "base/def.hpp"
#include "spec/ini/reader.hpp"

constexpr char test_FILE[] = "INI.txt";

using namespace std;
using namespace gblParser::abstract;
using namespace gblParser;

typedef ini::document current_d;
typedef ini::reader   current_r;

typedef general_reader<current_r> reader;

int main()
{
    auto start = std::chrono::system_clock::now();
    auto  d = current_d();
    std::stringstream ss = stringstream("[GLOBAL]");

    if(general_reader<current_r>::Load(ifstream(&test_FILE[0]) , d))
    {
        for(auto it = d.Elements().begin() ; it != d.Elements().end() ; it++)
        {
            std::cout << "CONTENUTO ELEMENTO =" <<(*it)->get_val() << '\n';
        }
        std::cout << " NUMERO ELEMENTI =" << d.Elements().size() << '\n';
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Operations completed in " << elapsed << " milliseconds \n" ;
    std::cout << std::endl;
    return 0;
}