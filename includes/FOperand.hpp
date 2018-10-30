#ifndef FOPERAND_HPP
# define FOPERAND_HPP

# include "IOperand.hpp"

# ifndef FOPERAND_HPP_DEFINED
    #  define FOPERAND_HPP_DEFINED
    class FOperand;
    #  include "Operand.hpp"
# endif

# include <string>

class FOperand {
public:
	typedef IOperand const * (FOperand::*IOPFP)(std::string const &) const;
	FOperand( void );
	FOperand( FOperand const & obj );
	~FOperand( void );
	FOperand & operator=( FOperand const & rhs );

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	
private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};

#endif
