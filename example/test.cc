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
#include "rpc/basic/singleton_base.hh"
#include "rpc/thread/thread_pool.hh"
#include "rpc/interface/interface.hh"
using std::cout;
using std::endl;
using rpclite::internal::SingletonBase;

/****** Class or Function declearation ******/

void foo();

void foo() {
	printf("foo\n");
}

void bar(int i) {
	printf("bar:%d\n", i);
}

rpc_struct(st, rpc_field(int, a));

int main() {
	rpclite::ThreadPool<2> tp;
	tp.submit(foo);
	tp.submit(bar, 2);
	tp.submit(bar, 5);

	st s;
	s.a = 5;
	return 0;
}



