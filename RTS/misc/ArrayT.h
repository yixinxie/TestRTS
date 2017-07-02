#pragma once
#include <assert.h>
#include "BasicMem.h"
// only use this for primitive types
template<typename T>
class ArrayT{
private:
	void resize(void) {
		int newSize = arraySize * 2;

		T* newArray = ori_alloc_array_r(T, newSize, "array resiz template");

		for (int i = 0; i < arraySize; ++i) {
			newArray[i] = arrayData[i];
		}
		ori_dealloc(arrayData);
		arrayData = newArray;
		arraySize = newSize;
	}
	
	int arraySize;
	T* arrayData;
public:
	int length;
	
	ArrayT(int defaultSize = 4) {
		arraySize = defaultSize;
		arrayData = ori_alloc_array_r(T, arraySize, "array template");
		length = 0;

	}
	~ArrayT() {
		ori_dealloc(arrayData);
	}
	void clear(void) {
		length = 0;
	}
	void push(T val) {
		if (length == arraySize) {
			resize();
		}
		arrayData[length] = val;
		length++;
	}
	void removeAt(int idx) {
		assert(idx >= 0 && idx < length);
		length--;
		for (int i = idx; i < length; ++i) {
			arrayData[i] = arrayData[i + 1];
		}
	}
	void remove(T val) {
		for (int i = 0; i < length; ++i) {
			if (arrayData[i] == val) {
				removeAt(i);
				break;
			}
		}
	}
	
	T& operator[] (int idx) {
		assert(idx >= 0 && idx < length);
		return arrayData[idx];
	}
};