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

	std::string _string;
};

} // rpclite

#endif


