
# define GL_SILENCE_DEPRECATION
# define TRUE 1
# include <OpenGL/gl3.h>
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include "../lib/libft/includes/libft.h"

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

char *read_file(char *shader_path, int *size);
