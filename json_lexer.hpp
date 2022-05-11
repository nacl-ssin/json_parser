//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_LEXER_HPP
#define JSON_PARSER_JSON_LEXER_HPP

#include <vector>
#include <stack>
#include "json_token.hpp"
#include "json_type.hpp"


class json_lexer {
public:
	/**
	 * 解析json_str
	 * @param json_str
	 */
	static json_type_base *parse(const std::string &json_str) {
		auto tokens = token_list(json_str);
		std::cout << tokens.size() << std::endl;
		for (auto &e : tokens) {
			std::cout << e._value << " ";
		}
		std::cout << std::endl << "size = " << tokens.size() << std::endl;
		int i = 0;
		if (tokens[0]._token == json_token_type::OBJECT_BEGIN) {
			return token_to_object(tokens, i);
		} else if (tokens[0]._token == json_token_type::ARRAY_BEGIN) {
			return token_to_array(tokens, i);
		} else {
			return nullptr;
		}
	}


	static json_type_base *token_to_object(std::vector<token> &toks, int &i) {
		std::cout << "object---------------------------begin" << std::endl;
		// 跳过begin token
		++i;
		token k, v;
		json_type_base *jnode = new json_object;

		std::cout << "i = " << i << std::endl;
		while (i < toks.size() && k._token != json_token_type::OBJECT_END) {
			// 获取token key : value
			k = toks[i];
			if (i + 2 >= toks.size()) {
				break;
			}
			v = toks[i + 2];
			std::cout << k._value << " : " << v._value << std::endl;
			switch (v._token) {
				case json_token_type::OBJECT_BEGIN: {
					i += 2;
					jnode->add(k._value, token_to_object(toks, i));
					++i;
					if (toks[i]._token == json_token_type::COMMA) {
						++i;
					} else if (toks[i]._token == json_token_type::OBJECT_END) {
						goto object_end;
					}
					continue;
				}
				case json_token_type::ARRAY_BEGIN: {
					i += 2;
					jnode->add(k._value, token_to_array(toks, i));
					++i;
					if (toks[i]._token == json_token_type::COMMA) {
						++i;
					} else if (toks[i]._token == json_token_type::OBJECT_END) {
						goto object_end;
					}
					continue;
				}
				case json_token_type::STRING: {
					auto jstr = new json_string;
					jstr->_data = v._value;
					jnode->add(k._value, jstr);
					break;
				}
				case json_token_type::NUMBER: {
					auto jstr = new json_number;
					jstr->_data = v._value;
					jnode->add(k._value, jstr);
					break;
				}
				case json_token_type::BOOLEAN: {
					auto jstr = new json_boolean;
					jstr->_data = v._value;
					jnode->add(k._value, jstr);
					break;
				}
				case json_token_type::NIL: {
					auto jstr = new json_null;
					jstr->_data = v._value;
					jnode->add(k._value, jstr);
					break;
				}
				default:
					break;
			}

			i += 3;
			// 可能是对象结束
			if (toks[i]._token == json_token_type::OBJECT_END) {
				break;
			}
			i += 1;
		}

		object_end:
		std::cout << "object---------------------------end" << std::endl;
		return jnode;
	}


	static json_type_base *token_to_array(std::vector<token> &toks, int &i) {
		std::cout << "array----------------------begin" << std::endl;
		// 跳过begin token
		++i;
		auto t = toks[i];
		json_type_base *jnode = new json_array;

		while (i < toks.size() && t._token != json_token_type::ARRAY_END) {
			t = toks[i];
			std::cout << t._value << std::endl;
			switch (t._token) {
				case json_token_type::OBJECT_BEGIN: {
					jnode->add(token_to_object(toks, i));
					++i;
					if (toks[i]._token == json_token_type::COMMA) {
						++i;
					} else if (toks[i]._token == json_token_type::ARRAY_END) {
						goto array_end;
					}
					continue;
				}
				case json_token_type::ARRAY_BEGIN: {
					jnode->add(token_to_array(toks, i));
					++i;
					if (toks[i]._token == json_token_type::COMMA) {
						++i;
					} else if (toks[i]._token == json_token_type::ARRAY_END) {
						goto array_end;
					}
					continue;
				}
				case json_token_type::STRING: {
					auto jstr = new json_string;
					jstr->_data = t._value;
					jnode->add(jstr);
					break;
				}
				case json_token_type::NUMBER: {
					auto jstr = new json_number;
					jstr->_data = t._value;
					jnode->add(jstr);
					break;
				}
				case json_token_type::BOOLEAN: {
					auto jstr = new json_boolean;
					jstr->_data = t._value;
					jnode->add(jstr);
					break;
				}
				case json_token_type::NIL: {
					auto jstr = new json_null;
					jstr->_data = t._value;
					jnode->add(jstr);
					break;
				}
				default:
					break;
			}

			++i;
			// 可能是数组结束
			if (toks[i]._token == json_token_type::ARRAY_END) {
				break;
			}
			++i;
		}

		// [[],]    =>     [[],]
		//   ^                 ^
		//	or :out of rang，返回
		// []    =>     []
		//  ^              ^
		array_end:
		if (i < toks.size()) {
			std::cout << "{{{{{" << toks[i]._value << "}}}}}" << std::endl;
		}
		std::cout << "array----------------------end" << std::endl;
		return jnode;
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
	static std::vector<token> token_list(const std::string &json_str) {
		std::vector<token> tokens;
		auto n = json_str.size();
		for (size_t i = 0; i < n; ++i) {
			if (json_str[i] == ' ' || json_str[i] == '\n') {
				continue;
			}

			switch (json_str[i]) {
				case '[':
					//std::cout << "[ ";
					tokens.emplace_back("[", json_token_type::ARRAY_BEGIN);
					break;
				case ']':
					//std::cout << "] ";
					tokens.emplace_back("]", json_token_type::ARRAY_END);
					break;
				case '{':
					//std::cout << "{ ";
					tokens.emplace_back("{", json_token_type::OBJECT_BEGIN);
					break;
				case '}':
					//std::cout << "} ";
					tokens.emplace_back("}", json_token_type::OBJECT_END);
					break;
				case ',':
					//std::cout << ", ";
					tokens.emplace_back(",", json_token_type::COMMA);
					break;
				case ':':
					//std::cout << ": ";
					tokens.emplace_back(":", json_token_type::COLON);
					break;
				case '"': {
					std::string str = read_str(json_str, i);
					//std::cout << str << " ";
					tokens.emplace_back(str, json_token_type::STRING);
					break;
				}
				case 't':
				case 'f': {
					auto b = read_boolean(json_str, i);
					//std::cout << b << " ";
					tokens.emplace_back(b, json_token_type::BOOLEAN);
					break;
				}
				case 'n':
					//std::cout << "null ";
					i += 3;
					tokens.emplace_back("null", json_token_type::NIL);
					break;
				default:
					std::string num = read_number(json_str, i);
					//std::cout << num << " ";
					tokens.emplace_back(num, json_token_type::NUMBER);
					break;
			}
		}

		return tokens;
	}


	/**
	 * 读取一个字符串
	 * @param src
	 * @param start
	 * @return
	 */
	static std::string read_str(const std::string &src, size_t &start) {
		++start;
		size_t i = start;
		auto n = src.size();
		while (start < n && src[start] != '"') {
			++start;
		}
		return src.substr(i, start - i);
	}


	/**
	 * 读取一个数字
	 * @param src
	 * @param start
	 * @return
	 */
	static std::string read_number(const std::string &src, size_t &start) {
		size_t i = start;
		bool dot = false;
		auto n = src.size();
		while (start < n) {
			if (isdigit(src[start])) {
				start++;
			} else if (src[start] == '.') {
				if (dot) {
					// error: invalid json str
					break;
				}
				dot = true;
				++start;
			} else {
				break;
			}
		}
		--start;
		return src.substr(i, start - i + 1);
	}


	static std::string read_boolean(const std::string &src, size_t &start) {
		if (src[start] == 't') {
			start += 3;
			return src.substr(start - 3, 4);
		} else {
			start += 4;
			return src.substr(start - 4, 5);
		}
	}
};


#endif //JSON_PARSER_JSON_LEXER_HPP
