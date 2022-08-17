#include "vector.hpp"

int main()
{
	ft::vector<int> v1;
	ft::vector<float> v2(5, 14.5f);

	v1.affi();
	v2.affi();
	std::cout << "size = " << v2.size() << " capacity = " << v2.capacity() << " max_size = " << v2.max_size() << std::endl;
	std::cout << std::boolalpha << v1.empty() << " " << v2.empty() << std::endl;
}