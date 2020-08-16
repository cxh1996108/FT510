#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char ** argv) {
/*- If no arguments (other than its own name) are provided (argc ==
    1), then your program should read from standard input, sort the
    lines of input, print the results, free memory, and exit
    successfully.*/
  if (argc == 1) {
    std::vector<std::string> s;
    std::string line;
  	while (getline(std::cin,line)) {
      s.push_back(line);
 		}
  	std::sort(s.begin(),s.end());
    std::vector<std::string>::iterator it = s.begin();
    while(it != s.end()){
      std::cout<<*it<<std::endl;
      ++it;
    }
  	return EXIT_SUCCESS;
	} 
/*  - If 1 or more arguments are provided (argc > 1), then your program
    should treat each argument as an input file name. For each file
    name specified, it should open that file, read all of the lines of
    data in it, sort the lines, print the results, free the memory,
    and close the file. If any errors occur, your program should print
    an appropriate error message and exit with EXIT_FAILURE. If no
    errors occur, your program should indicate its success after
    processing all of the files.*/
  if (argc > 1) {
  	for(int i=1;i<argc;i++)
    {
      std::string line;
      std::vector<std::string> s;
      std::ifstream ifs(argv[i]);
      if(!ifs.is_open()){
        perror("Could not open file");
	    	return EXIT_FAILURE;
      }
      while(getline(ifs,line)){
        s.push_back(line);
      }
      std::sort(s.begin(),s.end()); 
      std::vector<std::string>::iterator it = s.begin();
      while(it != s.end()){
        std::cout<<*it<<std::endl;
        ++it;
      }
    }
  }
  return EXIT_SUCCESS;
}