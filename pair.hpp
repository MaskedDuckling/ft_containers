#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft{
	template<class T1, class T2>
		class pair
		{
		public:
			typedef T1  first_type;
			typedef T2  second_type;

			pair():_first(0),_second(0){}
			pair(const first_type& a, const second_type& b):_first(a),_second(b){}

			pair& operator= (const pair& pr){
				this->_first = pr.get_first();
				this->_second = pr.get_second();
			}

			void swap (pair& pr) {
				first_type tmp1 = pr.get_first();
				second_type tmp2 = pr.get_second();

				pr.set_first(this->_first);
				pr.set_second(this->_second);

				this->_first = tmp1;
				this->_second = tmp2;
			}

			first_type get_first(){
				return (_first);
			}
			second_type get_second(){
				return (_second);
			}
			void	set_first(first_type t1){
				_first = t1;
			}
			void	set_second(second_type t2){
				_second = t2;
			}
		private:
			first_type  _first;
			second_type _second;
		};
}
#endif
