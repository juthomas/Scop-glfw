
#include "../include/scop.h"
#define BUFF_SIZE 256

static char *str_add(char *s1, char *s2, int index1, int index2)
{
	char *tmp;
	char *beg;
	char *tmps1;
	char *tmps2;
	tmps1 = s1;
	tmps2 = s2;

	if (!(tmp = (void*)malloc(sizeof(void) * (index1 + index2))))
	{
		ft_putstr_fd("Error fileloader malloc", 2);
		return (NULL);
	}
	beg = tmp;
	while (index1--)
	{
		*(char*)tmp++ = *(const char*)s1++;
	}
	while (index2--)
	{
		*(char*)tmp++ = *(const char*)s2++;
	}
	if (tmps1)
	{
		free(tmps1);
	}
	return (beg);
}

char *read_file(char *shader_path, int *size)
{
	int fd;
	int index;
	int total_index;
	char *shader;
	char buffer[BUFF_SIZE];


	total_index = 0;
	shader = NULL;
	if ((fd = open(shader_path, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error opening shader\n", 2);
	}
	while ((index = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[index]= '\0';
		shader = str_add(shader, buffer,  total_index, index);
		total_index = index + total_index;
	}
	shader[total_index] = '\0';
	if (size != NULL)
	{
		*size = total_index;
	}
	return (shader);
}