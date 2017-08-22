#pragma once
#include "ArrayInt.h"
#include "BasicMem.h"
ArrayInt::ArrayInt(int defaultSize){
	arraySize = defaultSize;
	arrayData = allocArray<int>(arraySize, "array int");
	length = 0;
}
ArrayInt::ArrayInt() {
	arraySize = 4;
	arrayData = allocArray<int>(arraySize, "array int");
	length = 0;
}
ArrayInt::~ArrayInt(){
	deallocND(arrayData);
	//ori_dealloc(arrayData);
}
void ArrayInt::clear(){
	length = 0;
}
void ArrayInt::push(int val){
	if (length == arraySize){
		resize();
	}
	arrayData[length] = val;
	length++;
}
void ArrayInt::removeAt(int idx){
	assert(idx >= 0 && idx < length);
	length--;
	for (int i = idx; i < length; ++i){
		arrayData[i] = arrayData[i + 1];
	}
}
void ArrayInt::remove(int val){
	for (int i = 0; i < length; ++i){
		if (arrayData[i] == val){
			removeAt(i);
			break;
		}
	}
}
void ArrayInt::resize(){
	int newSize = arraySize * 2;

	int* newArray = allocArray<int>(newSize, "array int re");

	for (int i = 0; i < arraySize; ++i){
		newArray[i] = arrayData[i];
	}
	//ori_dealloc(arrayData);
	deallocT(arrayData);
	arrayData = newArray;
	arraySize = newSize;
}