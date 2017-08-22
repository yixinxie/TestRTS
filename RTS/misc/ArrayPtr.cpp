#pragma once
#include "ArrayPtr.h"
#include "BasicMem.h"
ArrayPtr::ArrayPtr(int defaultSize){
	arraySize = defaultSize;
	arrayData = allocArray<void*>(arraySize, "array ptr");
	callCons(arrayData, arraySize);
	length = 0;

}
ArrayPtr::~ArrayPtr(){
	//ori_dealloc(arrayData);
}
void ArrayPtr::clear(){
	length = 0;
}
void ArrayPtr::push(void* val){
	if (length == arraySize){
		resize();
	}
	arrayData[length] = val;
	length++;
}
void ArrayPtr::removeAt(const int idx){
	assert(idx >= 0 && idx < length);
	length--;
	for (int i = idx; i < length; ++i){
		arrayData[i] = arrayData[i + 1];
	}
}
void ArrayPtr::remove(const void* val){
	for (int i = 0; i < length; ++i){
		if (arrayData[i] == val){
			removeAt(i);
			break;
		}
	}
}
void ArrayPtr::resize(){
	int newSize = arraySize * 2;

	void** newArray = allocArray<void*>(newSize,"array int re");

	for (int i = 0; i < arraySize; ++i){
		newArray[i] = arrayData[i];
	}
	deallocT(arrayData);
	//ori_dealloc(arrayData);
	arrayData = newArray;
	arraySize = newSize;
}