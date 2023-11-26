#include "Components.h"
#include <cassert>
#include <iostream>

bool operator>=(const Signature &lhs, const Signature &rhs)
{
	assert(lhs.size() == rhs.size());
	for(std::size_t i = 0; i < rhs.size(); i++) {
		if(rhs[i] == true && lhs[i] != true)
			return false;
	}
	return true;
}
