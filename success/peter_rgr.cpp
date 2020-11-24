#include <iostream>
#include <vector>
#include <string>
//just for simple use

void is_opened(char* argv[]) {
	FILE* check;
	check = fopen(argv[1], "r");
	if (!check) {
		std::cout << "No availible file" << std::endl;
		fclose(check);
		exit(0);
	}
	else {
		std::cout << "File in progress" << std::endl;
		fclose(check);
	}
}

std::string file_to_string (char* argv[])
{
    //includes argv[], transmitted file to string
    std::string true_string;
	FILE* fl;
	fl = fopen(argv[1], "r");
	int ch;
	while(!feof(fl)){
		ch = fgetc(fl);
        true_string.push_back((char)ch);
	}
	fclose(fl);

    true_string.pop_back();

	return true_string; 
}

std::vector<std::string> reflex(std::string string){
    std::vector<std::string> new_string;
    std::string word;
    string.shrink_to_fit();
    for(size_t i = 0; i < string.size(); ++i){
        if(string.at(i) == '\n'){
            new_string.push_back(word);
            word.clear();
            ++i;
            if(i >= string.size()){
                break;
            }
        }
        word.push_back(string.at(i));
    }
    return new_string;
}

void print_string(std::vector<std::string> string){
    for(size_t i = 0; i < string.size(); ++i){
        std::cout << string.at(i) << ' ' << std::endl;
    }
}

void deal(char* argv[]){
    is_opened(argv);
    std::string whole_string = file_to_string(argv);
    std::vector<std::string> buf_string = reflex(whole_string);
    std::string current_rule; //here we include current markov`s rule
    std::vector<std::string> buf_rule;
    std::string data_string = buf_string[buf_string.size() - 1];
    std::vector<std::string> buf_data_string;
    buf_string.pop_back();

    for(size_t i = 0, k = 0; i < data_string.size(); ++i, ++k){
        if(data_string.at(i) == ' '){
            buf_data_string.push_back(data_string.substr(i - k, k));
            k = -1;
        }
    }
  
    for(size_t i = 0, n = 0; i < buf_string.size(); ++i){
        current_rule = buf_string.at(i);
        for(size_t j = 0, k = 0; j < data_string.size(); ++j, ++k){
            if(current_rule[j] == ' '){
                buf_rule.push_back(current_rule.substr(j - k, k));
                j += 3;
                k = -1;
            }
        }
        for(size_t z = 0; z < buf_data_string.size(); ++z){
            if(buf_data_string.at(z) == buf_rule.at(0)){
                buf_data_string.at(z) = buf_rule.at(1);
            }
        }
        buf_rule.clear();
    }

    print_string(buf_data_string);
}

int main(int argc, char* argv[]){

    if(argc != 2){
        std::cout << "Invalid params, try again" << std::endl;
        return 0;
    }

    deal(argv);

    return 0;
}