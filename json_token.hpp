#include <utility>

//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_TOKEN_HPP
#define JSON_PARSER_JSON_TOKEN_HPP

enum class json_token_type {
	OBJECT_BEGIN,
	OBJECT_END,
	ARRAY_BEGIN,
	ARRAY_END,
	COMMA,
	COLON,
	STRING,
	NUMBER,
	NIL,
	BOOLEAN,
};

struct token {
	std::string _value;
	json_token_type _token;

	token() {}

	token(std::string val, json_token_type token) : _value(std::move(val)), _token(token) {}
};


#endif //JSON_PARSER_JSON_TOKEN_HPP
