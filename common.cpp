#include "common.h"

std::ostream &operator<<(std::ostream &out, const Vec2 &vec)
{
	out << "x:" << vec.x << " y:" << vec.y;
	return out;
}

std::ostream &operator<<(std::ostream &out, const SDL_Rect &rec)
{
	out << "x:" << rec.x << " y:" << rec.y 
	<< " w:" << rec.w << " h:" << rec.h;
	return out;
}

bool has_overlap(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	if(ax > (bx + bw) || 
	   (ax + aw) < bx ||
	   ay > (by + bh) ||
	   (ay + ah) < by) {
		return false;
	}

	return true;
}
