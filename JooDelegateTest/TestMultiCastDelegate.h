#pragma once

#include <iostream>
#include "JooDelegate/MultiCastDelegate.h"

class MultiMemberTester
{
public:
	int mData;

	MultiMemberTester(int d)
		: mData(d)
	{}

	void Test(int a, int b)
	{
		std::cout << "MultiMemberTester::Test Called!: " << a + b + mData << std::endl;
	}

	void Test2(int a, int b) const
	{
		std::cout << "MultiMemberTester::Test2 Called!: " << a + b + mData << std::endl;
	}
};

void MultiTestFunction(int a, int b)
{
	std::cout << "MultiTestFunction Called!: " << a + b << std::endl;
}

struct MultiFunctor
{
	void operator()(int a, int b)
	{
		std::cout << "MultiFunctor Called!: " << a + b << std::endl;
	}
};

using namespace joo;

DECLARE_MULTI_CAST_DELEGATE(MultiCastDelegate, int, int)

void TestMultiCastDelegate()
{
	int c = 10;
	auto lambda = [c](int a, int b) {std::cout << "Lambda Called!: " << a + b + c << std::endl; };
	std::shared_ptr<MultiMemberTester> tester = std::make_shared<MultiMemberTester>(10);
	MultiMemberTester* tester2 = new MultiMemberTester(20);

	MultiCastDelegate delegate;
	
	delegate.AddStatic(MultiTestFunction);
	delegate.AddStatic(MultiFunctor());
	delegate.AddLambda(lambda);
	auto handle = delegate.AddShared(tester, &MultiMemberTester::Test);
	delegate.AddRaw(tester2, &MultiMemberTester::Test2);

	delegate.Broadcast(1, 2);

	std::cout << "--------------Remove shared---------------" << std::endl;
	delegate.Remove(handle);
	delegate.Broadcast(3, 4);

	std::cout << "--------------Remove All------------------" << std::endl;
	delegate.RemoveAll();

	delegate.Broadcast(5, 6);
}