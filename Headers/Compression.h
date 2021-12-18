#ifndef COMPRESSION_H
#define COMPRESSION_H
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <cstdint>
#include <vector>
using namespace std;

// The node of a tree
struct Node1
{
    char character;
    int frequency;
    Node1* left, * right;
};

// order the heap after comparing objects
struct comp
{
    bool operator()(Node1* l, Node1* r)
    {
        // As the frequency decrease  ,the node get the heighest piriority
        return (l->frequency) > (r->frequency);
    }
};


Node1* getNode(char character, int frequency, Node1* left, Node1* right);
void encoding(Node1* root, string str, unordered_map<char, string>& huffmanCode);
void decoding(Node1* root, int& i, string& str, string& decoded);
void buildHuffmanTree(string text);
string Huffman_encoding(string text);
string Huffman_decoding(string encoded_text);
std::vector<uint8_t> toBinary(std::string const& binStr);

#endif // COMPRESSION_H
