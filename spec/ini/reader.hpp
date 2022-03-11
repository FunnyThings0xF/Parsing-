#pragma once
#include <iostream>
#include <memory>
#include <fstream>

using namespace std;

using namespace gblParser::abstract;

namespace gblParser
{
    namespace ini
    {
        class keyvalue : public virtual element_base
        {
        public:
            keyvalue() : value("")
            {
                #ifdef _DEBUG 
                    std::cout << "keyvalue() called" << '\n';
                #endif
            };
            keyvalue(const string& s) : value(s)
            {
                #ifdef _DEBUG
                std::cout << "keyvalue(const string& ) called" << '\n';
                #endif 
            };
            keyvalue(const keyvalue& kv) : value(kv.value)
            {
                #ifdef _DEBUG
                std::cout << "keyvalue(const keyvalue& ) called" << '\n';
                #endif
            };

            keyvalue(keyvalue&& kv) noexcept : value(std::move(kv.value))
            {
                #ifdef _DEBUG
                    std::cout << "keyvalue(keyvalue&& ) called" << '\n';
                #endif
            };

            ~keyvalue() = default;
        public:
            bool operator==(const keyvalue& kv)
            {
                return kv.value == this->value;
            };
            bool operator!=(const keyvalue& kv)
            {
                return !(*this == kv);
            }
            bool operator==(keyvalue&& kv)
            {
                return kv.value == this->value;
            };
            bool operator!=(keyvalue&& kv)
            {
                return !(*this == std::move(kv));
            }
        public:
            const string& get_val() override { return value; }
        public:
            static const bool ccaft(const string& str_arg)
            {
                return str_arg.find('=') != string::npos;
            }
            static const bool ccaft(string&& str_arg)
            {
                return move(str_arg).find('=') != string::npos;
            }
        private:
            const string value;
        };

        class section : public virtual element_base
        {
            public:
                section() : value("") 
                {   
                    #ifdef _DEBUG
                     std::cout << "section() called" << '\n'; 
                    #endif
                
                    _linkedElements = std::vector<shared_ptr<element_base>>();
                };
                section(const string& s) : value(s) 
                {
                    #ifdef _DEBUG
                     std::cout << "section(const string& ) called" << '\n'; 
                    #endif

                    _linkedElements = std::vector<shared_ptr<element_base>>();
                };
                section(const section& kv) : value(kv.value) 
                { 
                    #ifdef _DEBUG
                        std::cout << "section(const section&) called" << '\n'; 
                    #endif

                    _linkedElements = std::vector<shared_ptr<element_base>>();
                };
                section(section&& kv) noexcept : value(std::move(kv.value)) 
                {
                    #ifdef _DEBUG
                     std::cout << "section(section&& ) called" << '\n'; 
                    #endif

                    _linkedElements = std::vector<shared_ptr<element_base>>();
                };
                ~section() = default;
            
            public:
            bool operator==(const section& s)
            {
                return s.value == this->value;
            };
            bool operator!=(const section& s)
            {
                return !(*this == s);
            }
            bool operator==(section&& s)
            {
                return s.value == this->value;
            };
            bool operator!=(section&& s)
            {
                return !(*this == std::move(s));
            }
        
            
            private:
                const string value;
                std::vector<shared_ptr<element_base>> _linkedElements;
            public:
                static const bool ccaft(const string& str_arg)
                {
                    return str_arg.find('[') != string::npos && str_arg.find(']') != string::npos && str_arg.find('=') == string::npos;
                }
                static const bool ccaft(string&& str_arg)
                {
                    return move(str_arg).find('[') != string::npos && move(str_arg).find(']') != string::npos && str_arg.find('=') == string::npos;
                }
            public:
                const string& get_val() override { return value; }
        };
   
        class document 
        {
            public:
               document() 
               {
                   _elements = std::vector<shared_ptr<element_base>>();
               }
               ~document()
               {
                   if(_elements.size() > 0)
                        _elements.erase(_elements.begin() , _elements.end());
               }

            public:
                template<typename _Tobj>
                void Add(_Tobj&& obj)
                {
                    static_assert(std::is_base_of<element_base, _Tobj>::value, "argument is not a base element");
                    _elements.push_back(make_shared<_Tobj>(forward<_Tobj>(obj)));
                }

                template<typename _Tobj>
                void Remove(_Tobj&& obj)
                {
                    static_assert(std::is_base_of<element_base, _Tobj>::value, "argument is not a base element");
                    
                    int _index = -1;                    
                    int cnt = 0;
                    for(auto it = _elements.begin() ; it != _elements.end() ; *it++)
                    {
                        auto curr_obj = dynamic_cast<_Tobj*>((*it).get());
                        if(curr_obj != nullptr)
                        {
                            if(*curr_obj == obj)
                            {
                                _index = cnt;
                            }
                        }
                        cnt++;
                    }

                    if(_index > 0) _elements.erase(_elements.begin() + _index);

                }

                std::vector<shared_ptr<element_base>>& Elements()
                {
                    return _elements;
                }
            private:
                std::vector <shared_ptr<element_base>> _elements;
        };
    
        class reader : public virtual general_reader<reader>
        {
            public:
                reader() = delete;
            public:
                static bool Load(istream* stream,document& doc)
                {
                    doc = document();
                    string item = "";
                    std::cout << "Called Load(ifstream& ) method! \n";
                    if(!stream->good()) return false;
                    while (std::getline(*stream, item))
                    {
                        if(keyvalue::ccaft(item)) doc.Add(keyvalue(item));
                        else if(section::ccaft(item)) doc.Add(section(item));
                    }
                    return true;
                }
                static bool Load(ifstream &stream , document& doc)
                {
                    doc = document();
                    string item = "";
                    std::cout << "Called Load(ifstream& ) method! \n";
                    if(!stream.good()) return false;
                    while (std::getline(stream, item))
                    {
                        if(keyvalue::ccaft(item)) doc.Add(keyvalue(item));
                        else if(section::ccaft(item)) doc.Add(section(item));
                    }
                    return true;
                }

                static bool Load(ifstream&& stream , document& doc)
                {
                    doc = document();
                    string item = "";
                    std::cout << "Called Load(ifstream& ) method! \n";
                    if(!stream.good()) return false;
                    while (std::getline(stream, item))
                    {
                        if(keyvalue::ccaft(item)) doc.Add(keyvalue(item));
                        else if(section::ccaft(item)) doc.Add(section(item));
                    }
                    return true;
                }
        };
    }
}