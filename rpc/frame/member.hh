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
//#include "rpc/frame/type_info.hh"

/****** Class or Function declare ******/

namespace rpclite {

class Member {
private:
	// union member
	union {
		int _int;
		long _long;
		unsigned int _uint;
		unsigned long _ulong;
		float _float;
		double _double;
		bool _bool;
	};

	// string member
	std::string _string;

	// type
	//TypeInfo::TypeCode _type;

public:
	// constructor
	/*
	Member() : _type(TypeInfo::TypeCode::INT32) {}
	Member(int v) : _int(v), _type(TypeInfo::TypeCode::INT32) {}
	Member(long v) : _long(v), _type(TypeInfo::TypeCode::INT64) {}
	Member(unsigned int v) : _uint(v), _type(TypeInfo::TypeCode::UINT32) {}
	Member(unsigned long v) : _ulong(v), _type(TypeInfo::TypeCode::UINT64) {}
	Member(float v) : _float(v), _type(TypeInfo::TypeCode::FLOAT) {}
	Member(double v) : _double(v), _type(TypeInfo::TypeCode::DOUBLE) {}
	Member(bool v) : _bool(v), _type(TypeInfo::TypeCode::BOOL) {}
	*/
	Member() {};
	Member(int v) : _int(v) {}

public:
	// TODO: implement subscript operator
	Member& operator[] (size_t pos) {
		return *this;
	}

	// TODO: implement get
	template<class T>
	T get() { return static_cast<T>(0); }

	// member to std::tuple
	template<class T>
	void to_tuple(T& tuple) {}
};



} // rpclite

#endif


