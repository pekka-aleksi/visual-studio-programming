#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include <cstdio> 


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructuresLive
{

	class MyQueue {

		void resize() {

			size_t MAX_SIZE = 2 << 15;
			size_t new_size = this->max_size * 2 > MAX_SIZE ? MAX_SIZE : this->max_size * 2;

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


		size_t max_size = 2;
		
		size_t left = 0;
		size_t right = 1;

		int* array = nullptr;
	public:

		MyQueue() {
			this->array = new int[this->max_size];
		}
		~MyQueue() { delete[] this->array; this->array = nullptr; }

		int remove() {

			auto val = this->array[this->left];
			this->leftplus();
			
			return val;
		}
	
		void add(int x) {
			
			if (this->getSize() >= this->max_size) 
				resize();

			this->array[this->right - 1] = x;
			this->rightplus();
		}


		size_t getSize() { return this->right - (this->left + 1); }


		void leftplus() {
			this->setLeftRight(this->left + 1, this->right);
		}

		void rightplus() {
			this->setLeftRight(this->left, this->right+1);
		}


		void setLeftRight(size_t left, size_t right) {
			this->left = left;
			this->right = right;
		}


	};

	TEST_CLASS(MyQueueTest)
	{
	public:

		TEST_METHOD(CreateEmptyQueue)
		{
			MyQueue queue;
			Assert::AreEqual((size_t)0, queue.getSize());
		}

		TEST_METHOD(AddOneElementToQueue) {
			MyQueue queue;
			queue.add(1);
			Assert::AreEqual((size_t)1, queue.getSize());
		}

		TEST_METHOD(RemoveElementFromQueue) {
			MyQueue queue;
			queue.add(55);
			auto val = queue.remove();

			Assert::AreEqual((size_t)0, queue.getSize());
			Assert::AreEqual(55, val);
		}


		TEST_METHOD(Add3ElementsToQueue) {
			MyQueue queue;
			queue.add(1);
			queue.add(2);
			queue.add(3);
			Assert::AreEqual((size_t)3, queue.getSize());
		}

		TEST_METHOD(Remove3ElementsFromTheQueueAllInOne) {
			MyQueue queue;
			queue.add(1);
			queue.add(2);
			queue.add(3);
			
			Assert::AreEqual(1, queue.remove());
			Assert::AreEqual((size_t)2, queue.getSize());

			Assert::AreEqual(2, queue.remove());
			Assert::AreEqual((size_t)1, queue.getSize());

			Assert::AreEqual(3, queue.remove());
			Assert::AreEqual((size_t)0, queue.getSize());

		}

	};

}