#pragma once

#include <iostream>
#include "JooDelegate/UniCastDelegate.h"

class UniMemberTester
{
public:
	int mData;

	UniMemberTester(int d)
		: mData(d)
	{}

	int Test(int a, int b)
	{
		return a + b + mData;
	}

	int Test2(int a, int b) const
	{
		return a + b + mData;
	}
};

int UniTestFunction(int a, int b)
{
	return a + b;
}

struct UniFunctor
{
	int operator()(int a, int b)
	{
		return a + b;
	}
};

using namespace joo;

DECLARE_UNI_CAST_DELEGATE_RetVal(int, TestDelegate, int, int)


inline void TestUniCastDelegate()
{
	auto lambda = [](int a, int b) ->int { return a + b; };

	TestDelegate delegate;

	delegate.BindStatic(UniTestFunction);
	std::cout << "UniTestFunction2 Called!: " << delegate.Execute(1, 2) << std::endl;

	delegate.BindStatic(UniFunctor());
	std::cout << "UniFunctor Called!: " << delegate.Execute(3, 4) << std::endl;

	delegate.BindLambda(lambda);
	std::cout << "lambda Called!: " << delegate.Execute(5, 6) << std::endl;

	std::shared_ptr<UniMemberTester> tester = std::make_shared<UniMemberTester>(10);
	delegate.BindShared(tester, &UniMemberTester::Test);
	std::cout << "UniMemberTester::Test Called!: " << delegate.Execute(7, 8) << std::endl;

	UniMemberTester* tester2 = new UniMemberTester(20);
	JDelegateHandle handle1 = delegate.BindRaw(tester2, &UniMemberTester::Test);
	std::cout << "UniMemberTester::Test Called!: " << delegate.Execute(9, 10) << std::endl;

	JDelegateHandle handle2 = delegate.BindShared(tester, &UniMemberTester::Test2);
	std::cout << "UniMemberTester::Test2 Called!: " << delegate.Execute(11, 12) << std::endl;

	std::cout << "Handle Event Id to be unbind: " << handle2.GetDelegateEventId() << std::endl;
	delegate.UnBind(handle2);

	std::cout << "After unbind: " << delegate.ExecuteIfBound(13, 14) << std::endl;
}