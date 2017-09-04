#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "../misc/SimpleVector.h"
#define TRACE(x)	do {std::stringstream s; s << x; OutputDebugStringA(s.str().c_str()); printf(s.str().c_str());} while (0)
//#pragma comment(lib, "Rpcrt4.lib")
// not using the memory allocator
struct SpriteSheetUV {
	char name[32];
	Vector2 left_bottom;
	Vector2 right_top;
};
struct CharBuffer{
	char* buffer;
	int length;
	CharBuffer(void) :buffer(nullptr), length(0){

	}
	inline void dispose(void){
		if (buffer != nullptr)delete buffer;
	}
		

};
//struct OriGUID{
//	unsigned __int64 d0;
//	unsigned __int64 d1;
//};
class CharHelper{
public:
	static CharBuffer* loadBinaryFile(std::string File);
	static CharBuffer* loadTextFile(std::string File);
	static void writeTextFile(const char* fileName, const CharBuffer& charBuffer);
	static void splitToLines(const std::string &s, std::vector<std::string> &elems);
	static std::vector<std::string> split(const std::string &s, char delim);
	static void split(const std::string &s, char delim, std::vector<std::string> &elems);
	static Vector3 charToVec3(const char* chars);
	static Vector2 charToVec2(const char* chars);
	static float charToFloat(const char* chars);
	static int charToInt(const char* chars);
	static unsigned __int64 charToUInt64(const char* chars);
	static IntVector2 charToIntVec2(const char* chars);
	static unsigned int charHash(const char* chars);
	static bool charEndsWith(const char* base_str, const char* cmp_str);
	static void parseUVTxt(const char* content, std::vector<SpriteSheetUV>& out);
	static void CharHelper::trimString(const std::string& original, std::string& out);
	//static void genGUID(OriGUID* guid);
};
