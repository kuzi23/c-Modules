#include "Form.hpp"

Form::Form() : _name("default"), _gradeToSign(150), _gradeToExecute(150), _signed(false)
{
}

Form::Form(std::string const &name, int gradeToSign, int gradeToExecute) : _name(name), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _signed(false)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
}

Form::Form(const Form &src) : _name(src.getName()), _gradeToSign(src.getGradeToSign()), _gradeToExecute(src.getGradeToExecute()), _signed(src.getSigned())
{
}

Form &Form::operator=(const Form &rhs)
{
	if (this != &rhs)
		this->_signed = rhs.getSigned();
	return (*this);
}

Form::~Form()
{
}

std::string const &Form::getName() const
{
	return (this->_name);
}

const char *Form::GradeTooHighException::what() const throw()
{
	return ("Grade is too high!");
}

const char *Form::GradeTooLowException::what() const throw()
{
	return ("Grade is too low!");
}

std::ostream &operator<<(std::ostream &o, const Form &rhs)
{
    o << rhs.getName() << ", form grade " << rhs.getGradeToSign() << ", " << rhs.getGradeToExecute() << ".";
    return (o);
}

int Form::getGradeToSign() const
{
    return (this->_gradeToSign);
}

int Form::getGradeToExecute() const
{
    return (this->_gradeToExecute);
}

bool Form::getSigned() const
{
    return (this->_signed);
}

void Form::beSigned(Bureaucrat const &bureaucrat)
{
    if (bureaucrat.getGrade() > this->getGradeToSign())
        throw Form::GradeTooLowException();
    this->_signed = true;
}