#include <iostream>
#include <queue>
#include <functional>

#include "gtest/gtest.h"

using namespace std;

/// 10 TESTS
///
/// Stack class specs
/// Name of the class:  Stack
///
/// Public methods:
/// void push(int value)   adds value to the top of the stack
/// int pop()  removes and returns top value of the stack
/// int peek()  returns top value of the stack without removing it
/// bool isEmpty()  returns true if the stack is empty, false otherwise
/// int size() returns the number of items on the stack
///
/// push, isEmpty, and size should work in all cases
/// pop and peek will only be called on non-empty stacks
///
/// freeing momory after new allocation
///

class Stack {
private:
    int numElements;
    int maxNumElements;
    int *elements;
    void resize();
public:
    Stack();
   ~Stack();
    void push(int value); //  adds value to the top of the stack
    int pop();            //  removes and returns top value of the stack
    int peek();           //  returns top value of the stack without removing it
    bool isEmpty();       //  returns true if the stack is empty, false otherwise
    int size();           //  returns the number of items on the stack
};

Stack::Stack() {
    numElements = 0; // size of the stack
    maxNumElements = 20; // size of the array pointed to (not equal to
    elements = new int[maxNumElements];
}

Stack::~Stack() {
    delete [] elements;
}

void Stack::resize() {
    int newSize = maxNumElements *= 2; // doubling maxNumElemnts to increase the size of the
                         // new array that the stack's elements will be moved to
    int *newArray = new int[newSize]; // making the new array to copy to

    for(int i = 0; i < numElements; i++){
        newArray[i] = elements[i];
    }
    delete [] elements;
    elements = newArray;
    maxNumElements = newSize;
}

void Stack::push(int value){
    // resize the array if it's all full
    if(numElements == maxNumElements){
        resize();
    }
    elements[numElements] = value;
    numElements += 1;
}

int Stack::pop(){
    int popVal = elements[numElements - 1]; // getting the last element in the stack
    numElements -= 1; // telling the stack to ignore this element by decrementing numElements
    return popVal;
}

int Stack::peek(){
     return elements[numElements - 1]; // getting the last element in the stack
}

bool Stack::isEmpty(){
     return (numElements == 0); // check for equality of numElements with zero
}

int Stack::size(){
    return numElements; // returning the size as stored in numElements
}

TEST(TestStack, EmptyStackIsEmpty) { // check if a newly declared stack is empty
    Stack s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(TestStack, PushAndCheckSize) { // push a number of 1's onto the stack then check that the size matches
    Stack s;
    int garbageVal = 1;
    int numPushes = 56;
    for(int i = 0; i < numPushes; i++){
        s.push(garbageVal);
    }

    ASSERT_EQ(s.size(), numPushes);
}

TEST(TestStack, PushAndPopAndGetSize) { // push a number of 1's, pop a number of 1's, then check that size is correct
    Stack s;
    int garbageVal = 1;

    int numPushes = 56;
    int numPops = 21;

    for(int i = 0; i < numPushes; i++){
        s.push(garbageVal);
    }
    for(int i = 0; i < numPops; i++){
        s.pop();
    }

    ASSERT_EQ(s.size(), (numPushes - numPops));
}

TEST(TestStack, PushAndIsntEmpty) { // checking s.push(8) actually increments the stack's size
    Stack s;
    s.push(8);
    ASSERT_FALSE(s.isEmpty());
}

TEST(TestStack, PushThenPeek) { // push an int then check if peek returns that int
    Stack s;
    int garbageVal = 8;

    s.push(garbageVal);

    ASSERT_EQ(s.peek(), garbageVal);
}

TEST(TestStack, AlternatingPushPopAndPeek) { // lots of pushing, peeking, popping, and checking equality
    Stack s;

    s.push(47);
    ASSERT_EQ(s.pop(), 47);

    s.push(35);
    s.push(66);
    s.push(43);
    ASSERT_EQ(s.peek(), 43);
    ASSERT_EQ(s.peek(), 43);
    ASSERT_EQ(s.pop(), 43);
    ASSERT_EQ(s.pop(), 66);
    ASSERT_EQ(s.peek(), 35);
    ASSERT_EQ(s.pop(), 35);
}

TEST(TestStack, The100Test) { // push ints 1-100 onto the stack, then peek and pop them one by one, checking their values are right
    Stack s;
    for(int i = 1; i <= 100; i++){
        s.push(i);
        ASSERT_EQ(i, s.peek());
    }
    for(int i = 100; i >= 1; i--){
        ASSERT_EQ(i, s.peek());
        ASSERT_EQ(i, s.pop());
    }
}

TEST(TestStack, PopAndCheckReturnValue) {
    Stack s;
    int garbageVal = 8;

    s.push(garbageVal);

    ASSERT_EQ(s.pop(), garbageVal);
}

TEST(TestStack, PushTwiceAndCheckPops) {
    Stack s;
    s.push(1);
    s.push(2);
    ASSERT_NE(s.pop(), s.pop());
}

TEST(TestStack, CheckSizeIsChanging) {
    Stack s;
    s.push(6);
    int size1 = s.size();
    s.push(22);
    int size2 = s.size();
    ASSERT_NE(size1, size2);

    s.pop();
    size1 = s.size();
    s.pop();
    size2 = s.size();
    ASSERT_NE(size1, size2);
}

TEST(TestStack, ICantThinkOfAnyMoreTests) {
    Stack s;

    s.push(1000);
    s.push(s.pop() - 47);

    ASSERT_EQ(s.peek(), 953);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
