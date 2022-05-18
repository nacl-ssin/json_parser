//
// Created by 26372 on 2022/5/5.
//

#ifndef JSON_PARSER_JSON_TYPE_HPP
#define JSON_PARSER_JSON_TYPE_HPP

#include <unordered_map>

namespace nacl {

	enum class json_flag {
		ARRAY,
		OBJECT,
		STRING,
		NIL,
		NUMBER,
		BOOLEAN
	};


	class json_type_base;


	struct json_data {
		std::string _str;
		json_type_base *_jnode;

		json_data() : _jnode(nullptr) {
		}

		json_data(json_type_base *jnode) : _jnode(jnode) {
		}

		json_data(std::string str, json_type_base *jnode) : _str(std::move(str)), _jnode(jnode) {
		}
	};


	class json_type_base {
		friend class json_item;

	protected:
		json_flag _flag;

	public:
		explicit json_type_base(json_flag flag) : _flag(flag) {
		}

		virtual std::string get() = 0;

		virtual json_type_base *get(int idx) = 0;

		virtual json_type_base *get(const std::string &_key) = 0;

		virtual void add(const json_data &jdata) = 0;

		json_flag type() const {
			return _flag;
		}

		virtual ~json_type_base() = default;
	};


	// object
	class json_object : public json_type_base {
	public:
		std::unordered_map<std::string, json_type_base *> _data;

	public:
		json_object() : json_type_base(json_flag::OBJECT) {

		}

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

		void add(const json_data &jdata) override {
			_data[jdata._str] = jdata._jnode;
		}

		~json_object() override {
			for (auto &e : _data) {
				delete e.second;
				e.second = nullptr;
			}
		}
	};


	// array
	class json_array : public json_type_base {
	public:
		std::vector<json_type_base *> _data;

	public:
		json_array() : json_type_base(json_flag::ARRAY) {

		}

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

		void add(const json_data &jdata) override {
			_data.push_back(jdata._jnode);
		}

		~json_array() override {
			for (auto &e : _data) {
				delete e;
				e = nullptr;
			}
		}
	};


	// string/boolean/null/number
	class json_simple : public json_type_base {
	private:
		std::string _data;

	public:
		explicit json_simple(std::string data, json_flag flag) : json_type_base(flag), _data(std::move(data)) {
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

		void add(const json_data &jdata) override {
			_data = jdata._str;
		}
	};


	class json_item {
		friend class json_lexer;

		using ref_type = int;
	private:
		ref_type *_ref_ptr;
		json_type_base *_jr;

		json_item(json_type_base *jr, int ref_num) : _jr(jr), _ref_ptr(new ref_type(ref_num)) {
		}

	public:
		json_item(json_type_base *jr) : _jr(jr), _ref_ptr(nullptr) {
		}

		json_item(const json_item &ji) : _jr(ji._jr), _ref_ptr(ji._ref_ptr) {
			if (_ref_ptr) {
				++*_ref_ptr;
			}
		}

		json_item &operator=(json_item ji) {
			std::swap(_jr, ji._jr);
			std::swap(_ref_ptr, ji._ref_ptr);
			return *this;
		}

		~json_item() {
			destroy();
		}

		std::string get_value(const std::string &key) const {
			auto jn = _jr->get(key);
			if (jn) {
				return jn->get();
			}
			return "";
		}

		std::string get_element(int idx) const {
			auto jn = _jr->get(idx);
			if (jn) {
				return jn->get();
			}
			return "";
		}

		json_item next(const std::string &key) const {
			return _jr->get(key);
		}

		json_item next(int idx) const {
			return _jr->get(idx);
		}

		bool is_ary() const {
			return _jr->_flag == json_flag::ARRAY;
		}

		bool is_obj() const {
			return _jr->_flag == json_flag::OBJECT;
		}

		bool contains(const std::string &key) {
			return _jr->get(key) != nullptr;
		}

		void to_file(const std::string &file_path) {
			to_file(file_path, std::ios_base::in | std::ios_base::trunc);
		}


	private:
		/**
		 * 解析str，并将结果输出到文件
		 * @param file_path
		 * @param mode
		 */
		void to_file(const std::string &file_path, std::ios_base::openmode mode) {
			std::ofstream ifs(file_path, mode);
			if (ifs.is_open()) {
				std::string format_str;
				inner(_jr, format_str, false, 1, 0);
				int indent = 0;
				std::string buf;
				for (auto c : format_str) {
					if (c == ']' || c == '}') {
						indent -= 4;
						//std::cout << std::endl;
						buf += "\n";
						for (int i = 0; i < indent; ++i) {
							buf += " ";
							//std::cout << " ";
						}
					}

					//std::cout << c;
					buf += c;
					if (c == ':') {
						//std::cout << " ";
						buf += " ";
					}
					if (c == '[' || c == '{' || c == ',') {
						if (c == '[' || c == '{') {
							indent += 4;
						}
						//std::cout << std::endl;
						buf += "\n";
						for (int i = 0; i < indent; ++i) {
							//std::cout << " ";
							buf += " ";
						}
					}

					if (buf.size() >= 512) {
						ifs << buf;
						buf.clear();
					}
				}
				if (!buf.empty()) {
					ifs << buf;
				}
				//std::cout << buf << std::endl;
				//std::cout << std::endl;

			} else {
			}
		}

		void inner(json_type_base *jr, std::string &format_str, bool is_end, int depth, int indent) {
			if (jr->type() == json_flag::OBJECT) {
				auto tmp = (json_object *) jr;
				format_str.push_back('{');
				//std::cout << "{\n";
				//for (int i = 0; i < indent; ++i)
				//	std::cout << " ";
				int i = 0;
				for (auto &e : tmp->_data) {
					auto iter = tmp->_data.begin();
					//std::cout << e.first << ": ";
					format_str.append("\"" + e.first + "\"" + ":");
					inner(e.second, format_str, i == tmp->_data.size() - 1, depth + 1, indent += 2);
					i++;
				}
				//std::cout << "} ";
				format_str.push_back('}');
				if (depth != 1 && !is_end) {
					format_str.push_back(',');
					//std::cout << ", ";
				}
			} else if (jr->type() == json_flag::ARRAY) {
				auto tmp = (json_array *) jr;
				//std::cout << "[";
				//for (int i = 0; i < indent; ++i)
				//	std::cout << " ";
				format_str.push_back('[');
				for (int i = 0; i < tmp->_data.size(); ++i) {
					auto iter = tmp->_data.begin() + i;
					inner(*iter, format_str, iter == tmp->_data.end() - 1, depth + 1, indent += 2);
				}
				//std::cout << "]";
				format_str.push_back(']');
				if (depth != 1 && !is_end) {
					//std::cout << ",";
					format_str.push_back(',');
				}
			} else {
				//std::cout << jr->get() << " ";
				std::string str = jr->get();
				if (jr->_flag == json_flag::STRING) {
					format_str += "\"" + str + "\"";
				} else {
					format_str += str;
				}
				if (!is_end) {
					//std::cout << ", ";
					format_str.push_back(',');
				}
			}
		}

		void destroy() {
			if (_ref_ptr && *_ref_ptr <= 1) {
				std::cout << "destroy" << std::endl;
				delete _jr;
				delete _ref_ptr;
				_jr = nullptr;
				_ref_ptr = nullptr;
			}
			if (_ref_ptr) {
				--*_ref_ptr;
			}
		}
	};
}

#endif //JSON_PARSER_JSON_TYPE_HPP
