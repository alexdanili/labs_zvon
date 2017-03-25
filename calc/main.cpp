#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <set>
#include <stdlib.h>
#include <map>
#include <regex>

struct Node
{

    Node* left;
    Node* right;
    Node* parent;
    Node* now;
    bool wch;
    std::string value;
    std::set<char> opers;


    Node* end()
    {
        Node* tmp = this;
        while(tmp->left != nullptr || tmp->right != nullptr)
        {
            tmp = tmp->right;
        }
        return tmp;
    }

    void calc(Node* Tree)
    {


        float result = 0;
        if((Tree->value[0] == '+') || (Tree->value[0] == '-') || (Tree->value[0] == '*') || (Tree->value[0] == '/')) //opers.find(*((Tree->value).c_str())) != opers.end()
        {
            if(Tree->left && Tree->right)
            {
                if(((Tree->left->value.length() > 1) || (Tree->left->value.length() == 1 && (opers.find(*((Tree->left->value).c_str())) == opers.end()))) && ((Tree->right->value.length() > 1) || (Tree->right->value.length() == 1 && (opers.find(*((Tree->right->value).c_str())) == opers.end()))))
                {
                    if(Tree->left->wch == false && Tree->right->wch == false)
                    {
                        switch (*((Tree->value).c_str())) {
                        case '+':
                            result =std::stof(Tree->right->value) + std::stof(Tree->left->value);
                            break;
                        case '-':
                            result =std::stof(Tree->right->value) - std::stof(Tree->left->value);
                            break;
                        case '*':
                            result =std::stof(Tree->right->value) * std::stof(Tree->left->value);
                            break;
                        case '/':
                            result =std::stof(Tree->right->value) / std::stof(Tree->left->value);
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        switch (*((Tree->value).c_str())) {
                        case '+':
                            result =std::stof(Tree->right->value) + std::stof(Tree->left->value);
                            break;
                        case '-':
                            result =std::stof(Tree->left->value) - std::stof(Tree->right->value);
                            break;
                        case '*':
                            result =std::stof(Tree->right->value) * std::stof(Tree->left->value);
                            break;
                        case '/':
                            result =std::stof(Tree->left->value) / std::stof(Tree->right->value);
                            break;
                        default:
                            break;
                        }
                    }
                    Tree->right = nullptr;
                    Tree->left = nullptr;
                    Tree->wch = true;
                    std::ostringstream ss;
                    ss << result;
                    Tree->value = ss.str();

                    if(Tree->parent)
                    {

                        calc(Tree->parent);
                    }
                }
                else
                {


                    if(Tree->left->value.length() == 1 && opers.find(*((Tree->left->value).c_str())) != opers.end())
                        calc(Tree->left);
                    else if(Tree->right->value.length() == 1 && opers.find(*((Tree->right->value).c_str())) != opers.end())
                        calc(Tree->right);
                }

            }
            else
            {
                calc(Tree->parent);
            }

        }
        else
        {
            calc(Tree->parent);
        }
    }

    void show(Node* Tree)
    {
        if (Tree!=NULL)
        {
            show(Tree->left);
            std::cout<<Tree->value;
            show(Tree->right);
        }
    }


    Node()
    {
        wch = false;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        now = this;
        value = "";
        opers.insert('p');
        opers.insert('+');
        opers.insert('-');
        opers.insert('*');
        opers.insert('/');
        opers.insert('p');
    }





    void add(std::string value_,int i = 1)
    {

        if(opers.find(value_[0]) != opers.end())
        {
            if(parent == nullptr && value == "")
            {
                value = value_;
            }
            else
            {
                if(now->right == nullptr)
                {
                    now->right = new Node();
                    now->right->parent = now;
                    now->right->value = value_;
                    now = now->right;
                }
                else
                {
                    if(now->left == nullptr)
                    {
                        now->left = new Node();
                        now->left->parent = now;
                        now->left->value = value_;
                        now = now->left;
                    }
                    else
                    {
                        now = now->parent;
                        add(value_);
                    }
                }
            }
        }
        else
        {
            if(now->left == nullptr)
            {
                now->left = new Node();
                now->left->parent = now;
                now->left->value = value_;
            }
            else
            {
                if(now->right == nullptr)
                {
                    now->right = new Node();
                    now->right->parent = now;
                    now->right->value = value_;
                    now = now->parent;
                }
                else
                {
                    now = now->parent;
                    add(value_);
                }
            }
        }

    }

};

std::vector<std::string> split(std::string a, std::string b)
{
    std::vector<std::string> r;
    int i = 0;
    while (i != -1) {
        i = a.find(b);

        r.push_back(a.substr(0,i));
        a = a.substr(i+b.size(),a.size());
    }
    return r;
}

int main()
{
    Node root;
    std::string s;
   // std::fstream fin = "input.txt";

    std::getline(std::cin,s);
    std::string delimiter = " ";
    std::vector<std::string> tokens = split(s,delimiter);
    std::map<std::string,std::string> vars;
    std::regex var("([a-zA-Z_0-9]*)\\s*=\\s*([0-9]*)");
    std::smatch res;
    std::vector<int> del;
    for(unsigned int i = 0; i < tokens.size(); i++)
    {
        if(std::regex_search(tokens[i],res,var))
        {
            std::string name = res[1];
            std::string value = res[2];
            vars[name] = value;
            del.push_back(i);
        }
    }

    for(int i = 0; i < del.size(); i++)
    {
        tokens.erase(tokens.begin()+del[i]);
        if(i+1 < del.size())
        del[i+1]--;
    }
    for(int i = tokens.size()-1; i >= 0 ; i--)
    {
        if(vars.find(tokens[i]) == vars.end())
        {
            root.add(tokens.at(i),i);
        }
        else
        {
            root.add((vars[tokens[i]]),i);
        }

    }
    root.show(&root);
    std::cout<<"\n";
    root.calc(&root);
    std::cout<<"\n";
    root.show(&root);
    return 0;
}
