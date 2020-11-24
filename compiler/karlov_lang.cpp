#include <iostream>
// #include <exception>

using namespace std;

class flag{
protected:
    bool m_Bad;
    bool m_Empty;
    bool m_Include;
public:
    flag(){
        m_Bad = false;
        m_Empty = false;
        m_Include = false;
    }
    flag(flag& fl){
        m_Bad = fl.m_Bad;
        m_Empty = fl.m_Empty;
        m_Include = fl.m_Include;
    }
    void set_Bad(){
        if(m_Bad == true)
            return;
        m_Bad = true;
    }
    void set_Empty(){
        if(m_Empty == true)
            return;
        m_Empty = true;
    }
    void set_Include(){
        if(m_Include == true)
            return;
        m_Include = true;
    }
    void unset_Bad(){
        if(m_Bad == false)
            return;
        m_Bad = false;
    }
    void unset_Empty(){
        if(m_Bad == false)
            return;
        m_Empty = false;
    }
    void unset_Include(){
        if(m_Include == false)
            return;
        m_Include = false;
    }
    bool& get_Bad(){
        return m_Bad;
    }
    bool& get_Empty(){
        return m_Empty;
    }
    bool& get_Include(){
        return m_Include;
    }
};

class list : public flag{//нужно же как то создавать множества
    size_t m_value;
    //brief next - след. число, uppernext - переход на вложенное множество
    //...
    //...
    list* m_pNext, *m_pUppernext;
public:
    list(const long long value = 0){
        if(value == -1){ //пустое множество
            set_Empty();
            m_value = 0; //нужно быть уверенным в том, что 0 это не значение
            m_pNext = m_pUppernext = nullptr;
        }
        else{
            m_value = value;
            m_pNext = m_pUppernext = nullptr;
        } 
    }
    list(const list& ls){ //Так как у нас будет список, мы будем использовать поверхностное копирование
        if(this == &ls)
            return;
        m_value = ls.m_value;
        m_Bad = ls.m_Bad;
        m_Empty = ls.m_Empty;
        m_Include = ls.m_Include;
        m_pNext = ls.m_pNext;
        m_pUppernext = ls.m_pUppernext;
    }
    ~list(){
        delete m_pNext;
        delete m_pUppernext;
    }
    void set_value(const long long value){
        if(value == -1){ //подумать насчет флагов, типо можно не мучаться особо сильно и с их помощью выставлять свежее значение
            set_Empty();
            m_value = 0;
        }
        else{
            m_value = value;
        }
    }
    long long get_value(){
        if(m_Empty == true)
            return -1;
        else
            return m_value; 
    }
    size_t size(){
        size_t len = 0;
        //...нужно пройтись по всему списку и подспискам, это просто нудно писать
    }
    bool operator==(list& ls){
        //...нужно сравнивать достаточно глубоко
    }
    bool operator!=(list& ls){
        //...нужно сравнивать достаточно глубоко
    }
    
    list symm(list& ls){
        list nw;
        //...нужно пройтись вглубь и сравнивать
        return nw;
    }

    ostream& operator<<(ostream& os/*,const list& ls*/){ //почему то ругается на лист в аргументах
        //...нужно пройтись до глубины
        return os;
    }

    istream& operator>>(istream& is/*, list& ls*/){ //почему то ругается на лист в аргументах
        //...тут нам понадобится итератор 
        return is;
    }
    //...не хватает разности, конъюнкции, дизъюнкции
    void change_head(const list& ls){
        //,,,хз
    }
    list& operator[](const list& ls){
        //...магия с итераторами
    }
};

int main(){



    return 0;
}
