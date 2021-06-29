#pragma once

#include <string_view>
#include <sstream>
#include <string>

class URLDecoder {
private:

	static char toHex (char ch) {
		if ('0' <= ch && ch <= '9') {
			return ch - '0';
		}

		if ('A' <= ch && ch <= 'F') {
			return ch - 'A' + 10;
		}

		if ('a' <= ch && ch <= 'f') {
			return ch - 'a' + 10;
		}

		return -1;
	}

	static char charFromHex (std::string_view str) {
		return (toHex (str[0]) << 4) | toHex (str[1]);
	}

	static char decodeInternal (std::string_view str) {
		char ch = charFromHex (str);
		switch (ch) {
			case 0x21: return '!';
			case 0x23: return '#';
			case 0x24: return '$';
			case 0x26: return '&';
			case 0x27: return '\'';
			case 0x28: return '(';
			case 0x29: return ')';
			case 0x2A: return '*';
			case 0x2B: return '+';
			case 0x2C: return ',';
			case 0x2F: return '/';
			case 0x3A: return ':';
			case 0x3B: return ';';
			case 0x3D: return '=';
			case 0x3F: return '?';
			case 0x40: return '@';
			case 0x5B: return '[';
			case 0x5D: return ']';
		}
		return ch;
	}


public:

	static std::string decode (std::string_view str) {
		std::stringstream result;

		bool start = false;
		size_t begin, count = 0;

		for (size_t i = 0; i < str.length (); ++i) {
			char ch = str[i];

			if (ch == '%') {
				if (start) {
					result << str.substr (begin, count + 1);
				}
				start = true;
				begin = i;
				count = 0;
			}
			else {
				if (start) {
					count++;

					if (count == 2) {
						char decoded = decodeInternal (str.substr (begin + 1, count));

						if (decoded == (-1)) {
							result << str.substr (begin, count + 1);
						}
						else {
							result << decoded;
						}

						start = false;
						count = 0;
						continue;
					}
				}

				if (!start || count > 2) {
					result << ch;
				}

			}
		}

		if (start) {
			result << str.substr (begin, count + 1);
		}

		return result.str ();
	}
};


