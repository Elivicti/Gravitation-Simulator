#pragma once
#include <cmath>
#include <ctime>
#include <ostream>

#ifndef __VECTOR2DCLASS_HEADER__
#define __VECTOR2DCLASS_HEADER__

struct Position
{
    double x;
    double y;

    constexpr Position(double _x = 0.0, double _y = 0.0) :x(_x), y(_y) {}

    friend inline std::ostream& operator<<(std::ostream& os, const Position& pos)
    {
        return os << "x = " << pos.x
            << ", y = " << pos.y;
    }
};

constexpr Position CoordinateX = { 1.0, 0.0 }; //������X�ķ�������
constexpr Position CoordinateY = { 0.0, 1.0 }; //������Y�ķ�������

const double PI = acos(0) * 2;

class Vector2D
{
public:
    Vector2D()noexcept :pos(0.0, 0.0), length(0.0)
    {
    }
    Vector2D(double x, double y) :pos(x, y)
    {
        CalLength();
    }
    Vector2D(const Position& _pos) :pos(_pos)
    {
        CalLength();
    }
    Vector2D(const Position& pos1, const Position& pos2) :pos(pos2.x - pos1.x, pos2.y - pos1.y)
    {
        CalLength();
    }

    Vector2D& setToZero()
    {
        this->pos.x = 0.0;
        this->pos.y = 0.0;
        this->length = 0.0;
        return *this;
    }

    inline double X() const 
    { 
        return pos.x; 
    }
    inline double Y() const 
    { 
        return pos.y;
    }
    inline double Length() const 
    { 
        return length; 
    }
    inline void X(double x) 
    { 
        pos.x = x; CalLength(); 
    }
    inline void Y(double y) 
    { 
        pos.y = y; CalLength(); 
    }
    inline Position positon() const { return this->pos; }

    inline void setXY(double x, double y)
    {
        pos.x = x;
        pos.y = y;
        CalLength();
    }
    inline void setXY(const Position& pos)
    {
        this->pos = pos;
        CalLength();
    }

    //����������֮��нǵ�����ֵ
    inline double angle_cos(const Vector2D& vec) const 
    { 
        return (pos.x * vec.pos.x + pos.y * vec.pos.y) / (length * vec.Length()); 
    }
    //������������ļн�
    inline double angle(const Vector2D& vec) const 
    { 
        return acos(this->angle_cos(vec)); 
    }

    //���ش������ķ�������
    inline Vector2D direction() const
    { 
        return Vector2D(pos.x / length, pos.y / length); 
    }
    inline void direction(Vector2D& direc) const 
    { 
        direc.setXY(pos.x / length, pos.y / length); 
    }

    static Vector2D& direction(double x1, double y1, double x2, double y2, Vector2D& direc)
    {
        direc.setXY(x2 - x1, y2 - y1);
        direc /= direc.length;
        return direc;
    }
    static Vector2D& direction(const Position& pos1, const Position& pos2, Vector2D& direc)
    {
        direc.setXY(pos2.x - pos1.x, pos2.y - pos1.y);
        direc /= direc.length;
        return direc;
    }

    //�Ѵ�������vec����ֽ�
    int Decomposition(Vector2D& vecX, Vector2D& vecY, const Vector2D& CoorVec = CoordinateX) const;

private:
    Position pos;   //�յ�����
    double length;  //ģ��

    inline void CalLength() 
    { 
        this->length = sqrt(pos.x * pos.x + pos.y * pos.y); 
    }

    friend class Body;
    friend class Simulator;
public: //Operator overload
    inline Vector2D& operator=(const Vector2D& vec)
    {
        pos = vec.positon();
        length = vec.Length();
        return *this;
    }
    inline Vector2D& operator=(const Position& pos)
    {
        this->pos = pos;
        CalLength();
        return *this;
    }
    inline bool operator==(const Vector2D& vec) const 
    { 
        return (pos.x == vec.pos.x && pos.y == vec.pos.y); 
    }
    inline bool operator!=(const Vector2D& vec) const 
    { 
        return (pos.x != vec.pos.x || pos.y != vec.pos.y); 
    }

    inline Vector2D operator+(const Vector2D& vec) const 
    { 
        return Vector2D(pos.x + vec.pos.x, pos.y + vec.pos.y); 
    }
    inline Vector2D operator-(const Vector2D& vec) const 
    { 
        return Vector2D(pos.x - vec.pos.x, pos.y - vec.pos.y); 
    }

    inline Vector2D& operator+=(const Vector2D& vec)
    {
        pos.x += vec.pos.x;
        pos.y += vec.pos.y;
        CalLength();
        return *this;
    }
    inline Vector2D& operator-=(const Vector2D& vec)
    {
        pos.x -= vec.pos.x;
        pos.y -= vec.pos.y;
        CalLength();
        return *this;
    }

    inline Vector2D operator*(const double& num) const 
    { 
        return Vector2D(pos.x * num, pos.y * num); 
    }
    inline Vector2D operator/(const double& num) const 
    {
        return Vector2D(pos.x / num, pos.y / num); 
    }

    inline Vector2D& operator*=(const double& num)
    {
        pos.x *= num;
        pos.y *= num;
        length *= num;
        return *this;
    }
    inline Vector2D& operator/=(const double& num)
    {
        pos.x /= num;
        pos.y /= num;
        length /= num;
        return *this;
    }

    inline double operator*(const Vector2D& vec) const 
    { 
        return (pos.x * vec.pos.x + pos.y * vec.pos.y); 
    }

    friend inline Vector2D operator*(const double& num, const Vector2D& vec)
    {
        return Vector2D(vec.pos.x * num, vec.pos.y * num);
    }
    friend inline Vector2D operator-(const Vector2D& vec)
    {
        return Vector2D(-vec.pos.x, -vec.pos.y);
    }

    friend inline std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
    {
        return os << "x = " << vec.pos.x
            << ", y = " << vec.pos.y
            << ", length = " << vec.Length();
    }

};

inline Position operator+(const Position& pos1, const Position& pos2)
{
    Position tmp = { pos1.x + pos2.x , pos1.y + pos2.y };
    return tmp;
}
inline Position operator-(const Position& pos1, const Position& pos2)
{
    Position tmp = { pos1.x - pos2.x , pos1.y - pos2.y };
    return tmp;
}
inline Position& operator+=(Position& pos1, const Position& pos2)
{
    pos1.x += pos2.x;
    pos1.y += pos2.y;
    return pos1;
}
inline Position& operator-=(Position& pos1, const Position& pos2)
{
    pos1.x -= pos2.x;
    pos1.y -= pos2.y;
    return pos1;
}

inline bool operator==(const Position& pos1, const Position& pos2) 
{ 
    return (pos1.x == pos2.x) && (pos1.y == pos2.y); 
}
inline bool operator!=(const Position& pos1, const Position& pos2) 
{ 
    return (pos1.x != pos2.x) || (pos1.y != pos2.y); 
}

inline Position operator-(const Position& pos)
{
    return Position(-pos.x, -pos.y);
}

#endif //! __VECTOR2DCLASS_HEADER__