#include <string>
#include <exception>
#include "Bureaucrat.hpp"

class Form{
    private:
        const std::string _name;
        const int _gradeToSign;
        const int _gradeToExecute;
        bool _signed;

    public:
        Form();
        Form(std::string const &name, int gradeToSign, int gradeToExecute);
        Form(const Form &src);
        Form &operator=(const Form &rhs);
        ~Form();

        std::string const &getName() const;
        int getGradeToSign() const;
        int getGradeToExecute() const;
        bool getSigned() const;

        void beSigned(Bureaucrat const &bureaucrat);

        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char *what() const throw();
        };
};