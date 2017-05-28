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
#include "rpc/frame/type_info.hh"

/****** Class or Function declare ******/

namespace rpclite {

class UniType {
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

	// special member
	std::string _string;

	// type
	TypeInfo::TypeCode _type;

public:
	// constructor
	UniType(int v) : _int(v), _type(TypeInfo::TypeCode::INT32) {}
	UniType(long v) : _long(v), _type(TypeInfo::TypeCode::INT64) {}
	UniType(unsigned int v) : _uint(v), _type(TypeInfo::TypeCode::UINT32) {}
	UniType(unsigned long v) : _ulong(v), _type(TypeInfo::TypeCode::UINT64) {}
	UniType(float v) : _float(v), _type(TypeInfo::TypeCode::FLOAT) {}
	UniType(double v) : _double(v), _type(TypeInfo::TypeCode::DOUBLE) {}
	UniType(bool v) : _bool(v), _type(TypeInfo::TypeCode::BOOL) {}
};

} // rpclite

#endif


