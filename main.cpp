#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "PatternTemplates.h"

using namespace std;

// Цвет кроссовок
enum class SneakersColor : int
{
    Blue,
    Black,
    Red,
    Unknown
};

// Реализация паттерна "Стратегия"

enum class PutOnMannerEnum : int
{
  LacingUp,
  FastenItWithVelcro,
  Zipper,

  // Новая стратегия для вариантов 1 и 3 (надеть, завязав шнурки и застегнув молнию)
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

// Фабричный метод для создания стратегий
PutOnStrategy *CreatePutOnStrategy(PutOnMannerEnum putonManner)
{
  switch(putonManner)
  {
    case PutOnMannerEnum::LacingUp: return new LacingUpPutOnStrategy;
    case PutOnMannerEnum::FastenItWithVelcro: return new FastenItWithVelcroPutOnStrategy;
    case PutOnMannerEnum::Zipper: return new ZipperPutOnStrategy;

    // Новый способ
    case PutOnMannerEnum::ZipperLacingUp: return new ZipperLacingUpStrategy;

    default: return nullptr;
  }
}

class Sneakers // Родительский (базовый) класс "Кроссовки"
{
private: // "Закрытые" компоненты (не доступны в унаследованных классах)
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
        // Способ надевания кроссовок не задан, ничего не делаем
        cout << "Do nothing!";
        return;
      }
      else
      {
        // Съесть заданным способом
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


protected: // "Защищенные" компоненты (доступны в унаследованных классах, но не доступны внешнему наблюдателю)
    bool SneakersAreSuper;

public: // "Открытые" компоненты, определяющие интерфейс класса

    Sneakers(SneakersColor color) : Color(color), Weight(0.0), SneakersAreSuper(false), PutOnManner(nullptr)
    {
        // Значение инициализируется случайным числом 0 или 1
        SneakersAreSuper = static_cast<bool>(rand()%2);
    }

    virtual ~Sneakers() // Деструктор (объявлен виртуальным, чтобы обеспечить корректное уничтожение унаследованных классов)
    {
      if(PutOnManner != nullptr) delete PutOnManner;
    }

    // Функция с реализацией
    bool AreSuper() const { return SneakersAreSuper; }

    // Функция с реализацией
    SneakersColor GetColor() const { return Color; }

    // Функция с реализацией
    double GetWeight() const { return Weight; }

    virtual void PrintType() = 0;

    virtual void Mud() = 0;

    // Функция с реализацией
    void PutOn()
    {
        // 1. Вывести название кроссовок
        PrintType();
        cout << " : ";

        // 2. Определить, кроссовки супер или нет
        DetectSuperOrNot();
        cout << " : ";

        // 2.1 Почистить от грязи
        Mud();
        cout << " : ";

        // 3. Если супер, то надеть с использованием выбранной стратегии
        DoPutOnUsingStrategy();

        // 4. Конец алгоритма
        cout << endl;
    }

    void SetPutOnManner(PutOnStrategy *putonManner) { PutOnManner = putonManner; }
};

class RunSneakers : public Sneakers // Класс-наследник "Беговые кроссовки"
{
public:
    RunSneakers();
    ~RunSneakers() {}

    void PrintType() { cout << "Running sneakers"; }
    void Mud() { cout << "Clean the mud with a special tool"; }
};

// Реализация конструктора
RunSneakers::RunSneakers() : Sneakers(SneakersColor::Blue)
{
  // Определить стратегию надевания беговых кроссовок по умолчанию(вариант 1)
  SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::LacingUp));
}

class FootballSneakers : public Sneakers // Класс-наследник "Футбольные кроссовки"
{
public:
    FootballSneakers() : Sneakers(SneakersColor::Black) { SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::Zipper)); }
    ~FootballSneakers() {}

    void PrintType() { cout << "FootballSneakers"; }
    void Mud() { cout << "Wipe off the mud with a thrashing"; }
};

class BasketballSneakers : public Sneakers // Класс-наследник "Баскетбольные кроссовки"
{
public:
    BasketballSneakers() : Sneakers(SneakersColor::Red) { SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::Zipper)); }
    ~BasketballSneakers() {}

    void PrintType() { cout << "BasketballSneakers"; }
    void Mud() { cout << "Remove mud with a brush"; }
};

//Реализация паттерна "фабричный метод" для создания кроссовок

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

// Декоратор итератора для выделения кроссовок по цвету

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

// Декоратор итератора для выделения "супер" или "плохих" кроссовок

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

// Функция, позволяющая "надеть" любые кроссовки из любого контейнера, вне зависимости от его внутреннего устройства
void PutOnEmAll(Iterator<Sneakers*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Sneakers *currentSneakers = it->GetCurrent();
        currentSneakers->PutOn();
    }
}

// Функция, позволяющая "надеть" только "супер" кроссовки (демонстрация решения проблемы "в лоб")
void PutOnEmAllAreSuper(Iterator<Sneakers*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Sneakers *currentSneakers = it->GetCurrent();
        if(!currentSneakers->AreSuper()) continue;

        currentSneakers->PutOn();
    }
}

// Функция, позволяющая "надеть" только черные кроссовки (демонстрация решения проблемы "в лоб")
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

    // Массив кроссовок

    ArrayClass<Sneakers*> sneakersArray;
    for(size_t i=0; i<N; i++)
    {
        int sneakers_num = rand()%3+1; // Число от 1 до 3 (случайные кроссовки)
        SneakersType sneakers_type = static_cast<SneakersType>(sneakers_num);
        Sneakers *newSneakers = CreateSneakers(sneakers_type);
        sneakersArray.Add(newSneakers);
    }

    cout << "The size of the sneaker array: " << sneakersArray.Size() << endl;

    // Связанный список кроссовок (для демонстрации адаптера)

    list<Sneakers*> sneakersVector; // а еще можно vector, forward_list, ...
    for(size_t i=0; i<N; i++)
    {
        int sneakers_num = rand()%3+1; // Число от 1 до 3 (случайные кроссовки)
        SneakersType sneakers_type = static_cast<SneakersType>(sneakers_num);
        Sneakers *newSneakers = CreateSneakers(sneakers_type);
        sneakersVector.push_back(newSneakers); // Добавить новые кроссовки в конец списка
    }

    cout << "The size of the sneakers list: " << sneakersVector.size() << endl;

        // Задать способ надевания на этапе создания
        // newSneakers->SetPutOnManner(CreatePutOnStrategy(PutOnMannerEnum::ZipperLacingUp));

    // Обход в простом цикле
    cout << endl << "Putting on all in a simple loop:" << endl;
    for(size_t i=0; i<sneakersArray.Size(); i++)
    {
        Sneakers *currentSneakers = sneakersArray[i];
        currentSneakers->PutOn();
    }

    // Обход всех элементов при помощи итератора
    cout << endl << "Putting on all using iterator:" << endl;
    Iterator<Sneakers*> *allIt = sneakersArray.GetIterator();
    PutOnEmAll(allIt);
    delete allIt;

    // Обход всех "супер" кроссовок
    cout << endl << "Putting on all super sneakers using iterator:" << endl;
    Iterator<Sneakers*> *aresuperIt = new SneakersAreSuperDecorator(sneakersArray.GetIterator(), true);
    PutOnEmAll(aresuperIt);
    delete aresuperIt;

    // Обход всех синих кроссовок
    cout << endl << "Putting on all blue sneakers using iterator:" << endl;
    Iterator<Sneakers*> *blueIt = new SneakersColorDecorator(sneakersArray.GetIterator(), SneakersColor::Blue);
    PutOnEmAll(blueIt);
    delete blueIt;

    // Обход всех "супер" синих кроссовок
    cout << endl << "Putting on all super blue sneakers using iterator:" << endl;
    Iterator<Sneakers*> *aresuperBlueIt =
        new SneakersAreSuperDecorator(new SneakersColorDecorator(sneakersArray.GetIterator(), SneakersColor::Blue), true);
    PutOnEmAll(aresuperBlueIt);
    delete aresuperBlueIt;

    // Демонстрация работы адаптера
    cout << endl << "Putting on all super blue sneakers using adapted iterator (another container):" << endl;
    Iterator<Sneakers*> *adaptedIt = new ConstIteratorAdapter<std::list<Sneakers*>, Sneakers*>(&sneakersVector);
    Iterator<Sneakers*> *adaptedBlueIt = new SneakersAreSuperDecorator(new SneakersColorDecorator(adaptedIt, SneakersColor::Blue), true);
    PutOnEmAll(adaptedBlueIt);
    delete adaptedBlueIt;
    // adaptedIt удалять не надо, так как он удаляется внутри декоратора adaptedBlueIt

    return 0;
}
