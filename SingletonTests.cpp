#include "Singleton.hpp"
#include <gtest/gtest.h>
using namespace std;
TEST(DatabaseTests, IsSingletonTest)
{
  auto& db = SingletonDatabase::get();
  auto& db2 = SingletonDatabase::get();
  std::cout<<"instance count : "<<db.instance_count<<endl;
  ASSERT_EQ(1, db.instance_count);
  ASSERT_EQ(1, db2.instance_count);
}

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
  SingletonRecordFinder rf;
  std::vector<std::string> names{ "Seoul", "Mexico City" };
  int tp = rf.total_population(names);
   // std::cout<<"-----TP = "<<tp<< std::endl;
    EXPECT_EQ(17500000 + 17400000, tp);

    //EXPECT_EQ(17500000 + 17400000, 34900000);
}

TEST(RecordFinderTests, DependantTotalPopulationTest)
{
  DummyDatabase db{};
  ConfigurableRecordFinder rf(db) ;
  EXPECT_EQ(4, rf.total_population(
    std::vector<std::string>{"alpha", "gamma"}));
}


