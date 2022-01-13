#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestrcutor:\t" << this << endl;
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
	}*Root;	//Корень дерева
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int i : il)insert(i, Root);
	}
	~Tree()
	{
		Clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
		cout << "\n---------------------------------------------\n";
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void Erase(int Data)
	{
		Erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / Count(Root);
	}
	void Clear()
	{
		Clear(Root);
		Root == nullptr;
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		//Root - корень поддерева
		//this->Root - корень всего дерева
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)//Если есть место для добавления элемента,
				Root->pLeft = new Element(Data);//Добавляем элемент прямо сюда.
			else//В противном случае
				insert(Data, Root->pLeft);	//идем налево, и ищим место, 
											//куда добавить элемент.
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	void Erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		Erase(Data, Root->pLeft);
		Erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf()) //если элемент является листком, то его можно удалить
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight)) //Если в левой ветке больше элементов, чем в правой
				{
					Root->Data = maxValue(Root->pLeft); //то заменяем значение удаляемого элемента максимальным значением левой ветки
					Erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else //в противном случае
				{
					Root->Data = minValue(Root->pRight); // заменяем значение удаляемого элемента минимальным значением правой ветки
					Erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	int minValue(Element* Root)const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/

		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		return Count(Root->pLeft) + Count(Root->pRight) + 1;*/
		//return Root ? Count(Root->pLeft) + Count(Root -> pRight) + 1 : 0;
		return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)const
	{
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.Count() << endl;
	cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;
#endif // BASE_CHECK

	Tree tree = { 50,25,72,16,32,64,80,8,11,48,77,85 };
	tree.print();
	int value;
	cout << "Введите удаляемое значение: "; cin >> value;
	tree.Erase(value);
	tree.print();
}