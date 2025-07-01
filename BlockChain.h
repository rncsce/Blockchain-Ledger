#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "Block.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

template <typename T>
class BlockChain{
    public:
        // Default Deconstructor: initializes Block Chain of Block objcets
        BlockChain();
        // Default Deconstructor: deallocated memory used by Block Chain object
        ~BlockChain();
        // addBlock Function: creates and adds Block to Block Chain
        void addBlock(string data);
        // addBlock Function: add fully initialized block to Block Chain
        void addBlock(Block<T>* newBlock);
        // validateBlockChain Function: validates Block Chain's hashes
        bool validateBlockChain();
        // saveBlockChain Function: saves Block Chain to file
        void saveBlockChain(string fileName);
        // loadBlockChain Function: loads in Block Chain from file
        void loadBlockChain(string fileName);
        // displayBlockChain: displays Block Chain to terminal
        void displayBlockChain();
    private:
        // m_size: number of Blocks in Block Chain
        int m_size;
        // createHash Function: creates hash based on Block's data
        string createHash(Block<T>* newBlock);
        // intToHexStream: converts integer to hex
        string intToHexStream(int num);
        // genesisBlock Block Object Pointer: first block pointer in Block Chain
        Block<T>* genesisBlock;
        // m_back Block Object Pointer: last Block pointer in Block Chain
        Block<T>* m_back;
};
#include "BlockChain.h"
// Default Deconstructor
template<typename T> BlockChain<T>::BlockChain(){
    genesisBlock = NULL; // Initialize genesisBlock pointer
    m_size = 0; // Initialize BlockChain's size
    m_back = NULL; // Initialize BlockChain's last Block pointer
}
// Default Deconstructor
template<typename T> BlockChain<T>::~BlockChain(){
    Block<T>* currBlock = genesisBlock; // Initialize and set the current Block to BlockChain's genesisBlock
    for(int i = 0; i < m_size; i++){ // Iterate number of BlockChain's Blocks times
        Block<T>* nextBlock = currBlock -> getNextBlock(); // Initialize Block, nextBlock as currBlock's next Block 
        delete currBlock; // Delete the current Block
        currBlock = nextBlock; // Set the current Block to the next Block
    }
}
// addBlock Function (string)
template<typename T> void BlockChain<T>::addBlock(string data){ // Parameter: string
    // If adding first Block in BlockChain
    if (genesisBlock == NULL){ // If BlockChain's genesisBlock is NULL
        genesisBlock = new Block<T>("Genesis Block"); // Initialize genesisBlock
        genesisBlock -> setCurrHash(createHash(genesisBlock)); // Create and set genesisBlock's current hash
        m_back = genesisBlock; // Set BlockChain's back to genesisBlock
        ++m_size; // Increment BlockChain's size by one
    }
    Block<T>* newBlock = new Block<T>(data); // Create new block with provided data
    newBlock -> setIndex(m_size);  // Set the new Block's index to current size of BlockChain
    m_back -> setNextBlock(newBlock); // Set BlockChain's last Block's next Block to the new Block
    newBlock -> setPrevHash(m_back -> getCurrHash()); // Set newBlock's previous hash to BlockChain's last Block's current hash
    newBlock -> setCurrHash(createHash(newBlock)); // Create and set newBlock's current hash 
    m_back = newBlock; // Set BlockChain's back to the new Block
    ++m_size; // Increment BlockChain's size by one
    // Block information output statements 
    cout << "New Block Added! " << endl;
    cout << "--------------------" << endl;
    cout << "Block Information:" << endl;
    cout << "Index: " << newBlock -> getIndex() << endl;
    cout << "Time Stamp: " << newBlock -> getTimeStamp() << endl;
    cout << "Data: " << newBlock -> getData() << endl;
    cout << "Previous Hash: " << newBlock -> getPrevHash() << endl;
    cout << "Current Hash: " << newBlock -> getCurrHash() << endl;
    cout << "--------------------" << endl;
}
// addBlock Function (Block)
template<typename T> void BlockChain<T>::addBlock(Block<T>* newBlock){ // Parameter: Block Object
    newBlock -> setIndex(m_size); // Set newBlock's index to current size of BlockChain
    if (genesisBlock == NULL){ // If genesisBlock is NULL
        genesisBlock = newBlock; // Set newBlock as BlockChain's genesisBlock
    } else { // If genesisBlock is not NULL
        m_back -> setNextBlock(newBlock); // Set BlockChain's last Block's next Block to the new Block
        newBlock -> setPrevHash(m_back -> getCurrHash()); // Set the new Block's previous hash to the Block Chain's last Block's current hash
    }
    m_back = newBlock; // Set the BlockChain's last Block's pointer to the new Block
    ++m_size; // Increment size by 1
}
// createHash Function
template<typename T> string BlockChain<T>::createHash(Block<T>* block){ // Parameter: Block Object
    string content = to_string(block -> getIndex()) + block -> getTimeStamp() + block -> getData() + block -> getPrevHash(); // Initialize string of Block's index, time stamp, data, and previous hash
    int ASCIIVal = 0; // Initialize int, ASCIIVal // ASCII sum
    for(int i = 0; i < content.size(); i++){ // Iterate for number of characters in content string
        ASCIIVal += int(content[i]); // Add ASCII value of string's character to the total ASCII value
    }
    return intToHexStream(ASCIIVal); // Convert the summed ASCII value to Hex
}
// intToHexStream Function
template<typename T> string BlockChain<T>::intToHexStream(int num) {
    stringstream ss; // Initialize string stream
    ss << hex << num; // Convert number to hex value
    return ss.str(); // Return the hex value as a string
}
// validataeBlockChain Function
template<typename T> bool BlockChain<T>::validateBlockChain(){
    if (genesisBlock == NULL){
        cout << "Block chain is empty." << endl;
        return true;
    }
    Block<T>* currBlock = genesisBlock; // Set the current Block to the BlockChain's genesis Block
    Block<T>* nextBlock = currBlock -> getNextBlock(); // Set the next Block to the current Block's next Block
    for(int i = 0; i < m_size - 1; i++){ // Iterate for one less than the number Blocks in BlockChain (# comparisons = one less than number of blocks)
        if(currBlock -> getCurrHash() != nextBlock -> getPrevHash()){ // If the current Block is not equal to the current Block's previos hash
            return false; // Return false
        }
        if(createHash(currBlock) != currBlock -> getCurrHash()){ // If the created hash of the current Block is not the same as the current Block's current hash
            return false; // Return false
        } 
        currBlock = nextBlock; // Set the current Block's pointer to the next Block
        nextBlock = currBlock -> getNextBlock(); // Set the next Block's pointer the current Block's next Block         
    }
    return true; // Return true // All Block's in BlockChain current and previous hashes matched
}
// saveBlockChain Function
template<typename T> void BlockChain<T>::saveBlockChain(string fileName){ // Parameter: file name string
    ofstream outFile(fileName); // Intitialize output file stream
    if(outFile.is_open()){ // If output file is open
        Block<T>* currBlock = genesisBlock; // Set current Block to genesis Block
        for(int i = 0; i < m_size; i++){ // Iterate for number of Blocks in BlockChain
            outFile << currBlock -> getIndex() << '|' << currBlock -> getTimeStamp() << '|' << currBlock -> getData() << '|' << currBlock -> getPrevHash() << '|' << currBlock -> getCurrHash() << endl; // Write current Block's index, time stamp, data, previous hash, current hash, delimited by | to output file
            currBlock = currBlock -> getNextBlock(); // Set current Block to current Block's next Block
        }
    }
    outFile.close(); // Close output file
}
// loadBlockChain Function
template<typename T> void BlockChain<T>::loadBlockChain(string fileName){ // Parameter: file name string
    ifstream inFile(fileName); // If input file is open
    string line; // Declare string for line
    string data; // Declare string for data
    if(inFile.is_open()){ // If input file is open
        while(getline(inFile, line)){ // While getline access line separated by newline from file
            Block<T>* newBlock = new Block<T>(" "); // Create new Block with NULL data
            stringstream ss(line); // Open string stream for line
            getline(ss, data, '|'); // Read string delimited by |
            newBlock -> setIndex(stoi(data)); // Set string accessed to the new Block's index // String converted to int
            getline(ss, data, '|'); 
            newBlock -> setTimeStamp(data); // Set string accessed to the new Block's time stamp 
            getline(ss, data, '|');
            newBlock -> setData(data); // Set string accessed to the new Block's data
            getline(ss, data, '|');
            newBlock -> setPrevHash(data); // Set string accessed to the new Block's previous hash
            getline(ss, data, '|');
            newBlock -> setCurrHash(data); // Set string accessed to the new Block's current hash
            addBlock(newBlock); // Add the new Block to the BlockChain
        }
    } 
    inFile.close(); // Close input file
}
// displayBlockChain Function
template<typename T> void BlockChain<T>::displayBlockChain(){
    Block<T>* currBlock = genesisBlock; // Set current Block to the BlockChain's genesisBlock
    for(int i = 0; i < m_size; i++){ // Iterate for number of Blocks in BlockChain
        cout << currBlock -> getIndex() << "|" << currBlock -> getTimeStamp() << "|" << currBlock -> getData() << "|" << currBlock -> getPrevHash() << "|" << currBlock -> getCurrHash() << endl; // Output current Block's index, time stamp, data, previous hash, current hash, delimited by | to terminal
        currBlock = currBlock -> getNextBlock(); // Reset current Block to the current Block's next Block
    }
}
#endif
