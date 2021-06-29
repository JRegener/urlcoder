#pragma once

#include <string>
#include <sstream>

class URLEncoder {
private:
	static bool isLatin (char ch) {
		return
			(ch >= '0' && ch <= '9') ||
			(ch >= 'a' && ch <= 'z') ||
			(ch >= 'A' && ch <= 'Z');
	}

	static std::string hexFromChar (char ch) {
		return {
			hex_digits[(ch >> 4) & byte_mask],
			hex_digits[ch & byte_mask]
		};
	}


	static std::string encodeInternal (char ch) {
		switch (ch) {
			case '!': return "21";
			case '#': return "23";
			case '$': return "24";
			case '&': return "26";
			case '\'':return "27";
			case '(': return "28";
			case ')': return "29";
			case '*': return "2A";
			case '+': return "2B";
			case ',': return "2C";
			case '/': return "2F";
			case ':': return "3A";
			case ';': return "3B";
			case '=': return "3D";
			case '?': return "3F";
			case '@': return "40";
			case '[': return "5B";
			case ']': return "5D";
		}

		return hexFromChar (ch);
	}

public:

	static std::string encode (const std::string& str) {
		std::stringstream result;

		for (size_t i = 0; i < str.length (); ++i) {
			if (isLatin (str[i])) {
				result << str[i];
			}
			else {
				result << '%' << encodeInternal (str[i]);
			}
		}

		return result.str ();
	}

private:
	static constexpr char hex_digits[] = "0123456789ABCDEF";
	static constexpr char byte_mask = 0x0F;
};
