#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

template<typename R, typename A>
class Function {
 public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};

#endif
