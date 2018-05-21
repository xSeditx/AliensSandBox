#pragma once
#ifndef _VERTEX_H_

#include <iostream>
#include"C:\Users\Curt\Documents\Visual Studio 2012\Libraries\glm-0.9.2.7\glm\glm.hpp"

/*

X = X * Cos(Angle) + y * -Sin(Angle)
Y = X * Sin(Angle) + y * Cos(Angle)



X = X
Y = Y + Cos(angle) +  Z * -Sin(Angle)
Z = Y + Sin(angle) +  Z *  Cos(Angle)

*/

#define DEG2RAD(x) ((x * M_PI) / 180.0)

const double epsilon = 4.37114e-05;

//======================================================================================================================================================================
//_________________ VERTEX 2D X/Y ______________________________________________________________________________________________________________________________________
//======================================================================================================================================================================

struct Vec2{
      //  float x;float y;
        Vec2();
        Vec2(const float& x,const float& y);
        union{
            struct{
                float x,y;
            };
            struct{
                float u,v;
            };
            float Coord[2];
        };

        Vec2& add(const Vec2& other);
        Vec2& subtract(const Vec2& other);
        Vec2& divide(const Vec2& other);
        Vec2& multiply(const Vec2& other);
        
        friend Vec2 operator +(Vec2 left, const Vec2& right);
        friend Vec2 operator -(Vec2 left, const Vec2& right);
        friend Vec2 operator /(Vec2 left, const Vec2& right);
        friend Vec2 operator *(Vec2 left, const Vec2& right);

        Vec2& operator =(const float& value); // Test these // Possible make them friends
        Vec2  operator +(const float& value);
        Vec2  operator -(const float& value);
        Vec2  operator *(const float& value);
        Vec2  operator /(const float& value);
        
        Vec2& operator +=(const Vec2& other);
        Vec2& operator -=(const Vec2& other);
        Vec2& operator *=(const Vec2& other);
        Vec2& operator /=(const Vec2& other);
        

        Vec2& operator +=(const float &other);
        Vec2& operator -=(const float &other);
        Vec2& operator *=(const float &other);
        Vec2& operator /=(const float &other);

        Vec2& add       (const float other); // USED FOR THE MANIPULATION OF BOTH ELEMENTS OF THE VECTOR WITH A SINGLE NUMBER
        Vec2& subtract  (const float other); // 
        Vec2& divide    (const float other); // USAGE:    VECTOR2D   = float VALUE
        Vec2& multiply  (const float other); // RESULT:   VECTOR2D.X = float VALUE
        Vec2& assign    (const float other); //           VECTOR2D.Y = float VALUE


        bool operator ==(const Vec2& other);
        bool operator !=(const Vec2& other);
        
        friend std::ostream& operator<<(std::ostream& stream,const Vec2& vector);


        static inline Vec2 Get_Displacement(Vec2 A, Vec2 B){
             return Vec2(A.x - B.x, A.y - B.y);
        }

};


//======================================================================================================================================================================
//___________________ VERTEX 3D X/Y ____________________________________________________________________________________________________________________________________
//======================================================================================================================================================================

struct Vec3{

       union {
           struct{
              float x,y,z;
           };
           struct{
              float r,g,b;
           };
           float Coord[3];
       };
   
        Vec3();
        Vec3(const float& x,
             const float& y,
             const float& z);

        Vec3(glm::vec3 other);

        Vec3& add(const Vec3& other);
        Vec3& subtract(const Vec3& other);
        Vec3& divide(const Vec3& other);
        Vec3& multiply(const Vec3& other);
        
        friend Vec3 operator +(Vec3 left, const Vec3& right);
        friend Vec3 operator -(Vec3 left, const Vec3& right);
        friend Vec3 operator /(Vec3 left, const Vec3& right);
        friend Vec3 operator *(Vec3 left, const Vec3& right);
        
        Vec3& operator +=(const Vec3& other);
        Vec3& operator -=(const Vec3& other);
        Vec3& operator *=(const Vec3& other);
        Vec3& operator /=(const Vec3& other);

        Vec3& operator =(const float& value); // Test these

        Vec3 operator +(const float& value) const;
        Vec3 operator -(const float& value) const;
        Vec3 operator *(const float& value) const;
        Vec3 operator /(const float& value) const;

        bool operator ==(const Vec3& other);
        bool operator !=(const Vec3& other);
        
        friend std::ostream& operator<<(std::ostream& stream,const Vec3& vector);

       void  Normalize();

       float GetDistance(const Vec3 &other);
       float DotProduct(const Vec3 &vec) const;

       Vec3 Vec3::CrossProduct(const Vec3 &other);

static Vec3 Vec3::CrossProduct(const Vec3 &first, const Vec3 &other);
static Vec3  Normalize(const Vec3 &vec);
static float GetDistance(const Vec3 &v1, const Vec3 &v2);
static float DotProduct(const Vec3 &vec, const Vec3 &vec2);

static Vec3 GetNormal(Vec3 v1, Vec3 v2, Vec3 v3);


static Vec3 RayCast(Vec3 pos, Vec3 angle, float distance); // Need to review the following three functions
static float RayX(float x, float angle, float distance);   // They need to work independent of the Current ModelView Matrix I believe
static float RayY(float y, float angle, float distance);
static float RayZ(float z, float angle, float distance);


operator glm::vec3(); 

 
static float Get_Angle(Vec3 a, Vec3 b){

    float fA =  sqrt(a.x * a.x + a.y * a.y + a.z + a.z);
    float fB =  sqrt(b.x * b.x + b.y * b.y + b.z + b.z);
    float fDot = a.x * b.x + a.y * b.y + a.z + b.z;
    return acosf(fDot / (fA * fB));
}



static float Get_Angle2(Vec3 a, Vec3 b){
   
    float  fCrossX, fCrossY, fCrossZ, fCross, fDot;

    fCrossX = a.y * b.z - a.z * b.y;
    fCrossY = a.z * b.x - a.x * b.z;
    fCrossZ = a.x * b.y - a.y * b.x;
    fCross =  sqrt(fCrossX * fCrossX + fCrossY * fCrossY + fCrossZ * fCrossZ);
    fDot = a.x * b.x + a.y * b.y + a.z + b.z;
    return atan2(fCross, fDot);
}


                                                        

};




//Vec3 GlmtoVec3(glm::vec3  vec);
//glm::vec3  Vec3ToGlm(Vec3 vec);

//======================================================================================================================================================================
//_________________ VERTEX 4D X/Y ______________________________________________________________________________________________________________________________________
//======================================================================================================================================================================

struct Vec4{

       union{
           struct{
               float x,y,z,w;
           };
           struct{
               float r,g,b,a;
           };
           struct{
               float x,y,w,h;
           };
           float Coords[4];
       };

        Vec4();
        Vec4(const float& x,const float& y,const float& z, const float& w);
        
        Vec4& add(const Vec4& other);
        Vec4& subtract(const Vec4& other);
        Vec4& divide(const Vec4& other);
        Vec4& multiply(const Vec4& other);
        
        Vec4& operator +=(const Vec4& other);
        Vec4& operator -=(const Vec4& other);
        Vec4& operator *=(const Vec4& other);
        Vec4& operator /=(const Vec4& other);
        
        bool operator ==(const Vec4& other);
        bool operator !=(const Vec4& other);
        
        friend Vec4 operator +(Vec4 left, const Vec4& right);
        friend Vec4 operator -(Vec4 left, const Vec4& right);
        friend Vec4 operator /(Vec4 left, const Vec4& right);
        friend Vec4 operator *(Vec4 left, const Vec4& right);

        friend std::ostream& operator<<(std::ostream& stream,const Vec4& vector);
};



//======================================================================================================================================================================
//_________________ MATRIX 3D ___________________________________________________________________________________________________________________________________________
//======================================================================================================================================================================
//  NEEDS WORK. SET THIS UP FOR 2D ROTATIONS AND TRANSLATIONS TO SIMPLIFY AND CLEAN UP THE MATH IN A 2D PROGRAM
struct Matrix3{

        union{
                float elements[9];
        	struct{
                Vec3 columns[3];
        	};
        };

        Matrix3();
        Matrix3(float *data);
        Matrix3(Vec3 a, Vec3 b, Vec3 c);


        Matrix3(float Diagonal);
        
        float Element(int col, int row);

               Matrix3& Multiply(const Matrix3& other);

       friend  Matrix3  operator *(Matrix3 left,const Matrix3 &right);
               Matrix3& operator *=(const Matrix3& other);

        static Matrix3 Identity();
        static Matrix3 Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far);
        static Matrix3 Perspective (float FOV,float Aspect_Ratio,float Near,float Far);
        static Matrix3 Translation(const Vec3& Translation);
        static Matrix3 Rotation(float Angle,const Vec3& Axis);
        static Matrix3 Scale(const Vec3& Translation);

friend std::ostream& operator<<(std::ostream& stream,const Matrix3& mat4);
};




//======================================================================================================================================================================
//_________________ MATRIX 4D ___________________________________________________________________________________________________________________________________________
//======================================================================================================================================================================
       
  


struct Matrix4{

        union{
                float elements[16];
        	struct{
                Vec4 columns[4];
        	};
        };
        
        Matrix4();
        Matrix4(Vec4 a, Vec4 b, Vec4 c, Vec4 d);
        Matrix4(float Diagonal);
        
        float Element(int col, int row);

               Matrix4& Multiply(const Matrix4& other);
        
       friend  Matrix4  operator *(Matrix4 left,const Matrix4 &right);
               Matrix4& operator *=(const Matrix4& other);

        static Matrix4 Identity();
        static Matrix4 Orthographic(float Left,float Right,float Top,float Bottom,float Near, float Far);
        static Matrix4 Perspective (float FOV,float Aspect_Ratio,float Near,float Far);
        static Matrix4 Translation(const Vec3& Translation);
        static Matrix4 Rotation(float Angle,const Vec3& Axis);
        static Matrix4 Scale(const Vec3& Translation);

friend std::ostream& operator<<(std::ostream& stream,const Matrix4& mat4);
};


struct Vertex3D
{
        Vec3 Position;
        Vec3 Color;
        Vec3 Normals;
};



Matrix4 LookAt(const Vec3 &eyePos, const Vec3 &centerPos, const Vec3 &upDir);


inline float Squared(float x) { return x*x; }


typedef Vec3 RGBf;
typedef Vec4 RGBAf;
typedef Vec4 Range;











#endif _VERTEX_H_
