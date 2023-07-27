#include "DataGenerator.h" 
#include "AlgoTiming.h"
#include "count_comparision_Algo.h"
#include "AlgoTesting.h" 
#include "cmd.h"


void Experiments()
{
    TestingAll();
}

int main(int argc, char* argv[])
{
    //Experiments();
    if (argc == 5) {
        if (strcmp(argv[1], "-a") == 0) 
        { 
            ifstream fin(argv[3]);
            if (!fin)
            {
                command3(argv[2], argv[3], argv[4]);
            }
            else{
                fin.close();
                command1(argv[2], argv[3], argv[4]);
            }
        }
        else{
            command4(argv[2], argv[3], argv[4]);
        }
    }
    else{
        if (argc == 6) 
        {
            if (strcmp(argv[1], "-a") == 0)
            {
                command2(argv[2], argv[3], argv[4], argv[5]);
            }
            else{
                command5(argv[2], argv[3], argv[4], argv[5]);
            }
        }
    }
}
