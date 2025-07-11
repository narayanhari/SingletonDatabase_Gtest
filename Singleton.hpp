#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <vector>

class Database
{
public:
  virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public Database
{
  SingletonDatabase()
  {
    std::cout << "Initializing database" << std::endl;

    std::ifstream ifs("capitals.txt");

    std::string s, s2;
    auto trim = [](std::string &str) {
	    // remove leading/trailing whitespace
	    str.erase(str.begin(), std::find_if_not(str.begin(), str.end(), ::isspace));
	    str.erase(std::find_if_not(str.rbegin(), str.rend(), ::isspace).base(), str.end());
    };
    while (getline(ifs, s) && getline(ifs, s2))
    {
      trim(s);
      //if (!s.empty() && (s.back() == '\t' || s.back() == '\r'))
       	//s.pop_back();
      if(s.empty()) continue;
      int pop = std::stoi(s2);
      capitals[s] = pop;
    }
    instance_count++;
  }

  std::map<std::string, int> capitals;

public:
  static int instance_count;

  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  static SingletonDatabase& get()
  {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const std::string& name) override
  {
    auto it = capitals.find(name);
    if(it == capitals.end())
    {
	    std::cout<<" City not found returning 0"<<std::endl;
	    return 0;
    }
    return capitals[name];
  }

  /*
  static SingletonDatabase* get_instance()
  {
    if (!instance)
      instance = new SingletonDatabase;
    return instance; // atexit
  }
  */
};

int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database
{
  std::map<std::string, int> capitals;
public:


  DummyDatabase()
  {
    capitals["alpha"] = 1;
    capitals["beta"] = 2;
    capitals["gamma"] = 3;
  }

  int get_population(const std::string& name) override {
    return capitals[name];
  }
};

struct SingletonRecordFinder
{
  int total_population(std::vector<std::string> names)
  {
    int result = 0;
    for (auto& name : names)
    {
        int a =  SingletonDatabase::get().get_population(name);
	result += a;
    }
       std::cout <<" TOTAL_POLULATION NAME val = " << result<<std::endl;
    return result;
  }
};

struct ConfigurableRecordFinder
{
  explicit ConfigurableRecordFinder(Database& db)
    : db{db}
  {
  }

  int total_population(std::vector<std::string> names)
  {
    int result = 0;
    for (auto& name : names)
      result += db.get_population(name);
      //std::cout <<" TOTAL_POLULATION NAME val = " << result<<std::endl;
    return result;
  }

  Database& db;
};
