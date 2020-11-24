#include <iostream>

class multiset
{
    long long value;

public:
    multiset *next;
    multiset(long long val = 0)
    {
        value = val;
        next = nullptr;
    }
    multiset(const multiset &set) //хуета, переделывай
    {
        value = set.value;
        while (set.next)
        {
            next->value = set.next->value;
            next = set.next;
            next = next->next;
        }
    }
    ~multiset()
    {
        if (next)
        {
            delete next;
            next = nullptr;
        }
    }
    void push_back(long long val)
    {
        multiset *semi = new multiset(val);
        this->next = semi;
    };
    bool is(long long val)
    {
        if (value == val)
            return true;
        while (next)
        {
            if (next->value == val)
                return true;
            next = next->next;
        }
        return false;
    }
    long long &get_val()
    {
        return value;
    }
    multiset &operator=(multiset &set)
    {
        value = set.value;
        while (set.next)
        {
            next->value = set.next->value;
            next = set.next;
            next = next->next;
        }
    }
};

class iterator
{
public:
    multiset *begin, *end;

public:
    iterator() = delete;
    iterator(multiset &set)
    {
        begin = &set;
        while (set.next != nullptr)
        {
            set = *set.next;
        }
        end = &set;
    }
    void reset_iter(multiset *set)
    {
        begin = set;
        while (set->next)
        {
            set = set->next;
        }
        end = set;
    }
    multiset *operator++()
    {
        if (begin == nullptr)
            return nullptr;
        if (begin == end)
            return end;
        begin = begin->next;
        return begin;
    }
    multiset *operator+(size_t inc)
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
    size_t size()
    {
        return begin - end;
    }
    const size_t size() const
    {
        return begin - end;
    }
};

class interface
{
    multiset set;

public:
    iterator iter;
    multiset &get_set()
    {
        return set;
    }

    iterator &get_iter()
    {
        return iter;
    }

    interface(long long value = 0) : set(value), iter(set) {}
    interface(const interface &inter) = delete;
    multiset &operator[](size_t inc)
    {
        return *iter.operator+(inc);
    }

    void Add_first_missing()
    {
        for (size_t i = 0; !set.is(i); ++i)
            set.push_back(i);
        iter.reset_iter(&set);
    }

    bool operator==(interface &inter)
    {
        if (iter.size() != inter.iter.size())
            return false;
        for (size_t i = 0; i < iter.size(); ++i, iter.begin++, inter.iter.begin++)
        {
            if (iter.begin->get_val() != inter.iter.begin->get_val())
                return false;
        }
        iter.reset_iter(set.next);
        inter.iter.reset_iter(inter.set.next);
        return true;
    }

    multiset &Union(interface &inter)
    {
        multiset Res(set);
        for (int i = 0; i < inter.iter.size(); i++, inter.iter.operator+(i))
            Res.push_back(inter.iter.begin->get_val());
        return Res;
    }

    multiset &intersection(interface &inter)
    {
        multiset res;
        for (size_t i = 0; i < iter.size(); ++i, inter.iter.operator+(i))
        {
            if (iter.begin->is(inter.iter.begin->get_val()) && res.is(inter.iter.begin->get_val()))
                res.push_back(inter.iter.begin->get_val());
        }
        return res;
    }
    multiset &diff(interface &inter)
    {
        multiset res;
        for (size_t i = 0; i < iter.size(); ++i, inter.iter.operator+(i))
        {
            if (!iter.begin->is(inter.iter.begin->get_val()) && !res.is(inter.iter.begin->get_val()))
                res.push_back(inter.iter.begin->get_val());
        }
        return res;
    }
    multiset &symm(interface &inter)
    {
        multiset res = diff(inter);
        multiset semi = inter.diff(*this);
        iter.reset_iter(&semi);

        for (size_t i = 0; i < iter.size(); ++i, iter.operator+(i))
        {
            res.push_back(iter.begin->get_val());
        }

        return res;
    }
};

std::ostream &operator<<(std::ostream &os, interface &inter)
{
    for (size_t i = 0; i < inter.iter.size(); ++i, inter.iter.operator+(i))
    {
        os << "//" << inter.iter.begin->get_val() << "//";
    }
    inter.iter.reset_iter(&inter.get_set());
    os << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, interface &inter)
{
    size_t len = is.tellg();
    char *str = new char[len];
    for (size_t i = 0; i < len; ++i)
    {
        str[i] = 0;
    }
    str[len - 1] = '\0';
    is.seekg(0);
    if (is.read(&str[0], len))
    {
        long long *values;
        size_t delim = 0;
        bool start_end = false;
        if (str[0] && str[1] && str[len - 2] && str[len - 1] == '/')
            start_end = true;
        if (start_end == true)
            for (size_t i = 0; i < len; ++i)
            {
                if (str[i] == '/' && isdigit(str[i - 1]))
                    delim++;
            }
        values = new long long[delim + 1];
        for (size_t i = 0; i < delim + 1; ++i)
        {
            values[i] = 0;
        }
        for (size_t i = 0, j = 0; i < len; ++i)
        {
            if (isdigit(str[i]))
                values[j] = values[j] * 10 + (str[i] - 48);
            if (isdigit(str[i - 1]) && !isdigit(str[i]))
                j++;
        }
        for (size_t i = 0; i < delim + 1; ++i)
            inter.get_set().push_back(values[i]);
        return is;
    }
    else
    {
        std::cout << "Cant read input" << std::endl;
        return is;
    }

    //дописать парсер
}

int main()
{

    return 0;
}