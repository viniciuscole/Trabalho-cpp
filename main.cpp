#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main(){
    locale Brloc("pt_BR.UTF-8");
    cin.imbue(Brloc);
    
    

    return 0;
}