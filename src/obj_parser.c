#include "../include/scop.h"
// #define is_number(a) (a<='9' && a>='0')
int		begin_with(char *input, char *ref)
{
	if (input && ref)
	{
		while (*input && *ref && *input == *ref)
		{
			input++;
			ref++;
		}
		if (*ref == 0)
			return (1);
	}
	return (0);
}


enum		e_obj_symbols
{
	F_OBJ_SYMBOL,
	V_OBJ_SYMBOL

};


// float atof(char *s)
// {
// 	float res=0.f;
// 	unsigned long dec=1;
// 	int signe=1;
// 	unsigned long i=0;
	
// 	if(s){
// 		while(s[i]==' ' || s[i]=='\t'){
// 			i++;
// 		}
// 		if(s[i]=='+' || s[i]=='-'){
// 			if(s[i++]=='-'){
// 				signe=-1;
// 			}
// 		}
// 		while(is_number(s[i])){
// 			res*=10;
// 			res+=(int)(s[i++]-'0');
// 		}
// 		if(s[i]==',' || s[i]=='.'){
// 			i++;
// 			while(is_number(s[i])){
// 				dec*=10;
// 				res+=(float)(s[i++]-'0')/(float)dec;
// 			}
// 		}
// 	}
	
// 	return res;
// }

float	get_x_number(char *input, int number_number)
{
	int i;

	i = 0;
	for (int current_number = 1; current_number <= number_number; current_number++)
	{

		while (input[i] == ' ' )
		{
			i++;
		}
		if (current_number == number_number)
		{
			return (atof(&input[i]));
		}
		while (input[i] != ' ' && input[i] != '\n' && input[i] != '\0')
		{
			i++;
		}
	
	}
	return (0);
}

int count_floats_in_current_line(char *input)
{
	int current_floats;

	current_floats = 0;

	int i;
	i = 0;

	int state = 1;
	while (input[i] != '\0' && input[i] != '\n')
	{
		if (state == 1 && ((input[i]<='9' && input[i]>='0') || input[i] == '.'))
		{
			state = 2;
			current_floats++;
		}
		else if (input[i] != '\n' && ( input[i] == ' ' || input[i] == '-'))
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
		i++;
	}
	return (current_floats);
}


int		count_vertex_and_frags(char *input, int symbol)
{
	int count;

	count = 0;
	int i = 0;
	int x = 0;
	int tmp_count;
	while (input[i] != '\0')
	{
		if (x == 0)
		{
			if (symbol == V_OBJ_SYMBOL && begin_with(&input[i], "v")) // Vertex position
			{
				count += count_floats_in_current_line(&input[i]);
			}
			else if (symbol == F_OBJ_SYMBOL && begin_with(&input[i], "f")) // Fragment position
			{
				if (count_floats_in_current_line(&input[i]) != 3)
				{
					count += 3;
				}
				count += 3;
			}
		}
		x++;
		if (input[i] == '\n')
		{
			x = 0;
		}
		i++;
	}
	return (count);
}

void	feed_float_array_with_current_line(float *float_array, int *current_float_array_index, char *input)
{
	int i;
	i = 0;

	int state = 1;
	while (input[i] != '\0' && input[i] != '\n')
	{
		if (state == 1 && ((input[i] <='9' && input[i] >='0') || input[i] == '.' || input[i] == '-'))
		{
			state = 2;
			float_array[(*current_float_array_index)++] = atof(&input[i]);
		}
		else if (input[i] != '\n' && ( input[i] == ' ' ))
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
		i++;
	}
}

void	feed_uint32_array_with_current_line(uint32_t *float_array, int *current_float_array_index, char *input)
{
	int i;
	i = 0;

	int state = 1;
	while (input[i] != '\0' && input[i] != '\n')
	{
		if (state == 1 && ((input[i] <='9' && input[i] >='0') || input[i] == '-'))
		{
			state = 2;
			float_array[(*current_float_array_index)++] = atoi(&input[i]);
		}
		else if (input[i] != '\n' && ( input[i] == ' ' ))
		{
			state = 1;
		}
		else
		{
			state = 0;
		}
		i++;
	}
}


void	obj_parser(char *input, float *vertex_positions, int *vertex_positions_count, uint32_t *frags, int *frags_count)
{
	//ft_putstr(input);
	// float		*vertex_positions;
	// uint32_t			*frags;
	t_float3	vertex_texcoords;
	t_float4	vertex_normals;


	GLint		vertex_position_indicies;
	GLint		vertex_texcoord_indicies;
	GLint		vertex_normal_indicies;

	int i;
	int x;

	x = 0;
	i = 0;

	// int		vertex_positions_count;
	int		vertex_positions_current_index;

	// int		frags_count;
	int		frags_current_index;

	frags_current_index = 0;
	vertex_positions_current_index = 0;

	*vertex_positions_count = count_vertex_and_frags(input, V_OBJ_SYMBOL);
	printf("vertex numbers : %d\n", count_vertex_and_frags(input, V_OBJ_SYMBOL));

	*frags_count = count_vertex_and_frags(input, F_OBJ_SYMBOL);
	printf("frags numbers : %d\n", count_vertex_and_frags(input, F_OBJ_SYMBOL));


	vertex_positions = (float*)malloc(sizeof(float) * (*vertex_positions_count ));
	frags = (uint32_t*)malloc(sizeof(uint32_t) * (*frags_count));


	while (input[i] != '\0')
	{
		if (x == 0)
		{
			if (begin_with(&input[i], "#"))
			{

			}
			else if (begin_with(&input[i], "o"))
			{

			}
			else if (begin_with(&input[i], "s"))
			{

			}
			else if (begin_with(&input[i], "f"))
			{
				feed_uint32_array_with_current_line(frags, &frags_current_index, &input[i]);
				if (count_floats_in_current_line(&input[i]) == 4)
				{
					frags[frags_current_index+1] = frags[frags_current_index-1];
					frags[frags_current_index-1] = frags[frags_current_index-4];
					frags[frags_current_index] = frags[frags_current_index-2];

					frags[frags_current_index-4] -= 1;
					frags[frags_current_index-3] -= 1;
					frags[frags_current_index-2] -= 1;
					frags[frags_current_index-1] -= 1;
					frags[frags_current_index] -= 1;
					frags[frags_current_index+1] -= 1;
					frags_current_index+=2;
					printf("current index f: %d\n", frags_current_index);
				}
				else
				{
					frags[frags_current_index-3] -= 1;
					frags[frags_current_index-2] -= 1;
					frags[frags_current_index-1] -= 1;
				}
				

			}
			else if (begin_with(&input[i], "v")) // Vertex position
			{
				feed_float_array_with_current_line(vertex_positions, &vertex_positions_current_index, &input[i]);
				// printf("v  1: %f\n", get_x_number(&input[i+1], 1));
				// printf("v  2: %f\n", get_x_number(&input[i+1], 2));
				// printf("v  3: %f\n", get_x_number(&input[i+1], 3));
				printf("current index v: %d\n", vertex_positions_current_index);
			}



			ft_putchar(input[i]);
			ft_putchar('\n');
		}
		x++;
		if (input[i] == '\n')
		{
			x = 0;
		}
		i++;
	}
}
