# include <stdio.h>
# include "../include/scop.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


#  define SCR_HEIGHT 600
#  define SCR_WIDTH 800




// Parse Bmp Header
// Infos at:
// http://www.apprendre-en-ligne.net/info/images/formatbmp.pdf
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

	return (header);
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, float *mix_level, t_float3 *rotation, t_float3 *translation, t_float3 *size);

// settings



void	print_mat4(float *mt4)
{
	int i = 0;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			printf("%f ", mt4[i]);
			i++;
		}
		printf("\n");
	}
}

int main()
{
	const char *fragmentShaderSource;
	const char *vertexShaderSource;

	fragmentShaderSource = read_file("shaders/basic/fragment.glsl", 0);
	vertexShaderSource = read_file("shaders/basic/vertex.glsl", 0);

	// float *vertices;
	// int svertices;
	// uint32_t *indices;
	// int sindices;

	// obj_parser(read_file("resources/42.obj", 0),vertices, &svertices, indices, &sindices);

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

	glEnable(GL_DEPTH_TEST); 

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
    // float vertices[] = {
    //     // positions          // colors           // texture coords
    //      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    //      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    //     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    // };
   float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
// float vertices[] = {
// -1.0, -1.0, 1.0,
// 1.0, -1.0, 1.0,
// 1.0, 1.0, 1.0,
// 1.0, 1.0, 1.0,
// -1.0, 1.0, -1.0,
// 1.0, 1.0, -1.0,
// -1.0, -1.0 -1.0,
// 1.0, -1.0, -1.0
// };

// int indices[] = {
// 1-1, 2-1, 3-1,
// 3-1, 2-1, 4-1,
// 3-1, 4-1, 5-1,
// 5-1, 4-1, 6-1,
// 5-1, 6-1, 7-1,
// 7-1, 6-1, 8-1,
// 7-1, 8-1, 1-1,
// 1-1, 8-1, 2-1,
// 2-1, 8-1, 4-1,
// 4-1, 8-1, 6-1,
// 7-1, 1-1, 5-1,
// 5-1, 1-1, 3-1,
// };
    // float vertices[] = {
    //      0.5f,  0.5f, 0.0f,  // top right
    //      0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };




	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
	 char *data_bmp = (char*)read_file("textures/awesomeface.bmp", 0);

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
	data_bmp = (char*)read_file("textures/container.bmp", 0);
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

	float mix_level = 0.5;
	// float rotation = 0;
	t_float3 rotation = {.x = 0, .y = 0, .z = 0};
	t_float3 translation = {.x = 0, .y = 0, .z = 0};
	t_float3 size = {.x = 1, .y = 1, .z = 1};

	glUseProgram(shaderProgram);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
	glUniform1f(glGetUniformLocation(shaderProgram, "mix_level"), mix_level);
	// int vertexColorLocation = glGetUniformLocation(shaderProgram, "texture2");



	// glUniform1f(vertexColorLocation, 0)

	// as we only have a single shader, we could also just activate our shader once beforehand if we want to 

		float *mt4;

		mt4 = create_mat4();


		float *view;

		view = create_mat4();
		view = translate_mat4(view, (t_float3){.x = 0, .y = 0, .z = 0.0});

		float *projection;
		projection = create_mat4();
		projection = set_projection_matrix(projection, 90.);




	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window, &mix_level, &rotation, &translation, &size);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		
		//glUseProgram(shaderProgram);

	 	// glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		mt4 =reset_mat4(mt4);
		// mt4 = rotate_x_mat4(mt4, rotation.x);
		//mt4 = rotate_mat4(mt4, rotation);
		mt4 = rotate_mat4(mt4, (t_float3){.x = glfwGetTime() * 0.5, .y = glfwGetTime() * 1, .z = 0});
		
		mt4 = scale_mat4(mt4, size);
		//mt4 = translate_mat4(mt4, translation);
		 mt4 = translation_mat4(mt4, translation);


		// print_mat4(mt4);
		// printf("\n\n");

		GLfloat testGL[16] = {	1, 0, 0, 0.5,
								0, 1, 0, 0.5,
								0, 0, 1, 0.5,
								0, 0, 0, 1};
		mt4	 = convert_mat4_to_4fv(mt4);






		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, view);
		
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, projection);
		
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, (const GLfloat*)mt4);
		// glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, testGL);


		glUniform1f(glGetUniformLocation(shaderProgram, "mix_level"), mix_level);


		glUseProgram(shaderProgram);


		glBindVertexArray(VAO);
        
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
void processInput(GLFWwindow *window, float *mix_level, t_float3 *rotation, t_float3 *translation, t_float3 *size)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotation->x += 0.01;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotation->x -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotation->y += 0.01;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotation->y -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		rotation->z += 0.01;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		rotation->z -= 0.01;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		translation->x += 0.01;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		translation->x -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		translation->y += 0.01;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		translation->y -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		translation->z += 0.01;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		translation->z -= 0.01;

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		size->x += 0.01;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		size->x -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		size->y += 0.01;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		size->y -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		size->z += 0.01;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		size->z -= 0.01;


}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}