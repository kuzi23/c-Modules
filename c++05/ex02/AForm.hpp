#ifndef AFORM_HPP
# define AFORM_HPP

# include <string>
# include <exception>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool				_signed;
		const int			_gradeToSign;
		const int			_gradeToExecute;

	public:
		AForm();
		AForm(std::string const &name, int gradeToSign, int gradeToExecute);
		AForm(const AForm &src);
		AForm &operator=(const AForm &rhs);
		virtual ~AForm();

		std::string const	&getName() const;
		bool				getSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;

		void				beSigned(Bureaucrat const &bureaucrat);

		virtual void		execute(Bureaucrat const &executor) const = 0;

		class GradeTooHighException : public std::exception {
			public: virtual const char *what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public: virtual const char *what() const throw();
		};
		class FormNotSignedException : public std::exception {
			public: virtual const char *what() const throw();
		};
};

std::ostream	&operator<<(std::ostream &o, const AForm &rhs);

#endif