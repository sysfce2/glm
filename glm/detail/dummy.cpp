///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file glm/core/dummy.cpp
/// @date 2011-01-19 / 2011-06-15
/// @author Christophe Riccio
///
/// GLM is a header only library. There is nothing to compile. 
/// dummy.cpp exist only a wordaround for CMake file.
///////////////////////////////////////////////////////////////////////////////////

#define GLM_MESSAGES
#include "../glm.hpp"

#include <limits>
/*
#if(GLM_ARCH & GLM_ARCH_SSE2)

#include <vector>
#include <array>
#include <cstdio>
#include <functional>
#include <thread>
#include <mutex>

struct float4
{
public: 
	typedef void (base::*method)() const;

	method do_method;

	void (base::*do_print)() const;

	void call_print()
	{
		do_print = &base::print;
		(this->*do_print)();
	}

	void call_method()
	{
		do_method = &base::print;
		(this->*do_method)();
	}

	virtual void print() const {printf("B\n");}
};

template <typename T>
class tmpl
{
public:
	template <typename U>
	void print(U const & u) const
	{
		printf("tmpl::print()\n");
	}
};

class derived : public base
{
public: 
	virtual void print(){printf("D\n");}
};

template<typename T>
void test_tmpl()
{
	tmpl<T> Tmpl;
	Tmpl.template print<float>(76.f);
}

int test_class()
{
	base Base;
	Base.print();

	derived Derived;
	Derived.print();

	base & Ref = Derived;
	Ref.print();

	base * Ptr = &Derived;
	Ptr->print();

	auto Auto = std::bind(&derived::print, Derived);
	Auto();

	Base.do_print = &base::print;
	(Base.*Base.do_print)();
	Base.call_print();
	Base.call_method();
	(Base.*Base.do_method)();

	return 0;
}

void bind_print(int i)
{
	printf("bind_print: %d\n", i);
}

void bind_print2(int i, int j)
{
	printf("bind_print2: %d, %d\n", i, j);
}

using namespace std::placeholders; 

int test_bind()
{
	auto A = std::bind(bind_print, _1);
	A(76);

	auto B = std::bind(bind_print2, _1, _2);
	B(76, 82);

	return 0;
}

int test()
{
	std::vector<int> v;
	for(int i = 0; i < 5; ++i)
		v.push_back(i);

	std::vector<int>::iterator itA = v.begin();
	std::vector<int>::iterator itB = v.begin();

	std::vector<int>::iterator itX = itA++;
	std::vector<int>::iterator itY = ++itB;

	return 0;
}

class workerA
{
public:
	void operator()() const
	{
		printf("workerA\n");
	}

private:
	std::vector<int> Lists;
};

class workerB
{
public:
	void run()
	{
		printf("workerB\n");
	}
};

int foo(int val) 
{ 
	int n=0; 
	while (val) 
	{ 
		val &= val-1; 
		n++;
	} 
	return n; 
}

class workerMutex
{
public:
	workerMutex
	(
		int const Id,
		std::vector<std::pair<int, std::size_t>> & Lists,
		std::mutex & Mutex
	) :
		Id(Id),
		Lists(Lists),
		Mutex(Mutex)
	{}

	bool insert()
	{
		Mutex.lock();
		std::size_t Size = Lists.size();
		Lists.push_back(std::pair<int, std::size_t>(this->Id, Size));
		Mutex.unlock();

		return Size < 1000;
	}

	void operator()()
	{
		printf("workerMutex\n");
		while(this->insert());
	}

private:
	int const Id;
	std::vector<std::pair<int, std::size_t>> & Lists;
	std::mutex & Mutex;
};

int test_mutex()
{
	std::mutex Mutex;
	std::vector<std::pair<int, std::size_t>> Lists;

	workerMutex WorkerA(1, Lists, Mutex);
	workerMutex WorkerB(2, Lists, Mutex);

	std::thread ThreadA(std::ref(WorkerA));
	std::thread ThreadB(std::ref(WorkerB));

	ThreadA.join();
	ThreadB.join();

	for(std::size_t i = 0; i < Lists.size(); ++i)
		printf("(%d, %d), ", Lists[i].first, Lists[i].second);

	return 0;
}

int main()
{
	test_mutex();

	{
		int A = foo(0);
		int B = foo(1);
		int C = foo(2);
		int D = foo(3);
		int E = foo(4);
		int F = foo(5);
		int G = foo(6);
		int H = foo(7);
		int I = foo(8);
		int J = foo(9);
	}

	workerA WorkerA;
	workerB WorkerB;

	std::thread ThreadA(std::ref(WorkerA));
	std::thread ThreadB(&workerB::run, &WorkerB);

	ThreadA.join();
	ThreadB.join();

	//int t = 2 * 3 % 10;

	int Error(0);

	{
		int* a[10];
		int (*b)[10];
		int c;
		int d[10];
		int e[5][10];
		int (*f)[5][10];

		a[0] = &c;
		b = &d;
		b = &e[0];
		f = &e;
	}

	test();
	test_class();
	test_bind();
	test_tmpl<float>();

	{
		int (*ptr)[10];
		int* gni[10];

		int Array[10];

		ptr = &Array;
		gni[0] = &Array[0];
	}

	{
		int s1 = 3;
		int s2 = 3;

		int sA = s1++;
		int sB = ++s2;

		glm::ivec2 v1(3);
		glm::ivec2 v2(3);

		glm::ivec2 vA = v1++;
		glm::ivec2 vB = ++v2;

		Error += 0;
	}

	{
		int x = -2<<2;

		int j = 2;
		printf("%d, %d\n", ++j, ++j);

		Error += 0;

		char c=48;
		int i, mask=01;
		for(i=1; i<=5; i++)
		{
			printf("%c", c|mask);
			mask = mask<<1;
		}
	}
#endif//GLM_ARCH
*/

template <class T = int>
class C;

template <class T>
class C
{
public:
	T value;
};

int main()
{
/*
#	if(GLM_ARCH & GLM_ARCH_SSE2)
		test_simd();
#	endif
*/ 

	C<> c;

	return 0;
}