// // #include "OrgChart.hpp"
// #include "OrgChart.cpp"

// using namespace ariel;
// int main()
// {

//     OrgChart organization;
//     organization.add_root("CEO")
//         .add_sub("CEO", "CTO")
//         .add_sub("CEO", "CFO")
//         .add_sub("CEO", "COO")
//         .add_sub("CTO", "VP_SW")
//         .add_sub("COO", "VP_BI")
//         .add_sub("CFO", "VP_HOX")
//         .add_sub("VP_SW", "VP2_SW")
//         .add_sub("VP_HOX", "VP_HOX2")
//         .add_sub("VP_BI", "VP_BI2");

//     int c = -1;

//     std::cout << "Choose iteration: " << std::endl;
//     std::cout << "0 - level Order" << std::endl;
//     std::cout << "1 - reverse Order" << std::endl;
//     std::cout << "2 - preOrder" << std::endl;
//     std::cout << "3 - for Printing"
//               << "\n\n";

//     while (true)
//     {
//         std::cin >> c;
//         switch (c)
//         {
//         case 0:
//             for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
//             {
//                 std::cout << (*it) << " ";
//             }
//             std::cout << "\n";
//             break;

//         case 1:

//             for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it)
//             {
//                 std::cout << (*it) << " ";
//             }
//             std::cout << "\n";
//             break;

//         case 2:
//             for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it)
//             {
//                 std::cout << (*it) << " ";
//             }
//             std::cout << "\n";
//             break;

//         case 3:
//             std::cout << organization << std::endl;
//             break;

//         default:
//             break;
//         }
//     }
// }