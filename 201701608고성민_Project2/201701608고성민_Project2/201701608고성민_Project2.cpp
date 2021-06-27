#include "Hotel.h"
#include "Royal.h"
#include "Standard.h"
#include "Suite.h"

int main()
{
    ifstream setting("setting.txt");
    Hotel h(setting);
    setting.close();

    ifstream fin("input.txt");
    h.open(fin);
    fin.close();

    return 0;
}
