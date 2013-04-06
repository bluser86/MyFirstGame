#include <fstream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

class Config
{
private:
    Config(){};
    Config(const Config&);
    Config& operator=(const Config&);
    map<string,string> store;
public:
    static Config& Instance()
    {
        static Config instance;
        return instance;
    }
    void Parse(ifstream& is);
    template<typename _T> _T Get(string key);
    void GetResolution(int &cX, int &cY);
};