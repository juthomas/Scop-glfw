
#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION
# define TRUE 1
# include <OpenGL/gl3.h>
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include "../lib/libft/includes/libft.h"
// # ifdef SCR_WIDTH
// #  define SCR_WIDTH 800
// # endif
// # ifdef SCR_HEIGHT
// #  define SCR_HEIGHT 600
// # endif
# define IDENTITY 1

typedef struct	s_float2
{
	float			x;
	float			y;
}				t_float2;


typedef struct	s_float3
{
	float			x;
	float			y;
	float			z;
}				t_float3;

typedef struct	s_float4
{
	float			x;
	float			y;
	float			z;
	float			w;
}				t_float4;


// Struct for usefull scop var
typedef struct	s_scop
{
	GLFWwindow		*win;
	int				width;
	int				height;
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	shaderProgram;

}				t_scop;

// Bmp Header
// Infos at:
// http://www.apprendre-en-ligne.net/info/images/formatbmp.pdf
typedef struct	s_bmp_header{
	uint16_t ftype;
	uint32_t fsize;
	uint16_t freserve1;
	uint16_t freserve2;
	uint32_t foffbits;
	uint32_t bsize;
	uint32_t bwidth;
	uint32_t bheight;
	uint16_t bplanes;
	uint16_t bbitcount;
	uint32_t bcompression;
	uint32_t bsizeimage;
	uint32_t bxpelspermeter;
	uint32_t bypelspermeter;
	uint32_t bclrused;
	uint32_t bclrimportant;
}				t_bmp_header;


// Matrix (et pas matrice)

// Copy mt4_src to mt4_dst, return mt4_dst
float			*cpy_mat(float *mt4_src, float *mt4_dst);

// Reset mt4 to :
// 1 0 0 0 
// 0 1 0 0 
// 0 0 1 0 
// 0 0 0 1
// return mt4
float			*reset_mat4(float *mt4);

// Create and return an identity matrix containing:
// 1 0 0 0 
// 0 1 0 0 
// 0 0 1 0 
// 0 0 0 1
float			*create_mat4();

// Create translation matrix from a reseted/new matrix, return mt4
float			*translation_mat4(float *mt4, t_float3 translation_vector);

// Create scaling matrix from a reseted/new matrix, return mt4
float			*scaling_mat4(float *mt4, t_float3 scaling_vector);

// Create rotation around X matrix from a reseted/new matrix, return mt4
float			*rotation_x_mat4(float *mt4, float angle);

// Create rotation around Y matrix from a reseted/new matrix, return mt4
float			*rotation_y_mat4(float *mt4, float angle);

// Create rotation around Z matrix from a reseted/new matrix, return mt4
float			*rotation_z_mat4(float *mt4, float angle);

// Translation current matrix, return mt4
float			*translate_mat4(float *mt4, t_float3 translation_vector);

// Scale current matrix, return mt4
float			*scale_mat4(float *mt4, t_float3 scaling_vector);

// Rotate around X current matrix, return mt4
float			*rotate_x_mat4(float *mt4, float angle);

// Rotate around Y current matrix, return mt4
float			*rotate_y_mat4(float *mt4, float angle);

// Rotate around Z current matrix, return mt4
float			*rotate_z_mat4(float *mt4, float angle);

// Rotate current matrix, return mt4
float			*rotate_mat4(float *mt4, t_float3 rotation_vector);

// Multiply mt4 by vector, return a new vector
t_float4		multiply_mat4_per_float4(float *mt4, t_float4 vector);

// Multiply mt4_1 by mt4_2, return mt4_dst if non NULL, else a new mt4
float			*multiply_mat4_per_mat4(float *mt4_1, float *mt4_2, float *mt4_dst);

//
float			*convert_mat4_to_4fv(float *mat);

float			*set_projection_matrix(float *mt4, float fov);

char *read_file(char *shader_path, int *size);
#endif