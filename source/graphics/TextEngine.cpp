#include "TextEngine.h"

#include <iostream>

#include "common/Modification.h"
#include "graphics/device/Device.h"

namespace gfx
{

TextEngine::TextEngine(device::Device & device, Modification const & modification) :
	device(device),
	modPath(modification.getPath()),
	fonts({
		{NormalFont,		{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm.bmp"}},
		{NormalOverFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_over.bmp"}},
		{NormalDarkFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_dark.bmp"}},
		{NormalBadFont,		{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_bad.bmp"}},
		{NormalGoodFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_norm_good.bmp"}},
		{TinyFont,			{device, modPath + "sys/gfx/font_tiny.bmpf", modPath + "sys/gfx/font_tiny.bmp"}},
		{HandwritingFont,	{device, modPath + "sys/gfx/font_norm.bmpf", modPath + "sys/gfx/font_handwriting.bmp"}},
	})
{}

void TextEngine::drawSingleLine(FontType fontType, std::string const & text,
	math::Vector2i position, TextHorizontalPadding horizontalPadding,
	TextVerticalPadding verticalPadding)
{
	if (text.size() == 0) {
		return;
	}

	BmpFont const & font = fonts.at(fontType);

	unsigned const textWidth = calculateTextWidth(font, text);
	unsigned const textHeight = font.getFrameHeight();

	math::Vector2i destination = position;
	if (horizontalPadding == TextHorizontallyCentered) {
		destination.x -= textWidth / 2;
	} else if (horizontalPadding == TextPadRight) {
		destination.x -= textWidth;
	}

	if (verticalPadding == TextVerticallyCentered) {
		destination.y -= textHeight / 2;
	} else if (verticalPadding == TextPadDown) {
		destination.y -= textHeight;
	}

	for (unsigned i = 0; i < text.size(); ++i) {
		if (text[i] == ' ') {
			destination.x += font.getFrameWidth() / 2;
		} else {
			auto space = text.find(' ', i + 1);
			std::string word = text.substr(i, space - i);
			device.drawText(font, word, destination);
			i += word.size() - 1;
			destination.x += calculateTextWidth(font, word);
		}
	}
}

unsigned TextEngine::calculateTextWidth(BmpFont const & font, std::string const & text)
{
	unsigned width = 0;
	for (uint8_t character : text) {
		if (character == ' ') {
			width += font.getFrameWidth() / 2;
		} else {
			width += font.getCharacterWidth(character);
		}
	}

	return width;
}

} // namespace gfx
