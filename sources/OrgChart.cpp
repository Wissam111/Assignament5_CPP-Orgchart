/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 05/2022
 */

#include "OrgChart.hpp"
namespace ariel
{
    /*
     * @brief adding/changing the root Node
     */
    OrgChart &OrgChart::add_root(std::string const &new_r)
    {
        if (_root)
        {
            _root->key = new_r;
        }
        else
        {
            _root = createNode(new_r);
        }
        _root->lvl = 0;

        return *this;
    }

    /*
     * @brief adding new element into the tree
     */
    OrgChart &OrgChart::add_sub(std::string const &n1, std::string const &n2)
    {

        Node *temp = getNode(_root, n1);
        Node *new_Node = createNode(n2);
        temp->node_children.push_back(new_Node);
        new_Node->lvl = temp->lvl + 1;
        return *this;
    }

    /*
     * @brief  output operator for the orgchart
     */
    std::ostream &operator<<(std::ostream &out, OrgChart const &orgChart)
    {
        std::string str;

        OrgChart ::Iterator itr{LEVEL_ORDER, orgChart._root};
        int currentLvl = 0;
        for (unsigned i = 0; i < itr.vec_order.size() - 1; i++)
        {
            if (currentLvl != itr.vec_order[i]->lvl)
            {
                currentLvl = itr.vec_order[i]->lvl;
                str += "\n";
            }
            str += itr.vec_order[i]->key + "     ";
        }

        out << str;
        return out;
    }

    /*
     * @brief searching for an element with given key and tree root.
     */
    OrgChart::Node *OrgChart::getNode(Node *root, std::string const &key)
    {

        Iterator itr{LEVEL_ORDER, root};

        for (unsigned i = 0; i < itr.vec_order.size() - 1; i++)
        {

            if (itr.vec_order[i]->key == key)
            {
                return itr.vec_order[i];
            }
        }
        throw std::invalid_argument("Invalid operations!");
    }

    /*
     * @brief deleting each node in the tree
     */
    void OrgChart::deleteTree(Node *root)
    {
        if (!root)
        {
            return;
        }
        Iterator itr{LEVEL_ORDER, root};

        for (unsigned i = 0; i < itr.vec_order.size(); i++)
        {

            delete itr.vec_order[i];
        }
    }

    OrgChart &OrgChart::operator=(OrgChart &&a) noexcept
    {
        if (&a == this)
        {
            return *this;
        }
        delete _root;
        _root = a._root;
        a._root = nullptr;
        return *this;
    }

    /*-------------iterator class implementation-------------*/

    void OrgChart::Iterator::fill(ORDER order, Node *root)
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
    /*
     * @brief filling the iterator vector in level Order traverse
     */
    void OrgChart ::Iterator::fill_lvlOrder(Node *root)
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

    /*
     * @brief filling the iterator vector in reverse Order traverse
     */
    void OrgChart ::Iterator::fill_revOrder(Node *root)
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

    /*
     * @brief filling the iterator vector in  preOrder traverse
     */
    void OrgChart::Iterator::fill_preOrder(Node *root)
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

    OrgChart::Iterator &OrgChart::Iterator::operator++()
    {
        curr_index++;
        return *this;
    }

    std::string &OrgChart::Iterator::operator*() const
    {
        return vec_order[curr_index]->key;
    }

    bool OrgChart::Iterator::operator==(OrgChart::Iterator const &otherIter) const
    {
        return vec_order[curr_index] == otherIter.vec_order[otherIter.curr_index];
    }

    bool OrgChart::Iterator::operator!=(OrgChart::Iterator const &otherIter) const
    {
        return !(*this == otherIter);
    }

    std::string *OrgChart::Iterator::operator->() const
    {
        return &vec_order[curr_index]->key;
    }

}
