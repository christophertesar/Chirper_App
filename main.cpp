#include "chirper.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

int main(){

Chirp chirp;

chirp.setup_account();

chirp.menu();

cout << "See you next time!" << endl;

return 0;
}
