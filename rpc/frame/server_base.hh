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

#ifndef __RPC_LITE_SERVER_BASE_HH__
#define __RPC_LITE_SERVER_BASE_HH__

/****** Include Library ******/

#include <map>
#include <functional>
#include "rpc/thread/thread_pool.hh"

/****** Class or Function declare ******/

namespace rpclite {

class ServerBase {
private:
	ThreadPool<2> _thread_pool;

public:
	// constructor & destructor
	ServerBase() {}
	ServerBase(ServerBase const&) = delete;
	ServerBase& operator=(ServerBase const&) = delete;
	~ServerBase() {}

};

}

#endif


