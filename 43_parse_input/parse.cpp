#include "parse.hpp"

#include <exception>
// any other headers you need
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

class invalid_input : public std::exception {
  // override what() here
public:
  const char * what () const throw () {
    return "Wrong input format";
  }
};
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
    v.push_back("");
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
item_t * parseLine(std::string & line) {
  // write me
  //item_t* it = (item_t*)malloc(sizeof(*it));//WRONG!!!!!
  item_t* it = new item_t();
  std::vector<std::string> v;
  std::string c = ": ";
  splitString(line,v,c);
  it->first = v[0];
  std::vector<std::string> w;
  c = ", ";
  splitString(v[1],w,c);
  it->second = w;
  return it;  
}
//Print
void print(std::vector<item_t*> &item){
  for(size_t i=0;i<item.size();i++){
    std::cout<<"key = "<<item[i]->first<<std::endl;
    std::cout<<"  values = ";
    if(item[i]->second[1]==""){
      std::cout<<item[i]->second[0]<<std::endl;
    }
    else{
      std::cout<<item[i]->second[0];
      for(size_t j=1;j<item[i]->second.size();j++){
        std::cout<<"; "<<item[i]->second[j];
      }
      std::cout<<std::endl;
    }
  }
}
int main(int argc, char ** argv){
  if (argc != 2) {
    fprintf(stderr, "Input Error\n");
    return EXIT_FAILURE;
  }
  std::ifstream ifs(argv[1]);
  if(!ifs.is_open()){
    perror("Could not open file");
   	return EXIT_FAILURE;
  }
  std::string line;
  std::vector<item_t*> item;
/*Practice dynamic allocation by allocating an item_t *
  for each line read, storing these pointers in a vector. */
  while(getline(ifs,line)){
    try {
      if(line.find(":")== line.npos){
        throw invalid_input();
      }
      /*else if(line.find_first_of(":") != line.find_last_of(":")){
        throw invalid_input();
      }*/
    }
    catch (invalid_input & e) {
      std::cerr << e.what() << std::endl;
      continue;
    }
    item_t * it = parseLine(line);
    item.push_back(it);
  } 
  print(item);
  for(size_t i=0;i<item.size();i++){
    delete item[i];
  }
  return EXIT_SUCCESS;
  
}


