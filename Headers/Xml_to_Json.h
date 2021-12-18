#ifndef XML_TO_JSON_H
#define XML_TO_JSON_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stack>
using namespace std;
class Node
{
public:
    string key;
    string value;
    vector<Node *> children;
    friend class Tree;
    void setvalue(string v);
};
class Tree
{
public:
    Node *m_root;
    string format(int depth = 0, Node *parent = nullptr);
    string XMLToJson(int level = 0, Node *parent = nullptr);
    void setroot(Node *t);
    void addNode(Node *node, Node *parent);
};
Tree parse(string g);
#endif // XML_TO_JSON_H
