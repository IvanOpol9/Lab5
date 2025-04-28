#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "PatternTemplates.h"

using namespace std;

// ���� ���������
enum class SneakersColor : int
{
    Blue,
    Black,
    Red,
    Unknown
};

// ���������� �������� "���������"

enum class PutOnMannerEnum : int
{
  LacingUp,
  FastenItWithVelcro,
  Zipper,

  // ����� ��������� ��� ��������� 1 � 3 (������, ������� ������ � ��������� ������)
  ZipperLacingUp,

  None
};

class PutOnStrategy
{
public:
  virtual ~PutOnStrategy() {}
  virtual void PutOn() = 0;
};

class LacingUpPutOnStrategy : public PutOnStrategy
{
  void PutOn() { cout << "Put on lace-up sneakers..."; }
};

class FastenItWithVelcroPutOnStrategy : public PutOnStrategy
{
  void PutOn() { cout << "To put on sneakers velcro up..."; }
};

class ZipperPutOnStrategy : public PutOnStrategy
{
  void PutOn() { cout << "Put on fasten the zipper..."; }
};

class ZipperLacingUpStrategy : public PutOnStrategy
{
  void PutOn() { cout << "Put on tying the laces and zipping up..."; }
};

// ��������� ����� ��� �������� ���������
PutOnStrategy *CreatePutOnStrategy(PutOnMannerEnum putonManner)
{
  switch(putonManner)
  {
    case PutOnMannerEnum::LacingUp: return new LacingUpPutOnStrategy;
    case PutOnMannerEnum::FastenItWithVelcro: return new FastenItWithVelcroPutOnStrategy;
    case PutOnMannerEnum::Zipper: return new ZipperPutOnStrategy;

    // ����� ������
    case PutOnMannerEnum::ZipperLacingUp: return new ZipperLacingUpStrategy;

    default: return nullptr;
  }
}

class Sneakers // ������������ (�������) ����� "���������"
{
private: // "��������" ���������� (�� �������� � �������������� �������)
    SneakersColor Color;
    //int Color;
    int Brand;
    double Size;
    double Weight;

    PutOnStrategy *PutOnManner;

    void DoPutOnUsingStrategy()
    {
      if(PutOnManner == nullptr)
      {
        // ������ ��������� ��������� �� �����, ������ �� ������
        cout << "Do nothing!";
        return;
      }
      else
      {
        // ������ �������� ��������
        PutOnManner->PutOn();
      }
    }

    void DetectSuperOrNot()
    {
      if(AreSuper())
      {
          cout << "Super";
      }
      else
      {
          cout << "BAD";
      }
    }


protected: // "����������" ���������� (�������� � �������������� �������, �� �� �������� �������� �����������)
    bool SneakersAreSuper;

public: // "��������" ����������, ������������ ��������� ������

    Sneakers(SneakersColor color) : Color(color), Weight(0.0), SneakersAreSuper(false), PutOnManner(nullptr)
    {
        // �������� ���������������� ��������� ������ 0 ��� 1
        SneakersAreSuper = static_cast<bool>(rand()%2);
    }

    virtual ~Sneakers() // ���������� (�������� �����������, ����� ���������� ���������� ����������� �������������� �������)
    {
      if(PutOnManner != nullptr) delete PutOnManner;
    }

    // ������� � �����������
    bool AreSuper() const { return SneakersAreSuper; }

    // ������� � �����������
    SneakersColor GetColor() const { return Color; }

    // ������� � �����������
    double GetWeight() const { return Weight; }

    virtual void PrintType() = 0;

    virtual void Mud() = 0;

    // ������� � �����������
    void PutOn()
    {
        // 1. ������� �������� ���������
        PrintType();
        cout << " : ";

        // 2. ����������, ��������� ����� ��� ���
        DetectSuperOrNot();
        cout << " : ";

        // 2.1 ��������� �� �����
        Mud();
        cout << " : ";

        // 3. ���� �����, �� ������ � �������������� ��������� ���������
        DoPutOnUsingStrategy();

        // 4. ����� ���������
        cout << endl;
    }

    void SetPutOnManner(PutOnStrategy *putonManner) { PutOnManner = putonManner; }
};

class RunSneakers : public Sneakers // �����-��������� "������� ���������"
{
public:
    RunSneakers();
    ~RunSneakers() {}

    void PrintType() { cout << "Running sneakers"; }
    void Mud() { cout << "Clean the mud with a special tool"; }
};

// ���������� ������������
RunSneakers::RunSneakers() : Sneakers(SneakersColor::Blue)
{
  // ���������� ��������� ��������� ������� ��������� �� ���������(������� 1)
  SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::LacingUp));
}

class FootballSneakers : public Sneakers // �����-��������� "���������� ���������"
{
public:
    FootballSneakers() : Sneakers(SneakersColor::Black) { SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::Zipper)); }
    ~FootballSneakers() {}

    void PrintType() { cout << "FootballSneakers"; }
    void Mud() { cout << "Wipe off the mud with a thrashing"; }
};

class BasketballSneakers : public Sneakers // �����-��������� "������������� ���������"
{
public:
    BasketballSneakers() : Sneakers(SneakersColor::Red) { SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::Zipper)); }
    ~BasketballSneakers() {}

    void PrintType() { cout << "BasketballSneakers"; }
    void Mud() { cout << "Remove mud with a brush"; }
};

//���������� �������� "��������� �����" ��� �������� ���������

enum class SneakersType : int
{
  RunSneakers = 1,
  FootballSneakers = 2,
  BasketballSneakers = 3,

  Undefind = 0
};

/*int main() {
    int choice;

    std::cout << " 1 or 2 or 3? : ";
    std::cin >> choice;


switch (choice) {
        case 1:
            std::cout << "Var1" << std::endl;
            break;
        case 2:
            std::cout << "Var2" << std::endl;
            break;
        case 3:
            std::cout << "Var3" << std::endl;
            break;
        default:
            std::cout << "Uncorrect" << std::endl;
            break;}*/
Sneakers *CreateSneakers(SneakersType type)
{
    Sneakers *newSneakers = nullptr;
    if(type == SneakersType::RunSneakers)
    {
        newSneakers = new RunSneakers;
    }

    else if(type == SneakersType::FootballSneakers)
    {
        newSneakers = new FootballSneakers;
    }

    else if(type == SneakersType::BasketballSneakers)
    {
        newSneakers = new BasketballSneakers;
    }

    return newSneakers;
}

// ��������� ��������� ��� ��������� ��������� �� �����

class SneakersColorDecorator : public IteratorDecorator<class Sneakers*>
{
private:
    SneakersColor TargetColor;

public:
    SneakersColorDecorator(Iterator<Sneakers*> *it, SneakersColor color)
    : IteratorDecorator<Sneakers*>(it), TargetColor(color) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->GetColor() != TargetColor)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->GetColor() != TargetColor);
    }
};

// ��������� ��������� ��� ��������� "�����" ��� "������" ���������

class SneakersAreSuperDecorator : public IteratorDecorator<class Sneakers*>
{
private:
    bool TargetAreSuper;

public:
    SneakersAreSuperDecorator(Iterator<Sneakers*> *it, bool areSuper)
    : IteratorDecorator<Sneakers*>(it), TargetAreSuper(areSuper) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->AreSuper() != TargetAreSuper)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->AreSuper() != TargetAreSuper);
    }
};

// �������, ����������� "������" ����� ��������� �� ������ ����������, ��� ����������� �� ��� ����������� ����������
void PutOnEmAll(Iterator<Sneakers*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Sneakers *currentSneakers = it->GetCurrent();
        currentSneakers->PutOn();
    }
}

// �������, ����������� "������" ������ "�����" ��������� (������������ ������� �������� "� ���")
void PutOnEmAllAreSuper(Iterator<Sneakers*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Sneakers *currentSneakers = it->GetCurrent();
        if(!currentSneakers->AreSuper()) continue;

        currentSneakers->PutOn();
    }
}

// �������, ����������� "������" ������ ������ ��������� (������������ ������� �������� "� ���")
void PutOnEmAllBlack(Iterator<Sneakers*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Sneakers *currentSneakers = it->GetCurrent();
        if(currentSneakers->GetColor() != SneakersColor::Black) continue;

        currentSneakers->PutOn();
    }
}

int main()
{
    size_t N = 100;

    // ������ ���������

    ArrayClass<Sneakers*> sneakersArray;
    for(size_t i=0; i<N; i++)
    {
        int sneakers_num = rand()%3+1; // ����� �� 1 �� 3 (��������� ���������)
        SneakersType sneakers_type = static_cast<SneakersType>(sneakers_num);
        Sneakers *newSneakers = CreateSneakers(sneakers_type);
        sneakersArray.Add(newSneakers);
    }

    cout << "The size of the sneaker array: " << sneakersArray.Size() << endl;

    // ��������� ������ ��������� (��� ������������ ��������)

    list<Sneakers*> sneakersVector; // � ��� ����� vector, forward_list, ...
    for(size_t i=0; i<N; i++)
    {
        int sneakers_num = rand()%3+1; // ����� �� 1 �� 3 (��������� ���������)
        SneakersType sneakers_type = static_cast<SneakersType>(sneakers_num);
        Sneakers *newSneakers = CreateSneakers(sneakers_type);
        sneakersVector.push_back(newSneakers); // �������� ����� ��������� � ����� ������
    }

    cout << "The size of the sneakers list: " << sneakersVector.size() << endl;

        // ������ ������ ��������� �� ����� ��������
        // newSneakers->SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::ZipperLacingUp));

    // ����� � ������� �����
    cout << endl << "Putting on all in a simple loop:" << endl;
    for(size_t i=0; i<sneakersArray.Size(); i++)
    {
        Sneakers *currentSneakers = sneakersArray[i];
        currentSneakers->PutOn();
    }

    // ����� ���� ��������� ��� ������ ���������
    cout << endl << "Putting on all using iterator:" << endl;
    Iterator<Sneakers*> *allIt = sneakersArray.GetIterator();
    PutOnEmAll(allIt);
    delete allIt;

    // ����� ���� "�����" ���������
    cout << endl << "Putting on all super sneakers using iterator:" << endl;
    Iterator<Sneakers*> *aresuperIt = new SneakersAreSuperDecorator(sneakersArray.GetIterator(), true);
    PutOnEmAll(aresuperIt);
    delete aresuperIt;

    // ����� ���� ����� ���������
    cout << endl << "Putting on all blue sneakers using iterator:" << endl;
    Iterator<Sneakers*> *blueIt = new SneakersColorDecorator(sneakersArray.GetIterator(), SneakersColor::Blue);
    PutOnEmAll(blueIt);
    delete blueIt;

    // ����� ���� "�����" ����� ���������
    cout << endl << "Putting on all super blue sneakers using iterator:" << endl;
    Iterator<Sneakers*> *aresuperBlueIt =
        new SneakersAreSuperDecorator(new SneakersColorDecorator(sneakersArray.GetIterator(), SneakersColor::Blue), true);
    PutOnEmAll(aresuperBlueIt);
    delete aresuperBlueIt;

    // ������������ ������ ��������
    cout << endl << "Putting on all super blue sneakers using adapted iterator (another container):" << endl;
    Iterator<Sneakers*> *adaptedIt = new ConstIteratorAdapter<std::list<Sneakers*>, Sneakers*>(&sneakersVector);
    Iterator<Sneakers*> *adaptedBlueIt = new SneakersAreSuperDecorator(new SneakersColorDecorator(adaptedIt, SneakersColor::Blue), true);
    PutOnEmAll(adaptedBlueIt);
    delete adaptedBlueIt;
    // adaptedIt ������� �� ����, ��� ��� �� ��������� ������ ���������� adaptedBlueIt

    return 0;
}
