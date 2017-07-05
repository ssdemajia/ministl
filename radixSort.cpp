#include "algorithm.h"



typedef struct alpha{//用于24个字母的数组
    char c;
    std::vector<std::string> vec;
}Alpha;
class RadixSort
{
private:
  Alpha letter[24];
public:
    RadixSort()
    {
        for (size_t i = 1; i <= 24; i++) {
            letter[i].c = 'a'+i;
        }
    }
    ~RadixSort()
    {

    }
    void sort(std::vector<std::string> v)
    {

    }
};
int main(int argc, char const *argv[]) {

    return 0;
}
