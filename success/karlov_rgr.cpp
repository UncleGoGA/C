#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "bintree.h"

#pragma warning(disable:4996)

/*Написать программу, которая принимает в качестве аргументов число n и имя файла f,
содержащего разделённые пробелами слова длины n, и определяет, можно ли сформировать
матрицу размера n × n, в которой в каждой строке, а также в первом и последнем столбцах
стоят слова из f. Если возможно, то напечатать какую-нибудь матрицу.*/


void is_opened(char* argv[]) {
	FILE* check;
	check = fopen(argv[2], "r");
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

void print(std::vector<std::string> matrix){
	std::cout << "Current matrix below: " << std::endl;
	for(size_t i = 0; i < matrix.size(); ++i){
		std::cout << matrix[i] << std::endl;
	}
}

std::vector<std::string> file_to_vector (char* argv[])
{
    //includes argv[], transmitted file to string
	size_t word_size = *argv[1] - 48;
	size_t size = 0;
    std::vector<std::string> matrix;
	FILE* fl;
	fl = fopen(argv[2], "r");
	int ch;
	while(!feof(fl)){
		ch = fgetc(fl);
		size++;
	}
	fclose(fl);
	char* string = new char[size]; //what a size? - Thats good question, i dont wanna write another checker that we`ve got n words in file and we just read n words from it :)
	char* word = new char[word_size];
	FILE* file;
	file = fopen(argv[2], "r");
	fgets(string, (size), file);
	fclose(file);
	for(size_t i = 0, j = 0; i < size; i++, j++){
		if(string[i] != ' '){
			word[j] = string[i];
		}
		else{
			j = -1;
			matrix.push_back(word);
		}
	}
	delete[] string;
	delete[] word;
	return matrix; 
}

bool check(std::vector<std::string>& matrix){ //indicate us that its possible to create matrix
	tree* bintree = nullptr, *cur = nullptr, *prev = nullptr;
	std::string semi_base_word;
	std::string semi_in_word;
	std::string left_word;
	std::string right_word;
	std::vector<std::string> new_matrix;
	for(size_t i = 0; i < matrix.size(); ++i){
		Insertvalue(bintree, matrix[i]);
	}
	for(size_t j = 0; j < matrix.size(); ++j){
	for(size_t i = 0; i < matrix.size(); ++i){
		semi_base_word = matrix[j];
		new_matrix.push_back(matrix.at(j));
		for(size_t n = i, k = 0; k < semi_base_word.size() - 1; ++n, ++k){
			if(n == j){
				n++;
			}
			if(n >= matrix.size()){
				n = 0;
			}
			new_matrix.push_back(matrix.at(n));
		}
		for(size_t n = 0; n < semi_base_word.size(); ++n){
			semi_in_word = new_matrix.at(n);
			left_word.push_back(semi_in_word.at(0));
			right_word.push_back(semi_in_word.at(semi_in_word.size() - 1));
		}
		findtree(bintree, left_word, cur, prev);
		if(cur != nullptr){
			findtree(bintree, right_word, cur, prev);
				if(cur != nullptr){
					matrix.swap(new_matrix);
					return true;
				}
		}
		new_matrix.clear();
		left_word.clear();
		right_word.clear();
	}
	}
	return false;
}

void alg(char* argv[]){
	is_opened(argv);
	std::vector<std::string> matrix;
	matrix = file_to_vector(argv);
	if(check(matrix) == false){
		std::cout << "Cant realise matrix, invalid data" << std::endl;
	}
	else{
		print(matrix);
	}
}

int main(int argc, char* argv[]) {
	//argv[0] - program name
	//argv[1] - value(n)
	//argv[2] - file
	//can compile with g++ from 2020.

	if (argc != 3) {
		std::cout << "Invalid arguments" << std::endl;
		exit(0);
	}

	alg(argv);

	return 0;
}