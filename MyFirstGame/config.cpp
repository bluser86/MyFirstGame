#include "config.h"

void Config::Parse(ifstream& is)
{
    for(;;) 
    {
        // Define locals
        string key;
        string value;

        // Read line
        getline(is, key, '=');
        getline(is, value);

        if(!is) break;

        if(key.empty() || value.empty()) break;

        this->store[key] = value;
    }
}

template<typename _T> _T Config::Get(string key) 
{
    return (_T) this->store[key];
}

void Config::GetResolution(int &x, int &y)
{
    stringstream ss(this->Get<string>("gfxResolution"));
    string sX, sY;

    getline(ss, sX, 'x');
    getline(ss, sY);

    x = atoi(sX.c_str());
    y = atoi(sY.c_str());
}