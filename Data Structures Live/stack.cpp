#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <cstdio> 


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
		size_t max_size;

		int * array;
		bool empty = true;

	public:

		MyStack(size_t max_size=16): max_size(max_size)
		{
			this->array = new int[this->max_size];
		}

		~MyStack() { delete[] this->array; this->array = nullptr; }

		size_t getSize() { return size;  }

		void resize() {
			
			size_t MAX_SIZE = 2 << 15;

			size_t new_size = this->max_size * 2 > MAX_SIZE ? MAX_SIZE : this->max_size*2;

			char msg[256];
			std::sprintf(msg, "Running resize from %d to %d", this->max_size, new_size);

			Logger::WriteMessage(msg);

			int* tmp = new int[new_size];

			if (tmp != nullptr) {
				for (size_t a = 0; a < this->max_size; a++) {
					tmp[a] = this->array[a];
				}

				delete[] this->array;
				this->max_size = new_size;
				this->array = tmp;
			}
		}


		void push(int item) {

			if (this->size == this->max_size) {
				resize();
			} 
			
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

		TEST_METHOD(PushSmallAmountOfElementsToEmptyStack) {

			MyStack stack;

			size_t const  K = 3;

			for (int i=0; i< K; i++)
				stack.push(i);

			auto size = stack.getSize();

			Assert::AreEqual(K, size);
		}


		TEST_METHOD(PushLargeAmountOfElementsToEmptyStack) {

			MyStack stack;

			size_t const  K = 1025;

			for (int i = 0; i < K; i++)
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
