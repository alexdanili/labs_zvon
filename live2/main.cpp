#include <iostream>
#include <vector>
#include <windows.h>
#include <thread>
#include <random>

enum state_
{
    DEAD,
    YOUNG,
    OLD
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

    if (table[(x+SIZE-1)%SIZE][y].state == YOUNG) result[0]++;
    if (table[(x+SIZE-1)%SIZE][(y+SIZE-1)%SIZE].state == YOUNG) result[0]++;
    if (table[(x+SIZE-1)%SIZE][(y+1)%SIZE].state == YOUNG) result[0]++;
    if (table[x][(y+SIZE-1)%SIZE].state == YOUNG) result[0]++;
    if (table[x][(y+1)%SIZE].state == YOUNG) result[0]++;
    if (table[(x+1)%SIZE][(y+SIZE-1)%SIZE].state == YOUNG) result[0]++;
    if (table[(x+1)%SIZE][y].state == YOUNG) result[0]++;
    if (table[(x+1)%SIZE][(y+1)%SIZE].state == YOUNG) result[0]++;

    if (table[(x+SIZE-1)%SIZE][y].state == OLD) result[1]++;
    if (table[(x+SIZE-1)%SIZE][(y+SIZE-1)%SIZE].state == OLD) result[1]++;
    if (table[(x+SIZE-1)%SIZE][(y+1)%SIZE].state == OLD) result[1]++;
    if (table[x][(y+SIZE-1)%SIZE].state == OLD) result[1]++;
    if (table[x][(y+1)%SIZE].state == OLD) result[1]++;
    if (table[(x+1)%SIZE][(y+SIZE-1)%SIZE].state == OLD) result[1]++;
    if (table[(x+1)%SIZE][y].state == OLD) result[1]++;
    if (table[(x+1)%SIZE][(y+1)%SIZE].state == OLD) result[1]++;
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
            if(table[i][j].state != YOUNG){
                if((around(i,j,table)[0]+around(i,j,table)[1]) == 3 && around(i,j,table)[1] >= 2 && table[i][j].state == DEAD)
                {

                    result.at(i).at(j).state = YOUNG;
                }
                else if(((around(i,j,table)[0]+ around(i,j,table)[1]) == 2 || (around(i,j,table)[0]+around(i,j,table)[1]) == 3) &&  around(i,j,table)[0]<2 && table[i][j].state == OLD)
                {
                    result.at(i).at(j).state = OLD;
                }else
                {
                    result.at(i).at(j).state = DEAD;
                }
            }
            else
            {
                result.at(i).at(j).state = OLD;
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < table.size(); i++)
    {
        for(int j = 0; j < table[0].size(); j++)
        {
            if(table[i][j].state == YOUNG)
            {
                pos(j,i);
                SetConsoleTextAttribute(hConsole,10);
                std::cout<<"o";
            }
            else if(table[i][j].state == OLD)
            {
                pos(j,i);
                SetConsoleTextAttribute(hConsole,9);
                std::cout<<"O";
            }
            else
            {
                pos(j,i);
                SetConsoleTextAttribute(hConsole,0);
                std::cout<<"_";
            }
        }
        std::cout<<std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::default_random_engine generator;

    std::vector<std::vector<cell>> first;
    std::vector<std::string> input {"____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "________OOOO________",
                                    "_______O____O_______",
                                    "_______O____O_______",
                                    "_______O____O_______",
                                    "_______O____O_______",
                                    "________OOOO________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________",
                                    "____________________"
                                   };
    first.resize(20);
    for(int i = 0; i < 20; i++)
    {
        first[i].resize(20);
    }

    for(int i = 0; i < first.size(); i++)
    {
        for(int j = 0; j < first.size(); j++)
        {
            if(input[i][j] == 'O')
            {
                first[i][j].state = OLD;
            }
            else if(input[i][j] == 'o')
            {
                first[i][j].state = YOUNG;
            }

        }
    }

    for(int i = 0; i < first.size(); i++)
    {
        for(int j = 0; j  < first[0].size(); j++)
        {

            if(input[i][j] == 'o')
            {
               first[i][j].state = YOUNG;
            }
            else if(input[i][j] == 'O')
            {
               first[i][j].state = OLD;
            }
            else
            {
                first[i][j].state = DEAD;
            }

        }
    }

    while(true)
    {
        print(first);
        first = iteration(first);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}
