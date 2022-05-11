#include <iostream>
#include <fstream>
#include <string>
#include "json_lexer.hpp"


void test1() {
	std::string json_str = R"([ "1", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.,56"]  , 6 , "12300"])";

	auto jn = json_lexer::parse(json_str);
	std::cout << jn.get(0).get() << std::endl;
	std::cout << jn.get(1).get() << std::endl;
}


void test2() {
	std::string str1 = R"([ 2.001   , 33.34,   "44.7"  , "5" ])";
	std::string str = R"([ "1", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.56"]  , 6 , "12300"])";
	std::string obj_str = R"({"name" :  "zhangsan"   , "   age   ":12,"sex"     :          "male", "arr": [1, 2]})";
	//auto jn = json_lexer::parse(str1);

	//std::cout << jn.get(0).get() << std::endl;
	//std::cout << jn.get(1).get() << std::endl;
	//std::cout << jn.get(2).get() << std::endl;
	//std::cout << jn.get(3).get() << std::endl;

	auto jn = json_lexer::parse(obj_str);
	std::cout << jn.get("name").get() << std::endl;
	std::cout << jn.get("   age   ").get() << std::endl;
	std::cout << jn.get("sex").get() << std::endl;
	std::cout << jn.get("arr").get(0).get() << std::endl;
	std::cout << jn.get("arr").get(1).get() << std::endl;
}


void test3() {
	std::fstream fs("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/1.json");
	std::string json_str;

	if (fs.is_open()) {
		std::cout << "is open" << std::endl;
		char tmp[256] = {0};
		fs.read(tmp, sizeof(tmp) - 1);
		json_str.append(tmp);
	}
	std::cout << json_str << std::endl;
	std::cout << "------------------------------" << std::endl;

	auto jn = json_lexer::parse(json_str);
	std::cout << std::endl;

	std::cout << jn.get("name").get() << std::endl;
	std::cout << jn.get("age").get() << std::endl;
	std::cout << jn.get("ismale").get() << std::endl;
	std::cout << jn.get("eat").get() << std::endl;
	std::cout << jn.get("scores").get(0).get() << std::endl;
	std::cout << jn.get("scores").get(1).get() << std::endl;
	std::cout << jn.get("scores").get(2).get() << std::endl;
	std::cout << jn.get("scores").get(3).get() << std::endl;
	//std::cout << jn.get("scores").get(4).get() << std::endl;
	std::cout << jn.get("cars").get() << std::endl;
	std::cout << jn.get("phone").get() << std::endl;
	std::cout << jn.get("address").get() << std::endl;

	std::cout << "0000000000000000000000000000000000000000000000000000000" << std::endl;
	jn.destroy();
}


void test4() {
	std::fstream fs("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/2.json");
	std::string json_str;
	if (fs.is_open()) {
		std::cout << "is open" << std::endl;
		char tmp[726] = {0};
		fs.read(tmp, sizeof(tmp) - 1);
		json_str.append(tmp);
	}
	std::cout << json_str << std::endl;
	std::cout << "----------------------" << std::endl;

	json_node jn = json_lexer::parse(json_str);

	std::cout << "obj1 = " << std::endl;
	std::cout << jn.get(0).get("name").get() << std::endl;
	std::cout << jn.get(0).get("age").get() << std::endl;
	std::cout << jn.get(0).get("ismale").get() << std::endl;
	std::cout << jn.get(0).get("eat").get() << std::endl;
	std::cout << jn.get(0).get("scores").get(0).get() << std::endl;
	std::cout << jn.get(0).get("scores").get(1).get() << std::endl;
	std::cout << jn.get(0).get("scores").get(2).get() << std::endl;
	std::cout << jn.get(0).get("scores").get(3).get() << std::endl;
	std::cout << jn.get(0).get("cars").get() << std::endl;
	std::cout << jn.get(0).get("phone").get() << std::endl;
	std::cout << jn.get(0).get("address").get() << std::endl;
	std::cout << "obj2 = " << std::endl;
	std::cout << jn.get(1).get("name").get() << std::endl;
	std::cout << jn.get(1).get("age").get() << std::endl;
	std::cout << jn.get(1).get("ismale").get() << std::endl;
	std::cout << jn.get(1).get("eat").get() << std::endl;
	std::cout << jn.get(1).get("scores").get(0).get() << std::endl;
	std::cout << jn.get(1).get("scores").get(1).get() << std::endl;
	std::cout << jn.get(1).get("scores").get(2).get() << std::endl;
	std::cout << jn.get(1).get("scores").get(3).get() << std::endl;
	std::cout << jn.get(1).get("cars").get() << std::endl;
	std::cout << jn.get(1).get("phone").get() << std::endl;
	std::cout << jn.get(1).get("address").get() << std::endl;
	std::cout << "array" << std::endl;
	std::cout << jn.get(1).get("a").get(0).get() << std::endl;
	std::cout << jn.get(1).get("a").get(1).get() << std::endl;
	std::cout << jn.get(1).get("a").get(2).get() << std::endl;
	std::cout << jn.get(1).get("a").get(3).get(0).get() << std::endl;
	std::cout << jn.get(1).get("a").get(3).get(1).get() << std::endl;
	std::cout << jn.get(1).get("a").get(3).get(2).get() << std::endl;
	std::cout << "end" << std::endl;
	std::cout << jn.get(2).get(0).get() << std::endl;
	std::cout << jn.get(2).get(1).get() << std::endl;
	std::cout << jn.get(2).get(2).get() << std::endl;
	std::cout << jn.get(2).get(3).get() << std::endl;


	std::cout << jn.get(3).get("nihaobuhao").get() << std::endl;
	std::cout << jn.get(3).get("key").get("lives").get(0).get() << std::endl;
	std::cout << jn.get(3).get("key").get("lives").get(1).get() << std::endl;
	std::cout << jn.get(3).get("key").get("lives").get(2).get() << std::endl;

	jn.destroy();
}


int main() {
	//test1();
	//test2();
	test3();
	//test4();
	return 0;
}





