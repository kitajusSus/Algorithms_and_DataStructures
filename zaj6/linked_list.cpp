#include <iostream>


using namespace std;
// samoreferecnyjna lista 
class Link{
  public :
    int data;
    double dData;
    Link* pNext;
};
// to jest to samo ale inaczej,  inventory item to jest wskaźnik do obiektu przechowującego dane
/*
class Link{
  public; 
    inventoryItem* pIteam;
    Link* pNext;
};
*/
