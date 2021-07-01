#include "urldecoder.h"
#include "urlencoder.h"
#include <iostream>
#include <vector>

#if WIN32
#include <Windows.h>

static std::string wstringToString (const std::wstring& wstr) {
	if (wstr.empty ()) return std::string ();
	int sizeNeeded = WideCharToMultiByte (CP_UTF8, 0, &wstr[0], (int)wstr.size (), NULL, 0, NULL, NULL);
	std::string strTo (sizeNeeded, 0);
	WideCharToMultiByte (CP_UTF8, 0, &wstr[0], (int)wstr.size (), &strTo[0], sizeNeeded, NULL, NULL);
	return strTo;
}
#endif

int main (int argc, char** argv) {
	int argCount = 0;
	std::vector<std::string> args;

#if WIN32
	SetConsoleOutputCP (CP_UTF8);

	{
		LPWSTR* argList = CommandLineToArgvW (GetCommandLineW (), &argCount);

		if (argList == NULL) {
			std::cout << u8"CommandLineToArgvW failed" << std::endl;
			return EXIT_FAILURE;
		}

		for (size_t i = 0; i < argCount; ++i) {
			args.emplace_back (wstringToString (argList[i]));
		}

		LocalFree (argList);
	}
#else

	argCount = argc;
	for (size_t i = 0; i < argCount; ++i) {
		args.emplace_back (argv[i]);
	}

#endif

	if (argCount > 2) {
		if (args[1] == "encode") {
			std::cout << URLEncoder::encode (args[2]) << std::endl;
		}
		else if (args[1] == "decode") {
			std::cout << URLDecoder::decode (args[2]) << std::endl;
		}
		else {
			std::cout << u8"Unknown command" << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
