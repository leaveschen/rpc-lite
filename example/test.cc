/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: test.cc
 * @author: leaveschen
 * @date: 2017-05-20, 20:25:39
 * @version 1.0
 * @brief:
 **/

/****** Include Library ******/

#include <iostream>
#include <functional>
#include <map>
#include "rpc/thread/thread_pool.hh"
#include "rpc/interface/interface.hh"
#include "rpc/frame/meta_data.hh"
#include "rpc/basic/function_base.hh"
#include "rpc/frame/method.hh"
using std::cout;
using std::endl;

/****** Class or Function declearation ******/

//rpclite::Method m(5, 7);
void foo();
void bar(int i);
rpclite::Method m(5, std::function<void()>(foo));

void foo() {
	printf("foo\n");
}

void foo2() {
	printf("foo2\n");
}

void bar(int i) {
	printf("bar:%d\n", i);
}

void baz(float& i) {
	i *= 2;
}

struct S {
	void foo() {
		printf("S::foo\n");
	}
};

rpc_struct(st, rpc_field(int, a));

int main() {
	//rpclite::ThreadPool<2> tp;
	//tp.submit(foo);
	//tp.submit(bar, 2);
	//tp.submit(bar, 5);

	using rpclite::internal::invoke_by_tuple;
	invoke_by_tuple(foo, std::tuple<>());
	invoke_by_tuple(bar, std::tuple<int>{1});

	float i = 2.3;
	invoke_by_tuple(baz, std::tuple<float&>{i});
	cout << "baz:" << i << endl;

	S s;
	invoke_by_tuple(&S::foo, s, std::tuple<>());
	//rpclite::internal::invoke(&S::foo, s);

	rpclite::method_call(&foo2, rpclite::Member());
	rpclite::method_call(&S::foo, s, rpclite::Member());

	using rpclite::internal::func_traits;
	std::cout << "is return void:" << std::is_same<rpclite::internal::func_ret_void,
		func_traits<decltype(bar)>::func_return_type_t>::value << endl;
	std::cout << "is args none:" << std::is_same<rpclite::internal::func_arg_void,
		func_traits<decltype(&foo)>::func_args_count_t>::value << endl;

	//rpclite::MetaData::set_method(5, 10);
	//cout << rpclite::MetaData::get_method(5) << endl;
	return 0;
}



