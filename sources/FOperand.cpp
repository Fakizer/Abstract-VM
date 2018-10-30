
#include "FOperand.hpp"
#include <iostream>
#include <cerrno>

FOperand::FOperand( void ) {}
FOperand::FOperand( FOperand const & obj ) { static_cast<void>(obj); }
FOperand::~FOperand( void ) {}
FOperand & FOperand::operator=( FOperand const & rhs ) { static_cast<void>(rhs); return *this; }

IOperand const * FOperand::createInt8( std::string const & value ) const {
	return new Operand<int8_t>(std::stoi(value));
}
IOperand const * FOperand::createInt16( std::string const & value ) const {
	return new Operand<int16_t>(std::stoi(value));
}
IOperand const * FOperand::createInt32( std::string const & value ) const {
	return new Operand<int32_t>(std::stoi(value));
}
IOperand const * FOperand::createFloat( std::string const & value ) const {
	return new Operand<float>(std::stof(value));
}
IOperand const * FOperand::createDouble( std::string const & value ) const {
	return new Operand<double>(std::stod(value));
}
IOperand const * FOperand::createOperand( eOperandType type, std::string const & value ) const {
	static IOPFP creators[] = {
		&FOperand::createInt8,
		&FOperand::createInt16,
		&FOperand::createInt32,
		&FOperand::createFloat,
		&FOperand::createDouble
	};
	IOperand const * created = nullptr;
	try {
		IOPFP func = creators[type];
		created = (this->*func)(value);
		std::cout << "Value: ";
		std::cout << value << std::endl;
	} catch(std::exception & e) {
		throw AbstractVM::InvalidValue();
	}
	return created;
}
