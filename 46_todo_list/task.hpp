#include <list>
#include <string>

typedef std::string task_t;

class TaskDep {
 private:
  const task_t task;
  std::list<task_t> pres;

 public:
  // write these
  /* The provided file task.hpp gives the interface for a TaskDep class,
     which has a task and a list of its predecessors, the tasks that must
     be completed before this task can be done. You should write these
     methods.*/
  TaskDep(const task_t & t): task(t){}
  const task_t & getTask() const{
    return task;
  }
  void addPredecessor(const task_t & t){
    pres.push_back(t);
  }
  std::list<task_t> getPredecessors() const{
    return pres;
  }
};
