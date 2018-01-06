#pragma once

extern std::string MEFormat(const char *format, ...);


inline char MESanitizeAscii(char c) {
	if (c >= ' ' && c <= '~') {
		return c;
	} else {
		return '_';
	}
}