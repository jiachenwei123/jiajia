#include “Huffman.hpp”  
#include <algorithm>

//字符串每个结点的信息  
typedef size_t LongType;

struct CharInfo  
{
	char ch;         //字符  
	LongType count;    // 字符出现个数  
	string code;
	//比较字符串出现的个数是否相等  
	bool operator != (const CharInfo  & x) const  
	{
		return this->count  != x.count;
	}
	CharInfo operator + (const CharInfo  & x) const  
	{
		CharInfo ret;
		ret.count  = this->count  + x.count;
		return ret;
	}
	bool operator < (const CharInfo  & x) const  
	{
		return this->count  < x.count;
	}
};


class HuffmanCode  
{
	typedef HuffmanNode<CharInfo> Node;
public:
	HuffmanCode()
	{
		for (size_t i  = 0; i  < 256; i++)
		{
			_infos[i].ch  = i;
			_infos[i].count  = 0;
		}
	}
	void Code(const char* filename)
	{
		assert(filename);
		FILE* fout  = fopen(filename, “r”);
		assert(fout);

		//1.统计字符个数  
		char ch  = fgetc(fout);
		while (ch  != EOF)
		{
			_infos[ch].count++;
			ch  = fgetc(fout);
		}
		//2. 构建哈夫曼树  
		//非法值用字符出现次数为0  
		CharInfo invalid;
		invalid.count  = 0;
		HuffmanTree<CharInfo> tree(_infos, 256, invalid);

		//3生成哈夫曼编码  
		Node* root  = tree.GetRoot();
		GenerateHuffmanCode(root);
	}

	//从每个叶子结点往根节点走,规定左边标记为1,右边标记为0  
	void GenerateHuffmanCode(Node* root)
	{
		if (root  == NULL)
			return;
		if (root->_rchild  == NULL && root->_lchild  == NULL)
		{
			Node* cur  = root;
			Node* parent  = NULL;
			string s;
			while (cur->_parent  != NULL)
			{
				parent  = cur->_parent;
				if (parent->_lchild  == cur)
					s.push_back(’1’);
				else  
					s.push_back(’0’);
				cur  = parent;
			}
			//stl中提供的算法逆置,只需提供一段迭代器区间即可  
			reverse(s.begin(), s.end());
			root->_w.code  = s;
			//输出霍夫曼编码  
			cout  << ”ch:” << root->_w.ch  << “ ” << “count : ” << root->_w.count << “ ”  << root->_w.code  << endl;
		}
		GenerateHuffmanCode(root->_lchild);
		GenerateHuffmanCode(root->_rchild);
	}
protected:
	CharInfo _infos[256];
};

void TestHuffmanCode()
{
	HuffmanCode fc;
	fc.Code(”Input.txt”);
}

//test.cpp  
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
#include “HuffmanCode.hpp”  
int main()
{
	TestHuffmanCode();
	return 0;
}
