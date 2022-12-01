#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    size_t child_count;
    size_t metadata_count;
    vector<Node> children;
    vector<int> metadata;

    Node()
    : child_count(0), metadata_count(0)
    { }
};

size_t metadata_sum = 0;
Node parse_node(vector<int> &data)
{
    Node rval;
    rval.child_count = data.back();
    data.pop_back();

    rval.metadata_count = data.back();
    data.pop_back();

    for (size_t idx = 0; idx != rval.child_count; ++idx)
    {
        rval.children.push_back(parse_node(data));
    }

    for (size_t idx = 0; idx != rval.metadata_count; ++idx)
    {
        rval.metadata.push_back(data.back());
        data.pop_back();
        metadata_sum += rval.metadata.back();
    }
    
    return rval;
}

size_t node_value(Node const &node)
{
    if (node.children.empty())
    {
        return accumulate(node.metadata.begin(), node.metadata.end(), 0);
        
    }

    size_t sum = 0;
    for (int idx : node.metadata)
    {
        int index = idx - 1;
        if (index >= node.children.size())
            continue;

        sum += node_value(node.children[index]);
    }

    return sum;
}

int main()
{
    vector<int> data;

    while(!cin.eof())
    {
        int tmp;
        cin >> tmp;
        data.push_back(tmp);
    }

    vector<int> copy(data.rbegin(), data.rend()); //reverse data
    Node root = parse_node(copy);
    
    cout << "metadata sum: " << metadata_sum << "\n"; // answer to 1
    cout << "node value: " << node_value(root) << "\n"; // answer to 2
}