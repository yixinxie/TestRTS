#pragma once
#include "ArrayT.h"
#include "BasicMem.h"
//template<class ArrayT, typename T>
////ArrayT::ArrayT(int defaultSize){
////	arraySize = defaultSize;
////	arrayData = ori_alloc_array_r(T, arraySize, "array template");
////	length = 0;
////
////}
//
//void ArrayT::clear(){
//	length = 0;
//}
//void ArrayT<T>::push(T val){
//	if (length == arraySize){
//		resize();
//	}
//	arrayData[length] = val;
//	length++;
//}
//void ArrayT<T>::removeAt(int idx){
//	assert(idx >= 0 && idx < length);
//	length--;
//	for (int i = idx; i < length; ++i){
//		arrayData[i] = arrayData[i + 1];
//	}
//}
//void ArrayT<T>::remove(T val){
//	for (int i = 0; i < length; ++i){
//		if (arrayData[i] == val){
//			removeAt(i);
//			break;
//		}
//	}
//}
//void ArrayT<T>::resize(){
//	int newSize = arraySize * 2;
//
//	T* newArray = ori_alloc_array_r(T, newSize, "array resiz template");
//
//	for (int i = 0; i < arraySize; ++i){
//		newArray[i] = arrayData[i];
//	}
//	ori_dealloc(arrayData);
//	arrayData = newArray;
//	arraySize = newSize;
//}