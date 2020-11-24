#include <iostream>
#include <cmath>

class vector
{
    long long dec_value;
    bool *bin_value;
    size_t bin_len;

    long long transform(long long dec)
    {
        long long res = 0;
        do
        {
            res += dec % 2;
            res *= 10;
            dec /= 2;
        } while (dec > 0);
        // res /= 10;
        return res * 10;
    }
    void include_bin(long long bin)
    {
        len(bin) > 3 ? bin /= 10 : bin;
        for (size_t i = 0; i < bin_len; ++i)
        {
            bin_value[bin_len - i - 1] = bin % 10;
            //std::cout << bin_value[bin_len - i - 1] << std::endl;
            bin /= 10;
        }
        // for (size_t i = 0; i < bin_len; ++i)
        // {
        //     std::cout << bin_value[i] << std::endl;
        // }
    }
    size_t len(bool *bin)
    {
        bool *p = bin;
        while (*bin)
            bin++;
        return bin - p;
    }
    size_t len(long long decimal)
    {
        size_t lenght = 0;
        for (; decimal > 0; ++lenght){
            decimal /= 10;
        }
            
        return lenght;
    }
    long long convert(long long convertable)
    {
        int num = convertable;
        int dec_value = 0;
        // Initializing base value to 1, i.e 2^0
        int base = 1;
        int temp = num;
        while (temp)
        {
            int last_digit = temp % 10;
            temp = temp / 10;
            dec_value += last_digit * base;
            base = base * 2;
        }
        return dec_value;
    }
    void del_travel(vector *&next)
    {
        if (next)
        {
            del_travel(next->next);
            if(next->bin_value){
                delete[] next->bin_value;
                next->bin_value = nullptr;
            }
            delete next;
            next = nullptr;
            
        }
    }

public:
    vector *next;
    vector(long long decimal = 0)
    {
        dec_value = decimal;
        bin_len = len(transform(decimal)) > 3 ? len(transform(decimal)) - 1 : len(transform(decimal));
        bin_value = new bool[bin_len];
        include_bin(transform(decimal));
        next = nullptr;
    }
    vector(const vector &vc)
    { //глубокое копирование
        if(this == &vc)
            return;
        dec_value = vc.dec_value;
        bin_len = vc.bin_len;
        if(bin_value)
            delete bin_value;
        bin_value = new bool[bin_len];
        for (size_t i = 0; i < bin_len; ++i)
        {
            bin_value[i] = vc.bin_value[i];
        }
        next = vc.next;
    }

    ~vector()
    {
        if(bin_value){
            delete[] bin_value;
            bin_value = nullptr;
        }
        del_travel(next); 
    }

    size_t get_len()
    {
        return bin_len;
    }

    bool operator==(vector &vc)
    {
        return bin_len == vc.bin_len && get_bin() == vc.get_bin() && dec_value == vc.dec_value;
    }

    bool operator!=(vector &vc)
    {
        return bin_len == vc.bin_len && get_bin() == vc.get_bin() && dec_value == vc.dec_value;
    }

    bool operator>(vector &vc)
    {
        return bin_len > vc.bin_len && get_bin() > vc.get_bin() && dec_value > vc.dec_value;
    }

    bool operator<(vector &vc)
    {
        return bin_len < vc.bin_len && get_bin() < vc.get_bin() && dec_value < vc.dec_value;
    }

    bool operator>=(vector &vc)
    {
        return bin_len >= vc.bin_len && get_bin() >= vc.get_bin() && dec_value >= vc.dec_value;
    }

    bool operator<=(vector &vc)
    {
        return bin_len <= vc.bin_len && get_bin() <= vc.get_bin() && dec_value <= vc.dec_value;
    }
    vector &operator*(const vector &vc)
    { 
        vector semi(dec_value * vc.dec_value);
        return semi;
    }

    long long concat(vector &vc)
    {
        size_t size = len(vc.bin_len) + len(bin_len);
        long long st = get_bin(), nd = vc.get_bin();
        st *= pow(10, len(nd));
        st += nd;
        st = convert(st);
        return st;
    }

    bool &operator[](size_t i)
    {
        return bin_value[i];
    }

    long long get_dec()
    {
        return dec_value;
    }

    vector &operator=(const long long dec_value){
        vector sub{dec_value};
        *this = sub;
        return* this;
    }

    vector &operator=(const vector &vc)
    {
        if(this == &vc)
            return *this;
        next = vc.next;
        bin_len = vc.bin_len;
        if(bin_value){
            delete[] bin_value;
            bin_value = new bool[bin_len];
        }
        for(size_t i = 0; i < bin_len; ++i)
            bin_value[i] = vc.bin_value[i];
        dec_value = vc.dec_value;
        return *this;
    }

    void set_dec(long long value)
    {
        *this = vector(value);
    }

    long long get_bin()
    { //чтобы проще работать с бинарным оператором сравнения
        long long res = 0;
        for (size_t i = 0; i < bin_len; ++i)
        {
            res += bin_value[i];
            res *= 10;
        }

        res /= 10;
        return res;
    }

    long long sub_vector(size_t begin, size_t end)
    {
        //std::max(std::min) было бы хорошо использовать для проверки диапозона
        if (get_len() < begin && get_len() > end || begin > end)
        {
            std::cout << "Can`t realize subvector, invalid begin/end" << std::endl;
            return -1;
        }
        else
        {
            long long delim = pow(10, (len(get_bin() - begin))); //ограничим число слева
            long long semi = get_bin() % delim;
            if (end == get_len())
            {
                return convert(semi);
            }
            else
            {
                semi /= pow(10, len(get_bin()) - end); //ограничим число справа
                return convert(semi);
            }
        }
    }
};

class iterator
{
public:
    vector *begin, *end;

public:
    iterator() = delete;
    iterator(vector &vc)
    {
        begin = &vc;
        while (vc.next != nullptr)
        {
            vc = *vc.next;
        }
        end = &vc;
    }
    void reset_iter(vector *vc)
    {
        begin = vc;
        while (vc->next)
        {
            vc = vc->next;
        }
        end = vc;
    }
    vector *operator++()
    {
        if (begin == nullptr)
            return nullptr;
        if (begin == end)
            return begin;
        begin = begin->next;
        return begin;
    }
    vector *operator+(size_t inc)
    {
        if (begin == nullptr)
            return nullptr;
        for (size_t i = 0; i < inc; ++i)
        {
            if (begin == nullptr || begin == end)
                return begin;
            begin = begin->next;
        }
        return begin;
    }
    bool operator==(const iterator &sm)
    {
        return this == &sm;
    }
    bool operator!=(const iterator &sm)
    {
        return this == &sm;
    }
    bool operator<(const iterator &sm)
    {
        return this < &sm;
    }
    bool operator>(const iterator &sm)
    {
        return this > &sm;
    }
};

class interface
{

    size_t size = 0;

public:
    vector vc;
    iterator ivc;
    interface(long long value) : vc(value), ivc(vc), size(1) {}
    interface() = delete;
    interface(const interface& intr) = delete;
    ~interface()
    {
        vc.~vector();
    }
    void push_back(long long value)
    {
        size++;
        vc.next = new vector(value);
        ivc.reset_iter(&vc);
    }
    size_t get_size()
    {
        return size;
    }
    vector &operator[](size_t i)
    {
        return *ivc.operator+(i);
    }
};

std::ostream &operator<<(std::ostream &os, vector &vc)
{
    os << "dec: " << vc.get_dec() << " bin: " << vc.get_bin() << " ";
    return os;
}

std::ostream &operator<<(std::ostream &os, interface &invc)
{
    os << "{(";
    for (size_t i = 0; i < invc.get_size(); ++i)
    {
        if (i == invc.get_size() - 1)
        {
            os << invc[i];
            break;
        }
        os << invc[i] << " , ";
    }
    os << ")}";
    invc.ivc.reset_iter(&invc.vc);
    return os;
}

std::istream &operator>>(std::istream &is, vector &vec)
{
    long long value;
    is >> value;
    vec.set_dec(value);
    return is;
}

int main()
{
    long long a = 4;
    vector vec(a);
    interface inter(a);
    std::cout << inter[0].get_bin() << std::endl;
    std::cout << inter[0].get_dec() << std::endl;
    std::cout << inter[0].get_len() << std::endl;
    //std::cout << inter[0];
    inter.push_back(6);
    std::cout << inter << std::endl;
    std::cout << inter.get_size() << std::endl;
    inter[0] = inter[1].sub_vector(0, 3);
    inter.ivc.reset_iter(&inter[0]);
    std::cout << inter[0] << std::endl;
    inter[0] = inter[0].concat(inter[1]);
    std::cout << inter[0] << std::endl;
    inter.~interface();

    return 0;
}