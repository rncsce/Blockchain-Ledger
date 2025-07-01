#ifndef BLOCK_H
#define BLOCK_H
#include <ctime>
#include <string>

using namespace std;
template <typename T>
class Block{
    public:
        // Overloaded Constructor: initializes Block object
        Block(T data);
        // Default Deconstructor: deallocates memory used by Block object
        virtual ~Block();
        // setIndex Setter: sets Block's index
        void setIndex(int index);
        // getIndex Getter: returns Block's index
        int getIndex();
        // setTimeStamp Setter: sets Block's timestamp
        void setTimeStamp(string timeStamp);
        // getTimeStamp Getter: gets Block's timestamp
        string getTimeStamp();
        // setData Setter: sets Block's data
        void setData(T data);
        // getData Getter: gets Block's data
        T getData();
        // setCurrHash: set current Block's hash
        void setCurrHash(string currHash);
        // getCurrHash Getter: gets current Block's hash
        string getCurrHash();
        // setPrevHash Setter: set current Block's, previous block's hash
        void setPrevHash(string prevHash);
        // getPrevHash Getter: get current Block's, previous block's hash
        string getPrevHash();
        // setNextBlock Setter: set next Block
        void setNextBlock(Block<T>* nextBlock);
        // getNextBlock Getter: get next Block
        Block<T>* getNextBlock();
    private:
        // m_index: Block's index in Block chain
        int m_index;
        // m_timeString: Block's current time stamp as a string
        string m_timeString;
        // m_data: Block's data, templated type
        T m_data;
        // m_currHash: Block's current hash
        string m_currHash; 
        // m_prevHash: Block's previous hash
        string m_prevHash; 
        // m_next: recursive call of next Block object
        Block<T>* m_next;
};
#include "Block.h"
// Overloaded Constructor: initializes Block's member variables
template <typename T> Block<T>::Block(T data){
    m_index = 0; // Initialize Block's index as 0
    m_data = data; // Set data of Block
    m_currHash = "0"; // Initialize Block's hash as 0
    m_prevHash = "0"; // Initialize Block's previous Block's hash as 0
    m_next = NULL; // Initialize Block's next Block as NULL
    m_timeString = ""; // Initialize Block's time stamp string
    time_t m_timeStamp = time(0); // Initialize time stamp 
    string temp = ctime(&m_timeStamp); // Convert time stamp to string as temp variable
    for (int i = 0; i < temp.size() - 1; i++){ // Iterate for one less than size of temp string
        m_timeString += temp[i]; // Concatenate each character from temporary string to m_timeString to create timestamp string without newline
    }
}
// Default Deconstructor
template <typename T> Block<T>::~Block(){
}
// setIndex Setter
template <typename T> void Block<T>::setIndex(int index){
    m_index = index; // Set parameter as Block's index
}
// getIndex Getter
template <typename T> int Block<T>::getIndex(){
    return m_index; // Return Block's index
}
// setTimeStamp Setter
template <typename T> void Block<T>::setTimeStamp(string timeStamp){
    m_timeString = timeStamp; // Set parameter as Block's time stamp
}
// getTimeStamp Getter
template <typename T> string Block<T>::getTimeStamp(){
    return m_timeString; // Return date and time 
}
// setData Setter
template <typename T> void Block<T>::setData(T data){
    m_data = data; // Set parameter as Block's data
}
// getData Getter
template <typename T> T Block<T>::getData(){
    return m_data; // Return Block's data
}
// setCurrHashSetter
template <typename T> void Block<T>::setCurrHash(string currHash){
    m_currHash = currHash; // Set parameter as Block's current hash
}
// getCurrHash Getter
template <typename T> string Block<T>::getCurrHash(){
    return m_currHash; // Return current Block's hash
}
// setPrevHash Setter
template <typename T> void Block<T>::setPrevHash(string prevHash){
    m_prevHash = prevHash; // Set parameter as Block's previous hash
}
// getPrevHash Getter:
template <typename T> string Block<T>::getPrevHash(){
    return m_prevHash; // Return current Block's, previous Block's hash
}
// setNextBlock Setter
template <typename T> void Block<T>::setNextBlock(Block<T>* nextBlock){
    m_next = nextBlock; // Set parameter as Block's next Block
}
// getNextBlock Getter
template <typename T> Block<T>* Block<T>::getNextBlock(){
    return m_next; // Return current Block's, next Block
}
#endif
