#pragma once

// FilePathLength
#define MAX_FILEPATH_LENTGH 256

constexpr char stringDelimiter[] = "#"; // Character used to encapsulate data in linear NVS-strings (don't change)
constexpr char stringOuterDelimiter[] = "^"; // Character used to encapsulate encapsulated data along with RFID-ID in backup-file

inline bool isNumber(const char *str) {
	int i = 0;

	while (*(str + i) != '\0') {
		if (!isdigit(*(str + i++))) {
			return false;
		}
	}

	if (i > 0) {
		return true;
	} else {
		return false;
	}
}

// Checks if string starts with prefix
// Returns true if so
inline bool startsWith(const char *str, const char *pre) {
	if (strlen(pre) < 1) {
		return false;
	}

	return !strncmp(str, pre, strlen(pre));
}

// Checks if string ends with suffix
// Returns true if so
inline bool endsWith(const char *str, const char *suf) {
	const char *a = str + strlen(str);
	const char *b = suf + strlen(suf);

	while (a != str && b != suf) {
		if (*--a != *--b) {
			break;
		}
	}

	return b == suf && *a == *b;
}

inline void convertFilenameToAscii(String utf8String, char *asciiString) {
	// Arduino >= 2.0.5 filenames are already unicode, copy to result here without UTF-8 decoding
	strncpy(asciiString, (char *) utf8String.c_str(), utf8String.length() / sizeof(asciiString[0]));
	asciiString[utf8String.length()] = 0;
}

// Release previously allocated memory
inline void freeMultiCharArray(char **arr, const uint32_t cnt) {
	for (uint32_t i = 0; i < cnt; i++) {
		// Log_Printf(LOGLEVEL_DEBUG, freePtr, *(arr+i), arr);
		free(*(arr + i));
	}
	free(arr);
	*arr = NULL;
}
