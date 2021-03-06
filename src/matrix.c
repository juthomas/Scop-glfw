
# include "../include/scop.h"
# include <math.h>

#  define SCR_HEIGHT 600
#  define SCR_WIDTH 800

float			*cpy_mat(float *mt4_src, float *mt4_dst)
{
	mt4_dst[0] = mt4_src[0];
	mt4_dst[1] = mt4_src[1];
	mt4_dst[2] = mt4_src[2];
	mt4_dst[3] = mt4_src[3];

	mt4_dst[4] = mt4_src[4];
	mt4_dst[5] = mt4_src[5];
	mt4_dst[6] = mt4_src[6];
	mt4_dst[7] = mt4_src[7];

	mt4_dst[8] = mt4_src[8];
	mt4_dst[9] = mt4_src[9];
	mt4_dst[10] = mt4_src[10];
	mt4_dst[11] = mt4_src[11];

	mt4_dst[12] = mt4_src[12];
	mt4_dst[13] = mt4_src[13];
	mt4_dst[14] = mt4_src[14];
	mt4_dst[15] = mt4_src[15];
	return (mt4_dst);
}

float			*reset_mat4(float *mt4)
{
	mt4[0] = IDENTITY;
	mt4[1] = 0;
	mt4[2] = 0;
	mt4[3] = 0;

	mt4[4] = 0;
	mt4[5] = IDENTITY;
	mt4[6] = 0;
	mt4[7] = 0;

	mt4[8] = 0;
	mt4[9] = 0;
	mt4[10] = IDENTITY;
	mt4[11] = 0;
	
	mt4[12] = 0;
	mt4[13] = 0;
	mt4[14] = 0;
	mt4[15] = IDENTITY;
	return(mt4);
}

float			*create_mat4()
{
	float *mat4;

	mat4 = (float*)malloc(sizeof(float) * 16);
	mat4 = reset_mat4(mat4);
	return (mat4);
}


/*
 *      # # # X
 *      # # # Y
 *      # # # Z
 *      # # # #
 */
// Create translation matrix
float			*translation_mat4(float *mt4, t_float3 translation_vector)
{
	mt4[3] = translation_vector.x;
	mt4[7] = translation_vector.y;
	mt4[11] = translation_vector.z;
	return(mt4);
}


/*
 *      X # # #
 *      # Y # #
 *      # # Z #
 *      # # # #
 */
// Create scaling matrix
float			*scaling_mat4(float *mt4, t_float3 scaling_vector)
{
	mt4[0] = scaling_vector.x;
	mt4[5] = scaling_vector.y;
	mt4[10] = scaling_vector.z;
	return (mt4);
}

/*
 *      #   #   #   #
 *
 *      #  cos -sin #
 *
 *      #  sin cos  #
 *
 *      #   #   #   #
 */
// Create rotation matrix
float			*rotation_x_mat4(float *mt4, float angle)
{
	mt4[5] = cos(angle);
	mt4[6] = -sin(angle);
	mt4[9] = sin(angle);
	mt4[10] = cos(angle);
	return (mt4);
}

/*
 *     cos  #  sin  #
 *
 *      #   #   #   #
 *
 *     -sin #  cos  #
 *
 *      #   #   #   #
 */
// Create rotation matrix
float			*rotation_y_mat4(float *mt4, float angle)
{
	mt4[0] = cos(angle);
	mt4[2] = sin(angle);
	mt4[8] = -sin(angle);
	mt4[10] = cos(angle);
	return (mt4);
}


/*
 *     cos -sin #   #
 *
 *     sin cos  #   #
 *
 *      #   #   #   #
 *
 *      #   #   #   #
 */
// Create rotation matrix
float			*rotation_z_mat4(float *mt4, float angle)
{
	mt4[0] = cos(angle);
	mt4[1] = -sin(angle);
	mt4[4] = sin(angle);
	mt4[5] = cos(angle);
	return (mt4);
}



// translate current matrix
float			*translate_mat4(float *mt4, t_float3 translation_vector)
{
	float *mt4_tmp;
	float *mt4_result;

	mt4_tmp = create_mat4();
	mt4_tmp = translation_mat4(mt4_tmp, translation_vector);
	//return (mt4_tmp);
	mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, NULL);
	mt4 = cpy_mat(mt4_result, mt4);
	free(mt4_result);
	free(mt4_tmp);
	return (mt4);
}


// Scale current matrix
float			*scale_mat4(float *mt4, t_float3 scaling_vector)
{
	float *mt4_tmp;
	float *mt4_result;
	mt4_tmp = create_mat4();

	mt4_tmp = scaling_mat4(mt4_tmp, scaling_vector);
	mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, NULL);
	mt4 = cpy_mat(mt4_result, mt4);
	free(mt4_result);
	free(mt4_tmp);
	return (mt4);
}


// Rotate current matrix
float			*rotate_x_mat4(float *mt4, float angle)
{
	float *mt4_tmp;
	float *mt4_result;
	mt4_tmp = create_mat4();

	mt4_tmp = rotation_x_mat4(mt4_tmp, angle);
	mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, NULL);
	mt4 = cpy_mat(mt4_result, mt4);
	free(mt4_result);
	free(mt4_tmp);
	return (mt4);
}

// Rotate current matrix
float			*rotate_y_mat4(float *mt4, float angle)
{
	float *mt4_tmp;
	float *mt4_result;
	mt4_tmp = create_mat4();

	mt4_tmp = rotation_y_mat4(mt4_tmp, angle);
	mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, NULL);
	mt4 = cpy_mat(mt4_result, mt4);
	free(mt4_result);
	free(mt4_tmp);
	return (mt4);
}

// Rotate current matrix
float			*rotate_z_mat4(float *mt4, float angle)
{
	float *mt4_tmp;
	float *mt4_result;
	mt4_tmp = create_mat4();

	mt4_tmp = rotation_z_mat4(mt4_tmp, angle);
	mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, NULL);
	mt4 = cpy_mat(mt4_result, mt4);
	free(mt4_result);
	free(mt4_tmp);
	return (mt4);
}




float			*rotate_mat4(float *mt4,  t_float3 rotation_vector)
{
	float *mt4_tmp;
	float *mt4_result;
	mt4_tmp = create_mat4();
	mt4_result = create_mat4();
	mt4_result = cpy_mat(mt4, mt4_result);

	if (rotation_vector.x != 0)
	{
		mt4_tmp = rotate_x_mat4(mt4_tmp, rotation_vector.x);
		mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, mt4_result);
		mt4_tmp = reset_mat4(mt4_tmp);
		mt4 = cpy_mat(mt4_result, mt4);
	}
	if (rotation_vector.y != 0)
	{
		mt4_tmp = rotate_y_mat4(mt4_tmp, rotation_vector.y);
		mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, mt4_result);
		mt4_tmp = reset_mat4(mt4_tmp);
		mt4 = cpy_mat(mt4_result, mt4);
	}
	if (rotation_vector.z != 0)
	{
		mt4_tmp = rotate_z_mat4(mt4_tmp, rotation_vector.z);
		mt4_result = multiply_mat4_per_mat4(mt4_tmp, mt4, mt4_result);
		mt4_tmp = reset_mat4(mt4_tmp);
		mt4 = cpy_mat(mt4_result, mt4);
	}
	free(mt4_tmp);
	free(mt4_result);
	return (mt4);
}

t_float3	subtract_b_to_a_float3(t_float3 a, t_float3 b)
{
	return ((t_float3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z});
}

t_float3	normalize_float3(t_float3 vector)
{
	float len;

	len = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	return ((t_float3){.x = vector.x / len, .y = vector.y / len, .z = vector.z / len});
}

t_float3	cross_product_float3(t_float3 a, t_float3 b)
{
	return ((t_float3){.x = a.y * b.z - a.z * b.y,
						.y = a.z * b.x - a.x * b.z,
						.z = a.x * b.y - a.y * b.x});
}

t_float3	dot_product_float3(t_float3 a, t_float3 b)
{
	return ((t_float3){.x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z});
}

float		dot_float3(t_float3 a, t_float3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	*look_at(float *mt4_camera, float *mt4_target)
{
	t_float3 camera_pos;
	t_float3 camera_target;
	t_float3 camera_direction;
	t_float3 up;
	t_float3 camera_right;
	t_float3 camera_up;
	t_float3 f;
	t_float3 u;
	t_float3 s;



	float	*mt4_result;
	camera_pos = (t_float3){.x = 0.0, .y = 0.0, .z = 3.0};
	camera_target = (t_float3){.x = 0.0, .y = 0.0, .z = 0.0};
	up = (t_float3){.x = 0.0, .y = 1.0, .z = 0.0};

	camera_direction = normalize_float3(subtract_b_to_a_float3(camera_pos, camera_target));
	camera_right = normalize_float3(cross_product_float3(up, camera_direction));
	camera_up = cross_product_float3(camera_direction, camera_right);

	f = normalize_float3(subtract_b_to_a_float3(camera_target, camera_pos));
	s = normalize_float3(cross_product_float3(f, normalize_float3(up)));
	u = cross_product_float3(s, f);


	mt4_result = create_mat4();


	mt4_result[0] = s.x;
	mt4_result[1] = u.x;
	mt4_result[2] = f.x;
	// mt4_result[3] = 

	mt4_result[4] = s.y;
	mt4_result[5] = u.y;
	mt4_result[6] = f.y;
	// mt4_result[7] = 

	mt4_result[8] = s.z;
	mt4_result[9] = u.z;
	mt4_result[10] = f.z;
	// mt4_result[11] = 

	mt4_result[12] = -dot_float3(s, camera_pos);
	mt4_result[13] = -dot_float3(u, camera_pos);
	mt4_result[14] = dot_float3(f, camera_pos);
	// mt4_result[15] = 

	return (mt4_result);
}


float	*set_projection_matrix(float *mt4, float fov)
{
	float	scale;
	float	far;
	float	near;

	far = 10000;
	near = 0.001;
	scale = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	mt4 = reset_mat4(mt4);

	//mat4_set(&env->matrice.projection, IDENTITY);
	mt4[0] = scale / ((float)SCR_WIDTH / (float)SCR_HEIGHT);
	mt4[5] = scale;
	mt4[10] = -(far + near) / (far - near);
	mt4[11] = -1;
	mt4[14] = -2 * far * near / (far - near);
	return (mt4);
}



t_float4		multiply_mat4_per_float4(float *mt4, t_float4 vector)
{
	t_float4 ret;
	ret.x = mt4[0] * vector.x + mt4[1] * vector.y + mt4[2] * vector.z + mt4[3] * vector.w;
	ret.y = mt4[4] * vector.x + mt4[5] * vector.y + mt4[6] * vector.z + mt4[7] * vector.w;
	ret.z = mt4[8] * vector.x + mt4[9] * vector.y + mt4[10] * vector.z + mt4[11] * vector.w;
	ret.w = mt4[12] * vector.x + mt4[13] * vector.y + mt4[14] * vector.z + mt4[15] * vector.w;
	return (ret);
}

/*
 *      0  1  2  3        0  1  2  3
 *      4  5  6  7        4  5  6  7 
 *      8  9  10 11   *   8  9  10 11
 *      12 13 14 15       12 13 14 15
 */
float			*multiply_mat4_per_mat4(float *mt4_1, float *mt4_2, float *mt4_dst)
{
	float *mt4;

	if (mt4_dst == NULL)
	{
		mt4 = create_mat4();
	}
	else
	{
		mt4 = mt4_dst;
	}

	mt4[0] = mt4_1[0] * mt4_2[0] + mt4_1[1] * mt4_2[4] + mt4_1[2] * mt4_2[8] + mt4_1[3] * mt4_2[12];
	mt4[1] = mt4_1[0] * mt4_2[1] + mt4_1[1] * mt4_2[5] + mt4_1[2] * mt4_2[9] + mt4_1[3] * mt4_2[13];
	mt4[2] = mt4_1[0] * mt4_2[2] + mt4_1[1] * mt4_2[6] + mt4_1[2] * mt4_2[10] + mt4_1[3] * mt4_2[14];
	mt4[3] = mt4_1[0] * mt4_2[3] + mt4_1[1] * mt4_2[7] + mt4_1[2] * mt4_2[11] + mt4_1[3] * mt4_2[15];

	mt4[4] = mt4_1[4] * mt4_2[0] + mt4_1[5] * mt4_2[4] + mt4_1[6] * mt4_2[8] + mt4_1[7] * mt4_2[12];
	mt4[5] = mt4_1[4] * mt4_2[1] + mt4_1[5] * mt4_2[5] + mt4_1[6] * mt4_2[9] + mt4_1[7] * mt4_2[13];
	mt4[6] = mt4_1[4] * mt4_2[2] + mt4_1[5] * mt4_2[6] + mt4_1[6] * mt4_2[10] + mt4_1[7] * mt4_2[14];
	mt4[7] = mt4_1[4] * mt4_2[3] + mt4_1[5] * mt4_2[7] + mt4_1[6] * mt4_2[11] + mt4_1[7] * mt4_2[15];

	mt4[8] = mt4_1[8] * mt4_2[0] + mt4_1[9] * mt4_2[4] + mt4_1[10] * mt4_2[8] + mt4_1[11] * mt4_2[12];
	mt4[9] = mt4_1[8] * mt4_2[1] + mt4_1[9] * mt4_2[5] + mt4_1[10] * mt4_2[9] + mt4_1[11] * mt4_2[13];
	mt4[10] = mt4_1[8] * mt4_2[2] + mt4_1[9] * mt4_2[6] + mt4_1[10] * mt4_2[10] + mt4_1[11] * mt4_2[14];
	mt4[11] = mt4_1[8] * mt4_2[3] + mt4_1[9] * mt4_2[7] + mt4_1[10] * mt4_2[11] + mt4_1[11] * mt4_2[15];

	mt4[12] = mt4_1[12] * mt4_2[0] + mt4_1[13] * mt4_2[4] + mt4_1[14] * mt4_2[8] + mt4_1[15] * mt4_2[12];
	mt4[13] = mt4_1[12] * mt4_2[1] + mt4_1[13] * mt4_2[5] + mt4_1[14] * mt4_2[9] + mt4_1[15] * mt4_2[13];
	mt4[14] = mt4_1[12] * mt4_2[2] + mt4_1[13] * mt4_2[6] + mt4_1[14] * mt4_2[10] + mt4_1[15] * mt4_2[14];
	mt4[15] = mt4_1[12] * mt4_2[3] + mt4_1[13] * mt4_2[7] + mt4_1[14] * mt4_2[11] + mt4_1[15] * mt4_2[15];
	return (mt4);
}


float		*convert_mat4_to_4fv(float *mat)
{
	int         i;
	int         k;
	float       *dst;

	dst = create_mat4();

	i = -1;
	while (++i < 4)
	{
		k = -1;
		while(++k < 4)
			dst[k * 4 + i] = mat[i * 4 + k];
	}
	mat = cpy_mat(dst, mat);
	free(dst);
	return (mat);
}
