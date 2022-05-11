#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json_lexer.hpp"


void test1() {
	std::string json_str = R"([ "1", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.,56"]  , 6 , "12300"])";

	auto jr = json_lexer::parse(json_str);
	std::cout << jr->get(0)->get() << std::endl;
	std::cout << jr->get(1)->get() << std::endl;
}


void test2() {
	std::string str1 = R"([ 2.001   , 33.34,   "44.7"  , "5" ])";
	std::string str = R"([ "1", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.56"]  , 6 , "12300"])";
	std::string obj_str = R"({"name" :  "zhangsan"   , "   age   ":12,"sex"     :          "male", "arr": [1, 2]})";
	//auto jr = json_lexer::parse(str1);

	//std::cout << jr->get(0)->get() << std::endl;
	//std::cout << jr->get(1)->get() << std::endl;
	//std::cout << jr->get(2)->get() << std::endl;
	//std::cout << jr->get(3)->get() << std::endl;

	auto jr = json_lexer::parse(obj_str);
	std::cout << jr->get("name")->get() << std::endl;
	std::cout << jr->get("   age   ")->get() << std::endl;
	std::cout << jr->get("sex")->get() << std::endl;
	std::cout << jr->get("arr")->get(0)->get() << std::endl;
	std::cout << jr->get("arr")->get(1)->get() << std::endl;
}


void test3() {
	std::fstream fs("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/1.json");
	std::string json_str;
	if (fs.is_open()) {
		std::cout << "is open" << std::endl;
		char tmp[256] = {0};
		while (fs.good()) {
			fs.read(tmp, sizeof(tmp) - 1);
			json_str.append(tmp);
		}
	}

	std::cout << json_str << std::endl;

	auto jr = json_lexer::parse(json_str);
	std::cout << std::endl;

	std::cout << jr->get("name")->get() << std::endl;
	std::cout << jr->get("age")->get() << std::endl;
	std::cout << jr->get("ismale")->get() << std::endl;
	std::cout << jr->get("eat")->get() << std::endl;
	std::cout << jr->get("scores")->get(0)->get() << std::endl;
	std::cout << jr->get("scores")->get(1)->get() << std::endl;
	std::cout << jr->get("scores")->get(2)->get() << std::endl;
	std::cout << jr->get("scores")->get(3)->get() << std::endl;
	std::cout << jr->get("scores")->get(4)->get() << std::endl;
	std::cout << jr->get("cars")->get() << std::endl;
	std::cout << jr->get("phone")->get() << std::endl;
	std::cout << jr->get("address")->get() << std::endl;


}


void test4() {
	std::fstream fs("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/2.json");
	std::string json_str;
	if (fs.is_open()) {
		std::cout << "is open" << std::endl;
		char tmp[725] = {0};
		fs.read(tmp, sizeof(tmp) - 1);
		json_str.append(tmp);
	}
	//std::cout << json_str << std::endl;

	auto jr = json_lexer::parse(json_str);
	//std::cout << 1 << std::endl;

	delete jr;
}


int main() {
	//test1();
	//test2();
	test3();
	//test4();
	return 0;
}





