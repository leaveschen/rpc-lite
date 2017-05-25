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

#ifndef __RPC_LITE_TYPE_INFO_HH__
#define __RPC_LITE_TYPE_INFO_HH__

/****** Include Library ******/

#include <string>

/****** Class or Function declare ******/

namespace rpclite {

class TypeInfo final {
public:
	enum class TypeCode : int {
		VOID = 0,
		INT32,
		INT64,
		UINT32,
		UINT64,
		FLOAT,
		DOUBLE,
		BOOL,
		STRING
	};

	enum class Restrict : int {
		VOID = 0,
		REF,
		PTR,
		CONST
	};

private:
	TypeCode _typecode;
	Restrict _restrict;

	explicit TypeInfo(TypeInfo typecode, Restrict restrict) :
		_typecode(typecode), _restrict(restrict) {}

	std::string signature() const {
		string sign;
		switch (_typecode) {
			case TypeCode::VOID: sign = "v"; break;
			case TypeCode::INT32: sign = "i"; break;
			case TypeCode::INT64: sign = "l"; break;
			case TypeCode::UINT32: sign = "u"; break;
			case TypeCode::UINT64: sign = "ul"; break;
			case TypeCode::FLOAT: sign = "f"; break;
			case TypeCode::DOUBLE: sign = "d"; break;
			case TypeCode::BOOL: sign = "b"; break;
			case TypeCode::STRING: sign = "s"; break;
		}
		return std::move(sign);
	}

};

template<class T>
struct TypeCreator;

template<>
struct TypeCreator<int> {
	static TypeInfo create() { return TypeInfo(TypeInfo::TypeCode::INT32, TypeInfo::Restrict::VOID); }
};

template<>
struct TypeCreator<long> {
	static TypeInfo create() { return TypeInfo(TypeInfo::TypeCode::INT64, TypeInfo::Restrict::VOID); }
};

template<>
struct TypeCreator<unsigned int> {
	static TypeInfo create() { return TypeInfo(TypeInfo::TypeCode::UINT32, TypeInfo::Restrict::VOID); }
};

// TODO: complete the other case...

} // rpclite

#endif


