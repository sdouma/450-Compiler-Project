#include "utf8sequence.h"

#include <iostream>

using namespace std;

UTF8Sequence::UTF8Sequence(std::istream &is_)
: is(is_)
{
	offset = 0;
}

int UTF8Sequence::next()
{
	int ans;

restart:
	for (;;) { // loop past invalid starts
		ans = is.get();
		if ((ans & 0x80) == 0 || ans == -1) return ans;
		if ((ans & 0xC0) != 0x80) break;
	}
	int extra = 0;
	while ((ans & 0x80)) {
		++extra;
		ans = (ans << 1);
	}
	ans = ((ans & 0xFF) >> extra);
	--extra;

	while (extra > 0) {
		int part = is.get();
		if (part == -1) return -1;
		if ((part & 0xC0) != 0x80) goto restart;
		ans = (ans << 6) | (part & 0x3F);
		--extra;
	}
	return ans;
}

size_t UTF8Sequence::at() {
	return offset - ahead.size();
}


int UTF8Sequence::peek(unsigned delta)
{
	while (ahead.size() <= delta) {
		ahead.push_back(next());
		++offset;
	}
	std::list < int > ::iterator  i = ahead.begin();
	while (delta > 0) { ++i; --delta; }
	return *i;
}

void UTF8Sequence::shift(unsigned delta)
{
	while (ahead.size() < delta) {
		ahead.push_back(next());
		++offset;
	}
	while (delta > 0) {
		ahead.pop_front();
		--delta;
	}
}
