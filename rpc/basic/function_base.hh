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

template<class C, class R, class C1, class... Args, size_t... I>
decltype(auto) invoke_by_tuple_helper(R C::* f,
		C1&& obj,
		std::tuple<Args...>&& args,
		std::index_sequence<I...>) {
	static_assert(std::is_member_function_pointer<decltype(f)>::value,
			"invoke target is not a member function without a normal invoke way");
	return (std::forward<C1>(obj).*f)(std::get<I>(args)...);
}

template<class F, class... Args>
decltype(auto) invoke_by_tuple(F&& f, std::tuple<Args...>&& args) {
	return invoke_by_tuple_helper(std::forward<F>(f),
			std::forward<std::tuple<Args...>>(args),
			std::index_sequence_for<Args...>{});
}

template<class C, class R, class C1, class... Args>
decltype(auto) invoke_by_tuple(R C::* f, C1&& obj, std::tuple<Args...>&& args) {
	return invoke_by_tuple_helper(f,
			std::forward<C1>(obj),
			std::forward<std::tuple<Args...>>(args),
			std::index_sequence_for<Args...>{});
}

// function traits basis
struct func_ret_void {};
struct func_ret_non_void {};
struct func_arg_void {};
struct func_arg_non_void {};

// function traits, return type traits
template<class T>
struct func_return_type_traits { typedef func_ret_non_void type; };

template<>
struct func_return_type_traits<void> { typedef func_ret_void type; };

// function traits, args count traits
template<size_t N>
struct func_args_count_traits { typedef func_arg_non_void type; };

template<>
struct func_args_count_traits<0> { typedef func_arg_void type; };

// function traits
template<class F>
struct func_traits : func_traits<decltype(&F::operator())> {};

template<class C, class R, class... Args>
struct func_traits<R(C::*)(Args...)> : func_traits<R(Args...)> {};

template<class C, class R, class... Args>
struct func_traits<R(C::*)(Args...) const> : func_traits<R(Args...)> {};

template<class R, class... Args>
struct func_traits<R(*)(Args...)> : func_traits<R(Args...)> {};

template<class R, class... Args>
struct func_traits<R(Args...)> {
	typedef R result_t;
	typedef std::tuple<Args...> args_tuple_t;
	constexpr static size_t args_c = sizeof...(Args);

	typedef typename func_return_type_traits<result_t>::type func_return_type_t;
	typedef typename func_args_count_traits<args_c>::type func_args_count_t;
};


} // internal
} // rpclite

#endif


