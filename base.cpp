#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <memory>
using namespace std;

struct Point{
    int x = 0;
    int y = 0;
};

class Player{
public:
    Player(char ch){
        this->player_Texture = ch;
    }

    void movePlayer(char ch)
    {
        switch(ch){
            case 'A':
                position.x--;
                break;
            case 'D':
                position.x++;
                break;
            case 'W':
                position.y--;
                break;
            case 'S':
                position.y++;
                break;
        }
    }

    void setPosition(int x, int y){
        this->position.x = x;
        this->position.y = y;
    }

    Point getPlayerPosition()
    {
        return this->position;
    }

    char getTexture(){
        return player_Texture;
    }
private:
    char player_Texture = ' ';
    Point position;
};

class Platform{
public:
    Platform(int width, int height, Player& pl)
    {
        this->player = &pl;

        this->width  =  width;
        this->height = height;
        initPlatform();
    }

    ~Platform(){
        clearPlatform();
    }
    ///Расчет только на границы///
    void printPlatform(HANDLE& handle){

        if (player->getPlayerPosition().x==width-1)
            player->setPosition(player->getPlayerPosition().x-1, player->getPlayerPosition().y);
        if (player->getPlayerPosition().x<=0)
            player->setPosition(player->getPlayerPosition().x+1, player->getPlayerPosition().y);
        if (player->getPlayerPosition().y>=height-1)
            player->setPosition(player->getPlayerPosition().x, player->getPlayerPosition().y-1);
        if (player->getPlayerPosition().y<=0)
            player->setPosition(player->getPlayerPosition().x, player->getPlayerPosition().y+1);

        for (int i=0; i<height; ++i)
        {
            for (int j=0; j<width; ++j)
                if (i==player->getPlayerPosition().y && j==player->getPlayerPosition().x){
                    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                    std::cout<<player->getTexture();
                }
                else{
                    SetConsoleTextAttribute(handle, FOREGROUND_BLUE);
                    std::cout<<platform[i][j];
                }
            std::cout<<std::endl;
        }
    }
private:
    Player* player;
    int width  = 0;
    int height = 0;
    char** platform;
   //=================================//
    void initPlatform(){
        platform = (char**)malloc(sizeof(char*)*height);

        for (int i=0; i<height; ++i){
            platform[i] = (char*)malloc(sizeof(char)*width);
            for (int j=0; j<width; ++j)
            {
                if (i==0 || j==0 || i==height-1 || j==width-1)
                    platform[i][j] = '#';
                else
                    platform[i][j] = ' ';
            }
        }
    }
    void clearPlatform(){
        for (int i=0; i<height; ++i)
            free(platform[i]);
        free(platform);
    }

};

int main()
{
    char inputKey = ' ';
    Player player('P');
    Platform platform(20, 20, player);

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    while ((inputKey = getch())!=27)
    {
        system("cls");
        player.movePlayer(inputKey);
        platform.printPlatform(handle);
    }

    return 0;
}
