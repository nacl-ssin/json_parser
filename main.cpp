#include <iostream>
#include <string>
#include "json_lexer.hpp"

std::string read_file(const std::string &file_path);

void test1() {
	//std::string str = R"({"name": 124, "age" : 19, "other": [100, 102.1, {"eating": false, "cars":null, "card": [1, 2, 3, {"card1name": "china", "card2name": "one", "card3name": null}]}]})";

	std::string str = read_file("../test/2.json");
	std::cout << str << std::endl;
	auto ji = nacl::json_lexer::parse(str);
	std::cout << "000000000000" << std::endl;
	ji.to_file("../out/1.json");
	std::cout << "000000000000" << std::endl;

	//std::cout << "========================" << std::endl;
	//std::cout << ji.get_value("name") << std::endl;
	//std::cout << ji.get_value("age") << std::endl;
	//std::cout << ji.next("other").get_element(0) << std::endl;
	//std::cout << ji.next("other").get_element(1) << std::endl;
	//
	//nacl::json_item ji1(nullptr);
	//ji1 = ji;
	//
	//std::cout << "========================" << std::endl;
	//std::cout << ji1.next("other").next(2).get_value("eating") << std::endl;
	//std::cout << ji1.next("other").next(2).get_value("cars") << std::endl;
	//std::cout << ji1.next("other").next(2).next("card").get_element(0) << std::endl;
	//
	//std::cout << "========================" << std::endl;
	//nacl::json_item ji2(nullptr);
	//ji2 = ji1;
	//std::cout << ji2.next("other").next(2).next("card").get_element(1) << std::endl;
	//std::cout << ji2.next("other").next(2).next("card").get_element(2) << std::endl;
	//std::cout << ji2.next("other").next(2).next("card").next(3).get_value("card1name") << std::endl;
	//
	//nacl::json_item ji3(nullptr);
	//ji3 = ji1;
	//
	//std::cout << "========================" << std::endl;
	//std::cout << ji3.next("other").next(2).next("card").next(3).get_value("card2name") << std::endl;
	//std::cout << ji3.next("other").next(2).next("card").next(3).get_value("card3name") << std::endl;

}
//251,241,199
//fbf1c7

//249,245,215
//f9f5d7

//FFF8D1
int main() {
	test1();
	return 0;
}





