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
		SIMPLE
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

		virtual void add(const std::string &key, json_type_base *jnode) = 0;

		virtual void add(json_type_base *jonde) = 0;

		json_flag type() const {
			return _flag;
		}

		virtual ~json_type_base() = default;
	};


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
		explicit json_simple(std::string data) : json_type_base(json_flag::SIMPLE), _data(std::move(data)) {
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

		json_type_base *json_root() const {
			return _jr;
		}


		/**
		 * 解析str，并将结果输出到文件
		 * @param file_path
		 * @param mode
		 */
		void to_file(const std::string &file_path, std::ios_base::openmode mode) {
			std::ofstream ifs(file_path, mode);

			if (ifs.is_open()) {
				//std::cout << "-----------------------" << std::endl;
				inner(_jr, 1);
			} else {
			}
		}

		void inner(json_type_base *jr, int indent) {
			if (jr->type() == json_flag::OBJECT) {
				auto tmp = (json_object *) jr;
				std::cout << "{\n";
				for (auto &e : tmp->_data) {
					for (int i = 0; i < indent; ++i) {
						std::cout << "  ";
					}
					std::cout << e.first << ": ";
					inner(e.second, indent * 2);
				}
				std::cout << "}" << std::endl;
			} else if (jr->type() == json_flag::ARRAY) {
				auto tmp = (json_array *) jr;
				std::cout << "[";
				for (auto &e : tmp->_data) {
					inner(e, indent * 2);
				}
				std::cout << "]" << std::endl;
			} else {

				std::cout << jr->get() << " ";
			}
		}

		void to_file(const std::string &file_path) {
			to_file(file_path, std::ios_base::in | std::ios_base::trunc);
		}

	private:
		void destroy() {
			if (_ref_ptr && *_ref_ptr <= 1) {
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
