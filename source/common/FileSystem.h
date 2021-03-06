#pragma once

#include <string>
#include <vector>

#include "common/ByteBuffer.h"

namespace fs
{
	void scanFolder(std::string const & pathToFolder, std::vector<std::string> & results);

	bool checkFolderExists(std::string const & pathToFolder);
	bool checkFileExists(std::string const & pathToFile);

	std::size_t getFileSize(std::string const & pathToFile);
	bool loadFile(std::string const & pathToFile, ByteBuffer & buffer);
} // namespace fs
