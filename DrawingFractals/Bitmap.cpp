#include <fstream>
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

#include <iostream>

using namespace std;

Bitmap::Bitmap(int width, int height) : m_width(width), m_height(height), m_pPixels(new uint8_t[width * height * 3]())
{
}

bool Bitmap::write(string filename)
{
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;

	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (m_width * m_height * 3);
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

	infoHeader.width = m_width;
	infoHeader.height = m_height;

	ofstream file(filename, ios::out | ios::binary);

	if (!file) {
		cout << "Cannot create file" << endl;
		return false;
	}

	file.write((char*)&fileHeader, sizeof(fileHeader));
	file.write((char*)&infoHeader, sizeof(infoHeader));
	file.write((char*)m_pPixels.get(), m_width * m_height * 3);

	file.close();

	return true;
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	int baseIndex = (y * 3) * m_width + (x * 3);

	m_pPixels[baseIndex + 0] = blue;
	m_pPixels[baseIndex + 1] = green;
	m_pPixels[baseIndex + 2] = red;
}

Bitmap::~Bitmap()
{
}
