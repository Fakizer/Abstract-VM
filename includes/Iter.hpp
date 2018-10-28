
#ifndef ITER_HPP
# define ITER_HPP

# include <deque>
# include <stack>

// template <class T> class MutantStack : public std::stack< T, std::deque<T> > {
template <class T> class Iter : public std::stack<T> {
public:
	typedef typename std::deque<T>::iterator iterator;
	Iter( void );
	Iter( Iter const & obj );
	~Iter( void );
	Iter & operator=( Iter const & rhs );

	Iter<T>::iterator begin( void );
	Iter<T>::iterator end( void );
protected:

private:

};

template <class T> Iter<T>::Iter( void ) {}
template <class T> Iter<T>::Iter( Iter<T> const & obj ) { *this = obj; }
template <class T> Iter<T>::~Iter( void ) {}
template <class T> Iter<T> & Iter<T>::operator=( Iter<T> const & rhs ) {
	this->std::stack<T>::operator=(rhs);
	return *this;
}
template <class T> typename Iter<T>::iterator Iter<T>::begin( void ) {
	return this->c.begin();
}
template <class T> typename Iter<T>::iterator Iter<T>::end( void ) {
	return this->c.end();
}

#endif
