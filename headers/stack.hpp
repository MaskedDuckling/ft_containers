#ifndef STACK_HPP
# define STACK_HPP

#include <vector>

/*A l'air de marcher retenter avec ft::vector quand il est bon*/

namespace ft{
	template<class T, class Container = std::vector<T> >
		class stack
		{
        
		public:
            typedef T           value_type;
            typedef Container   container_type;
            typedef std::size_t      size_type;

			explicit stack(const container_type& cntr = container_type()): cntr(cntr)   {};
            
            ~stack(){};
            
            void pop(){
                cntr.pop_back();
            }

            bool empty() const{
                return (cntr.empty());
            }

            size_type size() const{
                return (cntr.size());
            }

            value_type& top(){
                return(cntr.back());
            }
            
            const value_type& top() const{
                return(cntr.back());
            }

            void push (const value_type& val){
                cntr.push_back(val);
            }

            friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return (lhs.cntr == rhs.cntr);
            }

            friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return (lhs.cntr != rhs.cntr);
            }

            friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return (lhs.cntr < rhs.cntr);
            }

            friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return (lhs.cntr <= rhs.cntr);
            }

            friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return (lhs.cntr > rhs.cntr);
            }	

            friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return (lhs.cntr >= rhs.cntr);
            }

        protected:
            container_type cntr;
		};
}
#endif