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
std::map<int, std::string> nexus;       //{1, 1#27}                      // пара номер номер комнаты - ее соседи

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
                int c = vm[i][j] - 48;
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
                    nexus[vm[i][j]-48].push_back(vm[i][j-1]);
                else
                    nexus[vm[i][j]-48].push_back('#');

                if(vm[i-1][j] != '#')                                               // up
                    nexus[vm[i][j]-48].push_back(vm[i-1][j]);
                else
                    nexus[vm[i][j]-48].push_back('#');

                if(vm[i][j+1] != '#')                                               // right
                    nexus[vm[i][j]-48].push_back(vm[i][j+1]);
                else
                    nexus[vm[i][j]-48].push_back('#');  
                
                if(vm[i+1][j] != '#')                                               // down
                    nexus[vm[i][j]-48].push_back(vm[i+1][j]);
                else
                    nexus[vm[i][j]-48].push_back('#');  
            }
        }
    }
    //std::cout << nexus[1] << '\n';
};
Room* FindRm(int id){
    Room* pr;
    for(auto& x : rooms){
        int s = x->getRoomId();
        if(s == id){
            pr = x;
        }
    }
    return pr;
};

Object& FindDr(Room* r, char dr){
    int ind;
    std::cout << dr << '\n';
    if(decode[dr] > 1) ind = decode[dr] - 2;
    else ind = decode[dr]+2;
    for(auto& o : r->getObj()){
        if(o->getName()[0] == code[ind]){
            //std::cout << ind << '\n';
            return (*o);
        }
    }
    throw 1;
};

void Room::Teleport(Player& p){
    if(p.Teletime.getElapsedTime().asSeconds() < 1){
        return;
    }
    sf::FloatRect prect = sf::FloatRect(p.coord.x + 8, p.coord.y+16, 16.0f, 16.0f);
    int id = p.roomId;

    for(auto obj : this->getObj()){
        if(obj->getName()[0] != 's'){
            
            int ind = decode[obj->getName()[0]];
            if(obj->CheckCollision(prect) && nexus[id][ind] != '#'){
                
                char dest = nexus[id][ind];
                //std::cout << "====" <<dest;
                Room* rm = FindRm(dest-48);
                Object d = FindDr(rm, obj->getName()[0]);
                p.coord = {d.getX(), d.getY()};
                p.roomId = dest-48; 
                p.Teletime.restart();  
                return;
            }
        }        
    }
};



