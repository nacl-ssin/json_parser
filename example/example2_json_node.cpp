//
// Created by 26372 on 2022/5/12.
//
#include <iostream>
#include "json_lexer.hpp"

extern std::string read_file(const std::string &file_path);

#ifdef JSON_NODE_V

void test3() {
	std::string json_str = read_file("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/1.json");
	std::cout << json_str << std::endl;
	std::cout << "------------------------------" << std::endl;

	auto ji = json_lexer::parse(json_str);
	std::cout << std::endl;
	json_node jn = ji.json_root();

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
	std::string json_str = read_file("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/2.json");
	std::cout << json_str << std::endl;
	std::cout << "----------------------" << std::endl;

	json_item ji = json_lexer::parse(json_str);
	json_node jn = ji.json_root();

	std::cout << "obj1 = " << std::endl;
	std::cout << jn.get(0).get("name").get() << std::endl;
	std::cout << jn.get(0).get("age").get() << std::endl;
	std::cout << jn.get(0).get("ismale").get() << std::endl;
	std::cout << jn.get(0).get("eat").get() << std::endl;
	std::cout << jn.get(0).get("scores").get(0).get() << std::endl;
	std::cout << jn.get(0).get("scores").get(1).get() << std::endl;
	std::cout << jn.get(0).get("scores").get(2).get() << std::endl;
	//std::cout << jn.get(0).get("scores").get(3).get() << std::endl;
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
	//std::cout << jn.get(1).get("scores").get(3).get() << std::endl;
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


void test5() {
	std::string json_str = read_file("C:/Users/26372/Desktop/Cpp/clion/json_parser/test/3.json");
	std::cout << json_str << std::endl;
	std::cout << "----------------------" << std::endl;

	auto ji = json_lexer::parse(json_str);
	json_node jn = ji.json_root();


	std::cout << jn.get("name").get() << std::endl;
	std::cout << jn.get("version").get() << std::endl;
	std::cout << jn.get("private").get() << std::endl;
	std::cout << jn.get("scripts").get("serve").get() << std::endl;
	std::cout << jn.get("scripts").get("build").get() << std::endl;
	std::cout << jn.get("scripts").get("lint").get() << std::endl;

	std::cout << jn.get("dependencies").get("@element-plus/icons-vue").get() << std::endl;
	std::cout << jn.get("dependencies").get("axios").get() << std::endl;
	std::cout << jn.get("dependencies").get("core-js").get() << std::endl;
	std::cout << jn.get("dependencies").get("element-plus").get() << std::endl;
	std::cout << jn.get("dependencies").get("vue").get() << std::endl;
	std::cout << jn.get("dependencies").get("vue-router").get() << std::endl;

	std::cout << jn.get("devDependencies").get("@vue/cli-plugin-babel").get() << std::endl;
	std::cout << jn.get("devDependencies").get("@vue/cli-plugin-babel").get() << std::endl;
	std::cout << jn.get("devDependencies").get("@vue/cli-plugin-eslint").get() << std::endl;
	std::cout << jn.get("devDependencies").get("@vue/cli-service").get() << std::endl;
	std::cout << jn.get("devDependencies").get("@vue/compiler-sfc").get() << std::endl;
	std::cout << jn.get("devDependencies").get("babel-eslint").get() << std::endl;
	std::cout << jn.get("devDependencies").get("eslint").get() << std::endl;
	std::cout << jn.get("devDependencies").get("eslint-plugin-vue").get() << std::endl;

	std::cout << jn.get("eslintConfig").get("root").get() << std::endl;
	std::cout << jn.get("eslintConfig").get("env").get("node").get() << std::endl;
	std::cout << jn.get("eslintConfig").get("extends").get(0).get() << std::endl;
	std::cout << jn.get("eslintConfig").get("extends").get(1).get() << std::endl;
	std::cout << jn.get("eslintConfig").get("parserOptions").get("parser").get() << std::endl;
	//std::cout << jn.get("eslintConfig").get("rules").get() << std::endl;


	std::cout << jn.get("browserslist").get(0).get() << std::endl;
	std::cout << jn.get("browserslist").get(1).get() << std::endl;
	std::cout << jn.get("browserslist").get(2).get() << std::endl;


}

#endif

int main() {
	test3();
	//test4();
	//test5();
}