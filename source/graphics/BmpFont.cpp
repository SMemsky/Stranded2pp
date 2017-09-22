#include "BmpFont.h"

#include "common/FileSystem.h"
#include "common/RingBuffer.h"
#include "graphics/device/Device.h"

namespace gfx
{

BmpFont::BmpFont(device::Device & device, std::string const & bmpFilename,
		std::string const & bmpfFilename) :
	device(device),
	bmpFilename(bmpFilename),
	texture(device.loadTextureFromFile(bmpFilename, false, true))
{
	loadFontFile(bmpfFilename);
}

BmpFont::~BmpFont()
{
	device.releaseTexture(bmpFilename);
}

void BmpFont::loadFontFile(std::string const & filename)
{
	if (!fs::checkFileExists(filename)) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": file does not exist");
	}

	RingBuffer buffer(fs::getFileSize(filename));
	if (!fs::loadFile(filename, buffer)) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": io error");
	}

	std::string header;
	if (!buffer.readNewlineTerminatedString(header)) {
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": missing info header");
	}

	uint16_t frames;
	uint16_t framesx;
	uint16_t framesy;
	if (!buffer.readUint16(frames)
		|| !buffer.readUint16(framesx)
		|| !buffer.readUint16(framesy))
	{
		throw std::runtime_error(
			std::string("Unable to load ") + filename + ": missing data header");
	}

	for (uint16_t i = 0; i < frames; ++i) {
		uint8_t character;
		uint16_t width;
		if (!buffer.readUint8(character)
			|| !buffer.readUint16(width))
		{
			throw std::runtime_error(
				std::string("Unable to load ") + filename + ": frame "
				+ std::to_string(i) + " is corrupted");
		}

		indexes[character] = i;
		charSizes[character] = width;
	}

	frameCount = frames;
	frameWidth = framesx;
	frameHeight = framesy;
}

} // namespace gfx