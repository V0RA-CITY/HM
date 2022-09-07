#include <iostream>
#include <vector>
#include <string>
#include<ostream>
#include<algorithm>

std::ostream& operator<<(std::ostream& s, const Card& aCard);

enum class rank
{

    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING,
    first = ACE,
    last = KING
};

rank operator++(rank& den) { return den = (rank)(std::underlying_type<rank>::type(den) + 1); };
rank operator*(rank den) { return den; };
rank begin(rank den) { return rank::first; };
rank end(rank den)
{
    rank de = rank::last;
    return ++de;
};


enum class suit
{
    CLUBS = 1,	
    DIAMONDS,	
    HEARTS,		
    SPADES,		
    first = CLUBS,
    last = SPADES
};

suit operator++(suit& Suit) { return Suit = (suit)(std::underlying_type<suit>::type(Suit) + 1); };
suit operator*(suit suit) { return suit; };
suit begin(suit suit) { return suit::first; };
suit end(suit Suit)
{
    suit su = suit::last;
    return ++su;
};

class Card
{
public:

    Card(rank r, suit s, bool ifu) : m_Suit(s), m_Rank(r), m_IsFaceUp(ifu)
    {};

    int GetValue() const;
    void Flip();

    friend std::ostream& operator<<(std::ostream& s, const Card& aCard);
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

int Card::GetValue() const
{
    int value = 0;
    if (m_IsFaceUp)
    {
        value = static_cast<int>(m_Rank);
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !m_IsFaceUp;
}


class Hand
{
public:
    Hand(){};
    ~Hand(){};

    void Add(Card* value)
    {
        HD.push_back(value);
    }

    void Clear()
    {
        HD.clear();
    }

    int GetValue() const
    {
        int tmp = 0;
        for (size_t i = 0; i < HD.size(); i++)
        {
            tmp += HD[i]->GetValue();
        }
        return tmp;
    }

protected:
    std::vector<Card*> HD;
};


class GenericPlayer : public Hand
{
public:
    GenericPlayer(){};
    ~GenericPlayer(){};

    virtual bool IsHitting();

    bool IsBoosted()
    {
        if (Hand::GetValue() > 21)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Bust()
    {
        std::cout << name << " is bust" << std::endl;
    }

private:
    std::string name;
};

class Player : public GenericPlayer
{
public:
    Player(const std::string& name = "");
    virtual ~Player() = default;

    virtual bool IsHitting() const;
    void Win() const;
    void Lose() const;
    void Push() const;
private:

};

class House : public GenericPlayer
{
public:
    House(){};
    ~House(){};

    virtual bool IsHitting() const
    {
        if (House::Hand::GetValue() <= 16)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void FlipFirstCard()
    {
        
    }

private:

};

class Deck : public Hand
{
public:
    Deck(){};
    ~Deck(){};

    void Populate()
    {
        Clear();
        for (const auto& s : suit())
        {
            for (const auto& r : rank())
            {
                Add(new Card(r, s, true));
            }
        }
    }

    void Shuffle()
    {
        std::random_shuffle(HD.begin(), HD.end());
    }

    void Deal(Hand& aHand)
    {
        if (!HD.empty())
        {
            aHand.Add(HD.back());
            HD.pop_back();
        }
        else
        {
            std::cout << "Нет карт. Невозможно дать карту.";
        }
    }

    void AddltionalCards(GenericPlayer& aGenerlcPlayer)
    {
        while (!aGenerlcPlayer.IsBoosted() && !aGenerlcPlayer.IsHitting())
        {
            Deal(aGenerlcPlayer);
            std::cout << aGenerlcPlayer << std::endl;

            if (aGenerlcPlayer.IsBoosted())
            {
                aGenerlcPlayer.Bust();
            }
        }
    }

private:

};


class Game
{
    public:
        Game(const std::vector<std::string>& names);
        ~Game() = default;




    private:
        Deck deck;
        House house;
        std::vector<Player> players;
};

int main()
{
    std::cout << "Hello World!\n";
}

