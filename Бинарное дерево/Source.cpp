#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;

struct Elem
{
	int OwnerPoints;//���� �������
	int OppPoints; //���� ���������
	char Macth[10];//����
	char Name[20];//�������
	char Oponent[20];// ��������

	Elem* left, * right, * parent;

};

class Tree
{
	//������
	Elem* root;
public:
	Tree();
	~Tree();
	//������ ���������� ����
	void Print(Elem* Node);
	//����� ���������� ����
	Elem* Serch(Elem* Node, char* key);
	//main �� ���������� ����
	Elem* Min(Elem* Node);
	//max �� ���������� ����
	Elem* Max(Elem* Node);
	// ��������� ��� ���������� ����
	Elem* Next(Elem* Node);
	//���������� ��� ���������� ����
	Elem* Previous(Elem* Node);
	//�������
	void Insert(Elem* z);
	//��������
	void Del(Elem* z = 0);
	// ���������� ������
	Elem* GetRoot();
};

Tree::Tree()
{
	root = NULL;

}

Tree::~Tree()
{
	Del();
}

//����������� �����
void Tree::Print(Elem* Node)
{
	if (Node != 0)
	{
		Print(Node->left);
		cout << "\n������� " << Node->Name <<" ���� "<< Node->Macth <<" ������� �������� "<< Node->Oponent << endl;
		Print(Node->right);
	}


}


Elem* Tree::Serch(Elem* Node, char* key)
{
	//���� ���� ���� � ����� �� ���������
	while (Node != 0 && strcmp(key, Node->Name) != 0)
	{
		if (strcmp(key, Node->Name) < 0)
		{
			Node = Node->left;
		}
		else
		{
			Node = Node->right;
		}
	}
	return Node;
}

Elem* Tree::Min(Elem* Node)
{
	//����� ������ ������������ "������" ��������
	if (Node != 0)
	{
		while (Node->left != 0)
		{
			Node = Node->left;
		}
	}
	return Node;
}

Elem* Tree::Max(Elem* Node)
{
	if (Node != 0)
	{
		while (Node->right != 0)
		{
			Node = Node->right;
		}
	}
	return Node;
}

Elem* Tree::Next(Elem* Node)
{
	Elem* y = 0;
	if (Node != 0)
	{
		//���� ���� ������ �������
		if (Node->right != 0)
		{
			return Min(Node->right);
		}
		//�������� ����
		y = Node->parent;
		//���� Node �� ������ � Node �� ������
		while (y != 0 && Node == y->right)
		{
			//�������� �����
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem* Tree::Previous(Elem* Node)
{
	Elem* y = 0;
	if (Node != 0)
	{
		//���� ���� ����� �������
		if (Node->left != 0)
		{
			return Max(Node->left);
		}
		//�������� ����
		y = Node->parent;
		//���� Node �� ������ � Node �� �����
		while (y != 0 && Node == y->left)
		{
			//�������� �����
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem* Tree::GetRoot()
{
	return root;
}

void Tree::Insert(Elem* z)
{
	//��������� ���
	z->left = NULL;
	z->right = NULL;

	Elem* y = NULL;
	Elem* Node = root;
	while (Node != 0)
	{
		//�������� ��������
		y = Node;
		if (strcmp(z->Name, Node->Name) < 0)
		{
			Node = Node->left;
		}
		else
		{
			Node = Node->right;
		}
	}

	z->parent = y;
	if (y == 0)
	{
		root = z;
	}
	else
	{
		if (strcmp(z->Name, y->Name) < 0)
		{
			y->left = z;
		}
		else
		{
			y->right = z;
		}
	}
}

void Tree::Del(Elem* z)
{
	if (z != 0)
	{
		Elem* Node, * y;

		if (z->left == 0 || z->right)
		{
			y = z;
		}

		else
		{
			y = Next(z);
		}

		if (y->left != 0)
		{
			Node = y->left;
		}

		else
		{
			Node = y->right;
		}

		if (Node != 0)
		{
			Node->parent = y->parent;
		}

		if (y->parent == 0)
		{
			root = Node;
		}

		else if (y == y->parent->left)
		{
			y->parent->left = Node;
		}
		else 
		{
			y->parent->right = Node;
		}
		if (y != z)
		{
			//����������� ������ ����
			strcpy(z->Name, y->Name);
			strcpy(z->Oponent, y->Oponent);
			strcpy(z->Macth, y->Macth);
			z->OppPoints = y->OppPoints;
			z->OwnerPoints = y->OwnerPoints;
		}
		delete y;
	}
	else
	{
		while (root != 0)
		{
			Del(root);
		}
	}

}


Tree tournament;
void Game(char Commands[] [20], int N)
{
	int p1, p2;
	Elem* temp;
	for (int k = 0; k < N - 1; k++)
	{
		for (int i = 0; i < N - 1; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				temp = new Elem;
				if (k == 0)
				{
					//���� 1
					strcpy(temp->Name, Commands[i]);
					strcpy(temp->Oponent, Commands[j]);
				}
				else
				{
					//���� 2
					strcpy(temp->Name, Commands[i]);
					strcpy(temp->Oponent, Commands[j]);
				}
				p1 = rand() % 6;
				p2 = rand() % 6;
				if (p1 > p2)
				{
					temp->OwnerPoints = 3;
					temp->OppPoints = 0;
				}
				else if (p1 == p2)
				{
					temp->OwnerPoints = 1;
					temp->OppPoints = 1;
				}
				else
				{
					temp->OwnerPoints = 0;
					temp->OppPoints = 3;
				}

				sprintf(temp->Macth, "%d:%d", p1, p2);
				tournament.Insert(temp);
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	//srand(time(NULL));
	const int N = 4;
	char Commands[4][20]{ "Arsenal","Liverpool","Lids-United","Manchester" };
	Game(Commands, N);
	tournament.Print(tournament.GetRoot());


	return 0;
}