/*
    @Author      : Kos Davide
    @Date        : 06/02/2022
    @Definition  : .Hpp file as a base class collections for creating a structure for parsing files / object / 
*/
#include "_global.h"
#include <fstream>
#include <sstream>

using namespace std;
namespace gblParser
{
    namespace Abstract
    {
        namespace interfaces
        {
            //Defining ReaderBase as an interface that represent a reader
            template <typename _Td>
            struct ReaderBase
            {
                public:
                    ReaderBase() = delete;
                    template <typename _Ts>
                    static void Load(_Ts&& stream) {_Td::Load(std::forward<_Ts>(stream));}
            };

            //Defining ElementBase as an interface that represent an element 
            struct ElementBase 
            {
                public:
                    ElementBase() = delete;
                    virtual char const *  name() = 0;
                    virtual void properties(char[]) = 0;
            };
        
            //Definining DocumentBase as an interface that represent a document
            struct DocumentBase 
            {
                    
            }
        }
    }
}