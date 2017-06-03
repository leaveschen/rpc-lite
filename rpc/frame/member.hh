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

#ifndef __RPC_LITE_UNITYPE_HH__
#define __RPC_LITE_UNITYPE_HH__

/****** Include Library ******/

#include <string>
#include <memory>
#include <vector>
#include <tuple>
//#include "rpc/frame/type_info.hh"

/****** Class or Function declare ******/

namespace rpclite {

class Member {
public:
	enum class TypeCode : int {
		VOID = 0,
		I32,
		I64,
		U32,
		U64,
		FLOAT,
		DOUBLE,
		BOOL,
		STRING,
		VECTOR,
		ARGS,
	};

public:
	// type code
	TypeCode _type;

	// union member
	union {
		int32_t _i32;
		int64_t _i64;
		uint32_t _u32;
		uint64_t _u64;
		float _float;
		double _double;
		bool _bool;
	};

	// string member
	std::string _string;

	// vector member
	std::vector<std::shared_ptr<Member>> _vector;

	// args member
	std::vector<std::shared_ptr<Member>> _args;

public:
	// constructor void type
	Member() : _type(TypeCode::VOID) {}

	// constructor basic type
	Member(int32_t v) : _type(TypeCode::I32), _i32(v) {}
	Member(int64_t v) : _type(TypeCode::I64), _i64(v) {}
	Member(uint32_t v) : _type(TypeCode::U32), _u32(v) {}
	Member(uint64_t v) : _type(TypeCode::U64), _u64(v) {}
	Member(float v) : _type(TypeCode::FLOAT), _float(v) {}
	Member(double v) : _type(TypeCode::DOUBLE), _double(v) {}
	Member(bool v) : _type(TypeCode::BOOL), _bool(v) {}

	// constructor string type
	Member(std::string const& v) : _type(TypeCode::STRING), _string(v) {}
	Member(char* const v) : _type(TypeCode::STRING), _string(v) {}

	// constructor vector type
	template<class T>
	Member(std::vector<T> const& v) : _type(TypeCode::VECTOR) {
		for (auto& one : v) { _vector.emplace_back(std::make_shared<Member>(one)); }
	}

	// XXX: constructor args type
	Member(std::initializer_list<Member> v) : _type(TypeCode::ARGS) {
		// TODO: here use default copy constructor...
		for (auto& one : v) { _args.emplace_back(std::make_shared<Member>(one)); }
	}

public:
	// get type code
	int type() { return static_cast<int>(_type); }

public:
	/* operator [] */
	Member& operator[] (size_t pos) {
		if (_type == TypeCode::VECTOR) {
			return *_vector[pos];
		} else if (_type == TypeCode::ARGS) {
			return *_args[pos];
		} else {
			throw std::logic_error("call Member operator[] neither vector nor args type");
		}
	}

	// TODO: implement get
private:
	struct _get_tag {};

public:
	template<class T>
	T get(std::enable_if_t<std::is_same<int, T>::value, _get_tag> = _get_tag()) {
		return _i32;
	}

	template<class T>
	T get(std::enable_if_t<!std::is_same<int, T>::value, _get_tag> = _get_tag()) {
		return static_cast<T>(0);
	}

};



} // rpclite

#endif


