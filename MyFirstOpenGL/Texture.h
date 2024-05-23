#pragma once
#include <GL/glew.h>

class Texture
{
public:

	GLuint textureMode;

	int width, height, nrChannels;
	unsigned char* textureInfo;
	int textureIndex;

	Texture(const char* _filePath, GLuint _textureMode, int _textureIndex);

	void InitTexture();
};
