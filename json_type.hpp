//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_TYPE_HPP
#define JSON_PARSER_JSON_TYPE_HPP

#include <unordered_map>

class json_type_base {
	friend class json_lexer;
protected:
	json_type_base *_next;

	virtual std::string get() = 0;

	virtual json_type_base *get(int idx) = 0;

	virtual json_type_base *get(const std::string &_key) = 0;
};


class json_object : public json_type_base {
private:
	std::unordered_map<std::string, json_type_base *> _data;

public:
	std::string get() override {
		return "";
	}

	json_type_base *get(int idx) override {
		return nullptr;
	}

	json_type_base *get(const std::string &_key) override {
		auto iter = _data.find(_key);
		if (iter != _data.end()) {
			return iter->second;
		}
		return nullptr;
	}
};


class json_array : public json_type_base {
private:
	std::vector<json_type_base *> _data;
public:
	std::string get() override {
		return "";
	}

	json_type_base *get(int idx) override {
		if (_data.size() <= idx) {
			return nullptr;
		}
		return _data[idx];
	}

	json_type_base *get(const std::string &_key) override {
		return nullptr;
	}
};


class json_number : public json_type_base {
private:
	std::string _data;

public:
	std::string get() override {
		return _data;
	}

	json_type_base *get(int idx) override {
		return nullptr;
	}

	json_type_base *get(const std::string &_key) override {
		return nullptr;
	}
};


class json_string : public json_type_base {
private:
	std::string _data;

public:
	std::string get() override {
		return _data;
	}

	json_type_base *get(int idx) override {
		return nullptr;
	}

	json_type_base *get(const std::string &_key) override {
		return nullptr;
	}
};


class json_boolean : public json_type_base {
private:
	std::string _data;

public:
	std::string get() override {
		return _data;
	}

	json_type_base *get(int idx) override {
		return nullptr;
	}

	json_type_base *get(const std::string &_key) override {
		return nullptr;
	}
};


class json_null : public json_type_base {
private:
	std::string _data;

public:
	std::string get() override {
		return _data;
	}

	json_type_base *get(int idx) override {
		return nullptr;
	}

	json_type_base *get(const std::string &_key) override {
		return nullptr;
	}
};


#endif //JSON_PARSER_JSON_TYPE_HPP
