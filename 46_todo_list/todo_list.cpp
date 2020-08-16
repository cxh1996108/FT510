#include "task.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
void splitString(std::string& s, std::vector<std::string>& v, std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  if(pos2 == s.npos && c == ": "){
    v.push_back(s.substr(pos1,s.size()-1));
    v.push_back("");
  }
  if(pos2 == s.npos && c == ", "){
    v.push_back(s.substr(pos1,s.size()));
    //v.push_back("");
  }
  else{
    while(std::string::npos != pos2)
    {
      v.push_back(s.substr(pos1, pos2-pos1));
   
      pos1 = pos2 + c.size();
      pos2 = s.find(c, pos1);
      if(c == ": "){
        break;
      }
    }
    if(pos1 != s.length())
      v.push_back(s.substr(pos1));
  }
}
TaskDep parseLine(std::string & line) {
  std::vector<std::string> v;
  std::string c = ": ";
  splitString(line,v,c);
  TaskDep t = TaskDep(v[0]);
  std::vector<std::string> w;
  c = ", ";
  splitString(v[1],w,c);
  for(size_t i=0;i<w.size();++i){
    t.addPredecessor(w[i]);
  }
  return t;  
}
std::list<task_t> answerList(std::list<TaskDep> &ta){
  std::list<task_t> ans;
  bool added = true;
  while(!ta.empty()){
    added = false;
    std::list<TaskDep>::iterator it = ta.begin();
    while(it!=ta.end()){
      std::list<task_t> temp = it->getPredecessors();
      //TaskDep has no predecessors, so add to answer list
      if(temp.front() == ""){
        task_t s = it->getTask();
        ans.push_front(s);
        added = true;
        it = ta.erase(it);
        continue;
      }
      //Check if every predecessor in that task's list has already been added to the answer list.
      else{
        std::list<task_t>::iterator p; //pres iterator in each TaskDep
        std::list<task_t>::iterator ait; //ans iterator
        std::list<task_t>::iterator insert_pos = ans.begin();
        bool f;
        int pos;
        int ins_pos = 0;
        for (p = temp.begin(); p != temp.end(); ++p) {
          f = false;
          pos = -1;
          for (ait = ans.begin(); ait != ans.end(); ++ait) {
            ++pos;
            if (*ait == *p) {
              f = true;
              if (pos > ins_pos) {
                ins_pos = pos;
                insert_pos = ait;
              }
              break;
            }
          }
        }
        if (f) {
          ans.insert(++insert_pos, it->getTask());
          added = true;
          it = ta.erase(it);
          continue;
        }
        ++it;
      }
    }
  }
  /*Print an error message that the dependecies do not allow a todo
    list to be created and exit failure*/
  if (ta.empty() && !added) {
    std::cerr << "Some task cannot be added" << std::endl;
    exit(EXIT_FAILURE);
  }
  return ans;
}
int main(int argc, char ** argv) {
  // open file for reading
  if (argc != 2) {
    fprintf(stderr, "Input Error\n");
    return EXIT_FAILURE;
  }
  std::ifstream ifs(argv[1]);
  if(!ifs.is_open()){
    perror("Could not open file");
   	return EXIT_FAILURE;
  }
  // make dependency list of tasks from input file
  std::string line;
  std::list<TaskDep> ta;
  while(getline(ifs,line)){
    if(line.find(":")== line.npos){
      perror("invalid input");
   	  return EXIT_FAILURE;
    }
    TaskDep t = parseLine(line);
    ta.push_back(t);
  }
  // order list according to dependencies
  std::list<task_t> ans;
  ans = answerList(ta);//
  // print todo list
  std::list<task_t>::iterator ait = ans.begin();
  for(;ait!=ans.end();++ait){
    std::cout<<*ait;
    if(*ait!=ans.back())
    std::cout<<", ";
  }
  std::cout<<std::endl;
  return EXIT_SUCCESS;
}
