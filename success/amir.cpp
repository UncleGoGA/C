#include <iostream>

bool is_open(char* argv[]){
    FILE* fp = fopen(argv[1], "r");

    if(!fp){
        fclose(fp);
        return false; 
    }
    fclose(fp);

    return true;
}

size_t size(char* str){
    char* p = str;

    while(*str){++str;};

    return str - p;
}

int my_strcmp(char* str, char* comp){
    size_t str_size = size(str);
    size_t comp_size = size(comp);

    if(str_size != comp_size){
        return 1;
    }

    for(size_t i = 0; i < str_size; ++i){
        if(str[i] != comp[i]){
            return -1;
        }
    }

    return 0;
}

char* file_to_str(char* argv[]){
    FILE* fp = fopen(argv[1], "r");
    int ch;
    size_t size = 0;

    while(!feof(fp)){
        ch = fgetc(fp);
        ++size;
    }

    char* file = new char[size];
    fclose(fp);
    fp = fopen(argv[1], "r");

    for(size_t i = 0; i < size; ++i){
        ch = fgetc(fp);
        file[i] = (char)ch;
    }

    return file;
}

void print(char* str){
    printf("%s", str);
}

char* substr(char* str, size_t pos, size_t n){
    char* newstr = new char[n];

    for(size_t i = pos, k = 0; k < n; ++k, ++i){
        newstr[k] = str[i];
    }

    return newstr;
}

void alg(char* argv[]){
    if(is_open(argv) == false){
        printf("Cant open file");
        exit(1);
    }

    char* file = file_to_str(argv);
    char* word = argv[2];
    char* semi_word;

    for(size_t i = 0, j = 0, k = 0; i < size(file); ++i, ++j, ++k){ //i - is iterator for whole str, j - is iterator for word, k - is iterator for current str
        if(file[i] == '\n'){
            j = -1;
            k = -1;
        }
        if(file[i] == ' '){
            semi_word = new char[j];
            semi_word = substr(file, i - j, j);
            j = -1;
            if(my_strcmp(word, semi_word) == 0){
                size_t z = k;
                // for(;file[z] != '\n'; ++z)
                // {
                //     printf("%c", file[z]);
                // }
                while(file[z + 1] != '\n'){
                    ++z;
                }
                printf("\n");
                print(substr(file,i - k, k + z - 3));
            }
            delete[] semi_word;
        }
    }    
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid params");
        return 0;
    }

    alg(argv);

    return 0;
}