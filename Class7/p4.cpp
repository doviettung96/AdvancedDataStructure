#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <map>

using namespace std;

struct Node
{
    char key;
    Node *left;
    Node *right;
    int freq;
    Node() : freq(0), left(NULL), right(NULL){};
    Node(char key, char freq) : key(key), freq(freq), left(NULL), right(NULL){};
    void display(){
        cout << freq << " " << endl;
    }
};

map<char, int> constructLetterFreqMap(string input)
{
    map<char, int> letter_freq_map;
    for (auto letter : input)
    {
        letter_freq_map[letter] += 1;
    }
    return letter_freq_map;
}

vector<Node *> constructNodeList(map<char, int> letter_freq_map)
{
    vector<Node *> node_list;
    for (auto m_it = letter_freq_map.begin(); m_it != letter_freq_map.end(); ++m_it)
    {
        Node *letter_freq_node = new Node(m_it->first, m_it->second);
        node_list.push_back(letter_freq_node);
    }
    return node_list;
}

Node *huffman(vector<Node *> node_list)
{
    auto compare_func = [](Node *a, Node *b) { return a->freq > b->freq; };
    priority_queue<Node *, vector<Node *>, decltype(compare_func)>
        Q(node_list.begin(), node_list.end(), compare_func);
    int n = node_list.size();
    for (int i = 0; i < n - 1; ++i)
    {
        Node *root = new Node();
        Node *left_child = Q.top();
        Q.pop();
        Node *right_child = Q.top();
        Q.pop();

        root->left = left_child;
        root->right = right_child;
        root->freq = left_child->freq + right_child->freq;
        Q.push(root);
    }
    Node *tree = Q.top();
    Q.pop();
    return tree;
}

void preorderVisit(Node *root, map<char, string> *huffman_encoder, string bit_code)
{
    if (root == NULL){
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        (*huffman_encoder)[root->key] = bit_code;
    }
    preorderVisit(root->left, huffman_encoder, bit_code + "0");
    preorderVisit(root->right, huffman_encoder, bit_code + "1");
}

map<char, string> constructEncodingMap(Node *root)
{
    map<char, string> huffman_encoder;
    preorderVisit(root, &huffman_encoder, "");
    return huffman_encoder;
}

string encode(map<char, string> huffman_encoder, string input){
    string encoded_input = "";
    for(auto letter: input){
        encoded_input += huffman_encoder[letter];
    }
    return encoded_input;
}

int main()
{
    string input;
    cin >> input;
    
    map<char, int> letter_freq_map = constructLetterFreqMap(input);

    vector<Node *> node_list = constructNodeList(letter_freq_map);
    
    cout << "Letter-freq list: " << endl;
    for(auto node : node_list){
        cout << node->key << ": " << node->freq << endl;
    }

    Node *huffman_tree = huffman(node_list);
    map<char, string> huffman_encoder = constructEncodingMap(huffman_tree);
    
    cout << "Huffman encode for the input string: " << endl;
    for(auto m_it = huffman_encoder.begin(); m_it != huffman_encoder.end(); ++m_it){
        cout << m_it->first << ": " << m_it->second << endl;
    }
}