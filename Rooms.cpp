#include <iostream>
#include <memory>
#include <experimental/random>
#include <vector>
std::vector<char> rooms({'1','2','3','4','5','6','7','8','9'});
int counter = 0;
void FindWays(char** mas, int x, int y, std::vector<int>* res){
    if(mas[x-1][y] == '#' && mas[x-1] != NULL)
        (*res->begin()) = 1; 
    if(mas[x+1][y] == '#' && mas[x+1] != NULL)
        (*(res->begin() + 1)) = 1; 
    if(mas[x][y-1] == '#' && mas[y-1] != NULL)
        (*(res->begin() + 2)) = 1; 
    if(mas[x][y+1] == '#' && mas[y+1] != NULL)
        (*(res->begin() + 3)) = 1; 
};
// [1, 1, 0, 1] u d NO r 
void ChooseRandWays(std::vector<int>* arr){ // arr = {0, 1, 0, 1}
    std::vector<int> Ione;
    for(int i = 0; i<4; i++){
        if((*arr)[i] == 1) 
            Ione.push_back(i);
    }
    if(Ione.size() == 0){/*std::cout << "No such ways"; */return;}

    int randInd = std::experimental::randint(0, (int)Ione.size()-1);
    Ione.erase(randInd + Ione.begin());

    //for(int i = 0; i<4; i++)  std::cout <<(*arr)[i] << '-';

    for(int i = 0; i<4; i++) (*arr)[i] = 0;
    for(int i = 0; i<Ione.size(); i++) (*arr)[Ione[i]] = 1;  
    //for(int i = 0; i<4; i++)  std::cout <<(*arr)[i] << '-';
}
void PlaceRooms(char** mas, int x, int y){ // x - строчка, y - столбец
    std::vector<int> ways{0, 0, 0, 0};
    FindWays(mas, x, y, &ways);
    ChooseRandWays(&ways); // Отсекаем один путь на рандом
    if(counter >= 9) return; 
    if(ways[0] == 1) {mas[x-1][y] = '@'; counter++;}
    if(ways[1] == 1) {mas[x+1][y] = '@'; counter++;}
    if(ways[2] == 1) {mas[x][y-1] = '@'; counter++;}
    if(ways[3] == 1) {mas[x][y+1] = '@'; counter++;}
    
    if(ways[0] == 1) PlaceRooms(mas, x-1, y);
    if(ways[1] == 1) PlaceRooms(mas, x+1, y);
    if(ways[2] == 1) PlaceRooms(mas, x, y-1);
    if(ways[3] == 1) PlaceRooms(mas, x, y+1);
};
void makeNumOfRooms(char** mas){
    for(int i = 0; i < 11; ++i)
        for(int j = 0; j < 11; ++j){
            if(mas[i][j] == '@'){
                if(rooms.size() == 0){ mas[i][j] = '#'; continue;}
                int Iroom = std::experimental::randint(0, static_cast<int>(rooms.size())-1);
                //std::cout << Iroom;
                mas[i][j] = rooms[Iroom]; 
                rooms.erase(rooms.begin() + Iroom); 
            }
        }    
}
int main(){
    int x0 = 5;
    int y0 = 5;
    char** mas = new char* [11];

    for(int i = 0; i < 11; ++i){
        mas[i] = new char [11];
        for(int j = 0; j < 11; ++j)
            mas[i][j] = '#';
    };
    
    mas[5][5] = '0';

    
    PlaceRooms(mas, x0, y0);
    makeNumOfRooms(mas);
    // std::cout << counter;
    for(int i = 0; i < 11; ++i){
        for(int j = 0; j < 11; ++j)
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