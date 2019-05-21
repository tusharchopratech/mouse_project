#ifndef MDaq_H
#define MDaq_H
using namespace std;
class MDaq
{
private:
    /* data */
public:
    MDaq();
    ~MDaq(){
        std::cout << "MDaq 1 Destructor." << std::endl;
    }
    void functionOne();
};

#endif