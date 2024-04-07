#pragma once
#include"vector3.h"

//converts hex numbers to the decimal ascii representation of a character
int hex_helper(char ch) {
	return (ch < 58)? ch - 48 : ch - 55;
}

Vector3 hex_to_vector3(const char hex[]) {
	return Vector3(
		(hex_helper(hex[0])) * 16 + (hex_helper(hex[1])),
		(hex_helper(hex[2])) * 16 + (hex_helper(hex[3])),
		(hex_helper(hex[4])) * 16 + (hex_helper(hex[5]))
	);
}