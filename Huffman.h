/*
Huffman Tree - Paul Miller
	- This is a huffman tree that generates huffman code map for added symbols.
	- Usage: Symbol, frequency pairs are added to the tree. Once all of the symbols are added
		calling generateCodes will populate the codeMap.
		Decode will return the symbol from the given code
		Encode will return the code for the given symbol
*/
#ifndef HTREE_H
#define HTREE_H
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <iterator>
//Huffman Tree
//
//All character frequency pairs mush be added before heapify is called in order for the algorithm to work

#define DELIM ' '
class HTree
{
public:
	HTree();
	~HTree();
	std::string decodeData(std::string data);
	std::string encodeData(std::string data);
	void print();
	void printForest();
	void clear();
protected:
	class HNode{
	public:
		HNode(char c, int freq, HNode *l=0, HNode*r=0);
		HNode(const HNode &o);
		~HNode();
		void  setFreq(int newFreq);
		char getC() const;
		bool isLeaf() const;
		int getFreq() const;
		HNode* getR()const;
		HNode* getL()const;
		void print(int i=0) ;
	private:
		char c; //char to be decoded
		int freq; //freq of char or if internal freq summation
		HNode *l, *r; //l = 1, r = 0
	};
	void add(char c, int freq=1);
	void add(HNode* n);
	void generateCodeMap();
	char decode( std::string code);
	std::string encode(char key);
	char decode(HNode* root, std::string code);
	void encode(HNode * root, std::string code);
	void heapify();
	HNode* popSmallest(); //get smallest from forest
	static HNode* merge(HNode* l, HNode*r);
private:
	bool isHeap;
	std::map<char, std::string> codeMap; //value each key is mapped to
	std::vector<HNode*> forest;//holds the set of nodes. Smallest two are removed and appended to each other
};

#endif //HTREE_H
