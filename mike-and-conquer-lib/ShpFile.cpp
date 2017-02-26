#include "ShpFile.h"

#include <vector>
#include <fstream>

#include "ImageHeader.h"


static std::vector<unsigned char> ReadAllBytes(char const* filename) {
	std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = ifs.tellg();

	std::vector<char>  result(pos);

	ifs.seekg(0, std::ios::beg);
	ifs.read(&result[0], pos);

	std::vector<unsigned char> unsignedResult;
	for (std::vector<char>::iterator it = result.begin(); it != result.end(); ++it) {
		unsignedResult.push_back(*it);
	}

	return unsignedResult;
}



uint16_t ReadUInt16(std::ifstream * stream) {
	char charByte0;
	char charByte1;
	*stream >> charByte0;
	*stream >> charByte1;
	return (charByte1 * 256) + charByte0;
}




ShpFile::ShpFile(std::string & filename) {
	shpFileStream = new std::ifstream(filename, std::ios::binary | std::ios::ate);
	std::ifstream::pos_type pos = shpFileStream->tellg();
	shpFileStream->seekg(0, std::ios::beg);

	charVector = ReadAllBytes(filename.c_str());
	numberOfImages = ReadUInt16(shpFileStream);  // 0, 1
	ReadUInt16(shpFileStream);  // 2, 3
	ReadUInt16(shpFileStream);  // 4, 5

	width = ReadUInt16(shpFileStream);  // 6, 7
	height = ReadUInt16(shpFileStream);  // 8, 9

	ReadUInt16(shpFileStream);  
	ReadUInt16(shpFileStream);  

	ImageHeader * imageHeader = new ImageHeader(*shpFileStream);
	imageHeaders.push_back(imageHeader);
}


int ShpFile::Width() {
	return width;
}

int ShpFile::Height() {
	return height;
}

long ShpFile::Size() {
	return charVector.size();
}


int ShpFile::NumberOfImages() {
	return numberOfImages;
}


std::vector<unsigned char> & ShpFile::SpriteFrame1() {
	return spriteFrame1Vector;
}	



std::vector<ImageHeader *> & ShpFile::ImageHeaders() {
	return this->imageHeaders;
}