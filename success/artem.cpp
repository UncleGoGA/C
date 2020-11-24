#include <iostream>
#include <string>
//слова оканчивающиеся на ый, заменить на очень
int count(char* str){
    char* p = str;
    while(*str){
        str++;
    }
    return str - p;
}

void fvii(std::string& str){
    char word[] = "очень";
    int size = str.size();
    for(size_t i = 0; str[i] != '\0' && i < size; ++i){
        if(str[i] == ' ' || str[i] == ','){
            if(str[i - 1] == 'й' && str[i - 2] == 'ы'){
                i--;
                while(str[i] != ' '){
                    i--;
                    if(str[i] == ' '){
                        break;
                    }
                }
                i++;
                for(size_t j = 0; j < 5; ++j, ++i){
                    str[i] = word[j]; 
                }
            }
        }
    }
}

int main(){
    setlocale(LC_ALL, "ru");
    //я жирный толстый хороший человек
    std::string str = "i`m lazy lazy good person";
    fvii(str);

    return 0;
}