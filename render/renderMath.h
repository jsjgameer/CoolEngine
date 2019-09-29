#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <windows.h>
#include <tchar.h>
#include <stdbool.h>
#include "geometry.h"



#define PI 3.141592653
#define angle_to_radian(X) ((X)/180*PI)  //角度转弧度
#define radian_to_angle(X) ((X)/PI*180)  //弧度转角度

typedef unsigned int IUINT32;
struct matrix_t {
	
	
	float m[4][4];

	matrix_t& operator* (float f) {
		int i, j;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++)
				this->m[i][j] = this->m[i][j] * f;
		}
		return *this;
	}


	matrix_t operator* (const matrix_t& right) //引用是副本，不像指针那样要求外界传递指针
	{
		matrix_t c;
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				c.m[i][j] =
					(this->m[i][0] * right.m[0][j]) +
					(this->m[i][1] * right.m[1][j]) +
					(this->m[i][2] * right.m[2][j]) +
					(this->m[i][3] * right.m[3][j]);
			}
		}
		return c;
	}

	matrix_t operator-(const matrix_t & b) {
		matrix_t c;
		int i, j;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++)
				c.m[i][j] = this->m[i][j] - b.m[i][j];
		}
		return c;
	}

	matrix_t operator+(const matrix_t & b) {
		matrix_t c;
		int i, j;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++)
				c.m[i][j] = this->m[i][j] + b.m[i][j];
		}
		return c;
	}


} ;




////不重载也行 使用结构体本身的内存对齐拷贝(但不是按位拷贝)
//Vec4f& operator=(const Vec4f&  value)
//{
//	Vec4f ncolor_t;
//	this->x = value.x;
//	this->y = value.y;
//	this->z = value.z;
//	this->w = value.w;
//	return *this;
//}
//
//Vec4f operator*(float value)
//{
//	Vec4f ncolor_t;
//	ncolor_t.x = x * value;
//	ncolor_t.y = y * value;
//	ncolor_t.z = z * value;
//
//	return ncolor_t;
//}
//
//
//Vec4f operator+(const Vec4f& value)
//{
//	Vec4f ncolor_t;
//	ncolor_t.x = x + value.x;
//	ncolor_t.y = y + value.y;
//	ncolor_t.z = z + value.z;
//
//	return ncolor_t;
//}
//
//Vec4f operator-(const Vec4f& value)
//{
//	Vec4f ncolor_t;
//	ncolor_t.x = x - value.x;
//	ncolor_t.y = y - value.y;
//	ncolor_t.z = z - value.z;
//
//	return ncolor_t;
//}
//
//
//} ; //使用的3D齐次坐标  其常规坐标为 {x/w, y/w, z/w; }
//typedef Vec4f point_t;



//不允许超过上下限 
float CMIDFloat(float x, float min, float max);

//不允许超过上下限
int CMID(int x, int min, int max);


// 计算插值：t 为 [0, 1] 之间的数值 lerp插值
float interp(float x1, float x2, float t);

// 矢量lerp插值，t取值 [0, 1]
void vector_interp(Vec4f *z, const Vec4f *x1, const Vec4f *x2, float t);

//void matrix_mul(matrix_t *c, const matrix_t *a, const matrix_t *b);

// 矩阵乘法：   y = x * m   	//向量/点，被转为矩阵后, 矩阵 乘 矩阵.  实现坐标转换
void matrix_apply(Vec4f	*y, const Vec4f *x, const matrix_t *m);

//标准矩阵 4X4 
void matrix_set_identity(matrix_t *m);

//零矩阵
void matrix_set_zero(matrix_t *m);

// 平移变换
void matrix_set_translate(matrix_t *m, float x, float y, float z);

// 缩放变换
void matrix_set_scale(matrix_t *m, float x, float y, float z);

void matrix_Obj2World(matrix_t *m, Vec4f rot, Vec4f pos);

void matrix_World2Obj(matrix_t *m, Vec4f rot, Vec4f pos, float scale);

//坐标系的变化 = 基坐标的位移+坐标系的旋转   坐标系的旋转 跟 这里坐标系内部向量的旋转是一样的
//这个矩阵是基于指定向量旋转的旋转矩阵。 该指定向量为 (x,y,z)
void matrix_set_rotate(matrix_t *m, float x, float y, float z, float theta, float xOffset, float yOffest, float zOffset);






