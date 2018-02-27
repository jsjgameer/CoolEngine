#pragma once
#include <stdbool.h>
#include "shaderStruct.h"


typedef enum {
	perspective, //透视
	orthographic //正视
} PROJECTION;

typedef struct  camera_temp
{
	//x朝画布外，z朝上，y朝右

	// 这里的 (x,y,z) 相当于DX 里的 (z,x,y)

	// public
	point_t pos; //位置
	vector_t front; //朝前
	vector_t worldup;  //朝上
	matrix_t view_matrix;
	matrix_t projection_matrix;
	matrix_t view_matrix_r;

	//宽高
	int width;
	int height;

	float fovy;//
	float zn; //近截面
	float zf; //远截面

			  //上下左右
	float left;
	float right;
	float bottom;
	float top;

	bool dirty; //是否清除
	PROJECTION projection;  //摄像机取景类型
	bool main;  //是否是主摄像机

				// private
	float aspect; //纵横比；屏幕高宽比
}camera;

extern float Forwardoffset;
extern camera camera_main;

#define MAX_NUM_CAMERA 10
extern camera cameras[];

void CameraInit();

void matrix_set_lookat(matrix_t *m, const vector_t *eye, const vector_t *at, const vector_t *up);

void matrix_set_perspective(matrix_t *m, float fovy, float aspect, float zn, float zf);

// 初始化，设置屏幕长宽
void transform_init(transform_t *ts, int width, int height);

void camera_update(device_t *device, camera * caneraMain);
void camera_updateShadow(device_t *device, camera * caneraMain);

void Forward();

void device_init(device_t *device, int width, int height, void *fb);

void device_destroy(device_t *device);

// 设置当前纹理
void device_set_texture(device_t *device, void *bits, long pitch, int w, int h);

// 清空 framebuffer 和 zbuffer
void device_clear(device_t *device, int mode);