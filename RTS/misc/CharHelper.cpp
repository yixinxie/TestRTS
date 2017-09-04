#include "CharHelper.h"
#include "ArrayT.h"

CharBuffer* CharHelper::loadBinaryFile(std::string File)
{
	CharBuffer* fileData = new CharBuffer;

	// open the file
	std::ifstream file(File, std::ios::in | std::ios::binary | std::ios::ate);

	// if open was successful
	if (file.is_open())
	{
		// find the length of the file
		int length = (int)file.tellg();

		// collect the file data
		fileData->buffer = new char[length];
		fileData->length = length;
		file.seekg(0, std::ios::beg);
		file.read(fileData->buffer, length);
		file.close();

	}
	return fileData;
}
CharBuffer* CharHelper::loadTextFile(std::string File)
{
	CharBuffer* fileData = new CharBuffer;
	// open the file
	std::ifstream file(File, std::ios::in | std::ios::binary | std::ios::ate);
	// if open was successful
	if (file.is_open())
	{
		// find the length of the file
		file.seekg(0, std::ios::end);
		int length = (int)file.tellg();
		int buffer_length = length + 1;
		// collect the file data
		fileData->buffer = new char[buffer_length];
		fileData->length = buffer_length;
		file.seekg(0, std::ios::beg);
		file.read(fileData->buffer, length);
		fileData->buffer[length] = 0;
		file.close();

	}
	return fileData;
}
void CharHelper::writeTextFile(const char* fileName, const CharBuffer& charBuffer)
{
	std::ofstream file(fileName, std::ios::out | std::ios::trunc);

	if (file.is_open())
	{
		file.write(charBuffer.buffer, charBuffer.length);
		file.close();
	}
}
void CharHelper::splitToLines(const std::string &s, std::vector<std::string> &lines) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item)) {
		lines.push_back(item);
	}
}
void CharHelper::split(const std::string &s, char delim, std::vector<std::string> &lines) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		lines.push_back(item);
	}
}


std::vector<std::string> CharHelper::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
Vector3 CharHelper::charToVec3(const char* tmp){
	std::vector<std::string> splitString = CharHelper::split((tmp), ',');
	float x = std::stod(splitString[0]);
	float y = std::stod(splitString[1]);
	float z = std::stod(splitString[2]);
	return Vector3(x, y, z);
}
Vector2 CharHelper::charToVec2(const char* tmp){
	std::vector<std::string> splitString = CharHelper::split((tmp), ',');
	float x = std::stod(splitString[0]);
	float y = std::stod(splitString[1]);

	return Vector2(x, y);
}
float CharHelper::charToFloat(const char* tmp){
	std::string _tmp = std::string(tmp);
	return std::stod(_tmp);
}
IntVector2 CharHelper::charToIntVec2(const char* tmp){
	std::vector<std::string> splitString = CharHelper::split((tmp), ',');
	int x = std::stoi(splitString[0]);
	int y = std::stoi(splitString[1]);

	return IntVector2(x, y);
}

int CharHelper::charToInt(const char* tmp){
	std::string _tmp = std::string(tmp);
	int x = std::stoi(_tmp);

	return x;
}
unsigned __int64 CharHelper::charToUInt64(const char* tmp){
	return strtoull(tmp, nullptr, 10);
}
unsigned int CharHelper::charHash(const char* str){
	unsigned int hash = 5381;
	unsigned char c;

	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}
bool CharHelper::charEndsWith(const char* base_str, const char* cmp_str) {
	int32 base_length = strlen(base_str);
	int32 cmp_length = strlen(cmp_str);
	bool same = true;
	for (int32 i = 1; i < 1024 && base_length - i >= 0 && cmp_length - i >= 0; ++i) {
		if (base_str[base_length - i] != cmp_str[cmp_length - i]) {
			same = false;
			break;
		}
	}
	return same;
}
void CharHelper::parseUVTxt(const char* content, std::vector<SpriteSheetUV>& out) {
	const std::string content_str(content);
	std::vector<std::string> lines;
	splitToLines(content_str, lines);
	for (int i = 0; i < lines.size(); ++i) {
		std::vector<std::string> pieces_equal = split(lines[i], '=');
		SpriteSheetUV newSheetUV;
		std::string name_str, uv_str;
		trimString(pieces_equal[0], name_str);
		strcpy_s(newSheetUV.name, name_str.c_str());
		trimString(pieces_equal[1], uv_str);
		std::vector<std::string> pieces_numbers = split(uv_str, ' ');

		newSheetUV.left_bottom.x = charToFloat(pieces_numbers[0].c_str());
		newSheetUV.left_bottom.y = charToFloat(pieces_numbers[1].c_str());

		newSheetUV.right_top.x = charToFloat(pieces_numbers[2].c_str());
		newSheetUV.right_top.y = charToFloat(pieces_numbers[3].c_str());

		out.push_back(newSheetUV);
	}
}
void CharHelper::trimString(const std::string& original, std::string& out) {
	const char* original_char = original.c_str();
	int32 length = original.length();
	int32 beginAt, endAt;
	for (int i = 0; i < length; ++i) {
		if (original_char[i] == ' ' ||
			original_char[i] == '\r'){

			
		}
		else {
			beginAt = i;
			break;
		}
	}
	for (int i = length - 1; i >= 0; --i) {
		if (original_char[i] == ' ' ||
			original_char[i] == '\r') {


		}
		else {
			endAt = i;
			break;
		}
	}
	out = original.substr(beginAt, endAt - beginAt + 1);
}