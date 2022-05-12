//
// Created by 26372 on 2022/5/12.
//

#ifndef JSON_PARSER_COMMON_CPP
#define JSON_PARSER_COMMON_CPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

std::string read_file(const std::string &file_path) {
	std::fstream fs(file_path);
	std::string json_str;
	if (fs.is_open()) {
		std::cout << "is open" << std::endl;
		char tmp[256] = {0};
		while (fs.good()) {
			memset(tmp, 0, sizeof(tmp));
			fs.read(tmp, sizeof(tmp) - 1);
			json_str.append(tmp);
		}
	}
	fs.close();
	return json_str;
}

#endif //JSON_PARSER_COMMON_CPP
