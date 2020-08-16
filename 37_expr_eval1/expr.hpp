#include <string>
#include <sstream>
class Expression{
  public:
    virtual std::string toString() const = 0;  
    virtual ~Expression() {}
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
};
class OpExpression : public Expression {
  private:	
    const char *Op; 
  	Expression *lhs, *rhs;
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
};