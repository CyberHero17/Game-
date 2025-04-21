#include <iostream>
#include <memory>
#include <experimental/random>
#include <vector>
std::vector<int> ids({1,2,3,4,5,6,7,8,9});
std::vector<int>* ptr = &ids;
std::vector<char> c;
int HowManyFreeWays(char k, char** mas){ // k - айдишеник комнаты
    int res = 0;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j){
            if( mas[i][j] == k){
                if(mas[i-1][j] == '#' && mas[i-1] != NULL)
                    res++;
                if(mas[i+1][j] == '#' && mas[i+1] != NULL)
                    res++;
                if(mas[i][j-1] == '#' && (mas+i)[j-1] != NULL)
                    res++;
                if(mas[i][j+1] == '#' && (mas+i)[j+1] != NULL)
                    res++;
                return res;
            }
        }
    return 0;
};
void Ways(char var, char** mas){
    int x, y;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j){
            if(mas[i][j] == var){
                x = i;
                y = j;
            }
        }
    if(mas[x-1][y] == '#' && mas[x-1] != NULL)
        c.push_back('u');
    if(mas[x+1][y] == '#' && mas[x+1] != NULL)
        c.push_back('d');
    if(mas[x][y-1] == '#' && (mas+x)[y-1] != NULL)
        c.push_back('l');
    if(mas[x][y+1] == '#' && (mas+x)[y+1] != NULL)
        c.push_back('r');
};

char randomRoom(std::vector<int>* arr){ 
    int randInd = std::experimental::randint(0, (int)arr->size()-1); 
    char res = (*(arr->begin()+randInd));   
    arr->erase(arr->begin()+randInd);
    return res;                 
};

void FindAllRooms(char var, char** mas){ // Здесь создаются комнаты идущие от нашей c различными номерами
    int neigh = HowManyFreeWays(var, mas)-1; // Число комнат идущих от нашей
    int x = 0;
    int y = 0;
    if(!neigh){
        std::cout << "No such a place";
        return; // Нет места 
    }
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j){
            if( mas[i][j] == var){
                x = i;
                y = j;
            }
        }
    Ways(var, mas);
    //std::cout << c.size();
    while(neigh){
        int randIndex = std::experimental::randint(0, (int)c.size()-1);
        if(*(c.begin() + randIndex) == 'u'){
            mas[x-1][y] = randomRoom(ptr);
            neigh--;
            continue;
        }
        if(*(c.begin() + randIndex) == 'd'){
            mas[x+1][y] = randomRoom(ptr);
            neigh--;
            continue;
        }
        if(*(c.begin() + randIndex) == 'r'){
            mas[x][y+1] = randomRoom(ptr);
            neigh--;
            continue;
        }
        if(*(c.begin() + randIndex) == 'l'){
            mas[x][y-1] = randomRoom(ptr);
            neigh--;
            continue;
        }        
    }
    c.clear();
};

int main(){
    char** mas = new char* [9];

    for(int i = 0; i < 9; ++i){
        mas[i] = new char [9];
        for(int j = 0; j < 9; ++j)
            mas[i][j] = '#';
    };
    
    mas[4][4] = 0;
    FindAllRooms(mas[4][4], mas);
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j)
            std::cout << mas[i][j];
        std::cout << '\n';
    };
    
    /*for(int i = 0; i < 9; i++ ){
        randomDEL(ptr);
        for(auto it = ids.begin(); it < ids.end(); ++it)
            std::cout << (*it);
        std::cout << '\n';
    }*/
    //std::cout << HowManyFreeWays(mas[4][4], mas);
    return 0;
}