
#include "../include/scop.h"

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


void	load_texture(unsigned int *texture, char *path_to_texture)
{
	char *data_bmp;
	t_bmp_header bmpheader;
	
	glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// data_bmp = (char*)open_shader("textures/awesomeface.bmp");
	data_bmp = (char*)read_file(path_to_texture, 0);
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
        ft_putstr_fd("Failed to load texture",2);
    }
}
