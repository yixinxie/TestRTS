#pragma once
#include <assert.h>
#include "BasicMem.h"
// only use this for primitive types
template<typename T>
class ArrayPtr{
private:
	void resize(void) {
		int newSize = arraySize * 2;

		T* newArray = allocArray<T>(newSize, "array resiz template");
		//callCons(newArray, newSize);
		//int unit_size = sizeof(T);
		//memcpy(newArray, arrayData, unit_size * arraySize);
		for (int i = 0; i < arraySize; ++i) {
			newArray[i] = arrayData[i];
		}
		deallocT(arrayData);
		arrayData = newArray;
		arraySize = newSize;
	}
	
	int arraySize;
	T* arrayData;
public:
	int length;
	
	ArrayPtr(int defaultSize) {
		arraySize = defaultSize;
		arrayData = allocArray<T>(arraySize, "array template");
		//callCons(arrayData, arraySize);
		length = 0;

	}
	ArrayPtr(void) {
		arraySize = 4;
		arrayData = allocArray<T>(arraySize, "array template");
		//callCons(arrayData, arraySize);
		length = 0;

	}
	void reserve(int defaultSize = 4) {
		if (arrayData != nullptr) {
			deallocT(arrayData);
		}
		arraySize = defaultSize;
		arrayData = allocArray<T>(arraySize, "array template");
		//callCons(arrayData, arraySize);
		length = 0;
	}
	~ArrayPtr() {
		deallocT(arrayData);
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
		int unit_size = sizeof(T);
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
	
	T operator[] (int idx) {
		assert(idx >= 0 && idx < length);
		return arrayData[idx];
	}
};

template<typename T>
class ArrayStruct {
private:
	void resize(void) {
		int newSize = arraySize * 2;

		T* newArray = allocArray<T>(newSize, "array resiz template");
		int unit_size = sizeof(T);
		memcpy(newArray, arrayData, unit_size * arraySize);
		//for (int i = 0; i < arraySize; ++i) {
		//	newArray[i] = arrayData[i];
		//}
		deallocT(arrayData);
		arrayData = newArray;
		arraySize = newSize;
	}

	int arraySize;
	T* arrayData;
public:
	int length;

	ArrayStruct(int defaultSize) {
		arraySize = defaultSize;
		arrayData = allocArray<T>(arraySize, "array struct template");
		length = 0;
	}

	ArrayStruct(void) {
		arraySize = 4;
		arrayData = allocArray<T>(arraySize, "array struct template");
		length = 0;

	}
	~ArrayStruct() {
		deallocND(arrayData);
	}
	int allocatedSize(void) const {
		return arraySize;
	}
	void reserve(int defaultSize = 4) {
		if (arrayData != nullptr) {
			deallocT(arrayData);
		}
		arraySize = defaultSize;
		arrayData = allocArray<T>(arraySize, "array struct template");
		length = 0;
	}
	void clear(void) {
		length = 0;
	}
	void push(const T& val) {
		if (length == arraySize) {
			resize();
		}
		memcpy(&arrayData[length], &val, sizeof(T));
		length++;
	}
	void removeAt(int idx) {
		assert(idx >= 0 && idx < length);
		length--;
		int unit_size = sizeof(T);
		for (int i = idx; i < length; ++i) {
			//arrayData[i] = arrayData[i + 1];
			memcpy(arrayData[i], arrayData[i + 1], unit_size);
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
	T* getPtr() const {
		return arrayData;
	}
};

template<typename T>
class ArrayPrimitive {
private:
	void resize(void) {
		int newSize = arraySize * 2;

		T* newArray = allocArray<T>(newSize, "array resiz template");
		int unit_size = sizeof(T);
		memcpy(newArray, arrayData, unit_size * arraySize);
		//for (int i = 0; i < arraySize; ++i) {
		//	newArray[i] = arrayData[i];
		//}
		deallocND(arrayData);
		arrayData = newArray;
		arraySize = newSize;
	}

	int arraySize;
	T* arrayData;
public:
	int length;

	ArrayPrimitive(int defaultSize) {
		arraySize = defaultSize;
		arrayData = allocArray<T>(arraySize, "array prim template");
		length = 0;

	}
	ArrayPrimitive(void) {
		arraySize = 4;
		arrayData = allocArray<T>(arraySize, "array prim template");
		length = 0;

	}
	~ArrayPrimitive() {
		deallocND(arrayData);
	}
	void reserve(int defaultSize = 4) {
		if (arrayData != nullptr) {
			deallocND(arrayData);
		}
		arraySize = defaultSize;
		arrayData = allocArray<T>(arraySize, "array prim template");
		length = 0;
	}
	void clear(void) {
		length = 0;
	}
	void push(T val) {
		if (length == arraySize) {
			resize();
		}
		int unit_size = sizeof(T);
		arrayData[length] = val;
		length++;
	}
	void removeAt(int idx) {
		assert(idx >= 0 && idx < length);
		length--;
		int unit_size = sizeof(T);
		for (int i = idx; i < length; ++i) {
			//arrayData[i] = arrayData[i + 1];
			memcpy(arrayData[i], arrayData[i + 1], unit_size);
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
	T* getPtr() {
		return arrayData;
	}
};