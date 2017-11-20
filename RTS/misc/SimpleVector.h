#pragma once
#define Math_PI 3.1415927f
typedef int int32;
typedef short int int16;
struct Vector3;
struct Vector2{
	float x, y;
	Vector2(const float _x, const float _y) :x(_x), y(_y) {
	}
	Vector2() :x(0), y(0){}

	Vector2 operator*(const float& val)
	{
		Vector2 vec;
		vec.x = this->x * val;
		vec.y = this->y * val;
		return vec;
	}
	Vector2 operator-(const Vector2& val)
	{
		Vector2 vec;
		vec.x = this->x - val.x;
		vec.y = this->y - val.y;
		return vec;
	}
	Vector2 operator+(const Vector2& val)
	{
		Vector2 vec;
		vec.x = this->x + val.x;
		vec.y = this->y + val.y;
		return vec;
	}
	Vector2 operator/(const float val)
	{
		Vector2 vec;
		vec.x = this->x / val;
		vec.y = this->y / val;
		return vec;
	}
	Vector2 operator+=(const Vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	Vector2 operator-=(const Vector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	bool operator==(const Vector2& rhs)
	{
		return this->x == rhs.x && this->y == rhs.y;
	}
	//Vector3 toVector3(void)
	//{
	//	return Vector3(x, y, 0);
	//}
	static Vector2 zero(void) {
		return Vector2(0.0f, 0.0f);
	}
	static Vector2 one(void) {
		return Vector2(1.0f, 1.0f);
	}
	void normalize()
	{
		float mag = sqrtf(x * x + y * y);
		x /= mag;
		y /= mag;
	}
	float simpleMag()
	{
		return abs(x) + abs(y);
	}
	float magSquared()
	{
		return x * x + y * y;
	}
	float distanceTo(const Vector2& other) const
	{
		float ret = (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
		return sqrtf(ret);
	}
	void rotateClockwise90() {
		float tmp = x;
		x = y;
		y = -tmp;
	}

};
struct Vector3{
	float x, y, z;
	Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {
	}
	Vector3() :x(0.0f), y(0.0f), z(0.0f){}

	Vector3 operator*(float val)
	{
		Vector3 vec;
		vec.x = this->x * val;
		vec.y = this->y * val;
		vec.z = this->z * val;
		return vec;
	}
	Vector3 operator+=(const Vector3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}
	Vector3 operator-=(const Vector3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		return *this;
	}
	bool operator==(const Vector3& rhs)
	{
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
	}
	float* getFirstFloatAddr()
	{
		return &x;
	}
};
struct Vector4{
	float x, y, z, w;
	Vector4(const float _x, const float _y, const float _z, const float _w) :x(_x), y(_y), z(_z), w(_w) {
	}
	Vector4(const Vector3 vec) :x(vec.x), y(vec.y), z(vec.z), w(1) {
	}
	Vector4() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
	}
	bool operator==(const Vector4& rhs)
	{
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && this->w == rhs.w;
	}
};
struct IntVector2{
	int x, y;
	IntVector2(const int _x, const int _y) :x(_x), y(_y){
	}
	IntVector2(const long _x, const long _y) :x(_x), y(_y){
	}
	IntVector2() :x(0), y(0){}
};
struct Color{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	Color(void) : r(0), g(0), b(0), a(0) {
	}
	Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) : r(_r), g(_g), b(_b), a(_a) {
	}
	Color(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b), a(255) {
	}
	Vector4 toVec4(void) {
		return Vector4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}
	static Color red() {
		return Color(255, 0, 0);
	}
	static Color green() {
		return Color(0, 255, 0);
	}
	static Color blue() {
		return Color(0, 0, 255);
	}
	static Color yellow() {
		return Color(255, 255, 0);
	}
	static Color black() {
		return Color(0, 0, 0);
	}
	static Color white() {
		return Color(255, 255, 255);
	}
	static Color cyan() {
		return Color(0, 255, 255);
	}
	static Color magenta() {
		return Color(255, 0, 255);
	}
};
