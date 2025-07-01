#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "BlockChain.h"

class UserInterface{
    public:
        // Default Constructor: runs UserInterface
        UserInterface();
        // Default Deconstructor: deallocates memory used by UserInterface
        ~UserInterface();
    private:
        // userInput: user's command key from user input
        int userInput;
        // blockData: string of block data from user input
        string blockData;
        // fileName: input/output file name from user input
        string fileName;
        // displayOptions Function: display's user's options of UserInterface
        void displayOptions();
        // validBlockChain Function: whether BlockChain's hashes are valid
        bool validBlockChain;
        // blockChain Object: initialized BlockChain
        BlockChain<string>* blockChain = new BlockChain<string>();
};
#endif
