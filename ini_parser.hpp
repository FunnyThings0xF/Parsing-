#include "def_base.hpp"

namespace gblParser
{
    using namespace gblParser::Abstract::interfaces;

    namespace INI 
    {
        class FileReader  : public ReaderBase<FileReader>
        {
            public:
                FileReader() = delete;
            public:
                static void Load(istream& f)
                {
                    //Check if file is good
                    if(f.good())
                    {
                        //Iterate over every single line
                        for (std::string line; std::getline(f, line); ) 
                        {
                            std::cout << line << std::endl;
                        }
                    }
                }
        };
    
        class Element : public ElementBase
        {
            public:

            private:

        };
    }
}