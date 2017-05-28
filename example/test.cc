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

rpc_struct(st, rpc_field(int, a));

int main() {
	//rpclite::ThreadPool<2> tp;
	//tp.submit(foo);
	//tp.submit(bar, 2);
	//tp.submit(bar, 5);

	st s;
	s.a = 5;

	//rpclite::MetaData::set_method(5, 10);
	//cout << rpclite::MetaData::get_method(5) << endl;
	rpclite::MetaData::get_method(5)();
	return 0;
}



