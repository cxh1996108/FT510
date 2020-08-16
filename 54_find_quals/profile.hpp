#ifndef __PROFILE_HPP__
#define __PROFILE_HPP__

#include <set>
#include <string>

//declare class Profile
class Profile;

//declare template instantiation std::hash<Profile>
template<>
struct std::hash<Profile>;

//provided Qualities class
class Qualities {
 public:
  int age_min;
  int age_max;
  double height_min;
  double height_max;
  int attr_min;
  int attr_max;
  std::set<std::string> inter_req;
  Qualities(int a_min,
            int a_max,
            double h_min,
            double h_max,
            int at_min,
            int at_max,
            const std::set<std::string> & i_req);
};

class Profile {
 private:
  std::string username;
  int age;
  double height;
  int attractiveness;
  std::set<std::string> interests;

 public:
  Profile() : username(""), age(0), height(0), attractiveness(0), interests() {}
  Profile(const std::string & un, int a, double h, int at);
  void addInterest(const std::string & inter);
  bool operator==(const Profile & rhs) const;
  bool isMatch(const Qualities & q) const;
  friend std::ostream & operator<<(std::ostream & os, const Profile & rhs);
  //add a friend, maybe
  friend struct std::hash<Profile>;
};

//specialize std::hash<Profile>
template<>
struct std::hash<Profile> {
  size_t operator()(const Profile & rhs) const {
  // how to hash this class
  std::hash<std::string> str_hash;
  return str_hash(rhs.username);
  }
};
#endif
