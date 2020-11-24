#include <iostream>

class vector{
    size_t len(long long decimal)
    {
        if(decimal == 0)
            return 1;
        
        size_t lenght = 0;
        for (; decimal > 0; ++lenght)
        {
            decimal /= 10;
        }

        return lenght;
    }

    long long dec_value;

public:
    long long *arr_value;

    long long get_dec(){
        return dec_value;
    }

    void set_dec(long long decimal){
        dec_value = decimal;
        if (arr_value)
        {
            delete[] arr_value;
        }
        arr_value = new long long[len(dec_value)];
        for (size_t i = 0; i < len(dec_value); ++i)
        {
            arr_value[len(dec_value) - 1 - i] = decimal % 10;
            decimal /= 10;
        }
    }

    long long get_arr()
    {
        long long semi = 0;
        for (size_t i = 0; i < get_len(); ++i)
        {
            semi += arr_value[i];
            semi *= 10;
        }

        return semi / 10;
    }

    size_t get_len(){
        return len(dec_value);
    }

    vector(long long dec = 0){
        dec_value = dec;
        arr_value = new long long[len(dec)];
        for(size_t i = 0; i < len(dec); ++i){
            arr_value[len(dec) - 1 - i] = dec % 10;
            dec /= 10;
        }
    }
    
    vector(const vector& vc){
        dec_value = vc.dec_value;
        long long dec_semi = dec_value;
        if(arr_value){
            delete[] arr_value;
        }
        arr_value = new long long[len(dec_value)];
        for(size_t i = 0; i < len(dec_value); ++i){
            arr_value[len(dec_value ) - 1 - i] = dec_semi % 10;
            dec_semi /= 10;
        }
    }

    ~vector(){
        delete[] arr_value;
    }

    vector& operator=(vector& vc){
        dec_value = vc.dec_value;
        if(arr_value)
            delete[] arr_value;
        arr_value = new long long[len(vc.dec_value)];
        for(size_t i = 0; i < len(dec_value); ++i)
            arr_value[i] = vc.arr_value[i];
        return *this;
    }

    bool operator==(vector& vc){
        return this->get_dec() == vc.get_dec() && this->get_len() == vc.get_len() && this->get_arr() == vc.get_arr();
    }

    bool operator!=(vector& vc){
        return this->get_dec() != vc.get_dec() && this->get_len() != vc.get_len() && this->get_arr() != vc.get_arr();
    }

    bool operator<(vector& vc){
        return this->get_dec() < vc.get_dec() && this->get_len() < vc.get_len() && this->get_arr() < vc.get_arr();
    }

    bool operator>(vector& vc){
        return this->get_dec() > vc.get_dec() && this->get_len() > vc.get_len() && this->get_arr() > vc.get_arr();
    }
    
    bool operator>=(vector& vc){
        return this->get_dec() >= vc.get_dec() && this->get_len() >= vc.get_len() && this->get_arr() >= vc.get_arr();
    }

    bool operator<=(vector& vc){
        return this->get_dec() <= vc.get_dec() && this->get_len() <= vc.get_len() && this->get_arr() <= vc.get_arr();
    }
};

class iterator
{
    public:
    long long *begin, *end;

    iterator() = delete;
    iterator(vector& vc){
        begin = vc.arr_value;
        end = &vc.arr_value[vc.get_len() - 1];
    }
    iterator(const iterator& iter){
        begin = iter.begin;
        end = iter.end;
    }

    void reset_iter(vector &vc)
    {
        begin = vc.arr_value;
        end = &vc.arr_value[vc.get_len() - 1];
    }

    long long* operator++(){
        if(begin == nullptr)
            return nullptr;
        if(begin == end)
            return begin;
        begin++;
        return begin;
    }

    long long* operator+(size_t inc){
        if (begin == nullptr)
            return nullptr;
        for (size_t i = 0; i < inc; ++i)
        {
            if(begin > end)
                return end;
            if (begin == end)
                return begin;
            begin++;
        }
        return begin;
    }

    bool operator==(const iterator &sm)
    {
        return this->begin == sm.begin && this->end == sm.end;
    }

    bool operator!=(const iterator &sm)
    {
        return this->begin == sm.begin && this->end == sm.end;
    }

    bool operator<(const iterator &sm)
    {
        return this->begin < sm.begin && this->end < sm.end;
    }

    bool operator>=(const iterator &sm){
        return this->begin >= sm.begin && this->end >= sm.end;
    }

    bool operator<=(const iterator &sm){
        return this->begin <= sm.begin && this->end <= sm.end;
    }

    bool operator>(const iterator &sm)
    {
        return this->begin > sm.begin && this->end > sm.end;
    }
};

std::istream& operator>>(std::istream is, vector& vc){
    long long semi = 0;
    is >> semi;
    vc.set_dec(semi);
    return is;
}

std::ostream& operator<<(std::ostream os, vector& vc){
    os << " Dec: "<< vc.get_dec() << " " << "Bin: " << vc.get_arr() << " " << std::endl;
    return os;
}

std::istream& operator>>(std::istream is, interface& inter){
    long long semi = 0;
    is >> semi;
    inter.set_value(semi);
    return is;
}

std::ostream& operator<<(std::ostream os, interface& inter){
    os << inter.vec;
    return os;
}

class interface{
public:
    vector vec;
    iterator ivec;

    interface(long long value): vec(value), ivec(vec){}
    interface(const interface& inter): vec(inter.vec), ivec(inter.ivec){}

    vector& get_vec(){
        return vec;
    }

    void set_value(long long value){
        vec.set_dec(value);
        ivec.reset_iter(vec);
    }

    long long& operator[](size_t inc){

        return *ivec.operator+(inc);
    }
    
    bool operator==(interface& inter){
        return vec==inter.vec && ivec==inter.ivec;
    }

    bool operator!=(interface &inter)
    {
        return vec != inter.vec && ivec != inter.ivec;
    }

    bool operator>=(interface &inter)
    {
        return vec >= inter.vec && ivec >= inter.ivec;
    }

    bool operator<=(interface &inter)
    {
        return vec <= inter.vec && ivec <= inter.ivec;
    }

    bool operator<(interface &inter)
    {
        return vec < inter.vec && ivec < inter.ivec;
    }

    bool operator>(interface &inter)
    {
        return vec > inter.vec && ivec > inter.ivec;
    }

    interface &operator=(interface &inter)
    {

    }
    void operator=(long long value){

    }
};

int main(){

    interface kek{4}, lol{6};

    std::cout << kek << std::endl;

    kek == lol;
    kek > lol;
    kek.vec.get_arr();



    return 0;
}
