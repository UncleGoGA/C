#include <iostream>
#include <vector>

//будем использовать std::pair для удобства хранения, фактически мы могли бы создать просто структуру с хранилищем под key && value

using namespace std;

//не будем забывать, что метод at как и erase с push_back не являются безопасными относительно исключений
//поэтому необходимо перехватить их и обработать
vector<pair<int, int>> end_game(vector<pair<int, int>>& game) {
	//по итогу выполнения, входной вектор будет пуст

	//идея такова, сначала заполняем действительный вектор костяшками, которые подходят без переворота
	//далее переворачиваем и вставляем все возможные

	vector<pair<int, int>> res;

	res.push_back(game.at(0));
	game.erase(game.begin());

	for (auto it = game.begin(), res_it = res.begin(); it != game.end(); ++it) {
		if (it->first == res_it->second) {
			res.push_back(*it); //любой указатель - итератор
			//но не любой итератор - указатель
			game.erase(it);
		}
	}

	for (auto it = game.begin(); it != game.end(); ++it) {
		for (auto res_it = res.begin(); res_it != res.end(); ++res_it) {
			if (it->second == res_it->second) {
				swap(it->first, it->second);
				res.push_back(*it); //любой указатель - итератор
				//но не любой итератор - указатель
				game.erase(it);
			}
			else if (it->first == res_it->second) {
				res.push_back(*it);
				game.erase(it);
			}
		}
	}

	return res;
}

std::ostream& operator<<(std::ostream& os, std::pair<int, int> cur_pair) {
	os << cur_pair.first << " - " << cur_pair.second << "\t";

	return os;
}

std::ostream& operator<<(std::ostream& os, std::vector<std::pair<int, int>> game) {
	std::pair<int, int> cur_pair;

	for (auto i_it = game.begin(); i_it != game.end(); ++i_it) {
		cur_pair = *i_it;
		for (auto j_it = game.begin(); j_it != game.end(); ++j_it) {
			if (j_it->first == cur_pair.second) {
				os << cur_pair;
				cur_pair = *j_it;
				game.erase(i_it);
			}
		}
		os << std::endl;
	}

	return os;
}

int main() {

	vector<pair<int, int>> game, res;

	try{
		res = end_game(game);
	}
	catch (...) {
		cout << "Smth went wrong" << "\n";
	}


	return 0;
}