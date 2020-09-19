#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructuresLive
{




	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}


	class MyStack {


		size_t size = 0;
		int array[16];
		bool empty = true;

	public:
		size_t getSize() { return size;  }
		void push(int item) {
			array[size] = item;
			size++;
		}

		int pop() {
			
			if (!size)
				throw std::out_of_range("stack is empty!");

			size--;
			
			return array[size];
		}
	};

	TEST_CLASS(MyStackTest)
	{
	public:
		
		TEST_METHOD(CreateEmptyStack)
		{
			MyStack stack;
			auto size = stack.getSize();
			Assert::AreEqual((size_t)0, size);
		}

		TEST_METHOD(PushOneElementToEmptyStack) {
			MyStack stack;
			stack.push(1);
			auto size = stack.getSize();
			Assert::AreEqual((size_t)1, size);
		}

		TEST_METHOD(PopOneElementFromOneElementStack) {
			MyStack stack;
			stack.push(100);
			auto value = stack.pop();
			Assert::AreEqual(100, value);
		}

		TEST_METHOD(PopOneElementFromEmptyStack) {

			auto func = [] { 
				MyStack stack;
				stack.push(100);
				auto value = stack.pop();
				auto value2 = stack.pop();
			};

			Assert::ExpectException<std::out_of_range>(func);			
		}

		TEST_METHOD(PushTenElementsToEmptyStack) {

			MyStack stack;

			size_t const  K = 3;

			for (int i=0; i< K; i++)
				stack.push(i);

			auto size = stack.getSize();

			Assert::AreEqual(K, size);
		}


		TEST_METHOD(PopThreeElementsFromStack) {

			MyStack stack;

			int const  K = 3;

			for (int i = 0; i < K; i++)
				stack.push(i);

			for (int i = 0; i < 3; i++)
				Assert::AreEqual(K - (i + 1), stack.pop());
		}



	};
}
