//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_LEXER_HPP
#define JSON_PARSER_JSON_LEXER_HPP

#include <fstream>
#include <vector>
#include <stack>
#include <cstring>
#include "json_type.hpp"

namespace nacl {

	enum class json_token_type {
		TOKEN_OBJECT_BEGIN,
		TOKEN_OBJECT_END,
		TOKEN_ARRAY_BEGIN,
		TOKEN_ARRAY_END,
		TOKEN_COMMA,
		TOKEN_COLON,
		TOKEN_STRING,
		TOKEN_NUMBER,
		TOKEN_NIL,
		TOKEN_BOOLEAN,
	};

	class token {
		friend class json_lexer;

	private:
		std::string _value;
		json_token_type _token;

	public:

		token() : _token(json_token_type::TOKEN_NIL) {

		}

		token(std::string val, json_token_type token) : _value(std::move(val)), _token(token) {
		}
	};


	class json_lexer {
	public:
		/**
		 * 解析json_str
		 * @param json_str
		 */
		static json_item parse(const std::string &json_str) {
			auto tokens = extract_token(json_str);

			std::cout << std::endl << "size = " << tokens.size() << std::endl;
			int i = 0;
			if (tokens[0]._token == json_token_type::TOKEN_OBJECT_BEGIN) {
				return {token_to_object(tokens, i), 1};
			} else if (tokens[0]._token == json_token_type::TOKEN_ARRAY_BEGIN) {
				return {token_to_array(tokens, i), 1};
			} else {
				return {new json_simple(tokens[0]._value, json_flag::STRING), 1};
			}
		}

	private:
		/**
		 * 获取json_str的token数组
		 * @param json_str
		 * @return
		 */
		static std::vector<token> extract_token(const std::string &json_str) {
			std::vector<token> tokens;
			auto n = json_str.size();
			for (size_t i = 0; i < n; ++i) {
				if (json_str[i] == '\r' && i + 1 < n && json_str[i] == '\n') {
					continue;
				}

				if (json_str[i] == ' ' || json_str[i] == '\n' || json_str[i] == '\r') {
					continue;
				}

				switch (json_str[i]) {
					case '[':
						std::cout << "[ ";
						tokens.emplace_back("[", json_token_type::TOKEN_ARRAY_BEGIN);
						break;
					case ']':
						std::cout << "] ";
						tokens.emplace_back("]", json_token_type::TOKEN_ARRAY_END);
						break;
					case '{':
						std::cout << "{ ";
						tokens.emplace_back("{", json_token_type::TOKEN_OBJECT_BEGIN);
						break;
					case '}':
						std::cout << "} ";
						tokens.emplace_back("}", json_token_type::TOKEN_OBJECT_END);
						break;
					case ',':
						std::cout << ", ";
						tokens.emplace_back(",", json_token_type::TOKEN_COMMA);
						break;
					case ':':
						std::cout << ": ";
						tokens.emplace_back(":", json_token_type::TOKEN_COLON);
						break;
					case '"': {
						std::string str = read_str(json_str, i);
						std::cout << str << " ";
						tokens.emplace_back(str, json_token_type::TOKEN_STRING);
						break;
					}
					case 't':
					case 'f': {
						std::string str = read_boolean(json_str, i);
						std::cout << str << " ";
						tokens.emplace_back(str, json_token_type::TOKEN_BOOLEAN);
						break;
					}
					case 'n':
						i += 3;
						tokens.emplace_back("null", json_token_type::TOKEN_NIL);
						std::cout << "null ";
						break;
					default:
						//std::cout << "default" << std::endl;
						std::string str = read_number(json_str, i);
						std::cout << str << " ";
						tokens.emplace_back(str, json_token_type::TOKEN_NUMBER);
						break;
				}
			}

			//std::cout << tokens.size() << std::endl;
			//for (auto &e : tokens) {
			//	std::cout << e._value << " ";
			//}
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


		static json_type_base *token_to_object(std::vector<token> &toks, int &i) {
			std::cout << "object---------------------------begin" << std::endl;
			// 跳过begin token
			++i;

			if (i >= toks.size()) {
				return nullptr;
			}

			token k = toks[i], v;

			// 是一个空对象
			if (k._token == json_token_type::TOKEN_OBJECT_END) {
				std::cout << "object---------------------------end" << std::endl;
				return nullptr;
			}

			json_type_base *jnode = new json_object;

			while (i < toks.size() && k._token != json_token_type::TOKEN_OBJECT_END) {
				// 获取token key : value
				k = toks[i];
				if (i + 2 >= toks.size()) {
					break;
				}
				v = toks[i + 2];
				std::cout << k._value << " : " << v._value << std::endl;
				switch (v._token) {
					case json_token_type::TOKEN_OBJECT_BEGIN: {
						i += 2;
						jnode->add(json_data(k._value, token_to_object(toks, i)));
						goto object_common_block;
					}
					case json_token_type::TOKEN_ARRAY_BEGIN: {
						i += 2;
						jnode->add(json_data(k._value, token_to_array(toks, i)));

						object_common_block:
						++i;
						if (toks[i]._token == json_token_type::TOKEN_COMMA) {
							++i;
						} else if (toks[i]._token == json_token_type::TOKEN_OBJECT_END) {
							goto object_end;
						} else {
							++i;
						}
						continue;
					}
					case json_token_type::TOKEN_STRING:
						jnode->add(json_data(k._value, new json_simple(v._value, json_flag::STRING)));
						break;
					case json_token_type::TOKEN_NUMBER:
						jnode->add(json_data(k._value, new json_simple(v._value, json_flag::NUMBER)));
						break;
					case json_token_type::TOKEN_BOOLEAN:
						jnode->add(json_data(k._value, new json_simple(v._value, json_flag::BOOLEAN)));
						break;
					case json_token_type::TOKEN_NIL:
						jnode->add(json_data(k._value, new json_simple(v._value, json_flag::NIL)));
						break;
					default:
						std::cout << "default" << std::endl;
						break;
				}

				i += 3;
				// 可能是对象结束
				if (toks[i]._token == json_token_type::TOKEN_OBJECT_END) {
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
			if (i >= toks.size()) {
				return nullptr;
			}

			token t = toks[i];
			// 空数组
			if (t._token == json_token_type::TOKEN_ARRAY_END) {
				return nullptr;
			}

			json_type_base *jnode = new json_array;

			while (i < toks.size() && t._token != json_token_type::TOKEN_ARRAY_END) {
				t = toks[i];
				std::cout << t._value << std::endl;
				switch (t._token) {
					case json_token_type::TOKEN_OBJECT_BEGIN: {
						jnode->add(json_data(token_to_object(toks, i)));
						goto array_common_block;
					}
					case json_token_type::TOKEN_ARRAY_BEGIN: {
						jnode->add(json_data(token_to_array(toks, i)));
						array_common_block:
						++i;
						// 解析完嵌套数组后，后面还有元素
						if (toks[i]._token == json_token_type::TOKEN_COMMA) {
							++i;
						} else if (toks[i]._token == json_token_type::TOKEN_ARRAY_END) {
							// 解析完嵌套数组后，后面没有元素
							goto array_end;
						} else {
							// unexpected
							++i;
						}
						continue;
					}
					case json_token_type::TOKEN_STRING:
						jnode->add(new json_simple(t._value, json_flag::STRING));
						break;
					case json_token_type::TOKEN_NUMBER:
						jnode->add(new json_simple(t._value, json_flag::NUMBER));
						break;
					case json_token_type::TOKEN_BOOLEAN:
						jnode->add(new json_simple(t._value, json_flag::BOOLEAN));
						break;
					case json_token_type::TOKEN_NIL:
						jnode->add(new json_simple(t._value, json_flag::NIL));
						break;
					default:
						std::cout << "default" << std::endl;
						break;
				}

				++i;
				// 可能是数组结束
				if (toks[i]._token == json_token_type::TOKEN_ARRAY_END) {
					break;
				}
				++i;
			}
			array_end:
			std::cout << "array----------------------end" << std::endl;
			return jnode;
		}
	};

}

#endif //JSON_PARSER_JSON_LEXER_HPP
