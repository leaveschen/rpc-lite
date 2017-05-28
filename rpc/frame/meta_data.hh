/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: <T_FILENAME>
 * @author: <T_AUTHOR>
 * @date: <T_LASTMOD>
 * @version 1.0
 * @brief:
 **/

#ifndef __RPC_LITE_META_DATA_HH__
#define __RPC_LITE_META_DATA_HH__

/****** Include Library ******/

#include <map>
#include <functional>

/****** Class or Function declare ******/

namespace rpclite {

typedef std::function<void()> method_t;

class MetaData {
private:
	// members
	std::map<int, method_t> _methods;

	MetaData() {}

	inline static MetaData* _inst() {
		static MetaData instance;
		return &instance;
	}

public:
	// interface
	static void set_method(int x, method_t y) {
		_inst()->_methods[x] = y;
	}

	static auto get_method(int x) {
		return _inst()->_methods[x];
	}

};

class Method {
public:
	// constructor & destructor
	Method(int x, method_t y) { MetaData::set_method(x, y); }
	template<class F, class... Args>
	Method(int x, F&& f, Args&&... args) {
		auto y = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		MetaData::set_method(x, y);
	}

	Method(Method const&) = delete;
	Method& operator=(Method const&) = delete;
	~Method() {}

};

} // rpclite

#endif


