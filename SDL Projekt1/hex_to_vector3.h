#pragma once
#include"Vector3.h"
#include<map>

//converts hex numbers and letters to decimal
int hex_helper(char ch) {
	if (ch < 58) return ch - 48;
	return ch - 55;
}

Vector3 hex_to_vector3(const char hex[]) {
	return Vector3(
		(hex_helper(hex[0])) * 16 + (hex_helper(hex[1])) / 255,
		(hex_helper(hex[2])) * 16 + (hex_helper(hex[3])) / 255,
		(hex_helper(hex[4])) * 16 + (hex_helper(hex[5])) / 255
	);
}