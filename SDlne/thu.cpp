#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main()
{
    fstream myfile;
    myfile.open("data.txt", ios::in | ios::out);
    int record[3];
    for(int i = 0; i < 3; i++)
    {
        myfile >> record[i];
    }
    if(scores > record[0])
    {
        record[2] = record[1];
        record[1] = record[0];
        record[0] = n;
    }
    else if(scores > record[1])
    {
        record[2] = record[1];
        record[1] = scores;
    }
    else if(scores > record[2])
    {
        record[2] = scores;
    }
    myfile.close();
    myfile.open("data.txt", ios::out | ios::trunc);
    char c = ' ';
    for(int i = 0; i < 3; i++)
    {
        myfile << record[i];
        myfile << c;
    }
    myfile.close();
    /*void newRecord()
    {
        SDL_Texture* congra = graphics.loadTexture("newrecord.jpg");
        Mix_Chunk* soundcongra = graphics.loadSound("subway-surfers-new-record.mp3");
        graphics.prepareScene(congra);
        graphics.presentScene();
        graphics.playChunk(soundcongra);
        SDL_Delay(6000);
        SDL_DestroyTexture(congra);
        Mix_FreeChunk(soundcongra);
    }*/
}
