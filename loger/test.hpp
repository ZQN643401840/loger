#include <iostream>

std::ostream& ok(std::ostream& os)
{
	os << " im ok " << std::endl;
	return os;
}
typedef std::ostream& (*p_ok)(std::ostream& os);