#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

namespace gblParser
{
    namespace abstract
    {
        class element_base
        {
            public:
                virtual ~element_base() {};
            public:
                virtual const string& get_val() = 0;
        };

        template <typename _Td>
        class document_base
        {
            public:
               document_base() 
               {
                 document = _Td();                   
               };
            public:
               template <typename _Tobj> 
               void Add(_Tobj&& obj) { document.Add(forward<_Tobj>(obj)); };
               template <typename _Tobj> 
               void Remove(_Tobj&& obj) { document.Remove(forward<_Tobj>(obj)); };
                    
               const vector<shared_ptr<element_base>>& Elements() const { return document.Elements(); }
            private:
                _Td document;
        };

        template <typename _Tr>
        class general_reader
        {
            public:
                template <typename _Ts , typename _Tdoc>
                static bool Load(_Ts&& arg , _Tdoc& d) { return _Tr::Load(std::forward<_Ts>(arg) , d); }
        };
    }
}