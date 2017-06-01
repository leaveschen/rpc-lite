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

#ifndef __RPC_LITE_METHOD_HH__
#define __RPC_LITE_METHOD_HH__

/****** Include Library ******/

#include "rpc/basic/function_base.hh"
#include "rpc/frame/member.hh"

/****** Class or Function declare ******/

namespace rpclite {

// method call with uniformed member object & normal function
namespace internal {

template<class F>
Member method_call_helper(F&& f, Member&& arg, func_ret_void const&, func_arg_void const&) {
	f();
	return Member();
}

template<class F>
Member method_call_helper(F&& f, Member&& arg, func_ret_void const&, func_arg_non_void const&) {
	typename func_traits<F>::args_tuple_t args_tuple;
	arg.to_tuple(args_tuple);
	invoke_by_tuple(f, args_tuple);
	return Member();
}

template<class F>
Member method_call_helper(F&& f, Member&& arg, func_ret_non_void const&, func_arg_void const&) {
	auto r = f();
	return Member(r);
}

template<class F>
Member method_call_helper(F&& f, Member&& arg, func_ret_non_void const&, func_arg_non_void const&) {
	typename func_traits<F>::args_tuple_t args_tuple;
	arg.to_tuple(args_tuple);
	auto r = invoke_by_tuple(f, args_tuple);
	return Member(r);
}

} // internal

template<class F>
Member method_call(F&& f, Member&& arg) {
	return method_call_helper(std::forward<F>(f),
			std::forward<Member>(arg),
			typename internal::func_traits<F>::func_return_type_t(),
			typename internal::func_traits<F>::func_args_count_t());
}

// method call with uniformed member object & member function
namespace internal {

template<class C, class R, class C1>
Member method_call_helper(R C::* f, C1&& obj, Member&& arg, func_ret_void const&, func_arg_void const&) {
	(std::forward<C1>(obj).*f)();
	return Member();
}

template<class C, class R, class C1>
Member method_call_helper(R C::* f, C1&& obj, Member&& arg, func_ret_void const&, func_arg_non_void const&) {
	typename func_traits<decltype(f)>::args_tuple_t args_tuple;
	arg.to_tuple(args_tuple);
	invoke_by_tuple(f, obj, args_tuple);
	return Member();
}

template<class C, class R, class C1>
Member method_call_helper(R C::* f, C1&& obj, Member&& arg, func_ret_non_void const&, func_arg_void const&) {
	auto r = (std::forward<C1>(obj).*f)();
	return Member(r);
}

template<class C, class R, class C1>
Member method_call_helper(R C::* f, C1&& obj, Member&& arg, func_ret_non_void const&, func_arg_non_void const&) {
	typename func_traits<decltype(f)>::args_tuple_t args_tuple;
	arg.to_tuple(args_tuple);
	auto r = invoke_by_tuple(f, obj, args_tuple);
	return Member(r);
}

} // internal

template<class C, class R, class C1>
Member method_call(R C::* f, C1&& obj, Member&& arg) {
	static_assert(std::is_member_function_pointer<decltype(f)>::value,
			"method_call target is not a member function without a normal invoke way");
	return method_call_helper(f,
			std::forward<C1>(obj),
			std::forward<Member>(arg),
			typename internal::func_traits<decltype(f)>::func_return_type_t(),
			typename internal::func_traits<decltype(f)>::func_args_count_t());
}

} // rpclite

#endif


