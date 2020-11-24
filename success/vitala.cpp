#include <iostream>
#include <vector>
#include <chrono>
#include <string.h>
#include <math.h>

/*��������� ������������ �������� ��� ������ � �������
� ������� �� ARR_SIZE ��������� ���� T ��������� ����� m ����. ����������������� ����� ��������
��� ������� �������: �������� ����� ��� ����������� ���������� ��������, � ����� ���������������� �����
��� ������ ����� ����� ARR_SIZE = 10000, T = short*/

#pragma warning(disable:4996)

#define ARR_SIZE 400
size_t CUR_POS = 1;

FILE* outfile;//because it easier to use it in funcions, i know that global vars are evil, btw.

void is_opened_file(char* argv[]) {//checking that file is exist
    FILE* f;
    f = fopen(argv[1], "rt");
    if (!f) {
        printf("There are no such file");
        exit(0);
    }
    fclose(f);
}

std::vector<std::string> file_to_string(char* argv[])
{
    //includes argv[], transmitted file to string

    std::vector<std::string> true_string;

    char* word = new char[17];
    FILE* dile;
    dile = fopen(argv[1], "r");
    for (size_t i = 0; !feof(dile); i++) {
        fread(word, 1, 8, dile);
        true_string.push_back(word);
    }

    fclose(dile);
    return true_string;

}

std::vector<int> file_to_vector_int(char* argv[]) { //we can use this funcion to scan short numbers and normal int, btw.
    std::vector<int> vec;
    FILE* dile;
    int value = 0;
    dile = fopen(argv[1], "r");

    while (fscanf(dile, "%d", &value) != EOF) {
        vec.push_back(value);
    }


    fclose(dile);
    return vec;
}

std::vector<double> file_to_vector_double(char* argv[]) {
    std::vector<double> vector;

    double value = 0;
    FILE* dile;
    dile = fopen(argv[1], "r");
    while (fscanf(dile, "%f", &value) != EOF) {
        vector.push_back(value);
    }

    fclose(dile);
    return vector;
}

void create_avg(std::vector<double> elapsed_time, std::vector<double>& avg) {
    long double average = 0;
    for (size_t i = 0; i < static_cast<size_t>(elapsed_time.size()); i++) {
        average += elapsed_time[i];
    }
    average /= elapsed_time.size();
    avg.push_back(average);
}

long long aprox_to_digits(double value, double digits){
    long long semi = value * pow(10, digits);
    double semi_double = semi / pow(10, digits);
    std::cout << "semi_double - "<<semi_double << std::endl;
    std::cout << "semi - " << semi << std::endl;
    return semi;
}

void info(std::vector<double> elapsed_times){
    for(size_t i = 0, j = (elapsed_times.size() / 2) + 1; j < elapsed_times.size(); ++i, ++j){
        // std::cout << aprox_to_digits(elapsed_times[j], 6) << " - interpol" << std::endl;
        // std::cout << aprox_to_digits(elapsed_times[i], 6) <<  " - linear" <<std::endl;
        if(aprox_to_digits(elapsed_times[i], 6) < aprox_to_digits(elapsed_times[j], 6)){
            printf("Interpol faster linear at %d\n", elapsed_times.at(i));
            break;
        }
        
    }
}

void info(bool flag, std::vector<double> elapsed_times) {
    //linear - false
    //interpol - true
    double average = 0;
    for (size_t i = 0; i < static_cast<size_t>(elapsed_times.size()); i++) {
        average += elapsed_times[i];
    }
    average /= elapsed_times.size();
    if (flag == false) {
        fprintf(outfile, "linear time - %lf\n", average);
    }
    else {
        fprintf(outfile, "interpol time - %lf\n", average);
    }
}

void aprox(double t1/*linear*/, double t2/*interpol*/) {
    if ((t1 - t2) < 0) {
        fprintf(outfile, "linear faster than interpol - %lf\n", (t1 - t2));
    }
    else if ((t1 - t2) > 0) {
        fprintf(outfile, "interpol faster than linear - %lf\n", (t1 - t2));
    }
    else {
        fprintf(outfile, "linear and interpol are equals for time");
    }
}

int min(int x, int y) { return (x <= y) ? x : y; }

template<typename T>
void merge(std::vector<T>& arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    T* L = new T[n1];
    T* R = new T[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] R;
    delete[] L;
    R = nullptr;
    L = nullptr;
}

template<typename T>
void mergeSort(std::vector<T>& arr)
{
    int curr_size;  // For current size of subarrays to be merged 
                    // curr_size varies from 1 to n/2 
    int left_start; // For picking starting index of left subarray 
                    // to be merged 

    // Merge subarrays in bottom up manner.  First merge subarrays of 
    // size 1 to create sorted subarrays of size 2, then merge subarrays 
    // of size 2 to create sorted subarrays of size 4, and so on. 
    for (curr_size = 1; curr_size <= arr.size() - 1; curr_size = 2 * curr_size)
    {
        // Pick starting point of different subarrays of current size 
        for (left_start = 0; left_start < arr.size() - 1; left_start += 2 * curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting  
            // point of right 
            int mid = min(left_start + curr_size - 1, arr.size() - 1);

            int right_end = min(left_start + 2 * curr_size - 1, arr.size() - 1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end] 
            merge(arr, left_start, mid, right_end);
        }
    }
}

template<typename T>
int find(std::vector<T> vector, std::vector<T> value) { //la costil
    int low = 0, high = vector.size() - 1, middle;
    while (true) {
        middle = (high + low) / 2;
        if (low > high) {
            return -1;
        }
        if (vector[high] == value[CUR_POS - 1]) {
            return high;
        }
        if (vector[low] == value[CUR_POS - 1]) {
            return low;
        }
        if (vector[middle] == value[CUR_POS - 1]) {
            return middle;
        }
        if (vector[middle] > value[CUR_POS - 1]) {
            high = middle - 1;
        }
        if (vector[middle] < value[CUR_POS - 1]) {
            low = middle + 1;
        }
    }
}

template<typename T>
int interpol(std::vector<T> vector, std::vector<T> value, std::vector<int> vector_int, int value_int) {
    //if (find(vector, value) == -1) {
    //    return 0;
    //}
    if (vector.size() == 0) {
        return 0;
    }
    //std::vector<int> vector_int; 
    //for (size_t i = 0; i < vector.size(); i++) {
    //    vector_int.push_back(i);
    //}
    size_t left = 0;
    size_t right = vector.size() - 1;
    size_t pos = 0;
    /*for (found = false; (vector_int[left] < value_int) && (vector_int[right] > value_int) && !found;)*/
    while ((vector_int[left] < value_int) && (vector_int[right] > value_int)) {
        pos = left + ((value_int - vector_int[left]) * (right - left)) / (vector_int[right] - vector_int[left]); //maybe used linked_list
        if (vector_int[pos] < value_int) {
            left = pos + 1;
        }
        else if (vector_int[pos] > value_int)
        {
            right = pos - 1;
        }
        else {
            return pos;
        }
    }
    return 0;
}

template<typename T>
bool linear_find(std::vector<T> vector, T value) {//--currently worked
    size_t size = vector.size();
    for (size_t i = 0; i < size; i++) {
        if (vector[i] == value) {
            return true;
        }
    }
    return false;
}

void alg(char* argv[]) {
    std::vector<double> elapsed_times;
    std::vector<double> avg;

    if (strcmp(argv[2], "char") == 0) {
        double t1, t2;
        std::vector<double> elapsed_times;
        std::vector<std::string> array = file_to_string(argv);
        std::vector<std::string> copy = array;
        std::vector<std::string> value = file_to_string(argv);
        double elapsed_seconds;
        bool whatmethod = false; //false - linear, true - interpol
        // mergeSort(copy);
        
        while (CUR_POS < ARR_SIZE - 1) {
            auto start = std::chrono::steady_clock::now();
            linear_find<std::string>(copy, value[CUR_POS]);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }
        
        // create_avg(elapsed_times, avg);
        // t1 = avg[0];
        // info(whatmethod, avg);
        // avg.clear();
        // elapsed_times.clear();
        CUR_POS = 1;
        copy = array;
        // whatmethod = true; //false - linear, true - interpol
        std::vector<int> vector_int;
        for (size_t i = 0; i < ARR_SIZE; ++i) {
            vector_int.push_back(i);
        }
        int value_int;
        bool started = false;
        auto start = std::chrono::steady_clock::now();
        mergeSort<std::string>(copy);
        while (CUR_POS < ARR_SIZE - 1) {
            if (started == true)
            auto start = std::chrono::steady_clock::now();
            value_int = find(array, value);
            interpol<std::string>(copy, value, vector_int, value_int);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            started = true;
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }

        info(elapsed_times);
        // create_avg(elapsed_times, avg);
        // t2 = avg[0];
        // info(whatmethod, avg);
        // aprox(t1, t2);
    }

    else if (strcmp(argv[2], "double") == 0) {
        double t1, t2;
        std::vector<double> elapsed_times;
        std::vector<double> array = file_to_vector_double(argv);
        std::vector<double> copy = array;
        std::vector<double> value = file_to_vector_double(argv);
        double elapsed_seconds;
        //bool whatmethod = false; //false - linear, true - interpol
        //mergeSort(copy);
        
        while (CUR_POS < ARR_SIZE - 1) {
            auto start = std::chrono::steady_clock::now();
            linear_find<double>(copy, value[CUR_POS]);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }
        
        // create_avg(elapsed_times, avg);
        // t1 = avg[0];
        // info(whatmethod, avg);
        // avg.clear();
        // elapsed_times.clear();
        CUR_POS = 1;
        copy = array;
        // whatmethod = true; //false - linear, true - interpol
        std::vector<int> vector_int;
        for (size_t i = 0; i < ARR_SIZE; ++i) {
            vector_int.push_back(i);
        }
        int value_int;
        bool started = false;
        auto start = std::chrono::steady_clock::now();
        mergeSort<double>(copy);
        while (CUR_POS < ARR_SIZE - 1) {
            if (started == true)
            auto start = std::chrono::steady_clock::now();
            value_int = find(array, value);
            interpol<double>(copy, value, vector_int, value_int);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            started = true;
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }

        info(elapsed_times);
        // create_avg(elapsed_times, avg);
        // t2 = avg[0];
        // info(whatmethod, avg);
        // aprox(t1, t2);
    }

    else if (strcmp(argv[2], "int") == 0) {
        double t1, t2;
        std::vector<double> elapsed_times;
        std::vector<int> array = file_to_vector_int(argv);
        std::vector<int> copy = array;
        std::vector<int> value = file_to_vector_int(argv);
        double elapsed_seconds;
        // bool whatmethod = false; //false - linear, true - interpol
        // mergeSort(copy);
        
        while (CUR_POS < ARR_SIZE - 1) {
            auto start = std::chrono::steady_clock::now();
            linear_find<int>(copy, value[CUR_POS]);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }
        
        // create_avg(elapsed_times, avg);
        // t1 = avg[0];
        // info(whatmethod, avg);
        // avg.clear();
        // elapsed_times.clear();
        CUR_POS = 1;
        copy = array;
        // whatmethod = true; //false - linear, true - interpol
        std::vector<int> vector_int;
        for (size_t i = 0; i < ARR_SIZE; ++i) {
            vector_int.push_back(i);
        }
        int value_int;
        bool started = false;
        auto start = std::chrono::steady_clock::now();
        mergeSort<int>(copy);
        while (CUR_POS < ARR_SIZE - 1) {
            if (started == true)
            auto start = std::chrono::steady_clock::now();
            value_int = find(array, value);
            interpol<int>(copy, value, vector_int, value_int);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            started = true;
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }
        info(elapsed_times);
        // create_avg(elapsed_times, avg);
        // t2 = avg[0];
        // info(whatmethod, avg);
        // aprox(t1, t2);
    }

    else if (strcmp(argv[2], "short") == 0) { //i dont even know what am i doing...
        double t1, t2;
        std::vector<double> elapsed_times;
        std::vector<int> array = file_to_vector_int(argv);
        std::vector<int> copy = array;
        std::vector<int> value = file_to_vector_int(argv);
        double elapsed_seconds;
        // bool whatmethod = false; //false - linear, true - interpol
        // mergeSort(copy);
        
        while (CUR_POS < ARR_SIZE - 1) {
            auto start = std::chrono::steady_clock::now();
            linear_find<int>(copy, value[CUR_POS]);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }
        
        // create_avg(elapsed_times, avg);
        // t1 = avg[0];
        // info(whatmethod, avg);
        // avg.clear();
        // elapsed_times.clear();
        CUR_POS = 1;
        copy = array;
        // whatmethod = true; //false - linear, true - interpol
        std::vector<int> vector_int;
        for (size_t i = 0; i < ARR_SIZE; ++i) {
            vector_int.push_back(i);
        }
        int value_int;
        bool started = false;
        auto start = std::chrono::steady_clock::now();
        mergeSort<int>(copy);
        while (CUR_POS < ARR_SIZE - 1) {
            if(started == true);
            auto start = std::chrono::steady_clock::now();
            value_int = find(array, value);
            interpol<int>(copy, value, vector_int, value_int);
            std::cout << "CUR_POS: " << CUR_POS - 1 << std::endl;
            CUR_POS++;
            auto end = std::chrono::steady_clock::now();
            started = true;
            elapsed_seconds = std::chrono::duration<double>(end - start).count();
            elapsed_times.push_back(elapsed_seconds);
        }
        
        info(elapsed_times);
        // create_avg(elapsed_times, avg);
        // t2 = avg[0];
        // info(whatmethod, avg);
        // aprox(t1, t2);
    }

    else {

        std::cout << "Unsupporter value type" << std::endl;

    }
}

int main(int argc, char* argv[]) {
    // argv[0] - program name
    // argv[1] - file name
    // argv[2] - value type in file
    //we`ve got funcions to work with std::string, int, short, double
    if (argc != 3) {
        std::cout << "Cant recognize input info, try again" << std::endl;
        return 0;
    }

    outfile = fopen("Elapsed_times.txt", "w");
    alg(argv);
    fclose(outfile);

    return 0;
}