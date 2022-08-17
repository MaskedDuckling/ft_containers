touch $1.hpp
echo "#ifndef ${1^^}_HPP
#define ${1^^}_HPP

class $1
{
private:
  
public:
	$1();
	$1($1 const & ref);

	~$1();

	$1 &operator=($1 const & rhs);
};

#endif" >> $1.hpp

touch $1.cpp
echo "#include \"$1.hpp\"

/**********************[Constructeur]**********************/
$1::$1(){
	
}

$1::$1($1 const & rhs){
    *this = rhs;
}

/**********************[Destructeur]**********************/

$1::~$1(){

}

/**********************[Fonction Membre]**********************/



/**********************[Operateur]**********************/

$1 &$1::operator=($1 const & rhs){

}

" >> $1.cpp