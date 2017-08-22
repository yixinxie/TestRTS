// basic memory management
#include <Windows.h>
#include "BasicMem.h"

//unsigned char* heapStart;
//int used;
//int size;
BasicMemory::BasicMemory(){
	id_counter = 0;
}
void BasicMemory::initHeap(int defaultHeapSize){
	size = defaultHeapSize;
	heapStart = new unsigned char[size];
	/*for (int i = 0; i < size; ++i){
		heapStart[i] = 0;
	}*/
	ZeroMemory(heapStart, size);
}
void* BasicMemory::alloc(int _size){
	unsigned char* ret = heapStart;
	if (used == 0){
		int sdf = 0;
	}
	ret += used;
	used += _size;
	int infoKey = (int)ret - (int)heapStart;
	sizes.insert({ infoKey, _size });

	
	// debug
	{
		MemAllocDebugDesc desc;
		desc.id = id_counter;
		desc.remarks = nullptr;
		debugDesc.insert({ infoKey , desc });
		id_counter++;
	}

	return (void*)ret;
}
void* BasicMemory::alloc_r(int _size, const char* _remarks){
	unsigned char* ret = heapStart;
	if (used == 0){
		int sdf = 0;
	}
	ret += used;
	used += _size;
	int infoKey = (int)ret - (int)heapStart;
	sizes.insert({ infoKey, _size });
	char *dbg = new char[64];
	
	{
		MemAllocDebugDesc desc;
		desc.id = id_counter;
		desc.remarks = new char[64];
		strcpy_s(desc.remarks, 64, _remarks);
		debugDesc.insert({ infoKey, desc });
		id_counter++;
	}

	return (void*)ret;
}
void BasicMemory::dealloc(void* ptr){
	int sdf = 0;
	int infoKey = (int)ptr - (int)heapStart;
	auto res = sizes.find(infoKey);
	if (res == sizes.end()){
		// key not found!
		printf("allocation not found %d.\n", infoKey);
	}else if (sizes[infoKey] == 0){
		printf("repeated deallocation at %d.\n", infoKey);
	}
	else{
		sizes[infoKey] = 0;
	}
}
void BasicMemory::report(void){
	int leakedCount = 0;
	auto desc_it = debugDesc.begin();
	for (auto it = sizes.begin(); it != sizes.end(); ++it){
		printf("%d size %d", it->first, it->second);
		if (it->second != 0){
			leakedCount++;
		}
		auto found = debugDesc.find(it->first);
		if (found != debugDesc.end()){
			printf(" remarks: %s (%d)\n", found->second.remarks, found->second.id);
		}
		else{
			printf("\n");

		}
		
	}
	printf("leak count: %d\n", leakedCount);
	
}
//template<class type> 
//type* BasicMemory::allocT() {
//	
//		
//}