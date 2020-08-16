#include <map>
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
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}
std::map<std::string, std::vector<std::string> > readWords(char* filename){
  std::map<std::string, std::vector<std::string> > M;
  std::ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Could not open Words");
   	exit(EXIT_FAILURE);
  }
  std::string line;
  while(std::getline(ifs,line)){
    std::vector<std::string> v;
    std::string c = ":";
    splitString(line,v,c);
    //Words file with invalid syntax: No colon
    if(v.size() != 2){
      perror("Words file with invalid syntax: No colon");
   	  exit(EXIT_FAILURE);
    }
    M[v[0]].push_back(v[1]);
  }
  //debug test
  /*std::map<std::string, std::vector<std::string> >::iterator it;
  for(it = M.begin();it != M.end();++it){
    std::cout<<it->first<<std::endl;
    for(size_t i=0;i<it->second.size();i++){
      std::cout<<it->second[i]<<" ";
    }
    std::cout<<std::endl;
  }*/
  return M;
}
void lineReplace(std::string &line,std::map<std::string, std::vector<std::string> > &M){
  std::string l;//random name
  std::string::size_type pos1, pos2;
  std::string temp;
  while(line.find("_") != line.npos){
    pos1 = line.find("_");
    pos2 = line.find("_",pos1+1);
    //input error like _time
    if(pos2 == line.npos){
      perror("Input Error:lack second _");
   	  exit(EXIT_FAILURE);
    }
    temp = line.substr(pos1+1,pos2-pos1-1);
    //std::cout<<"temp = "<<temp<<std::endl;//debug test
    if(atoi(temp.c_str()) == 0){
      //Story file with nonexistent category
      if(M.count(temp) == 0){
        perror("Story file with nonexistent category");
   	    exit(EXIT_FAILURE);
      }
      int r = rand() % M[temp].size();//random number
      //std::cout<<"random number= "<<r<<std::endl;//debug test
      l = (M[temp])[r];
    }
    else{
      int n = M["used"].size()-atoi(temp.c_str());
      if(n < 0){
        perror("Number refers past beginning of story");
   	    exit(EXIT_FAILURE);
      }
      l = (M["used"])[n]; 
    }
    line = line.replace(pos1,temp.length()+2,l);
    M["used"].push_back(l);//keep track of used words
  }
}
std::vector<std::string> readStory(char* filename,std::map<std::string, std::vector<std::string> > M){
  std::vector<std::string> S;
  std::ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Could not open Story");
   	exit(EXIT_FAILURE);
  }
  std::string line;
  while(std::getline(ifs,line)){
    lineReplace(line,M);
    std::cout<<line<<std::endl;//debug test
    S.push_back(line);
  }
  return S;
}
int main(int argc, char ** argv){
  if(argc != 4) {
    fprintf(stderr, "Input Error:3 command line arguments\n");
    return EXIT_FAILURE;
  }
  int r = atoi(argv[3]);//random seed
  if(r <= 0) {
    fprintf(stderr, "Input Error:random seed must be 1 or greater\n");
    return EXIT_FAILURE;
  }
  srand(r);//set the random seed
  //(1) read and store the categories and words in a map
  std::map<std::string, std::vector<std::string> > M;
  M = readWords(argv[2]);
  //(2) read the story template, parsing each blank and selecting an appropriate word.
  std::vector<std::string> S;//Story
  S = readStory(argv[1],M);
  return EXIT_SUCCESS;
}