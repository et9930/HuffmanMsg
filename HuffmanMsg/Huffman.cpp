#include "stdafx.h"
#include "Huffman.h"


Huffman::Huffman()
{

}


Huffman::~Huffman()
{
	delete[]HT;
	delete[]HCL;
}

void Huffman::InitHuffmanTree(int NodeNumber)
{
	HT = new HuffmanNode[NodeNumber];
	for (int i = 0; i < NodeNumber; i++)
	{
		HT[i].Data = "";
		HT[i].Weight = -1;
		HT[i].parent = -1;
		HT[i].lchild = -1;
		HT[i].rchild = -1;
		HT[i].isLeaf = FALSE;
	}
}

void Huffman::CreateHuffmanTree()
{
	int min1, min2;
	SortWeights();
	int totalNodes = 2 * WEIGHT_ARRAY_LENGTH - 1;
	InitHuffmanTree(totalNodes);
	for (int i = 0; i<WEIGHT_ARRAY_LENGTH; i++)
	{
		HT[i].Weight = Weights[i][1];
		Dec2Bin(&HT[i].Data, Weights[i][0]);
		HT[i].isLeaf = TRUE;
	}
	for (int i = WEIGHT_ARRAY_LENGTH; i < totalNodes; i++)
	{
		SelectMin(i, &min1, &min2);
		HT[min1].parent = i;
		HT[min2].parent = i;
		HT[i].lchild = min1;
		HT[i].rchild = min2;
		HT[i].Weight = HT[min1].Weight + HT[min2].Weight;
	}
}

void Huffman::SelectMin(int n, int * min1, int * min2)
{
	typedef struct
	{
		int NewWeight;//存储权  
		int p;//存储该结点所在的位置  
	}TempNode, *TempTree;

	TempTree TT = new TempNode[n];
	int i;
	int j = 0;
	for (i = 0; i<n; i++)
	{
		if (HT[i].parent == -1 && HT[i].Weight != -1)
		{
			TT[j].NewWeight = HT[i].Weight;
			TT[j].p = i;
			j++;
		}
	}//将HT中没有双亲的结点存储到TT中  

	int m1 = 0;
	int m2 = 0;
	for (i = 0; i<j; i++)
	{
		if (TT[i].NewWeight<TT[m1].NewWeight)//此处不让取到相等，是因为结点中有相同权值的时候，m1取最前的那个。			
			m1 = i;
	}
	for (i = 0; i<j; i++)
	{
		if (m1 == m2)
			m2++;//当m1在第一个位置的时候，m2向后移一位  
		if (TT[i].NewWeight <= TT[m2].NewWeight&& i != m1)//此处取到相等，是让在结点中有相同的权值的时候，m2取最后的那个。  														    
			m2 = i;
	}

	*min1 = TT[m1].p;
	*min2 = TT[m2].p;
	delete[]TT;
}


void Huffman::CreateRandomWeights()
{	
	
	for (int i = 0; i < WEIGHT_ARRAY_LENGTH; i++)
	{
		Weights[i][0] = i;
		Weights[i][1] = i;
	}
	int x = 0, tmp = 0;
	for (int i = WEIGHT_ARRAY_LENGTH - 1; i > 0; i--)
	{
		srand((unsigned)time(NULL));
		x = (RAND_MAX*rand() + rand()) % i + 1;
		tmp = Weights[i][1];
		Weights[i][1] = Weights[x][1];
		Weights[x][1] = tmp;
	}
}

void Huffman::HuffmanEncode()
{
	EncodedText = L"";
	int Length = OriText.GetLength();
	wchar_t SplitedText[MAX_TEXT_LENGTH+1] = { 0 };
	lstrcpynW(SplitedText, (LPCTSTR)OriText, Length + 1);
	for (int i = 0; i < Length; i++)
	{
		Dec2Bin(&BinText[i], (int)SplitedText[i]);
		for (int j = 0; j < WEIGHT_ARRAY_LENGTH; j++)
		{
			if (HCL[j].ori == BinText[i])
			{
				EncodedText = EncodedText + HCL[j].encode;
			}
		}
	}
}

void Huffman::HuffmanDecode()
{
	HuffmanNode *pCurrentPoint = NULL;
	*pCurrentPoint = HT[WEIGHT_ARRAY_LENGTH * 2 - 1];
	for (int i = 0; i < DeCRCText.GetLength(); i++)
	{
		if (pCurrentPoint->isLeaf == TRUE)
		{
			DecodedBinText = DecodedBinText + pCurrentPoint->Data;
			*pCurrentPoint = HT[WEIGHT_ARRAY_LENGTH * 2 - 1];
		}
		CString CurrentBit = DeCRCText.Mid(i, 1);
		if (CurrentBit == "0")
		{
			*pCurrentPoint = HT[pCurrentPoint->lchild];
		}
		if (CurrentBit == "1")
		{
			*pCurrentPoint = HT[pCurrentPoint->rchild];
		}
	}
	int BitLength = DecodedBinText.GetLength();
	wchar_t DecodedBit[MAX_TEXT_LENGTH * 16] = { 0 };
	lstrcpynW(DecodedBit, (LPCTSTR)DecodedBinText, BitLength * 16 + 1);
	for (int i = 0; i < BitLength / 16; i++)
	{
		int nResult = 0;
		for (int j = 0; j<16; j++)
		{
			nResult += (DecodedBit[i * 16 + j] - '0')*pow(2.0, 15 - j);
		}
		wchar_t Word = (wchar_t)nResult;
		CString CStrWord(Word);
		DecodedText = DecodedText + CStrWord;
	}
}

void Huffman::SortWeights()
{
	int temp[2] = { 0,0 };
	for (int i = 0; i < WEIGHT_ARRAY_LENGTH; i++)
	{
		for (int j = i; j < WEIGHT_ARRAY_LENGTH; j++)
		{
			if (Weights[i][1] > Weights[j][1])
			{
				temp[0] = Weights[i][0];
				temp[1] = Weights[i][1];
				Weights[i][0] = Weights[j][0];
				Weights[i][1] = Weights[j][1];
				Weights[j][0] = temp[0];
				Weights[j][1] = temp[1];
			}
		}
	}
}

void Huffman::Dec2Bin(CString * Bin, int Dec)
{
	wchar_t a[17];
	for (int i = 0; i < 16; i++)
	{
		a[i] = '0';
	}
	a[16] = '\0';
	int j = 15;
	while (Dec)
	{
		if (Dec % 2 == 0)
		{
			a[j] = '0';
		}
		else
		{
			a[j] = '1';
		}
		Dec = Dec / 2;
		j--;
	}
	Bin->Format(L"%s", a);
}

void Huffman::CreateHuffmanCodeList()
{
	HCL = new HuffmanCodeNode[WEIGHT_ARRAY_LENGTH];
	for (int i = 0; i < WEIGHT_ARRAY_LENGTH; i++)
	{
		HCL[i].ori = HT[i].Data;
		HCL[i].encode.Format(L"");
		GetTextEncode(&HCL[i].encode, -1, i);
	}
}

void Huffman::GetTextEncode(CString * encode, int child, int i)
{	
	CString Z = L"0";
	CString O = L"1";
	if (HT[i].lchild != -1 && HT[i].lchild == child)
	{
		//encode->Format(L"%d%s", 0, encode);
		*encode = Z + *encode;
	}
	if (HT[i].rchild != -1 && HT[i].rchild == child)
	{
		//encode->Format(L"%d%s", 1, encode);
		*encode = O + *encode;
	}
	if (HT[i].parent == -1)
	{
		return;
	}
	return GetTextEncode(encode, i, HT[i].parent);
}

void Huffman::setOriText(CString Text)
{
	OriText = Text;
}

void Huffman::setDeCRCText(CString Text)
{
	DeCRCText = Text;
}

CString Huffman::getEncodedText()
{
	int a = EncodedText.GetLength();
	return EncodedText;
}


