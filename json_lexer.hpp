//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_LEXER_HPP
#define JSON_PARSER_JSON_LEXER_HPP

#include <vector>
#include "json_token.hpp"
#include "json_type.hpp"


class json_lexer {
private:
	json_type_base *_json_root;

	json_lexer() : _json_root(nullptr) {
	}

public:
	/**
	 * 解析json_str
	 * @param json_str
	 */
	void parse(const std::string &json_str) {
		auto tokens = token_list(json_str);

	}


	/**
	 * 解析str，并将结果输出到文件
	 * @param file_path
	 */
	void to_file(const std::string &file_path) {
	}

private:
	/**
	 * 获取json_str的token数组
	 * @param json_str
	 * @return
	 */
	std::vector<token> token_list(const std::string &json_str) {
		std::vector<token> tokens;
		for (auto c : json_str) {
			switch (c) {
				case '[':
					tokens.emplace_back("[", json_token_type::ARRAY_BEGIN);
					break;
				case ']':
					tokens.emplace_back("]", json_token_type::ARRAY_END);
					break;
				case '{':
					tokens.emplace_back("{", json_token_type::OBJECT_BEGIN);
					break;
				case '}':
					tokens.emplace_back("}", json_token_type::OBJECT_END);
					break;
				case '"':
					tokens.emplace_back("[", json_token_type::STRING);
					break;
				case 't':
					tokens.emplace_back("[", json_token_type::BOOLEAN);
					break;
				case 'f':
					tokens.emplace_back("[", json_token_type::BOOLEAN);
					break;
				case 'n':
					tokens.emplace_back("[", json_token_type::NIL);
					break;
				default:
					break;
			}
		}

		return tokens;
	}
};


#endif //JSON_PARSER_JSON_LEXER_HPP
