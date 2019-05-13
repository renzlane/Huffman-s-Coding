
//#include "header.h"
//
//int main() {
//	string str = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal. Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we cannot dedicate -- we cannot consecrate -- we cannot hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.";
//	int n = str.length();
//	char arr[n+1];
//	strcpy(arr, str.c_str());
//
//	int size = sizeof(arr) / sizeof(arr[0]);
//
//    // Build frequency table
//    int frequencies[UniqueSymbols] = {0};
//    const char* ptr = SampleString;
//    while (*ptr != '\0')
//        ++frequencies[*ptr++];
//
//    INode* root = BuildTree(frequencies);
//
//    HuffCodeMap codes;
//    GenerateCodes(root, HuffCode(), codes);
//    delete root;
//
//    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
//    {
//        cout << it->first << " ";
//        copy(it->second.begin(), it->second.end(),
//                  ostream_iterator<bool>(cout));
//        cout << endl;
//    }
//    return 0;
//}
#include "huffman.h"

int main(int argc, char**argv) //amend this section; use built-in arguments
{
	std::cout << "\nHTree"
				<< "\nencode - Prompts to encode new data string"
				<< "\ndecode - Decodes encoded string"
				<< "\nprint  - Prints code table\n"
				<< "\nexit  - Exits program\n";
	HTree h;
	std::string encodedData,decodedData, input;
	if(argc == 2)
		input = argv[1];


	do
	{
		std::cout << ">";
		std::getline(std::cin,input);
		if(input == "encode")
		{
			std::cout << "Data:";
			std::getline(std::cin,input);
			encodedData= h.encodeData(input);
			std::cout <<"\nEncoded:\n" << encodedData << "\n";
		}
		else if(input == "decode")
		{
			decodedData= h.decodeData(encodedData);
			std::cout <<"\nDecoded:\n" << decodedData << "\n";
		}
		else if(input == "print")
		{
			h.print();
			std::cout << "\n";
		}
		//add section for compression ratio
	}while(input != "exit");
	return 0;
}

// Driver program to test above functions
//int main()
//{
//
//	string str = "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal. Now we are engaged in a great civil war, testing whether that nation, or any nation so conceived and so dedicated, can long endure. We are met on a great battle-field of that war. We have come to dedicate a portion of that field, as a final resting place for those who here gave their lives that that nation might live. It is altogether fitting and proper that we should do this. But, in a larger sense, we cannot dedicate -- we cannot consecrate -- we cannot hallow -- this ground. The brave men, living and dead, who struggled here, have consecrated it, far above our poor power to add or detract. The world will little note, nor long remember what we say here, but it can never forget what they did here. It is for us the living, rather, to be dedicated here to the unfinished work which they who fought here have thus far so nobly advanced. It is rather for us to be here dedicated to the great task remaining before us -- that from these honored dead we take increased devotion to that cause for which they gave the last full measure of devotion -- that we here highly resolve that these dead shall not have died in vain -- that this nation, under God, shall have a new birth of freedom -- and that government of the people, by the people, for the people, shall not perish from the earth.";
//	int n = str.length();
//	char arr[n+1];
//	strcpy(arr, str.c_str());
//	int size = sizeof(arr) / sizeof(arr[0]);
//
//	HuffmanCodes(arr, freq, size);
//
//	return 0;
//}

// This code is contributed by Aditya Goel
