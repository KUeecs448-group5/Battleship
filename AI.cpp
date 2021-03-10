#include "AI.h"

AI::AI(int difficulty){
    while(difficulty < 1 || difficulty > 3)
    {
        std::cerr << "ERROR: Invalid difficulty input. Please enter a valid on the bound [1,3]: ";
        std::cin >> difficulty;
    }
    m_difficulty = difficulty;
    shotGrid = new char*[10];
    shipGrid = new char*[10];
    for(int i = 0; i < 10; i++){
        shotGrid[i] = new char[10];
        shipGrid[i] = new char[10];
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; i++){
            shotGrid[i][j] = '0';
            shipGrid[i][j] = '0';
        }
    }
}

AI::~AI(){
}

void AI::takeShot(char** oppGrid){
    int xCoord = '/0';
    int yCoord = '/0';
    if(m_difficulty == 1){
        srand((unsigned) time(0));
        xCoord = rand() % 10;
        srand((unsigned) time(0));
        yCoord = rand() % 10;
        oppGrid[yCoord][xCoord] = 'X';   
    }
    else if(m_difficulty == 2){
        srand((unsigned) time(0));
        xCoord = rand() % 10;
        srand((unsigned) time(0));
        yCoord = rand() % 10;
        //recursive shot
    }
    else if(m_difficulty == 3){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(oppGrid[i][j] == 'S'){
                    oppGrid[i][j] = 'X';
                    //may need Ship object functions to display when AI has sunk a ship or to check win condition.
                    return;
                }
            }
        }
    }
    else{
        std::cerr << "ERROR: Invalid difficulty level.\n";
    }
}

void AI::placeShips(int length){
	int shipStarterCol;
	int shipStarterRow = 0;
	int shipLength = length;
	std::string shipLocation;
	std::string shipPlacement;

	//std::cout << "\nWhat orientation would you like the ship to be placed in?\n";
    srand((unsigned) time(0));
    if (rand() % 2 == 0){
        shipPlacement = "V";
    }
    else{
        shipPlacement = "H";
    }
    do{
            srand((unsigned) time(0));
            shipStarterCol = rand() % (11-length);
            srand((unsigned) time(0));
            shipStarterRow = rand() % (11-length);

        if(shipPlacement == "V"){
            for(int i = 0; i < length; i++){
                shipGrid[shipStarterRow + i][shipStarterCol] = 'S';
            }
        }
        else{
            for(int i = 0; i < length; i++){
                shipGrid[shipStarterRow][shipStarterCol + i] = 'S';
            }
        }
    }while(validatePosition(shipStarterRow, shipStarterCol, shipPlacement, shipLength) == false);
}

bool AI::validatePosition(int row, int col, std::string direction, int shipLength)
{
	bool isValid = false;
	int colnum = col;
	if(direction=="H" || direction == "h")
	{
		for(int i=0;i<shipLength;i++)
		{
			if((colnum)<=10 && shipGrid[row-1][colnum-1]=='0'){
				isValid = true;
			}
			else if(shipGrid[row-1][colnum-1]=='S')
			{
				return(false);
			}
			else
			{
				isValid = false;
			}
			colnum++;
		}
	}
	if(direction=="V" || direction == "v"){
		for(int j=0;j<shipLength;j++){
			if(row <= 10 && shipGrid[row-1][colnum-1]=='0' ){
				isValid = true;
			}
			else if(row>10)
			{
				return(false);
			}
			else if(shipGrid[row-1][colnum-1]=='S')
	 		{
			    return(false);
	 		}
			else
			{
				isValid = false;
			}
			row++;
		}
	}
	return(isValid);
}