// #include "OrgChart.hpp"

// namespace ariel
// {

//     template <typename T>
//     OrgChart<T> &OrgChart<T>::add_root(T const &new_r)
//     {
//         if (_root)
//         {
//             _root->key = new_r;
//         }
//         else
//         {
//             _root = createNode(new_r);
//         }

//         return *this;
//     }
//     //     // template <typename T>
//     //     // OrgChart<T> &OrgChart<T>::add_sub(T const &n1, T const &n2)
//     //     // {

//     //     //     Node *temp = getNode(n1);
//     //     //     if (!temp)
//     //     //     {
//     //     //         throw invalid_argument("Invalid operations!");
//     //     //     }

//     //     //     temp->node_children.push_back(createNode(n2));

//     //     //     return *this;
//     //     // }
//     //     // template <typename T>
//     //     // void OrgChart<T>::Iterator::fill_lvlOrder(Node *root)
//     //     // {
//     //     //     if (!root)
//     //     //     {
//     //     //         return;
//     //     //     }
//     //     //     std::queue<Node *> q;
//     //     //     q.push(root);

//     //     //     while (!q.empty())
//     //     //     {
//     //     //         int sz = q.size();

//     //     //         while (sz > 0)
//     //     //         {
//     //     //             Node *temp = q.front();
//     //     //             vec_order.push_back(temp);
//     //     //             q.pop();

//     //     //             for (int i = 0; i < temp->node_children.size(); i++)
//     //     //             {
//     //     //                 q.push(temp->node_children[i]);
//     //     //             }
//     //     //             sz--;
//     //     //         }
//     //     //     }
//     //     // }

//     //     // template <typename T>
//     //     // Node &OrgChart<T>::getNode(int key)
//     //     // {
//     //     // }

// }
