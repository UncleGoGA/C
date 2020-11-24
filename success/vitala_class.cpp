#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>

class Student
{
    char fio[31];
    unsigned short group;
    unsigned short results[5];

public:
    Student()
    {

        memset(fio, 0, 30);
        this->fio[0] = 'a';
        group = 1;
        for (size_t i = 0; i < 5; ++i)
        {
            results[i] = 0;
        }
    }
    Student(const char *fio, const unsigned short group, const unsigned short *results)
    {
        strcpy(this->fio, fio);
        this->group = group;
        for (size_t i = 0; i < 5; ++i)
        {
            this->results[i] = results[i];
        }
    }
    Student(Student &student)
    {
        strcpy(fio, student.fio);
        group = student.group;
        for (size_t i = 0; i < 5; ++i)
        {
            results[i] = student.results[i];
        }
    }
    ~Student(){}
    void print_fio()
    {
        //printf("%s", fio);
        std::cout << fio << std::endl;
    }
    char *get_fio()
    {
        return fio;
    }
    void set_fio(const char *fio)
    {
        strcpy(this->fio, fio);
    }

    void print_group()
    {
        //printf("%d", group);
        std::cout << group << std::endl;
    }
    unsigned short get_group()
    {
        return group;
    }
    void set_group(const int group)
    {
        this->group = group;
    }

    void print_results()
    {
        //printf("%d %d %d %d %d", results[0], results[1], results[2], results[3], results[4]);
        std::cout << results[0] << " " << results[1] << " " << results[2] << " " << results[3] << " " << results[4] << std::endl;
    }
    unsigned short *get_result()
    {
        return results;
    }
    unsigned short get_result_with_pos(size_t pos)
    {
        return results[pos];
    }
    void set_results(const unsigned short *results)
    {
        for (size_t i = 0; i < 5; ++i)
        {
            this->results[i] = results[i];
        }
    }
    void set_results(const unsigned short res, size_t pos)
    {
        this->results[pos] = res;
    }

    void show()
    {
        std::cout << fio << std::endl;
        std::cout << group << std::endl;
        std::cout << results[0] << " " << results[1] << " " << results[2] << " " << results[3] << " " << results[4] << std::endl;
    }
};

class Studentview
{
    Student *student;
    size_t size;
    size_t out_size;
    inline char *substr(char *str, size_t pos, size_t n)
    {
        char *newstr = new char[n];
        for (size_t i = pos, k = 0; k < n; ++k, ++i)
        {
            newstr[k] = str[i];
        }
        return newstr;
    }
    inline int convert(int convertable)
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
    // template <typename T>
    void siftDown(Student *numbers, int root, int bottom)
    {
        int maxChild; // ������ ������������� �������
        int done = 0; // ���� ����, ��� ���� ������������
        // ���� �� ����� �� ���������� ����
        while ((root * 2 <= bottom) && (!done))
        {
            if (root * 2 == bottom)  // ���� �� � ��������� ����,
                maxChild = root * 2; // ���������� ����� �������
                                     // ����� ���������� ������� ������� �� ����
            else if (numbers[root * 2].get_group() > numbers[root * 2 + 1].get_group())
                maxChild = root * 2;
            else
                maxChild = root * 2 + 1;
            // ���� ������� ������� ������ ������������� �������
            if (numbers[root].get_group() < numbers[maxChild].get_group())
            {
                Student temp = numbers[root]; // ������ �� �������
                numbers[root] = numbers[maxChild];
                numbers[maxChild] = temp;
                root = maxChild;
            }
            else          // �����
                done = 1; // �������� ������������
        }
    }

    // template <typename T>
    void heapSort(Student *numbers, int array_size)
    {
        if(array_size == 2){
            if(numbers[0].get_group() < numbers[1].get_group()){
            Student temp = numbers[0];
            numbers[0] = numbers[1];
            numbers[1] = temp;
        }
        }
        else{
        for (int i = (array_size / 2) - 1; i >= 0; i--)
            siftDown(numbers, i, array_size - 1);

        for (int i = array_size - 1; i >= 1; i--)
        {
            Student temp = numbers[0];
            numbers[0] = numbers[i];
            numbers[i] = temp;
            siftDown(numbers, 0, i - 1);
        }
        }
    }
    size_t whatsize(char *str)
    {
        char *start = str;
        while (*str)
        {
            ++str;
        }
        return str - start;
    }
    size_t how_many_digits(int num)
    {
        size_t count = 0;
        while (num > 0)
        {
            count++;
            num /= 10;
        }
        count--;
        return count;
    }
    char *str_view;

public:
    Studentview()
    {
        size = 0;
        student = new Student[size];
    }
    Studentview(size_t size)
    {
        this->size = size;
        student = new Student[size];
    }
    Studentview(const Studentview &studentview)
    {
        size = studentview.size;
        student = new Student[size];
    }
    ~Studentview()
    {
        delete[] student;
    }
    Student operator[](size_t iterator)
    {
        return student[iterator];
    }
    void sort()
    {
        heapSort(student, size);
    }
    void find()
    {
        bool check = false; //indicate us that we have any student with 2 in res
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < 5; ++j)
            {
                if (student[i].get_result_with_pos(j) == 2)
                {
                    check = true;
                }
            }
        }
        if (check == true)
        {
            for (size_t i = 0; i < size; ++i)
            {
                for (size_t j = 0; j < 5; ++j)
                {
                    if (student[i].get_result_with_pos(j) == 2)
                    {
                        std::cout << "Student with 2 in results" << std::endl;
                        std::cout << student[i].get_fio() << std::endl;
                        std::cout << student[i].get_group() << std::endl;
                    }
                }
            }
        }
        else
        {
            std::cout << "No one have 2 in results" << std::endl;
        }
    }

    void show_whole()
    {
        for (size_t i = 0; i < size; ++i)
        {
            student[i].show();
        }
    }

    void resize(size_t new_size)
    {
        Student *new_student = new Student[new_size];
        for (size_t i = 0; i < this->size; ++i)
        {
            new_student[i] = this->student[i];
        }
        size = new_size;
        delete[] student;
        student = new_student;
    }

    void enter(char *argv[])
    {
        FILE *file = fopen(argv[1], "r+b");
        if (file == 0)
        {
            exit(0);
        }
        size_t size = 0;
        size_t real_size = 0;
        char *semi_str;
        char *real_str; //because i dont wanna work with binaries
        int ch;
        while (!feof(file))
        {
            ch = fgetc(file);
            ++size;
        }
        out_size = size;
        real_size = size / sizeof(char);
        semi_str = new char[size];
        real_str = new char[real_size];
        char *word;

        memset(semi_str, 0, size);
        memset(real_str, 0, real_size);

        fseek(file, 0, SEEK_SET); //set pos at start in file

        for (size_t i = 0; !feof(file); ++i)
        {
            ch = fgetc(file);
            semi_str[i] = (char)ch;
        }
        fclose(file);
        //might be use strtol&strtoul but it cant analyze special symbols etc:' ', ',' and others.
        for (size_t i = 0, j = 0, k = 0; i < size; ++i, ++k)
        {
            if (k == 7)
            {
                word = substr(semi_str, i - k, k + 1);
                ch = atoi(substr(semi_str, i - k, k + 1));
                k = -1;
                real_str[j] = convert(ch);
                ++j;
                delete[] word;
            }
        }
        str_view = real_str;
        delete[] semi_str;
        semi_str = nullptr; //?
        size = 0;
        for (size_t i = 0; i < real_size; ++i)
        {
            if (real_str[i] == '\n')
            {
                size++;
            }
        }
        resize(size);
        //fio(31)' 'group' 'res[0]' 'res[1]' 'res[2]' 'res[3]' 'res[4]' ''\n'
        for (size_t i = 0, j = 0, k = 0, n = 0; i < real_size; ++i, ++j)
        {
            //i - iterator for whole str, j - iterator for current word, k - iterator for spaces, n - iterator of student arr
            if (real_str[i] == '\n')
            {
                k = 0;
                j = 0;
                n++;
            }
            if (real_str[i] == ' ')
            {
                k++;
            }
            if (k == 1)
            {
                word = substr(real_str, i - j, j + 4);
                if (word[0] == '\n')
                {
                    student[n].set_fio(substr(word, 1, j + 3));
                }
                else
                {
                    student[n].set_fio(word);
                }
                i += 4;
                j = 0;
                k++;
            }
            if (k == 4)
            {
                word = substr(real_str, i - j, j);
                student[n].set_group(atoi(substr(word, 0, j)));
                j = 0;
                i -= 2;
                k++;
            }
            if (k == 6)
            {
                word = substr(real_str, i - j, j);
                student[n].set_results(atoi(substr(word, 0, j)), 0);
                j = 0;
                k++;
            }
            if (k == 8)
            {
                word = substr(real_str, i - j, j);
                student[n].set_results(atoi(substr(word, 0, j)), 1);
                j = 0;
                k++;
            }
            if (k == 10)
            {
                word = substr(real_str, i - j, j);
                student[n].set_results(atoi(substr(word, 0, j)), 2);
                j = 0;
                k++;
            }
            if (k == 12)
            {
                word = substr(real_str, i - j, j);
                student[n].set_results(atoi(substr(word, 0, j)), 3);
                j = 0;
                k++;
            }
            if (k == 14)
            {
                word = substr(real_str, i - j, j);
                student[n].set_results(atoi(substr(word, 0, j)), 4);
                j = -1;
                k++;
            }
        }
    }

    void write()
    {
        // char* str = new char[out_size];
        // char* fio;
        // unsigned short group;
        // unsigned short* res;
        // memset(str, '\0', out_size);
        //fio(31)' 'group' 'res[0]' 'res[1]' 'res[2]' 'res[3]' 'res[4]' ''\n'
        std::ofstream tab("out.bin", std::ios::binary);
        tab.write(str_view, out_size);
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid params" << std::endl;
        exit(0);
    }

    Studentview stud;
    stud.enter(argv);
    stud.show_whole();
    stud.sort();
    stud.show_whole();
    stud.write();
    stud.find();
    return 0;
}