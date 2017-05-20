/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: singleton_base.hh
 * @author: leaveschen
 * @date: 2017-05-20, 20:43:25
 * @version 1.0
 * @brief:
 **/

#ifndef __RPC_LITE_SINGLETON_BASE_HH__
#define __RPC_LITE_SINGLETON_BASE_HH__

/****** Include Library ******/

#include <memory>

/****** Class or Function declare ******/

namespace rpclite {
namespace internal {

template<class T>
class SingletonBase {
private:
	// members
	std::shared_ptr<T> _p;

	// constructor
	SingletonBase() : _p(nullptr) { _p = std::make_shared<T>(); }

	// inner instance
	inline static SingletonBase<T>* _inst() {
		static SingletonBase<T> instance;
		return &instance;
	}

public:
	// interface
	static std::shared_ptr<T> instance() {
		return _inst()->_p;
	}
};

} // internal
} // rpclite

#endif


