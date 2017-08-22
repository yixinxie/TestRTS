// basic memory management
#pragma once
#include <vector>
#include <unordered_map>
struct MemAllocDebugDesc {
	char* remarks;
	int id;
};
// requires a declaration of the extern variable basicMem in the main file.
class BasicMemory{
private:
	std::unordered_map<int, int> sizes;
	// debug info
	std::unordered_map<int, MemAllocDebugDesc> debugDesc;

	// end of debug info.
	unsigned char* heapStart;
	int used;
	int size;
	int id_counter;
public:
	BasicMemory(void);
	void initHeap(int defaultHeapSize);
	void* alloc(int _size);
	void* alloc_r(int _size, const char* remarks);
	void dealloc(void* ptr);
	void report(void);

	//template<class T> inline type* allocT(void) {
	//	T* ret = alloc(sizeof(T));
	//	new(ret) T();
	//	return ret;
	//}
};
extern BasicMemory basicMem;
template<typename T> T* allocT(void) {
	T* ret = (T*)basicMem.alloc(sizeof(T));
	new(ret) T();
	return ret;
}
template<typename T> T* alloc_array(int count) {
	T* ret = (T*)basicMem.alloc(sizeof(T) * (count));
	for (int i = 0; i < count; ++i) {
		new(ret[i]) T();
	}
	return ret;
}
template<typename T> void dealloc(T* ptr) {
	ptr->~T();
	basicMem.dealloc(ptr);
}
#define ori_alloc(TYPE) (TYPE*)basicMem.alloc(sizeof(TYPE));
#define ori_alloc_r(TYPE, REMARKS) (TYPE*)basicMem.alloc_r(sizeof(TYPE), (REMARKS));
#define ori_alloc_array(TYPE, COUNT) (TYPE*)basicMem.alloc(sizeof(TYPE) * (COUNT));
#define ori_alloc_array_r(TYPE, COUNT, REMARKS) (TYPE*)basicMem.alloc_r(sizeof(TYPE) * (COUNT), (REMARKS));
#define ori_dealloc(PTR) basicMem.dealloc(PTR);
