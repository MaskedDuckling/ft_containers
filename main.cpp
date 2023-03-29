#include "headers/stack.hpp"
#include "headers/vector.hpp"
#include "headers/map.hpp"
#include "headers/map_iterator.hpp"
#include "headers/RB_tree.hpp"
#include <iostream>
#include <list>

/*CTRL+/ pour les commentaire de groupe*/

#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

int main()
{
	/*TEST MAP*/

	// ft::map<int,int> plop;
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	ft::map<T1, T2> plop(lst.begin(), lst.end());
	// ft::pair<int,int> pp;
	// for (int i = 0; i < 50;i++){
	// 	pp.first = i;
	// 	pp.second = 50-i;
	// 	plop.insert(pp);
	// }
	// test.affichage(test._root, 0);
	// std::cout << std::endl;
	// std::cout << std::endl;
	// std::cout << std::endl;
	// test.right_rotation(test._root);
	// test.right_rotation(test._root);
	// test.right_rotation(test._root);
	// test.affichage(test._root, 0);
	// std::cout << std::endl;
	// std::cout << std::endl;
	// std::cout << std::endl;
	// test.right_rotation(test._root);



	/*TEST VECTOR*/
		// ft::vector<std::string> vct(8);
		// ft::vector<std::string> vct2;
		// ft::vector<std::string>::iterator it = vct.begin();

		// for (unsigned long int i = 0; i < vct.size(); ++i)
		// 		it[i] = std::string((vct.size() - i), i + 65);
		// std::cout << vct.size() << std::endl;

		// std::cout << "push_back():\n" << std::endl;

		// vct.push_back("One long string");
		// vct2.push_back("Another long string");

		// std::cout << vct.size() << std::endl;
		// std::cout << vct2.size() << std::endl;

		// vct.pop_back();
		// vct2.pop_back();

		// std::cout << vct.size() << std::endl;
		// std::cout << vct2.size() << std::endl;

		// return (0);
		// std::list<int> lst;
		// std::list<int>::iterator lst_it;
		// for (int i = 1; i < 5; ++i)
		// 	lst.push_back(i * 3);

		// ft::vector<int> vct(lst.begin(), lst.end());
		// std::cout << vct.size() << std::endl;

		// lst_it = lst.begin();
		// for (int i = 1; lst_it != lst.end(); ++i)
		// 	*lst_it++ = i * 5;
		// vct.assign(lst.begin(), lst.end());
		// std::cout << lst.size() << std::endl;

		// vct.insert(vct.end(), lst.rbegin(), lst.rend());
		// // std::cout << vct.size() << std::endl;
		// // return (0);
		// ft::vector<int> Vint(1,0);
		// for (int i = 1; i <= 20; i++)
		// 	Vint.push_back(i);
		// ft::vector<int>::iterator it = Vint.begin();
		// ft::vector<int>::iterator ite = Vint.end();
		// std::cout << Vint.distance(it,ite);

		// ft::vector<int> Vempty;
		// ft::vector<int> Vint(size_t(1), 8);
		// ft::vector<float> Vfloat(1, 14.5f);

		// Vempty.affi();
		// Vint.affi();
		// Vfloat.affi();
		// std::cout << "Empty: Empty? = " << std::boolalpha << Vempty.empty()<< " size = " << Vempty.size() << " capacity = " << Vempty.capacity() << " max_size = " << Vempty.max_size() << std::endl;
		// std::cout << "Int: Empty? = " << std::boolalpha << Vint.empty()<< " size = " << Vint.size() << " capacity = " << Vint.capacity() << " max_size = " << Vint.max_size() << std::endl;
		// std::cout << "Float: Empty? = " << std::boolalpha << Vfloat.empty()<< " size = " << Vfloat.size() << " capacity = " << Vfloat.capacity() << " max_size = " << Vfloat.max_size() << std::endl;
		// Vint.push_back(6);
		// Vint.push_back(4);
		// Vint.push_back(2);
		// try{
		// 	std::cout << Vint.at(3) << std::endl;
		// 	std::cout << Vint.at(0) << std::endl;
		// 	std::cout << Vint.at(4) << std::endl;
		// }
		// catch (std::out_of_range & e){
		// 	std::cout << e.what();
		// }



	// /*TEST STACK*/
	// {
	// 	ft::stack<int> Sint;
	// 	for (int i = 0; i < 100; i+=2)
	// 		Sint.push(i);
	// 	std::cout << Sint.top() << std::endl;

	// }
}