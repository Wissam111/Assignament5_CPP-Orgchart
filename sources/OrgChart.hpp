
/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 05/2022
 */
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>

enum ORDER
{
    LEVEL_ORDER,
    PREORDER,
    REVERSE_ORDER
};

namespace ariel
{

    class OrgChart
    {

        /*--------struct represents node in the tree--------*/
        struct Node
        {
            std::string key;
            std::vector<Node *> node_children;
            int lvl = 0;
        };

        static Node *createNode(std::string const &key)
        {
            Node *temp = new Node;
            temp->key = key;
            return temp;
        };

        class Iterator
        {

        public:
            std::vector<Node *> vec_order;
            unsigned curr_index;

            Iterator(ORDER order, Node *root) : curr_index(0)
            {
                fill(order, root);
                vec_order.push_back(nullptr);
            }

            /*--------iterator operations--------*/
            Iterator &operator++();
            std::string &operator*() const;
            bool operator==(Iterator const &otherIter) const;
            bool operator!=(Iterator const &otherIter) const;
            std::string *operator->() const;

            /*--------filling the iterator vector--------*/
            void fill(ORDER order, Node *root);
            void fill_lvlOrder(Node *root);
            void fill_preOrder(Node *root);
            void fill_revOrder(Node *root);
        };

    private:
        Node *_root;

    public:
        OrgChart() : _root(nullptr){};
        ~OrgChart() { deleteTree(_root); }

        /*--------Move constructors and move assignment For Make Tidy--------*/
        OrgChart(const OrgChart &a) = delete;
        OrgChart &operator=(const OrgChart &a) = delete;
        OrgChart(OrgChart &&a) noexcept
            : _root(a._root)
        {
            a._root = nullptr;
        }
        OrgChart &operator=(OrgChart &&a) noexcept;
        /*--------searching for element--------*/
        static Node *getNode(Node *root, std::string const &key);

        /*--------adding elements--------*/
        OrgChart &add_root(std::string const &new_r);
        OrgChart &add_sub(std::string const &n1, std::string const &n2);

        /*--------Iterator traverse--------*/
        auto begin_level_order()
        {
            checkThrows();
            return Iterator(LEVEL_ORDER, _root);
        }
        auto end_level_order()
        {
            checkThrows();
            return Iterator(LEVEL_ORDER, nullptr);
        }
        auto begin_reverse_order()
        {
            checkThrows();
            return Iterator(REVERSE_ORDER, _root);
        };
        auto reverse_order()
        {
            checkThrows();
            return Iterator(REVERSE_ORDER, nullptr);
        };
        auto begin_preorder()
        {
            checkThrows();
            return Iterator(PREORDER, _root);
        }
        auto end_preorder()
        {
            checkThrows();
            return Iterator(PREORDER, nullptr);
        }
        auto begin()
        {
            return begin_level_order();
        }
        auto end()
        {
            return end_level_order();
        }

        void checkThrows()
        {
            if (_root == nullptr)
            {
                throw std::invalid_argument("Invalid operations!");
            }
        }

        /*--------output operator--------*/
        friend std::ostream &operator<<(std::ostream &out, OrgChart const &orgChart);

        /*--------deleting the tree--------*/
        static void deleteTree(Node *root);
    };
}