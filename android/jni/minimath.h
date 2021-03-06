#ifndef _MATH_MODULE_
#define _MATH_MODULE_

#include <cmath> 
#include <cstring>
#include <initializer_list>
 
extern float rnd();
extern float rnd(float, float);

const float PI        = 3.141592654;
const float TWO_PI    = 2.0f * PI;
const float DEG2RAD   = PI/180.0;
const float RAD2DEG   = 180.0/PI;

template<typename T> 
T lerp(const T &v0,const T &v1,float u) {return v0 + (v1 - v0) * u;}

struct vec 
{
    typedef const vec & ref;
public:
    union
    {
        struct {float x, y, z;};
        struct {float r, g, b;};
        float data[4];
    };
       
    vec(const float _x = 0, const float _y = 0 ,const float _z = 0) : 
    	x(_x), y(_y),z(_z)
    {}
    vec(std::initializer_list<float> l) 
    {
        std::memcpy(data,l.begin(),sizeof(data));
    }   

    vec   operator-  () const {return vec(-x,-y,-z);}
    float operator*  (const vec &a)  const {return x * a.x + y * a.y + z * a.z;}
    vec   operator*  (const float a) const {return vec( x * a, y * a, z * a);}
    vec   operator+  (const vec &a)  const {return vec(x + a.x, y + a.y, z+ a.z);}
    vec   operator-  (const vec &a)  const {return vec(x - a.x, y - a.y, z- a.z);}
    vec & operator+= (const vec &a)  {x += a.x; y += a.y; z += a.z; return *this;}
    vec & operator-= (const vec &a)  {x -= a.x; y -= a.y; z -= a.z; return *this;}
    vec & operator/= (const vec &a)  {x /= a.x; y /= a.y; z /= a.z; return *this;}
    vec & operator*= (const float a) {x *= a; y *= a; z *= a; return *this; }
    bool  operator== (const vec &a) const {return compare(a);}
    bool  operator!= (const vec &a) const {return !compare(a);}
    
    bool  compare(const vec &a) const {return ((x == a.x) && (y == a.y) && (z == a.z));}
    float length()  const {return std::sqrt(x * x + y * y + z * z);}
    
    friend vec operator* (const float a, const vec b) {return vec( b.x * a, b.y * a, b.z * a);}
};

struct mat
{
    typedef const mat & ref;
    union
    {
        float   d[4][4];
        float   data[16];
    };

    mat() : mat({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}) {}
    mat(std::initializer_list<float> l) {std::memcpy(data,l.begin(),sizeof(data));}   
    
    mat operator* (const mat &a) const
    {
        mat   dst;
        const float *m1  = reinterpret_cast<const float *>(this);
        const float *m2  = reinterpret_cast<const float *>(&a);
        float *ptr = reinterpret_cast<float *>(&dst);
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                *ptr = m1[0]*m2[j]+m1[1]*m2[j+4]+m1[2]*m2[j+8]+m1[3]*m2[j+12];
                ptr++;
            }
            m1 += 4;
        }
        return dst;
    }
    mat & operator*= (const mat &a)
    {
        *this = (*this) * a;
        return *this;
    }
    void position(const vec &v) 
    {
        d[0][3] = v.x;
        d[1][3] = v.y;
        d[2][3] = v.z;
    }
    vec position() const {return {d[0][3],d[1][3],d[2][3]};}

    static mat rotate(const vec &v)
    {
        auto sx = std::sin(v.x); auto cx = std::cos(v.x);
        auto sy = std::sin(v.y); auto cy = std::cos(v.y);
        auto sz = std::sin(v.z); auto cz = std::cos(v.z);
        return 
            mat({1,0,0,0,0,cx,-sx,0,0,sx,cx,0,0,0,0,1}) *
            mat({cy,0,sy,0,0,1,0,0,-sy,0,cy,0,0,0,0,1}) *
            mat({cz,-sz,0,0,sz,cz,0,0,0,0,1,0,0,0,0,1}); 
    }
    static mat scale(const vec &v)     {return {v.x,0,0,0,0,v.y,0,0,0,0,v.z,0,0,0,0,1};}
    static mat translate(const vec &v) {return {1,0,0,v.x,0,1,0,v.y,0,0,1,v.z,0,0,0,1};}
};




#endif