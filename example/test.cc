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

void bar(int i) {
	printf("bar:%d\n", i);
}

void baz(float& i) {
	i *= 2;
}

rpc_struct(st, rpc_field(int, a));

int main() {
	//rpclite::ThreadPool<2> tp;
	//tp.submit(foo);
	//tp.submit(bar, 2);
	//tp.submit(bar, 5);

	st s;
	s.a = 5;

	using rpclite::internal::invoke_by_tuple;
	invoke_by_tuple(foo, std::tuple<>());
	invoke_by_tuple(bar, std::tuple<int>{1});

	float i = 2.3;
	invoke_by_tuple(baz, std::tuple<float&>{i});
	cout << "baz:" << i << endl;

	//rpclite::MetaData::set_method(5, 10);
	//cout << rpclite::MetaData::get_method(5) << endl;
	return 0;
}



