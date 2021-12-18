#include"Compression.h"

// Function to get a new tree node either in the left or right
Node1* getNode(char character, int frequency, Node1* left, Node1* right)
{
    //create new node
    Node1* node = new Node1();

    node->character = character;
    node->frequency = frequency;
    node->left = left;
    node->right = right;

    return node;
}

Node1* main_root;

// traverse the Huffman Tree and store Huffman Codes in a map.
void encoding(Node1* root, string str, unordered_map<char, string>& huffmanCode)
{
    if (root == nullptr)
        return;

    // find a leaf node
    if (!root->left && !root->right) {
        huffmanCode[root->character] = str;
    }

    encoding(root->left, str + "0", huffmanCode);
    encoding(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decoding(Node1* root, int& i, string& str, string& decoded)
{
    char temp;

    if (root == nullptr) {
        return;
    }

    // find a leaf node
    if (!root->left && !root->right)
    {
        temp = root->character;
        decoded += temp;
        return;
    }

    i++;

    if (str[i] == '0')
        decoding(root->left, i, str, decoded);
    else
        decoding(root->right, i, str, decoded);

}

// Building Huffman Tree and decode given input text
void buildHuffmanTree(string text)
{
    // count frequency of appearance of each character and store it in a map
    unordered_map<char, int> frequency;
    for (char ch : text) {
        frequency[ch]++;
    }

    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<Node1*, vector<Node1*>, comp> pq;

    // Create a leaf node for each character and add it to the priority queue.
    for (auto pair : frequency) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        // Remove the two nodes of highest priority (lowest frequency) from the queue
        Node1* left = pq.top(); pq.pop();
        Node1* right = pq.top();	pq.pop();

        // Create a new internal node with these two nodes
        // as children and with frequency equal to the sum of the two nodes' frequencies. Add the new node
        // to the priority queue.
        int sum = left->frequency + right->frequency;
        pq.push(getNode('\0', sum, left, right));
    }

    // root stores pointer to root of Huffman Tree
    main_root = pq.top();
}

string Huffman_encoding(string text)
{
    buildHuffmanTree(text);

    string encoded = "";
    unordered_map<char, string> StringEncoded;
    encoding(main_root, "", StringEncoded);

    for (char ch : text) {
        encoded += StringEncoded[ch];
    }
    return encoded;
}

string Huffman_decoding(string encoded_text)
{
    string decoded = "";
    // traverse the Huffman Tree again and this time
    // decode the encoded string
    int index = -1;
    while (index < (int)encoded_text.size() - 2) {
        decoding(main_root, index, encoded_text, decoded);
    }
    return decoded;
}
std::vector<uint8_t> toBinary(std::string const& binStr)
{
    std::vector<uint8_t> result;
    result.reserve(binStr.size() / 8);
    size_t pos = 0;
    size_t len = binStr.length();
    while (pos < len)
    {
         size_t curLen = std::min(static_cast<size_t>(8), len-pos);
         auto curStr = binStr.substr(pos, curLen) + std::string(8-curLen, '0');
         std::cout << "curLen: " << curLen << ", curStr: " << curStr << "\n";
         result.push_back(std::stoi(curStr, 0, 2));
         pos += 8;
    }
    return result;
}
