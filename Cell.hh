#include <iostream>
using namespace std;

class Cell{

private:
    char cell_value;
    int frames;

public:
    
    #pragma region  Operators

    bool operator==(const char cell_value) const { 
        return this->cell_value == cell_value; 
    }

    #pragma endregion

    #pragma region Constructors

    Cell(const char cell_value){
        this->cell_value = cell_value;
    }

    #pragma endregion

    #pragma region Consultors

    char value() const { 
        return cell_value; 
    }

    #pragma endregion

};
