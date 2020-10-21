# include <stdio.h>
# include "../include/scop.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


#define BUFF_SIZE 256


void	put_exa(int nb, int len)
{
	if (len > 0)
		put_exa(nb / 16, len - 1);
	if (nb % 16 >= 0 && nb % 16 <= 9)
		ft_putchar(nb % 16 + 48);
	else
		ft_putchar(nb % 16 + 'a' - 10);
}

void	print_memory(const void *addr, size_t size)
{
    unsigned int i;

	unsigned int		tmp;
	void				*addr_tmp;
	unsigned char		*visi;
	short int			first;
	unsigned int		re;

	//size = size / sizeof(int);
	addr_tmp = (void*)addr;
	visi = (unsigned char *)addr;
	i = 0;
	tmp = 0;
	first = 1;
	while (i < size)
	{
		put_exa(visi[i], 1);
		if (i % 2 == 1 && i != 0)
			ft_putstr(" ");
		if ((i + 1) % 16 == 0 && i != 0)
		{
			first = 0;
			while ((tmp ) % 16 != 0 || first == 0)
			{
				if (visi[tmp] >= 32 && visi[tmp] <= 126)
					ft_putchar(visi[tmp]);
				else
					ft_putchar('.');
				//ft_putstr("...");
				first = 1;
				tmp++;
			}
			ft_putchar('\n');
			tmp = i + 1;
		}
		i++;
	}
		if ((i) % 16 != 0 && i != 0)
		{
//			put_exa(i%12, 1);
			re = (16 - (i % 16)) * 2;
			re = re + ((16 - (i % 16) + 1) / 2);
			while (re > 0)
			{
				ft_putchar(' ');
				re--;
			}
			first = 0;
			while (tmp < size)
			{
				if (visi[tmp] >= 32 && visi[tmp] <= 126)
					ft_putchar(visi[tmp]);
				else
					ft_putchar('.');
//				ft_putstr("...");
				first = 1;
				tmp++;
			}
			ft_putchar('\n');
			tmp = i;
		}
}

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



char *str_add(char *s1, char *s2, int index1, int index2)
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

uint32_t	convert_4bits_to_uint32(void *addr)
{
	return (*((uint8_t*)addr + 0x0) * 0x1000
			+ *((uint8_t*)addr + 0x1) * 0x0100
			+ *((uint8_t*)addr + 0x2) * 0x0010
			+ *((uint8_t*)addr + 0x3) * 0x0001);
}

t_bmp_header serialize_bmp_header(void *addr)
{
	t_bmp_header header;

	//File header
	header.ftype          = *((uint16_t*)(addr + 0x00));
	header.fsize          = *((uint32_t*)(addr + 0x02));
	header.freserve1      = *((uint16_t*)(addr + 0x06));
	header.freserve2      = *((uint16_t*)(addr + 0x08));
	header.foffbits       = *((uint32_t*)(addr + 0x0A));

	//Bitmap header
	header.bsize          = *((uint32_t*)(addr + 0x0E));
	header.bwidth         = *((uint32_t*)(addr + 0x12));
	header.bheight        = *((uint32_t*)(addr + 0x16));
	header.bplanes        = *((uint16_t*)(addr + 0x1A));
	header.bbitcount      = *((uint16_t*)(addr + 0x1C));
	header.bcompression   = *((uint32_t*)(addr + 0x1E));
	header.bsizeimage     = *((uint32_t*)(addr + 0x22));
	header.bxpelspermeter = *((uint32_t*)(addr + 0x26));
	header.bypelspermeter = *((uint32_t*)(addr + 0x2A));
	header.bclrused       = *((uint32_t*)(addr + 0x2E));
	header.bclrimportant  = *((uint32_t*)(addr + 0x32));

	// printf("next bytes :\n");
	// ft_print_memory(addr + 0x12, 4);
	// ft_print_memory(addr + 0x22, 4);

	// printf("\n");
	// printf("New sizeimage =%x\n", *((uint32_t*)(addr + 0x22)));
	return (header);
}

char *open_shader(char *shader_path)
{
	int fd;
	int index;
	int total_index;
	char *shader;
	char buffer[256];


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
	//printf("Shader :%s, \n", shader);

	return (shader);
}

	// const char *fragmentShaderSource;
	// const char *vertexShaderSource;

	// fragmentShaderSource = open_shader("shaders/basic/fragment.glsl");
	// vertexShaderSource = open_shader("shaders/basic/vertex.glsl");


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	const char *fragmentShaderSource;
	const char *vertexShaderSource;

	fragmentShaderSource = open_shader("shaders/basic/fragment.glsl");
	vertexShaderSource = open_shader("shaders/basic/vertex.glsl");


	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		ft_putstr_fd("Failed to create GLFW window", 2);
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		ft_putstr_fd("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", 2);
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		ft_putstr_fd("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", 2);
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		ft_putstr_fd("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", 2);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// printf("Hello\n");
	 // char *data_bmp = (char*)open_shader("textures/wall.bmp");
	//  char *data_bmp = (char*)open_shader("textures/container.bmp");
	 char *data_bmp = (char*)open_shader("textures/awesomeface.bmp");

	t_bmp_header bmpheader;
	bmpheader = serialize_bmp_header(data_bmp);

	// printf("bmp header :Width = %ud, Height = %ud\n", bmpheader.bwidth, bmpheader.bheight);
		printf("bmp header :Width = %ud, Height = %ud, Bit per px %x\n", bmpheader.bwidth, bmpheader.bheight, bmpheader.bbitcount);


	printf("Memory :\n");

	ft_print_memory(data_bmp, 42);

	// // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// // glBindVertexArray(0);

	// if (data)
	// {
	// 	//printf("data:%s\n", data);
	// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_INT_8_8_8_8, data + 0x000A);
    // 	glGenerateMipmap(GL_TEXTURE_2D);
	// }


 
    // load image, create texture and generate mipmaps
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    if (data_bmp)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if (bmpheader.bbitcount == 0x20)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpheader.bwidth, bmpheader.bheight, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data_bmp+bmpheader.foffbits);
		}
		else if (bmpheader.bbitcount == 0x18)
		{
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpheader.bwidth, bmpheader.bheight, 0, GL_BGR, GL_UNSIGNED_BYTE, data_bmp+bmpheader.foffbits);
		}
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ft_putstr_fd("Failed to load texture1",2);
    }
	free(data_bmp);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// data_bmp = (char*)open_shader("textures/awesomeface.bmp");
	data_bmp = (char*)open_shader("textures/container.bmp");
	bmpheader = serialize_bmp_header(data_bmp);
		printf("bmp header :Width = %ud, Height = %ud, bit per px %x\n", bmpheader.bwidth, bmpheader.bheight, bmpheader.bbitcount);


	printf("Memory :\n");
	ft_print_memory(data_bmp, 42);

    if (data_bmp)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if (bmpheader.bbitcount == 0x20)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpheader.bwidth, bmpheader.bheight, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data_bmp+bmpheader.foffbits);
		}
		else if (bmpheader.bbitcount == 0x18)
		{
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpheader.bwidth, bmpheader.bheight, 0, GL_BGR, GL_UNSIGNED_BYTE, data_bmp+bmpheader.foffbits);
		}
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        ft_putstr_fd("Failed to load texture2",2);
    }
	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	// int vertexColorLocation = glGetUniformLocation(shaderProgram, "texture2");

	// glUniform1f(vertexColorLocation, 0)

	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glUseProgram(shaderProgram);

	 	// glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		glUseProgram(shaderProgram);


		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// // render the triangle
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return (0);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}