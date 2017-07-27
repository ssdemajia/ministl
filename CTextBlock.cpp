#include <iostream>
//effective c++ 条款3 尽可能使用const
class CTextBlock
{
public:
    CTextBlock(char * text):pText(text){}
    std::size_t length() const;
    const char & operator[](std::size_t position) const;
    char & operator[](std::size_t position);
    friend std::ostream & operator<<(std::ostream &output, const CTextBlock & item);
private:
    char* pText;
    mutable std::size_t textLength;//添加mutable后可以对const成员变量改变
    mutable bool lengthIsValid;
};
std::ostream & operator<<(std::ostream &output, const CTextBlock & item)
{
    output<<item.pText<<std::endl;
    return output;
}

const char & CTextBlock::operator[](std::size_t position) const
{
    return pText[position];
}
char & CTextBlock::operator[](std::size_t position)
{
    return const_cast<char &>((*static_cast<const CTextBlock *>(this))[position]);
}
std::size_t CTextBlock::length() const
{
    if (!lengthIsValid) {
        textLength = std::strlen(pText);
        lengthIsValid = true;
    }
    return textLength;
}

int main(int argc, char const *argv[]) {
    char c[] = "hello";
    CTextBlock cctb(c);
    char *pc = &cctb[0];
    *pc = 'j';
    std::cout << cctb << std::endl;
    return 0;
}
