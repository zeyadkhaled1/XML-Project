#include "Xml_to_Json.h"
using namespace std;


    void Node:: setvalue(string v)
    {
        value = v;}


    void Tree:: setroot(Node *t)
    {
        m_root = t;
    }
    void Tree ::addNode(Node *node, Node *parent)
    {
        if (parent == nullptr)
        {
            parent = m_root;
        }
        parent->children.push_back(node);
    }

    string Tree:: format(int depth, Node *parent )
    {
        if (parent == nullptr)
        {
            parent = m_root;
            depth = 0;
        }
        string output = "";
        for (int i = 0; i < parent->children.size(); ++i)
        {
            Node *node = parent->children[i];

            string indentation = "";

            // indentation value
            for (int i = 0; i < depth; ++i)
            {
                indentation += "    ";
            }

            // insert key open
            output += indentation + "<" + node->key + ">\n"; // <name>

            if (node->children.size() > 0)
            {
                output += format(depth + 1, node);
            }
            else
            {
                // insert value
                output += indentation + "\t" + node->value + "\n"; // Nada
            }
            // close the key
            output += indentation + "</" + node->key + ">\n"; // </name>
        }
        return output;
    }
    string Tree ::XMLToJson(int level , Node *parent )
    {
        string kk;
        string output = "";
        if (parent == nullptr)
        {
            parent = m_root;
            level = 0;
        }

        for (int i = 0; i < parent->children.size(); ++i)
        {
            Node *node = parent->children[i]; // creating poienters to children of the parent node
            string Spacing = "\t";
            for (int i = 0; i < level; ++i) // lvl1 4 spacing , lvl2 8 spacing ,...
            {
                Spacing += "\t";
            }
            output += Spacing + "\"" + node->key + "\": "; //"class":

            if (node->children.size() > 0)
            {
//                if (node->children.size() > 1)
//                {
//                    Node *n = node->children[i];
//                    Node *m = node->children[i + 1];
//                    if (n->key == m->key)
//                    {
//                        output += "[";
//                    }

                    output += XMLToJson(level + 1, node);
                    // to know if this node is the last node in its level
                    //  from 119 to 127 each child

                    if (i == parent->children.size() - 1)
                    {
                        output += "\t"; // no action
                    }
                    else
                    {
                        output += ",\n";
                    }
//                }
            }
            else
            { // if it is leaf node
                if (i == parent->children.size() - 1)
                { // if last node in its level
                    output += "\"" + node->value + "\"";
                }
                else
                {
                    output += "\"" + node->value + "\""; //"1"
                    output += ",\n";
                }
            }
            kk = Spacing;
        }
//        for (int i = 0; i < parent->children.size(); ++i)
//        {
//            Node *node = parent->children[i];
//            if (node->children.size() > 1)
//            {
//                Node *n = node->children[i];
//                Node *m = node->children[i + 1];
//                if (n->key == m->key)
//                {
//                    output += "]";
//                }
//            } // output += "} \n";
//        }
        string x = "\t";
        return "{\n" + output + "\n" + kk + "}";
    }


Tree parse(string g)
{
    stack<Node *> stk;
    unsigned int h = g.find("<", 0), j;
    if (g.substr(h + 1, 1) == "?")
    {
        j = g.find(">", h);
        g.erase(h, j - h + 1);
    }
    string firsttag;
    unsigned int st = 0, ps;
    st = g.find("<", st);
    ps = g.find(">", st);
    firsttag = g.substr(st + 1, ps - st - 1);
    Node *root = new Node;
    Node *node = new Node;
    node->key = firsttag;
    Tree y;
    y.setroot(root);
    y.addNode(node, root);
    st = g.find("<", ps);
    ps = g.find(">", st);
    Node *parent = node;
    while (g.find("<", ps) != string ::npos)
    {
        if (g.substr(st + 1, 1) != "/")
        {
            Node *newnode = new Node;
            newnode->key = g.substr(st + 1, ps - st - 1);
            st = g.find("<", ps);
            y.addNode(newnode, parent);
            if (st != string::npos)
            {
                newnode->value = g.substr(ps + 1, st - ps - 1);
                if (g.substr(st + 1, 1) != "/")
                {
                    stk.push(parent);
                    parent = newnode;
                }
            }
            ps = g.find(">", st);
        }
        if (g.substr(st + 1, 1) == "/")
        {
            st = g.find("<", ps);
            ps = g.find(">", st);
            if (st != string::npos)
            {
                if (g.substr(st + 1, 1) == "/")
                {
                    if (!stk.empty())
                    {
                        parent = stk.top();
                        stk.pop();
                    }
                }
            }
        }
    }
    return y;
}

