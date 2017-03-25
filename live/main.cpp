#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>

enum state_
{
    DEAD,
    ALIVE
};

struct cell
{
    state_ state;
};

std::vector<int> around(int x, int y, std::vector<std::vector<cell>> table)
{
    std::vector<int> result;
    result.resize(3);
    int SIZE = table.size();

    if (table[(x+SIZE-1)%SIZE][y].state == ALIVE) result[0]++;
    if (table[(x+SIZE-1)%SIZE][(y+SIZE-1)%SIZE].state == ALIVE) result[0]++;
    if (table[(x+SIZE-1)%SIZE][(y+1)%SIZE].state == ALIVE) result[0]++;
    if (table[x][(y+SIZE-1)%SIZE].state == ALIVE) result[0]++;
    if (table[x][(y+1)%SIZE].state == ALIVE) result[0]++;
    if (table[(x+1)%SIZE][(y+SIZE-1)%SIZE].state == ALIVE) result[0]++;
    if (table[(x+1)%SIZE][y].state == ALIVE) result[0]++;
    if (table[(x+1)%SIZE][(y+1)%SIZE].state == ALIVE) result[0]++;
    return result;
}

std::vector<std::vector<cell>> iteration(std::vector<std::vector<cell>> table)
{
    std::vector<std::vector<cell>> result;
    result.resize(table.size());
    for(int i = 0; i < table.size();i++)
    {
        result[i].resize(table[0].size());
    }
    for(int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < table.size(); j++)
        {
            if(around(i,j,table)[0] == 3)
            {
                result.at(i).at(j).state = ALIVE;
            }
            else if(around(i,j,table)[0] < 2 || around(i,j,table)[0] > 3)
            {
                result.at(i).at(j).state = DEAD;
            }
            else if(around(i,j,table)[0] == 2 && table[i][j].state == ALIVE)
            {
                result.at(i).at(j).state = ALIVE;
            }
        }
    }
    return result;
}

void pos(short C, short R)
{
    COORD xy ;
    xy.X = C ;
    xy.Y = R ;
    SetConsoleCursorPosition(
                GetStdHandle(STD_OUTPUT_HANDLE), xy);
}
void print(std::vector<std::vector<cell>> table)
{

    for(int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < table[0].size(); j++)
        {
            if(table[i][j].state == ALIVE)
            {
                pos(i,j);
                std::cout<<"O";
            }
            else
            {
                pos(i,j);
                std::cout<<"_";
            }
        }
        std::cout<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::vector<cell>> first;
    std::vector<std::string> input {"_O____",
                                    "__O___",
                                    "OOO___",
                                    "______",
                                    "______",
                                    "______"};
    first.resize(input.size());
    for(int i = 0; i < first.size(); i++)
    {
        first[i].resize(first.size());
    }
    for(int i = 0; i < first.size(); i++)
    {
        for(int j = 0; j  < first[0].size(); j++)
        {
            if(input[i][j] == 'O')
            {
                first[i][j].state = ALIVE;
            }
        }
    }

    while(true)
    {
        print(first);
        first = iteration(first);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    return 0;
}
