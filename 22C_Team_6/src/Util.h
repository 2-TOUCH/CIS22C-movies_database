#pragma once

#include <string>
#include <vector>

/**
 * Split a string into a vector of strings based on the specified delimiter
 * @param str the string to split
 * @param delim the delimiter 
 * @return a vector of strings
 */
// From https://github.com/Themaister/Granite/blob/3e0ac0da7315e6a8ae6584ee0cc5c9cef82f02e5/util/string_helpers.cpp#L28
inline static std::vector<std::string> split(const std::string& str, const char* delim){
	if (str.empty())
		return {};
	std::vector<std::string> ret;
	size_t startIndex = 0;
	size_t index = 0;
	while ((index = str.find_first_of(delim, startIndex)) != std::string::npos) {
        ret.push_back(str.substr(startIndex, index - startIndex));
		startIndex = index + 1;
		if (index == str.size() - 1)
			ret.emplace_back();
	}

	if (startIndex < str.size())
		ret.push_back(str.substr(startIndex));

	return ret;
}
