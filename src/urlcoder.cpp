#include "urldecoder.h"
#include "urlencoder.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>

static std::string readArgs (const std::string & path) {
	std::string arg;
	
	std::filesystem::path filepath = std::filesystem::path (path);
	std::ifstream finput (filepath, std::ios::in);
	
	if (finput.is_open () && finput.good ()) {
		std::getline (finput, arg);

		if (finput.fail ()) {
			std::cout << u8"Error reading input file" << std::endl;
		}
	}
	else {
		std::cout << u8"Error opening file " << filepath.c_str() << std::endl;
	}
	
	finput.close ();

	if (arg.front() == '"' && arg.back () == '"') {
		return arg.substr (1, arg.length () - 2);
	}

	return arg;
}

int main (int argc, char** argv) {
#if WIN32
	SetConsoleOutputCP (CP_UTF8);
#endif

	if (argc > 2) {
		std::string arg = readArgs (argv[2]);

		if (std::strcmp (argv[1], "encode") == 0) {
			std::cout << URLEncoder::encode (arg) << std::endl;
		}
		else if (std::strcmp (argv[1], "decode") == 0) {
			std::cout << URLDecoder::decode (arg) << std::endl;
		}
		else {
			std::cout << u8"Unknown command" << std::endl;
		}
	}
	
	return EXIT_SUCCESS;
}
