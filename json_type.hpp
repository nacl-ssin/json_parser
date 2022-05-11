//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_TYPE_HPP
#define JSON_PARSER_JSON_TYPE_HPP

#include <unordered_map>

class json_type_base {
	friend class json_lexer;

public:
	virtual std::string get() = 0;

	virtual json_type_base *get(int idx) = 0;

	virtual json_type_base *get(const std::string &_key) = 0;

	virtual void add(const std::string &key, json_type_base *jnode) = 0;

	virtual void add(json_type_base *jonde) = 0;

	virtual ~json_type_base() = default;
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

	void add(const std::string &key, json_type_base *jnode) override {
		_data[key] = jnode;
	}

	void add(json_type_base *jnode) override {

	}

	~json_object() override {
		for (auto &e : _data) {
			delete e.second;
			e.second = nullptr;
		}
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

	void add(json_type_base *jnode) override {
		_data.push_back(jnode);
	}

	void add(const std::string &key, json_type_base *jnode) override {

	}

	~json_array() override {
		for (auto &e : _data) {
			delete e;
			e = nullptr;
		}
	}
};


class json_simple : public json_type_base {
private:
	std::string _data;

public:
	explicit json_simple(std::string data) : _data(std::move(data)) {
	}


	std::string get() override {
		return _data;
	}

	json_type_base *get(int idx) override {
		return nullptr;
	}

	json_type_base *get(const std::string &_key) override {
		return nullptr;
	}

	void add(const std::string &key, json_type_base *jnode) override {

	}

	void add(json_type_base *jonde) override {

	}
};


class json_node {
private:
	json_type_base *_jr;

public:
	json_node() : _jr(nullptr) {
	}

	json_node(json_type_base *jr) : _jr(jr) {
	}

	std::string get() {
		return _jr->get();
	}

	json_node get(const std::string &key) {
		return _jr->get(key);
	}

	json_node get(int idx) {
		return _jr->get(idx);
	}

	void destroy() {
		delete _jr;
	}
};

#endif //JSON_PARSER_JSON_TYPE_HPP
