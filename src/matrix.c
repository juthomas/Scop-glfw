
# include "../include/scop.h"
# include <math.h>

float		*create_mat4(float fill_number)
{
	float *mat4;
	int i;

	mat4 = (float*)malloc(sizeof(float) * 16);
	i = 0;
	while (i < 16)
	{
		mat4[i] = fill_number;
		i++;
	}
	return (mat4);
}

float			*translate_mat4(float *mt4, t_float3 translation_vector)
{
	mt4[0] = 1;
	mt4[1] = 0;
	mt4[2] = 0;
	mt4[3] = translation_vector.x;

	mt4[4] = 0;
	mt4[5] = 1;
	mt4[6] = 0;
	mt4[7] = translation_vector.y;

	mt4[8] = 0;
	mt4[9] = 0;
	mt4[10] = 1;
	mt4[11] = translation_vector.z;
	
	mt4[12] = 0;
	mt4[13] = 0;
	mt4[14] = 0;
	mt4[15] = 1;
	return(mt4);
}

t_float4		multiply_mat4_per_float4(float *mt4, t_float4 vector)
{
	t_float4 ret;
	ret.x = mt4[0] * vector.x + mt4[1] * vector.y + mt4[2] * vector.z + mt4[3] * vector.w;
	ret.x = mt4[4] * vector.x + mt4[5] * vector.y + mt4[6] * vector.z + mt4[7] * vector.w;
	ret.x = mt4[8] * vector.x + mt4[9] * vector.y + mt4[10] * vector.z + mt4[11] * vector.w;
	ret.x = mt4[12] * vector.x + mt4[13] * vector.y + mt4[14] * vector.z + mt4[15] * vector.w;
	return (ret);
}



t_float4	rotate_x(float angle, t_float4 dirVec)
{
	return((t_float4){.x = dirVec.x,
					.y = (cos(angle) * dirVec.y + sin(angle) * dirVec.z),
					.z = (-sin(angle) * dirVec.x + cos(angle) * dirVec.z)});
}