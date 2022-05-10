#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include "OrgChart.hpp"
using namespace ariel;
#include "doctest.h"
TEST_CASE("not valid  input test case")
{
    OrgChart<string> organization;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")
        .add_sub("CEO", "CFO")
        .add_sub("CEO", "COO")
        .add_sub("CTO", "VP_SW")
        .add_sub("COO", "VP_BI");
    std::string str = "CTF";
    for (int i = 0; i < 10; i++)
    {
        CHECK_THROWS(organization.add_sub(str, "VP_BI"));
        str += "A";
    }
}

TEST_CASE("valid input")
{
    OrgChart<string> organization;
    organization.add_root("CEO")
        .add_sub("CEO", "CTO")
        .add_sub("CEO", "CFO")
        .add_sub("CEO", "COO")
        .add_sub("CTO", "VP_SW")
        .add_sub("COO", "VP_BI")
        .add_sub("CEO", "CTO_VP");

    vector<std::string>
        vec_lvlOrder = {"CEO", "CTO", "CFO", "COO", "CTO_VP", "VP_SW", "VP_BI"};
    vector<std::string> vec_revOrder = {"VP_SW", "VP_BI", "CTO", "CFO", "COO", "CTO_VP", "CEO"};
    vector<std::string> vec_preOrder = {"CEO", "CTO", "VP_SW", "CFO", "COO", "VP_BI", "VP_BI2", "CTO_VP"};

    unsigned i = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
    {
        CHECK(*it == vec_lvlOrder[i]);
        i++;
    }
    i = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.end_reverse_order(); ++it)
    {
        CHECK(*it == vec_revOrder[i]);
        i++;
    }

    organization.add_sub("VP_BI", "VP_BI2");

    i = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
    {

        CHECK((*it) == vec_preOrder[i]);
        i++;
    }
}