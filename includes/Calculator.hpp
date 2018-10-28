
#ifndef CALCULATOR_HPP
# define CALCULATOR_HPP

# include "Iter.hpp"
# include "FOperand.hpp"
# include "AbstractVM.hpp"
# include <string>
# include <iostream>
# include <sstream>
# include <vector>
# include <algorithm>

class Calculator {
public:
	Calculator( void );
	Calculator( Calculator const & obj );

	~Calculator( void );

	Calculator & operator=( Calculator const & rhs );

	bool call(std::string cmd);
	void push(std::string val);
	void pop(void);
	void dump(void);
	void print(void);

	bool verbose;
	bool cont_on_error;
private:
	Iter<IOperand const*> stack;
	FOperand factory;
};

#endif
