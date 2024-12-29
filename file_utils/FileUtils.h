#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

namespace FileUtils {

std::string ReadFile(const std::filesystem::path& path) {
	assert(std::filesystem::exists(path));
	auto inputFile = std::ifstream(path);
	assert(static_cast<bool>(inputFile));
	return std::string(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());
}

} // namespace FileUtils