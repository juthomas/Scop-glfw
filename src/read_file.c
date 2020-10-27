
#include "../include/scop.h"
#define BUFF_SIZE 256

int64_t	get_file_size(char *file_path)
{
	int		fd;
	int64_t	size;
	int64_t	index;
	char buffer[BUFF_SIZE];

	size = 0;
	if ((fd = open(file_path, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error opening file : \n", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	while ((index = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		size += index;
	}
	close(fd);
	return (size);
}


char *read_file(char *file_path, int *size)
{
	int fd;
	int index;
	char *shader;
	char buffer[BUFF_SIZE];
	char *output;
	char *output_beg;
	int64_t	file_size;

	

	if ((file_size = get_file_size(file_path)) <= 0 )
	{
		return (NULL);
	}
	printf("file size:%d\n", file_size );

	if (!(output = (char*)malloc(sizeof(char) * file_size)))
	{
		ft_putstr_fd("Error malloc file \n", 2);
		return (NULL);
	}
	output_beg = output;


	if ((fd = open(file_path, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error opening file\n", 2);
	}
	while ((index = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[index]= '\0';
		ft_memcpy(output, buffer, index);
		output += index;
	}
	close(fd);
	*output = '\0';
	if (size != NULL)
	{
		*size = file_size;
	}
	return (output_beg);
}