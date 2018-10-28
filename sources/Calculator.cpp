
#include "Calculator.hpp"

Calculator::Calculator( void ) : verbose(false), cont_on_error(false) {}

Calculator::Calculator( Calculator const & obj ) : verbose(false), cont_on_error(false) { *this = obj; }

Calculator::~Calculator( void ) {
	Iter<IOperand const*>::iterator i;
	Iter<IOperand const*>::iterator end = this->stack.end();
	for (i = this->stack.begin(); i != end; i++) { delete *i; }
}

Calculator & Calculator::operator=( Calculator const & rhs ) {
	// IterStack<IOperand const*>::iterator i;
	// IterStack<IOperand const*>::iterator end = this->stack.end();
	// for (i = this->stack.begin(); i != end; i++) { delete &(*i); }
	// for (i = rhs.stack.begin(); i != rhs.stack.end(); i++) { this->stack.push(factory.createOperand((*i)->getType(), (*i)->toString())); }
	static_cast<void>(rhs);
	return *this;
}

bool Calculator::call(std::string cmd) {
	static const std::vector<std::string> ops = { "add", "sub", "mul", "div", "mod" };
	static std::string names[] = { "int8", "int16", "int32", "float", "double" };
	try {
		if (cmd.find(';') != std::string::npos) cmd.erase(cmd.find(';'), std::string::npos);
		if (cmd.find_first_not_of(" \t") != 0) cmd.erase(0, cmd.find_first_not_of(" \t"));
		while (cmd.size() != 0 && cmd.find_last_of(" \t") == cmd.size()-1) cmd.pop_back();
		if (cmd.size() == 0) return true;
		else if (cmd == "exit") return false;
		else if (cmd == "pop") { this->pop(); }
		else if (cmd == "dump") { this->dump(); }
		else if (cmd == "print") { this->print(); }
		else if (cmd.substr(0,5) == "push ") { this->push(cmd.substr(5,std::string::npos)); }
		else if (std::find(ops.begin(), ops.end(), cmd) != ops.end()) {
			if (this->stack.size() < 2) throw AbstractVM::NotEnoughValues();
			IOperand const * rhs = this->stack.top();
			this->stack.pop();
			IOperand const * lhs = this->stack.top();
			this->stack.pop();
			IOperand const * created = nullptr;
			if (this->verbose) std::cout << "Operation: " << cmd << ' ' << names[lhs->getType()] << '(' << lhs->toString() << ") " << names[rhs->getType()] << '(' << rhs->toString() << ')' << std::endl;
			if (cmd == "add") created = *lhs + *rhs;
			else if (cmd == "sub") created = *lhs - *rhs;
			else if (cmd == "mul") created = *lhs * *rhs;
			else if (cmd == "div") created = *lhs / *rhs;
			else if (cmd == "mod") created = *lhs % *rhs;
			else throw AbstractVM::UnknownOperation();
			this->stack.push(created);
			delete lhs;
			delete rhs;
		}
		else if (cmd.substr(0,7) == "assert ") {
			this->push(cmd.substr(7,std::string::npos));
			IOperand const * lhs = this->stack.top();
			this->stack.pop();
			IOperand const * rhs = this->stack.top();
			if (lhs->getType() != rhs->getType() || lhs->toString() != rhs->toString())
				throw AbstractVM::AssertNotTrue();
			else if (this->verbose) std::cout << "Assert passed: " << lhs->toString() << " == " << rhs->toString() << std::endl;
			delete lhs;
		}
		else {
			if (this->verbose) std::cout << "Error: Unknown instruction: " << cmd << std::endl;
			else throw AbstractVM::UnknownInstruction();
		}
		return true;
	} catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return this->cont_on_error;
	}
}
void Calculator::push(std::string val) {
	static std::string names[] = { "int8", "int16", "int32", "float", "double" };
	if (val.size() < 4) throw AbstractVM::InvalidValue();
	if (val.find('(') == std::string::npos) throw AbstractVM::InvalidValue();
	if (val.back() != ')') throw AbstractVM::InvalidValue();
	val.pop_back();
	unsigned int open_p = val.find('(');
	std::string type_string = val.substr(0, open_p);
	val.erase(val.begin(), val.begin()+open_p+1);
	if (this->verbose) std::cout << "Pushing " << type_string << '(' << val << ')' << std::endl; // DEBUG
	for (int i = Int8; i <= Double; i++ ) {
		if (type_string == names[i]) {
			this->stack.push(factory.createOperand(static_cast<eOperandType>(i), val));
			return;
		}
	}
	throw AbstractVM::InvalidValue();
}
void Calculator::pop(void) {
	if (this->stack.size() < 1) throw AbstractVM::PopOnEmpty();
	delete this->stack.top();
	this->stack.pop();
}
void Calculator::dump(void) {
	Iter<IOperand const*>::iterator i;
	Iter<IOperand const*>::iterator end = this->stack.end();
	for (i = this->stack.begin(); i != end; i++) { std::cout << (*i)->toString() << std::endl; }
}

void Calculator::print(void) {
	if (this->stack.size() < 1) throw AbstractVM::PrintNotInt8();
	IOperand const * top = this->stack.top();
	if (top->getType() != Int8) throw AbstractVM::PrintNotInt8();
	char c = std::stoi(top->toString());
	if (c > 32 && c < 127) { std::cout << c << '\n'; }
	else { std::cout << "Non-displayable character (" << std::stoi(top->toString()) << ')' << std::endl; }
}
