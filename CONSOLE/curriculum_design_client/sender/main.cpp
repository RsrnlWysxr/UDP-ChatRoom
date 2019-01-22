#include <iostream>
#include "Client.h"
using namespace std;

int main()
{
    client x;
    x.Startup();
    x.SetServerAddress();
    x.work();
}