#include "huffman.h"

HTree::HNode::HNode(char c, int freq, HNode *l, HNode*r)
		:c(c), freq(freq), l(l), r(r)
{
}
HTree::HNode::HNode(const HNode&o)
		:c(o.getC()),freq(o.getFreq())
{
	if(o.l)
		l = new HNode(*o.l);
	else
		l=0;
	if(o.r)
		r = new HNode(*o.r);
	else
		r=0;
}
HTree::HNode::~HNode()
{
/*
	std::cout << "Deleting ";
 	isLeaf() ? std::cout << c : std::cout<<"IN";
	std::cout<<":" <<freq<< "\n";
*/
	if(l) delete l;
	if(r) delete r;
}
char HTree::HNode::getC()const
{
	return c;
}
int HTree::HNode::getFreq()const
{
	return freq;
}
bool HTree::HNode::isLeaf()const
{
	return !(l || r);
}

HTree::HNode* HTree::HNode::getR()const
{
	return r;
}
HTree::HNode* HTree::HNode::getL()const
{
	return l;
}
void HTree::HNode::setFreq(int newFreq)
{
	freq = newFreq;
}

void HTree::HNode::print(int i)
{
	std::cout <<std::setfill('\t')<<std::setw(i) << " ";
 	isLeaf() ? std::cout << c : std::cout<<"IN";
	std::cout<<"|" <<freq<< "\n";
	std::cout << std::setfill(' ');
	if(l)l->print(i+1);
	if(r)r->print(i+1);
}

HTree::HTree()
{
	isHeap =  false;
}
HTree::~HTree()
{
	clear();
}
void HTree::clear()
{
	codeMap.clear();
	//manually delete entries allocated
	for(int i =0; i < forest.size();i++)
		if(forest[i])
		{
			delete forest[i];
			forest[i] = 0;
		}
	forest.clear(); //clear vector
	isHeap = false;
}
std::string HTree::encodeData(std::string data)
{
	clear(); //lear forest for new data string
	std::ostringstream oss;
	for(int i=0; i < data.size(); i++)
		add(data[i]);
	generateCodeMap();
	//print();
	for(int i=0; i < data.size(); i++)
	{
	//	std::cout << data[i] << " -> " << encode(data[i]) << "\n";
		oss << encode(data[i])<<DELIM;
	}
	return oss.str();

}
std::string HTree::decodeData(std::string data)
{
	std::ostringstream oss;
	for(int i=0; i < data.size(); i++){
		std::string code = "";
		char sym =0;
		while(i < data.size() && data[i] != DELIM)
		{
			code.push_back(data[i]);
			i++;
		}

		sym = decode(code);
//		std::cout << "Sym: " <<sym;
///		std::cin.get();
		oss << sym;

	}
	return oss.str();
}
std::string HTree::encode(char key)
{
	return codeMap[key];
}
char HTree::decode(std::string code)
{
	char c = 0;
	if(isHeap && forest.size() > 0)
		c =decode(forest[0], code);
	return c;
}
char HTree::decode(HNode* root, std::string code)
{

	char c = 0;
	if(root && code.size() >= 0){

		if(code.size()==0 && root->isLeaf())
		{
			return root->getC();
		}else
		{
			char d = code[0];
			code.erase(code.begin());
			if(d=='0')
				c = decode(root->getL(),code);
			else if(d=='1')
				c=decode(root->getR(),code);
		}
	}
	return c;
}
void HTree::generateCodeMap()
{
	heapify();//heapify data
	if(forest.size() > 0)
		encode(forest[0],"");
}
void HTree::encode(HNode * root,  std::string code)
{
	if(root)
	{
		if(root->isLeaf())codeMap[root->getC()] = code;
		std::string cL = code;
		std::string cR = code;
		cL.push_back('0');
 		cR.push_back('1');
		encode(root->getL(),cL);
		encode(root->getR(), cR);
	}
}
void HTree::print()
{
	std::cout << "#Code Table" << std::endl
			  << "| Sym | Code    |" << std::endl
			  << "| :-- | ------: |"<< std::endl;
	for(std::map<char, std::string>::iterator it = codeMap.begin(); it != codeMap.end(); it++)
		std::cout << "| " << std::setw(3) << it -> first << " | " << std::setw(7) << (it->second) << " |" <<std::endl;
}
void HTree::printForest()
{
	for(int i =0; i < forest.size();i++){
		std::cout << i << ":";
		if(forest[i])forest[i]->print();
		std::cout << std::endl;
	}
}
void HTree::add(char c, int freq)
{
	if(isHeap) return;
	//if node does not exist, does not need to check recursively, this function should be run before hepify!
	HNode *node=0;
	int i=0;
	while( i < forest.size() && !node)
	{
		if(forest[i] && forest[i]->getC() == c)
			node = forest[i];
		else
			i++;
	}
	if(node) //if found concat freq
	{
		node->setFreq(node->getFreq()+freq);
	}
	else
	{
		forest.push_back(new HNode(c,freq));
	}
}
void HTree::add(HNode* node)
{
	if(isHeap) return;
	if(node)forest.push_back(node);
}
void HTree::heapify()
{
	while(forest.size() >= 2)//while there are at least 2 to merge
	{
		HNode* minB = popSmallest();
		HNode* minA = popSmallest();
		HNode*internal = HTree::merge(minA, minB);
		add(internal);
		minA = minB = 0;
	}
	isHeap = true;
}
HTree::HNode* HTree::merge(HNode* l, HNode*r)
{
	if(l&&r)
		return new HNode(0, l->getFreq()+r->getFreq(), l, r);
	else
		return 0;
}
HTree::HNode* HTree::popSmallest()
{
	if(forest.size() <= 0)
		return 0;
	int i=0;
	for(int j=0;j < forest.size();j++)
	{
		if(forest[i]->getFreq() > forest[j]->getFreq())
			i = j;
	}
	HNode* n =  forest[i];

	forest.erase(forest.begin()+i);
	return n;

} //get smallest from forest
