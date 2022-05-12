//
// Created by 26372 on 2022/5/12.
//

#include <iostream>
#include "json_lexer.hpp"

void test1() {
	std::string json_str = R"([ "1", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.,56"]  , 6 , "12300"])";

	auto ji = json_lexer::parse(json_str);
	std::cout << ji.get_element(0) << std::endl;
	std::cout << ji.get_element(1) << std::endl;
}


#ifdef JOSON_NODE_V

void test2() {
	std::string str1 = R"([ 2.001   , 33.34,   "44.7"  , "5" ])";
	std::string str = R"([ "1", 2  , [   3, 4   ,[5], [5.5, [5.51, [5.52,[5.53]  ]  ]  ] ,  5.533    ], [   5.54, [   5.55   ], "5.56"]  , 6 , "12300"])";
	std::string obj_str = R"({"name" :  "zhangsan"   , "   age   ":12,"sex"     :          "male", "arr": [1, 2]})";
	//auto jn = json_lexer::parse(str1);

	//std::cout << jn.get(0).get() << std::endl;
	//std::cout << jn.get(1).get() << std::endl;
	//std::cout << jn.get(2).get() << std::endl;
	//std::cout << jn.get(3).get() << std::endl;

	auto ji = json_lexer::parse(obj_str);
	json_node jn = ji.json_root();
	std::cout << jn.get("name").get() << std::endl;
	std::cout << jn.get("   age   ").get() << std::endl;
	std::cout << jn.get("sex").get() << std::endl;
	std::cout << jn.get("arr").get(0).get() << std::endl;
	std::cout << jn.get("arr").get(1).get() << std::endl;
}

#endif

int main() {
	test1();
}
