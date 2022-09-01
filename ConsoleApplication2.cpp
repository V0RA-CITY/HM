#include <iostream>
#include <typeinfo>

using namespace std;


template< class CharT, class Traits >
basic_ostream<CharT, Traits>& endll(basic_ostream<CharT, Traits>& os)
{
	os.put(os.widen('\n'));
	os.put(os.widen('\n'));
	os.flush();

	return os;
}

void Int_cin ()
{
	int x;
	
		while (!(cin >> x) && !(cin.good()))
		{
			while (cin.get() != '\n')
			{
				cin.clear();
				cin.ignore();
			}
			cout << "Error try again!" << endl;
		}
	

		cout << "X is :" << x << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
//Наследование не прописываю т.к сейчас не могу найти классы которые писал (а Hand еше не писал вовсе со следующего занятия буду отдельным файлом всё как положено с наследованием нормальным скидывать простите(

class Player // : public GenericPlayer
{
public:
	Player(){};
	~Player(){};

	virtual bool IsHitting() const
	{
		char temp;
		cout << "Do you need more card?" << endl;
		cout << "Y/N" << endl;
		while (!(cin >> temp) && !(cin.good()))
		{
			while (cin.get() != 'Y' || cin.get() != 'N' || cin.get() != 'y' || cin.get() != 'n')
			{
				cin.clear();
				cin.ignore();
			}
			cout << "Write Y or N please!" << endl;
		}
	}

	void Win() const
	{
		cout << "m_name is win!!!" << endl;
	}

	void Lose() const
	{
		cout << "m_name is lose(" << endl;
	}

	void Push() const
	{
		cout << "m_name is draw -_-" << endl;
	}

private:

};

class House // : public GenericPlayer
{
public:
	House(){};
	~House(){};

	virtual bool IsHitting() const
	{
	
	}

	void FlipFirstCard()
	{

	}

private:

};

ostream& operator<< (ostream& out, int Card)
{
	if (true)
	{
		cout << "Масть и т.д" << endl;
	}
	else
	{
		cout << "XX" << endl;
	}
}

int main()
{
	Int_cin();

	cout << "Lol" << endl;
	cout << "Kek" << endll;
	cout << "Cheburek";

}

