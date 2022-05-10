#include <iostream>
#include <string>
#include <vector>
#include "json_lexer.hpp"

struct json_node {};

std::string &trim(std::string &str) {
	auto iter = str.begin();
	while (*iter == ' ') {
		++iter;
	}
	str.erase(str.begin(), iter);

	for (auto riter = str.rbegin(); riter != str.rend(); ++riter) {
		if (*riter == ' ')
			str.pop_back();
		else
			break;
	}

	return str;
}

int skip_space(const std::string &str, int i) {
	while (i < str.size() && str[i] == ' ') {
		++i;
	}
	return i;
}

int skip_close(const std::string &str, int i) {
	while (i < str.size()) {
		if (str[i] == ',')
			break;
		++i;
	}
	return i;
}

void parser_ary(std::string &str, int i);

int level = 0;

std::pair<json_node, int> get_value(const std::string &str, int start) {
	json_node n;

	if (str[start] == '[') {
		// array
		//parser_ary(str, start);
		++level;
		for (int i = 0; i <= level; ++i)
			std::cout << "|\t";
		std::cout << "level = " << level << ", begin" << std::endl;
		return {n, start};
	} else if (str[start] == '{') {
		// object
	} else {
		// number / string
		int i = start;
		while (i < str.size() && str[i] != ',' && str[i] != ']') {
			++i;
		}
		std::string s = str.substr(start, i - start);
		trim(s);
		for (int i = 0; i <= level; ++i)
			std::cout << "|\t";
		std::cout << s << std::endl;


		while (i < str.size() && (str[i] == ']' || str[i] == ' ')) {
			if (str[i] == ']') {
				for (int i = 0; i <= level; ++i)
					std::cout << "|\t";
				std::cout << "level = " << level << ", end" << std::endl;
				level--;
			}
			++i;
		}

		return {n, skip_space(str, i)};
	}

	return {n, start};
}


int parser_ary(const std::string &str, int i = 0) {
	for (int i = 0; i <= level; ++i)
		std::cout << "|\t";
	std::cout << "level = " << level << ", begin" << std::endl;
	for (; i < str.size();) {
		int start = skip_space(str, i);
		auto p = get_value(str, start);
		i = p.second;
		++i;
	}
	return 0;
}


int parser_obj(const std::string &str, int i = 0) {
	++i;
	while (i < str.size()) {
		std::string key;
		while (i < str.size() && str[i] != ':') {
			key.push_back(str[i]);
			++i;
		}
		++i;
		std::cout << key << ": ";
		std::string value;
		while (i < str.size() && str[i] != ',' && str[i] != '}') {
			value.push_back(str[i]);
			++i;
		}
		++i;
		std::cout << value << std::endl;
		trim(value);
		if (value.front() == '[') {
			parser_ary(value);
		} else if (value.front() == '{') {
			//parser_obj(value);
		} else {

		}
	}
	return 0;
}


void entry(const std::string &str, int pos = 0) {
	std::size_t n = str.size();
	while (pos < n) {
		if (str[pos] == '[') {
			pos = parser_ary(str, pos + 1);
		} else if (str[pos] == '{') {
			pos = parser_obj(str, pos + 1);
		} else {

		}
	}
}


void test1() {
	std::string json_str = R"([ "1,", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.,56"]  , 6 , "12300"])";

	std::string str = R"([ 2   , 33,   "44"  , "5" ])";
	std::string obj_str = R"({"name" :  "zhangsan"   , "   age   ":12,"sex"     :          "male", "arr": [1, 2]})";


	parser_ary(json_str);
	//parser_obj(obj_str);
}


int main() {
	//test1();
	//std::cout << sizeof(json_node) << std::endl;
	return 0;
}
















