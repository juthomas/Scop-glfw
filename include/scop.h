
# define GL_SILENCE_DEPRECATION
# define TRUE 1
# include <OpenGL/gl3.h>
# include <GLFW/glfw3.h>
# include <fcntl.h>
# include "../lib/libft/includes/libft.h"

typedef struct	s_scop
{
	GLFWwindow		*win;
	int				width;
	int				height;
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	shaderProgram;

}				t_scop;