/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: function_base.hh
 * @author: leaveschen
 * @date: 2017-05-20, 15:08:36
 * @version 1.0
 * @brief:
 **/

#ifndef __RPC_LITE_FUNCTION_BASE_HH__
#define __RPC_LITE_FUNCTION_BASE_HH__

/****** Include Library ******/

#include <functional>
#include <utility>
#include <type_traits>

/****** Class or Function declear ******/

namespace rpclite {
namespace internal {

template<class F, class... Args>
decltype(auto) invoke(F&& f, Args&&... args) {
	return std::forward<F>(f)(std::forward<Args>(args)...);
}

template<class T, class Type, class T1, class... Args>
decltype(auto) invoke(Type T::* f, T1&& t1, Args&&... args) {
	static_assert(std::is_member_function_pointer<decltype(f)>::value);
	return (std::forward<T1>(t1).*f)(std::forward<Args>(args)...);
}

} // internal
} // rpclite

#endif


