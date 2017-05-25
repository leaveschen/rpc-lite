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

#ifndef __RPC_LITE_INTERFACE_HH__
#define __RPC_LITE_INTERFACE_HH__

/****** Include Library ******/


/****** Class or Function declare ******/

namespace rpclite {

#define rpc_field(type, name) type name;

#define rpc_struct(name, ...) \
	struct name { \
		__VA_ARGS__ \
	};

} // rpclite

#endif


