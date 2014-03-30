#include <iostream>
#include <string>

bool is_balanced(const string& s)
{
	int count = 0;
	
	for(auto c: s) {
		switch (c) {
		case '(':
			count++;
			break;
		case ')':
			if (count == 0)
				return false;
			else
				count--;
			break;
		default:
			break;
		}
	}

	if (count == 0)
		return true;
	else
		return false;
}

int main()
{

}
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
