#pragma once
#include "math/vmatrix.h"

class CViewSetup {
public:
	int			x, x_old;
	int			y, y_old;
	int			width, width_old;
	int			height, height_old;
	bool		ortho;
	float		ortho_left;
	float		ortho_top;
	float		ortho_right;
	float		ortho_bottom;
	bool		custom_view_matrix;
	matrix3x4_t	mat_custom_view_matrix;
	char		pad_0x68[0x48];
	float		fov;
	float		viewmodel_fov;
	Vector		origin;
	QAngle		angles;
	float		z_near;
	float		z_far;
	float		near_viewmodel;
	float		nar_viewmodel;
	float		aspect_ratio;
	float		near_blur_depth;
	float		near_focus_depth;
	float		far_focus_depth;
	float		far_blur_depth;
	float		near_blur_radius;
	float		far_blur_radius;
	int			do_f_quality;
	int			motion_blur_mode;
	float		shutter_time;
	Vector		shutter_open_position;
	Vector		shutter_open_angles;
	Vector		shutter_close_position;
	Vector		shutter_close_angles;
	float		off_center_top;
	float		off_center_bottom;
	float		off_center_left;
	float		off_center_right;
	int			edge_blur;
};