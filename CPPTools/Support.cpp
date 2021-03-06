#include <iostream>
#include <memory>

#include "Support.h"

namespace Tools {
	char* strappend(char* to, char* from) {
		ulong_64b l, l1;
		to = (char*)realloc(to, (l = strlen(to)) + (l1 = strlen(from))+1);
		memcpy(to + l, from, l1);
		to[l + l1] = 0;
		return to;
	}

	char* strappend(char* to, const char* from) {
		ulong_64b l, l1;
		to = (char*)realloc(to, (l = strlen(to)) + (l1 = strlen(from))+1);
		memcpy(to + l, from, l1);
		to[l + l1] = 0;
		return to;
	}

	char* strappend(const char* from, char* to) {
		ulong_64b l, l1;
		to = (char*)realloc(to, (l = strlen(to)) + (l1 = strlen(from))+1);
		memcpy(to + l1, to, l);
		memcpy(to, from, l1);
		to[l + l1] = 0;
		return to;
	}

	char* __cdecl strappend(const char* from, const char* from1) {
		ulong_64b l, l1;
		char* to = (char*)malloc((l = strlen(from)) + (l1 = strlen(from1))+1);
		memcpy(to, from, l);
		memcpy(to + l, from1, l1);
		to[l + l1] = 0;
		return to;
	}

	void destructivePrint(char* message, ulong_64b size) {
		for (ulong_64b t = 0; t < size; ++t) std::cout << message[t];
		free(message);
	}

	void destructivePrint(char* message) {
		std::cout << message;
		free(message);
	}

	void destructivePrintln(char* message, ulong_64b size) {
		destructivePrint(message, size);
		std::cout << std::endl;
	}

	void destructivePrintln(char* message) {
		destructivePrint(message);
		std::cout << std::endl;
	}

	ulong_64b indexOf(char* in, char find) {
		ulong_64b t = strlen(in);
		for (ulong_64b t1 = 0; t1 < t; ++t1) if (in[t1] == find) return t1;
		return -1;
	}

	ulong_64b lastIndexOf(char* in, char find) {
		ulong_64b t = strlen(in);
		for (ulong_64b t1 = 0; t1 < t; ++t1) if (in[t - t1 - 1] == find) return t - t1;
		return -1;
	}

	char* copydata(const char* from, ulong_64b readBytes) {
		char* c = (char*)malloc(readBytes);
		memcpy(c, from, readBytes);
		return c;
	}

	char* toHexString(const void* data, ulong_64b size) {
		char* c = (char*)data;

		ulong_64b lastNonZero = 0;
		for (ulong_64b t = 0; t < size; ++t) if (c[t] != 0) lastNonZero = t;
		if (lastNonZero == 0) return (char*)memset(malloc(1), '0', 1);

		char* c1 = (char*)malloc(lastNonZero * 2);
		for (ulong_64b t = 0; t < lastNonZero; ++t) {
			c1[2 * t] = (c[t]) & 15;
			if (c1[(2 * t)] < 9) c1[(2 * t)] += 48;
			else c1[(2 * t)] += 55;

			c1[(2 * t) + 1] = (c[t] >> 4) & 15;
			if (c1[(2 * t) + 1] < 9) c1[(2 * t) + 1] += 48;
			else c1[(2 * t) + 1] += 55;
		}
		return c1;
	}

	char* toHexString(ulong_64b value) { return toHexString(&value, sizeof(value)); }

	bool isDigit(char c) { return (c > 47) && (c < 58); }

	bool isIP(char* c) {
		size_t t = strlen(c);
		size_t count = 0;
		for (size_t t1 = 0; t1 < t; ++t1) {
			if (c[t1] == '.') {
				if ((t1 + 1) == t) return false;
				++count;
			}
			else if (!isDigit(c[t1])) return false;
			if (count > 3) return false;
		}
		return count == 3;
	}

	bool isNumber(char* c) {
		for (size_t t = strlen(c); t > 0; --t) if (!isDigit(c[t - 1])) return false;
		return true;
	}
}