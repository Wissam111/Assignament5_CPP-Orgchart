#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

enum ORDER
{
    LEVEL_ORDER,
    PREORDER,
    REVERSE_ORDER
};

namespace ariel
{

    template <typename T>
    class OrgChart
    {

        struct Node
        {
            T key;
            std::vector<Node *> node_children;
        };

        Node *createNode(T key)
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
            void fill(ORDER order, Node *root)
            {

                if (order == LEVEL_ORDER)
                {
                    fill_lvlOrder(root);
                }
                if (order == REVERSE_ORDER)
                {
                    fill_revOrder(root);
                }
                if (order == PREORDER)
                {
                    fill_preOrder(root);
                }
            }
            Iterator &operator++()
            {
                curr_index++;
                return *this;
            }
            T &operator*() const
            {
                return vec_order[curr_index]->key;
            }

            bool operator==(Iterator const &otherIter) const
            {
                return vec_order[curr_index] == otherIter.vec_order[otherIter.curr_index];
            }
            bool operator!=(Iterator const &otherIter) const
            {
                return !(*this == otherIter);
            }

            T *operator->() const
            {
                return &vec_order.at(curr_index)->key;
            }
            void fill_lvlOrder(Node *root);
            void fill_preOrder(Node *root);
            void fill_revOrder(Node *root);
        };

    private:
        Node *_root;

    public:
        OrgChart() : _root(nullptr){};
        // ~OrgChart();

        /*--------searching for element--------*/
        Node *getNode(Node *root, T const &key)
        {

            Iterator itr{LEVEL_ORDER, root};

            for (unsigned i = 0; i < itr.vec_order.size() - 1; i++)
            {

                if (itr.vec_order[i]->key == key)
                {
                    return itr.vec_order[i];
                }
            }
            throw invalid_argument("Invalid operations!");
        }
        /*--------adding elements--------*/
        OrgChart &add_root(T const &new_r);
        OrgChart &add_sub(T const &n1, T const &n2);

        /*--------Iterator traverse--------*/
        auto begin_level_order() { return Iterator(LEVEL_ORDER, _root); }
        auto end_level_order() { return Iterator(LEVEL_ORDER, nullptr); }
        auto begin_reverse_order() { return Iterator(REVERSE_ORDER, _root); };
        auto end_reverse_order() { return Iterator(REVERSE_ORDER, nullptr); };
        auto begin_preorder() { return Iterator(PREORDER, _root); }
        auto end_preorder() { return Iterator(PREORDER, nullptr); }
        /*--------output operator--------*/
        template <typename E>
        friend std::ostream &operator<<(std::ostream &out, OrgChart<E> const &orgChart)
        {
            std::string str;

            std::queue<Node *> q;
            q.push(orgChart._root);
            str += "        " + orgChart._root->key + "        \n";
            while (!q.empty())
            {

                Node *temp = q.front();
                q.pop();
                for (unsigned i = 0; i < temp->node_children.size(); i++)
                {

                    q.push(temp->node_children[i]);
                    str += temp->node_children[i]->key + "-----";
                }
                str += "\n";
            }

            out << str;
            return out;
        }
    };

    template <typename T>
    OrgChart<T> &OrgChart<T>::add_root(T const &new_r)
    {
        if (_root)
        {
            _root->key = new_r;
        }
        else
        {
            _root = createNode(new_r);
        }

        return *this;
    }
    template <typename T>
    OrgChart<T> &OrgChart<T>::add_sub(T const &n1, T const &n2)
    {

        Node *temp = getNode(_root, n1);
        temp->node_children.push_back(createNode(n2));
        return *this;
    }

    template <typename T>
    void OrgChart<T>::Iterator::fill_lvlOrder(Node *root)
    {
        if (!root)
        {
            return;
        }
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {

            Node *temp = q.front();
            vec_order.push_back(temp);
            q.pop();

            for (unsigned i = 0; i < temp->node_children.size(); i++)
            {
                q.push(temp->node_children[i]);
            }
        }
    }

    template <typename T>
    void OrgChart<T>::Iterator::fill_revOrder(Node *root)
    {
        if (!root)
        {
            return;
        }
        std::queue<Node *> q;
        std::stack<Node *> s;
        q.push(root);
        while (!q.empty())
        {
            int sz = q.size();
            Node *temp = q.front();
            q.pop();
            s.push(temp);
            std::reverse(temp->node_children.begin(), temp->node_children.end());
            for (unsigned i = 0; i < temp->node_children.size(); i++)
            {
                q.push(temp->node_children[i]);
            }
        }
        while (!s.empty())
        {
            vec_order.push_back(s.top());
            s.pop();
        }
    }
    template <typename T>
    void OrgChart<T>::Iterator::fill_preOrder(Node *root)
    {
        if (!root)
        {
            return;
        }

        std::stack<Node *> s;
        s.push(root);

        while (!s.empty())
        {

            Node *temp = s.top();
            s.pop();
            vec_order.push_back(temp);

            for (unsigned i = 0; i < temp->node_children.size(); i++)
            {
                s.push(temp->node_children[i]);
            }
        }
    }

}