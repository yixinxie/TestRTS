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
	void remarks(const char* _remarks);
	void dealloc(void* ptr);
	void report(void);

	//template<class T> inline type* allocT(void) {
	//	T* ret = alloc(sizeof(T));
	//	new(ret) T();
	//	return ret;
	//}
};
extern BasicMemory basicMem;
template<typename T> T* newClass(void) {
	T* ret = (T*)basicMem.alloc(sizeof(T));
	new((T*)ret) T();
	return ret;
}
template<typename T> T* newClass(const char* remarks) {
	T* ret = (T*)basicMem.alloc_r(sizeof(T), remarks);
	new((T*)ret) T();
	return ret;
}
//template<typename T> T* alloc(void) {
//	T* ret = (T*)basicMem.alloc(sizeof(T));
//	return ret;
//}
//template<typename T> T* alloc(const char* remarks) {
//	T* ret = (T*)basicMem.alloc_r(sizeof(T), remarks);
//	return ret;
//}
//template<typename T> void callCons(T* ptr) {
//	new((T*)ptr) T();
//}

template<typename T> T* allocArray(int count) {
	T* ret = (T*)basicMem.alloc(sizeof(T) * (count));
	return ret;
}
template<typename T> T* allocArray(int count, const char* remarks) {
	T* ret = (T*)basicMem.alloc_r(sizeof(T) * (count), remarks);
	return ret;
}
template<typename T> void callCons(T* ptr, int count) {
	for (int i = 0; i < count; ++i) {
		new(ptr[i]) T();
	}
}

template<typename T> void deallocT(T* ptr) {
	ptr->~T();
	basicMem.dealloc(ptr);
}
template<typename T> void deallocND(T* ptr) {
	basicMem.dealloc(ptr);
}
//#define allocT(T) ret = (T*)basicMem.alloc(sizeof(T));new(ret) T();
//#define allocT(T) ret = (T*)basicMem.alloc(sizeof(T));new(ret) T();
//#define allocT_r(T, REMARKS) ret = (T*)basicMem.alloc(sizeof(T), REMARKS);new(ret) T();
//#define allocTArray(T, COUNT) ret = (T*)basicMem.alloc(sizeof(T) * (COUNT));for (int i = 0; i < (COUNT); ++i)new(ret[i]) T();
//#define allocTArray_r(T, COUNT, REMARKS) ret = (T*)basicMem.alloc_r(sizeof(T) * (COUNT), (REMARKS));for (int i = 0; i < (COUNT); ++i)new(ret[i]) T();

//#define ori_alloc(TYPE) (TYPE*)basicMem.alloc(sizeof(TYPE));
//#define ori_alloc_r(TYPE, REMARKS) (TYPE*)basicMem.alloc_r(sizeof(TYPE), (REMARKS));
//#define ori_alloc_array(TYPE, COUNT) (TYPE*)basicMem.alloc(sizeof(TYPE) * (COUNT));
//#define ori_alloc_array_r(TYPE, COUNT, REMARKS) (TYPE*)basicMem.alloc_r(sizeof(TYPE) * (COUNT), (REMARKS));
//#define ori_dealloc(PTR) basicMem.dealloc(PTR);
template < typename T > class SharedPtr
{
private:
	T*    pData;       // pointer
	int ref_count;

public:
	SharedPtr() : pData(0), ref_count(0)
	{
	}

	//SharedPtr(T* pValue) : pData(pValue), reference(0)
	//{
	//	// Create a new reference 
	//	reference = new RC();
	//	// Increment the reference count
	//	reference->AddRef();
	//}

	//SharedPtr(const SharedPtr<T>& sp) : pData(sp.pData), reference(sp.reference)
	//{
	//	// Copy constructor
	//	// Copy the data and reference pointer
	//	// and increment the reference count
	//	ref_count++;
	//}

	~SharedPtr()
	{
		// Destructor
		// Decrement the reference count
		// if reference become zero delete the data
		if (reference->Release() == 0)
		{
			delete pData;
		}
	}

	T& operator* ()
	{
		return *pData;
	}

	T* operator-> ()
	{
		return pData;
	}

	SharedPtr<T>& operator = (const SharedPtr<T>& sp)
	{
		// Assignment operator
		if (this != &sp) // Avoid self assignment
		{
			// Decrement the old reference count
			// if reference become zero delete the old data
			ref_count--;
			if (ref_count == 0)
			{
				delete pData;
			}

			// Copy the data and reference pointer
			// and increment the reference count
			pData = sp.pData;
			reference = sp.reference;
			reference->AddRef();
		}
		return *this;
	}
};