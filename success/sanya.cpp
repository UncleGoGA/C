#include <iostream>
#include <vector>

template<typename T>
int count(T* str){
    T* p = str;
    while(*str){
        str++;
    }
    return str - p;
}

template<typename T>
void siftDown(T* numbers, int root, int bottom)
{
    int maxChild; // ������ ������������� �������
    int done = 0; // ���� ����, ��� ���� ������������
    // ���� �� ����� �� ���������� ����
    while ((root * 2 <= bottom) && (!done))
    {
        if (root * 2 == bottom)    // ���� �� � ��������� ����,
            maxChild = root * 2;    // ���������� ����� �������
          // ����� ���������� ������� ������� �� ����
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        // ���� ������� ������� ������ ������������� �������
        if (numbers[root] < numbers[maxChild])
        {
            T temp = numbers[root]; // ������ �� �������
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else // �����
            done = 1; // �������� ������������
    }
}

template<typename T>
void heapSort(T* numbers, int array_size)
{

    for (int i = (array_size / 2) - 1; i >= 0; i--)
        siftDown(numbers, i, array_size - 1);

    for (int i = array_size - 1; i >= 1; i--)
    {
        T temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i - 1);
    }
}

template<typename T>
bool alg(T* numbers, int size){
    size_t fst_check = 0;
    size_t snd_check = 0;
    bool flag = false;
    bool flag_bouser = false;
    heapSort(numbers, size);
    for(size_t i = 0; i < size; ++i){
        if(flag == false){
            if(numbers[i] == numbers[i + 1]){
                fst_check++;
            }
            if(i != 0 && numbers[i] != numbers[i + 1] && numbers[i] == numbers[i - 1]){
                fst_check++;
                flag = true;
            }
        }
        if(flag == true){
                if(numbers[i] == numbers[i + 1]){
                snd_check++;
            }
            if(i != 0 && numbers[i] != numbers[i + 1] && numbers[i] == numbers[i - 1]){
                snd_check++;
                flag = false;
                flag_bouser = true;
            }
        }
        if(flag_bouser == true){
            flag_bouser = false;
            if(fst_check != snd_check){
                return false;
            }
        }
    }
return true;
}

int main(){

    int* arr = new int[10];
    for(size_t i = 0; i < 10; ++i){
        arr[i] = i;
    }
    arr[1] = 3;
    arr[4] = 3;
    arr[7] = 9;
    arr[5] = 3;

    alg(arr, 10);

    return 0;
}