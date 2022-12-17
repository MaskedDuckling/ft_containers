#include "vector.hpp"
#include "stack.hpp"


int main()
{
	ft::vector<int> Vempty;
	ft::vector<int> Vint(1, 8);
	ft::vector<float> Vfloat(1, 14.5f);

	Vempty.affi();
	Vint.affi();
	Vfloat.affi();
	std::cout << "Empty: Empty? = " << std::boolalpha << Vempty.empty()<< " size = " << Vempty.size() << " capacity = " << Vempty.capacity() << " max_size = " << Vempty.max_size() << std::endl;
	std::cout << "Int: Empty? = " << std::boolalpha << Vint.empty()<< " size = " << Vint.size() << " capacity = " << Vint.capacity() << " max_size = " << Vint.max_size() << std::endl;
	std::cout << "Float: Empty? = " << std::boolalpha << Vfloat.empty()<< " size = " << Vfloat.size() << " capacity = " << Vfloat.capacity() << " max_size = " << Vfloat.max_size() << std::endl;
	/*Vint.push_back(6);
	Vint.push_back(4);
	Vint.push_back(2);
	try{
		std::cout << Vint.at(3) << std::endl;
		std::cout << Vint.at(0) << std::endl;
		std::cout << Vint.at(4) << std::endl;
	}
	catch (std::out_of_range & e){
		std::cout << e.what() << std::endl;
	}*/
}