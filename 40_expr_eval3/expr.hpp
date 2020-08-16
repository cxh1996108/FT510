#include <string>
#include <sstream>
#include <cstdlib>
class Expression{
  public:
    virtual std::string toString() const = 0;  
    virtual ~Expression() {}
    virtual long evaluate() const = 0;
};
class NumExpression : public Expression{
  private:
    long num;
  public:
    NumExpression(long n): num(n) {} 
    virtual std::string toString() const{
      std::stringstream ss;
      ss<<num;
      return ss.str();
    }
    virtual long evaluate() const {
      return num;
    }
};
class OpExpression : public Expression {
  protected://IMPORTANT	
    const char *Op; 
  	Expression *lhs, *rhs;
    long num;
  public:
  	OpExpression(const char *op, Expression *l, Expression *r) : Op(op), lhs(l), rhs(r) {}
  	virtual std::string toString() const {
  		std::stringstream ss;
  		ss << "(" << lhs->toString() << " " << Op << " " << rhs->toString() << ")";
  		return ss.str();
  	}
  	virtual ~OpExpression() {
  		delete lhs;
  		delete rhs;
  	}
};
class PlusExpression : public OpExpression{
  public:
    PlusExpression(Expression * lhs, Expression * rhs): OpExpression("+",lhs,rhs){}
    virtual long evaluate() const {
      return (lhs->evaluate() + rhs->evaluate());  
    }
};
class MinusExpression : public OpExpression{
  public:
    MinusExpression(Expression * lhs, Expression * rhs): OpExpression("-",lhs,rhs){}
    virtual long evaluate() const {
      return (lhs->evaluate() - rhs->evaluate());  
    }
};

class TimesExpression : public OpExpression{
  public:
    TimesExpression(Expression * lhs, Expression * rhs): OpExpression("*",lhs,rhs){}
    virtual long evaluate() const {
      return (lhs->evaluate() * rhs->evaluate());  
    }
};
class DivExpression : public OpExpression{
  public:
    DivExpression(Expression * lhs, Expression * rhs): OpExpression("/",lhs,rhs){}
    virtual long evaluate() const {
      return (lhs->evaluate() / rhs->evaluate());  
    }
};

