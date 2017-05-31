/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: function_base.hh
 * @author: leaveschen
 * @date: 2017-05-20, 20:43:12
 * @version 1.0
 * @brief:
 **/

#ifndef __RPC_LITE_FUNCTION_BASE_HH__
#define __RPC_LITE_FUNCTION_BASE_HH__

/****** Include Library ******/

#include <functional>
#include <utility>
#include <type_traits>
#include <tuple>

/****** Class or Function declare ******/

namespace rpclite {
namespace internal {

// invoke
template<class F, class... Args>
decltype(auto) invoke(F&& f, Args&&... args) {
	return std::forward<F>(f)(std::forward<Args>(args)...);
}

template<class T, class Type, class T1, class... Args>
decltype(auto) invoke(Type T::* f, T1&& t1, Args&&... args) {
	static_assert(std::is_member_function_pointer<decltype(f)>::value,
			"invoke target is not a member function without a normal invoke way");
	return (std::forward<T1>(t1).*f)(std::forward<Args>(args)...);
}

// invoke by tuple
template<class F, class... Args, size_t... I>
decltype(auto) invoke_by_tuple_helper(F&& f,
		std::tuple<Args...>&& args,
		std::index_sequence<I...>) {
	return f(std::get<I>(args)...);
}

template<class F, class... Args>
decltype(auto) invoke_by_tuple(F&& f, std::tuple<Args...>&& args) {
	return invoke_by_tuple_helper(std::forward<F>(f),
			std::forward<std::tuple<Args...>>(args),
			std::index_sequence_for<Args...>{});
}

} // internal
} // rpclite

#endif


