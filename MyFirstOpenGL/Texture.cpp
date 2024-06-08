#include "Texture.h"
#include <stb_image.h>

Texture::Texture(const char* _filePath, GLuint _textureMode, int _textureIndex)
	: textureMode(_textureMode), textureIndex(_textureIndex)
{
	textureInfo = stbi_load(_filePath, &width, &height, &nrChannels, 0);
	InitTexture();
}

void Texture::InitTexture()
{
	//Definimos canal de textura activo
	GLuint textureID;
	glActiveTexture(textureMode);

	//Generar textura
	glGenTextures(1, &textureID);

	//Vinculamos texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Configurar textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Cargar imagen a la textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureInfo);

	//Generar mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	//Liberar memoria de la imagen cargada
	stbi_image_free(textureInfo);
}
