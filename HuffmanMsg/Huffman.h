#pragma once
class Huffman
{
public:
	Huffman();
	~Huffman();
	
	void CreateHuffmanTree();	
	void CreateRandomWeights();
	void HuffmanEncode();
	void HuffmanDecode();	
	void CreateHuffmanCodeList();
	
	void setOriText(CString Text);
	void setDeCRCText(CString Text);
	CString getEncodedText();
private:
	void GetTextEncode(CString * encode, int child, int i);
	void Dec2Bin(CString *Bin, int Dec);
	void SelectMin(int n, int *min1, int *min2);
	void SortWeights();
	void InitHuffmanTree(int NodeNumber);

	int Weights[WEIGHT_ARRAY_LENGTH][2];
	HuffmanCodeList HCL;
	HuffmanTree HT;
	CString OriText;
	CString BinText[MAX_TEXT_LENGTH];
	CString EncodedText;
	CString DeCRCText;
	CString DecodedBinText;
	CString DecodedText;
	FileList EncodedFileList;
};

