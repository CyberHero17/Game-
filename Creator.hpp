#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <experimental/random>
#include "map.cpp"
typedef std::vector<std::vector<char>> Vec2D;
int X0 = 5;
int Y0 = 5;

std::vector<Room*> rooms;                                      // Вектор с 10 комнатами, которые будут на карте
std::map<char, std::string> nexus;       //{1, 1#27}                      // пара номер номер комнаты - ее соседи

std::map<char, int> decode = {{'l', 0}, {'u', 1}, {'r', 2}, {'d', 3}};
std::map<int, char> code = {{0, 'l'}, {1, 'u'}, {2, 'r'}, {3, 'd' }};

int counter = 0;
Vec2D vm(11, std::vector<char>(11));                           // Может сгодиться для мини-карты 

void Fill(Vec2D& vm){
    for(auto& x : vm)
        for(auto& y : x){
            y = '#';
        }
    vm[5][5] = '0';
};
void Show(){
    for(auto& x : vm){
        for(auto& y : x){
            std::cout << y;
        }
        std::cout << '\n';
    }
};

void FindWays(Vec2D& vm, int x, int y, std::vector<int>& res){
    if(vm[x-1][y] == '#')
        (*(res.begin())) = 1; 
    if(vm[x+1][y] == '#')
        (*(res.begin() + 1)) = 1; 
    if(vm[x][y-1] == '#')
        (*(res.begin() + 2)) = 1; 
    if(vm[x][y+1] == '#')
        (*(res.begin() + 3)) = 1; 
};
void ChooseRandWays(std::vector<int>& arr){ // arr = {0, 1, 0, 1}
    std::vector<int> Ione;
    for(int i = 0; i<4; i++){
        if(arr[i] == 1) 
            Ione.push_back(i);
    }
    if(Ione.size() == 0){/*std::cout << "No such ways"; */return;}

    int randInd = std::experimental::randint(0, (int)Ione.size()-1);
    Ione.erase(randInd + Ione.begin());

    for(int i = 0; i<4; i++) arr[i] = 0;
    for(int i = 0; i<Ione.size(); i++) arr[Ione[i]] = 1;  
    
};
void PlaceRooms(Vec2D& mas, int x, int y){ // x - строчка, y - столбец
    std::vector<int> ways{0, 0, 0, 0};
    FindWays(mas, x, y, ways);
    ChooseRandWays(ways); // Отсекаем один путь на рандом
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
void makeNumOfRooms(Vec2D& mas){
    std::vector<char> rooms({'1','2','3','4','5','6','7','8','9'});
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
    Show();   
}
bool Place(Vec2D& vm){
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; ++j){
            if(vm[i][j] != '#'){
                std::string c;
                c.push_back(vm[i][j]);
                Room* r = new Room(c);
                r->CreateRoom(r, 720*j, 720*i);
                rooms.push_back(r);
            }
        }        
    }
    std::cout << "rooms ---> success" << rooms.size();
    return true;
};
void ConnectRm(Vec2D& vm){
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; ++j){
            if(vm[i][j] != '#'){
                if(vm[i][j-1] != '#')                                               // left
                    nexus[vm[i][j]].push_back(vm[i][j-1]);
                else
                    nexus[vm[i][j]].push_back('#');

                if(vm[i-1][j] != '#')                                               // up
                    nexus[vm[i][j]].push_back(vm[i-1][j]);
                else
                    nexus[vm[i][j]].push_back('#');

                if(vm[i][j+1] != '#')                                               // right
                    nexus[vm[i][j]].push_back(vm[i][j+1]);
                else
                    nexus[vm[i][j]].push_back('#');  
                
                if(vm[i+1][j] != '#')                                               // down
                    nexus[vm[i][j]].push_back(vm[i+1][j]);
                else
                    nexus[vm[i][j]].push_back('#');  
            }
        }
    }
    //std::cout << nexus['0'] << '\n';
};
Room* FindRm(std::string id){
    Room* pr;
    for(auto& x : rooms){
        std::string s;
        s.push_back(x->getRoomId());
        if(s == id){
            pr = x;
        }
    }
    return pr;
};

Object& FindDr(Room* r, char dr){
    int ind = 0;
    decode[dr] > 1 ? ind = decode[dr] - 2 : ind = decode[dr];
    for(auto o : r->getObj()){
        if(o->getName()[0] == code[ind])
            return (*o);
    }
    throw 1;
};

void Room::Teleport(Player& p){
    sf::FloatRect prect = sf::FloatRect(p.coord.x, p.coord.y, 24.0f, 48.0f);
    std::string id = p.roomId;
    char idc = id[0];
    for(auto obj : this->getObj()){
        if(obj->getName()[0] != 's'){
            
            int ind = decode[obj->getName()[0]];
            
            if(obj->CheckCollision(prect) && nexus[idc][ind] != '#'){
                // std::cout << obj->getName()[0];
                char dest = nexus[idc][ind];
                std::string dests; 
                dests.push_back(dest);
                Room* rm = FindRm(dests);
                Object d = FindDr(rm, dest);
                p.coord = {d.getX(), d.getY()};
                p.roomId = dests;   
                return;
            }
        }        
    }
    //std::cout << '\n';
};
