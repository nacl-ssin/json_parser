//
// Created by 26372 on 2022/5/12.
//
#include <iostream>
#include "json_lexer.hpp"

extern std::string read_file(const std::string &file_path);

void test6() {
	std::string json_str = read_file("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/3.json");
	std::cout << json_str << std::endl;
	std::cout << "----------------------" << std::endl;

	auto ji = json_lexer::parse(json_str);

	std::cout << ji.get_value("name") << std::endl;
	std::cout << ji.get_value("version") << std::endl;
	std::cout << ji.get_value("private") << std::endl;
	std::cout << ji.get_next("scripts").get_value("serve") << std::endl;
	std::cout << ji.get_next("scripts").get_value("build") << std::endl;
	std::cout << ji.get_next("scripts").get_value("lint") << std::endl;
	std::cout << ji.get_next("eslintConfig").get_value("root") << std::endl;
	std::cout << ji.get_next("eslintConfig").get_next("env").get_value("node") << std::endl;
	std::cout << ji.get_next("eslintConfig").get_next("extends").get_element(0) << std::endl;
	std::cout << ji.get_next("eslintConfig").get_next("extends").get_element(1) << std::endl;
	std::cout << ji.get_next("browserslist").get_element(0) << std::endl;
	std::cout << ji.get_next("browserslist").get_element(1) << std::endl;
	std::cout << ji.get_next("browserslist").get_element(2) << std::endl;
}


void test7() {
	std::string json_str = read_file("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/2.json");
	std::cout << json_str << std::endl;
	std::cout << "----------------------" << std::endl;

	auto ji = json_lexer::parse(json_str);

	std::cout << ji.get_next(0).get_value("name") << std::endl;
	std::cout << ji.get_next(0).get_value("age") << std::endl;
	std::cout << ji.get_next(0).get_value("ismale") << std::endl;
	std::cout << ji.get_next(0).get_value("eat") << std::endl;
	std::cout << ji.get_next(0).get_next("scores").get_element(0) << std::endl;
	std::cout << ji.get_next(0).get_next("scores").get_element(1) << std::endl;
	std::cout << ji.get_next(0).get_next("scores").get_element(2) << std::endl;
	std::cout << ji.get_next(0).get_next("scores").get_element(3) << std::endl;
	std::cout << ji.get_next(0).get_value("cars") << std::endl;
	std::cout << ji.get_next(0).get_value("phone") << std::endl;
	std::cout << ji.get_next(0).get_value("address") << std::endl;


	std::cout << ji.get_next(1).get_value("name") << std::endl;
	std::cout << ji.get_next(1).get_value("age") << std::endl;
	std::cout << ji.get_next(1).get_value("ismale") << std::endl;
	std::cout << ji.get_next(1).get_value("eat") << std::endl;
	std::cout << ji.get_next(1).get_next("scores").get_element(0) << std::endl;
	std::cout << ji.get_next(1).get_next("scores").get_element(1) << std::endl;
	std::cout << ji.get_next(1).get_next("scores").get_element(2) << std::endl;
	std::cout << ji.get_next(1).get_value("cars") << std::endl;
	std::cout << ji.get_next(1).get_value("phone") << std::endl;
	std::cout << ji.get_next(1).get_value("address") << std::endl;


	std::cout << ji.get_next(1).get_next("a").get_element(0) << std::endl;
	std::cout << ji.get_next(1).get_next("a").get_element(1) << std::endl;
	std::cout << ji.get_next(1).get_next("a").get_element(2) << std::endl;
	std::cout << ji.get_next(1).get_next("a").get_next(3).get_element(0) << std::endl;
	std::cout << ji.get_next(1).get_next("a").get_next(3).get_element(1) << std::endl;
	std::cout << ji.get_next(1).get_next("a").get_next(3).get_element(2) << std::endl;

	std::cout << ji.get_next(2).get_element(0) << std::endl;
	std::cout << ji.get_next(2).get_element(1) << std::endl;
	std::cout << ji.get_next(2).get_element(2) << std::endl;
	std::cout << ji.get_next(2).get_element(3) << std::endl;

	std::cout << ji.get_next(3).get_value("nihaobuhao") << std::endl;
	std::cout << ji.get_next(3).get_next("key").get_next("lives").get_element(0) << std::endl;
	std::cout << ji.get_next(3).get_next("key").get_next("lives").get_element(1) << std::endl;
	std::cout << ji.get_next(3).get_next("key").get_next("lives").get_element(2) << std::endl;
	std::cout << ji.get_next(3).get_value("nihaobuhao") << std::endl;
}

int main() {
	test6();
	//test7();
}
