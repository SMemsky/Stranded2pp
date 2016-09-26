#pragma once

#include <string>

#include "../Color.h"

#include "common/math/Matrix4.h"
#include "common/math/Rect.h"
#include "common/math/Vector2.h"
#include "common/math/Vector3.h"

namespace gfx
{

class Image;
class Material;
class Texture;
class Vertex3D;

namespace device
{

class Device
{
public:
	enum TransformType
	{
		Projection = 0,
		Model = 1,
		View,
		Texture0,
		Texture1,

		TransformCount
	};

	static const unsigned maxTextures = 2;
public:
	Device();
	virtual ~Device();

	virtual bool init() = 0;

	// Device info

	virtual math::Vector2u getRenderTargetSize() const = 0;

	// Data management

	virtual Texture* getTexture(const std::string& name) const = 0;
	virtual Texture* loadTextureFromFile(const std::string& name,
		bool applyColorKey = false) = 0;
	virtual void unloadAllTextures() = 0;

	// Rendering utilities

	virtual void beginScene() = 0;
	virtual void endScene() = 0;

	virtual void setClearColor(const Color& color) = 0;

	virtual void clearZBuffer() = 0;

	// Rendering properties

	virtual void setTransform(TransformType transformType,
		const math::Matrix4& transform) = 0;
	virtual void resetTransforms() = 0;
	virtual void setMaterial(const Material& material) = 0;

	// 3D Drawing

	virtual void draw3DLine(const math::Vector3f& start,
		const math::Vector3f& end,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void drawIndexedPrimitiveList(const Vertex3D* vertices,
		uint32_t vertexCount, const uint16_t* indices,
		uint32_t primitiveCount) = 0;

	// 2D Drawing

	virtual void drawPixel(unsigned x, unsigned y,
		const Color& pixelColor = Color(255, 255, 255, 255)) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Vector2i& imageDestination) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Vector2i& imageDestination,
		const math::Recti& sourceRectangle,
		const Color& color = Color(255, 255, 255, 255),
		const math::Recti* clippingRectangle = nullptr,
		bool useAlphaChannel = true) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Recti& destinationRectangle) = 0;

	virtual void draw2DImage(Texture* texture,
		const math::Recti& destinationRectangle,
		const math::Recti& sourceRectangle, const Color* colors = nullptr,
		const math::Recti* clippingRectangle = nullptr,
		bool useAlphaChannel = true) = 0;

	virtual void draw2DLine(const math::Vector2i& start,
		const math::Vector2i& end,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void draw2DPolygon(const math::Vector2i& center, float radius,
		unsigned vertexCount = 10,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	virtual void draw2DRectangle(const math::Recti& destinationRectangle,
		const Color& color = Color(255, 255, 255, 255),
		const math::Recti* clippingRectangle = nullptr) = 0;

	virtual void draw2DRectangle(const math::Recti& destinationRectangle,
		const Color& colorLeftUp, const Color& colorRightUp,
		const Color& colorLeftDown, const Color& colorRightDown,
		const math::Recti* clippingRectangle = nullptr) = 0;

	virtual void draw2DRectangleOutline(const math::Recti& destinationRectangle,
		const Color& color = Color(255, 255, 255, 255)) = 0;

	// Utility events

	virtual void onResize(const math::Vector2u& size) = 0;
protected:
	std::string deviceName;
};

} // namespace device

} // namespace gfx