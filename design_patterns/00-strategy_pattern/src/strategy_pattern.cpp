/*
The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
Strategy lets the algorithm vary independently from clients that use it.
*/

#include <iostream>

/* Family of Quack Behaviors */
class IQuackBehavior
{
public:
    virtual ~IQuackBehavior() = default;
    virtual void Quack() = 0;
};

class SimpleQuack : public IQuackBehavior
{
public:
    void Quack() override
    {
        std::cout << "Simple Quack !!! \n";
    }
};

class MuteQuack : public IQuackBehavior
{
public:
    void Quack() override
    {
        std::cout << "Mute Quack !!! \n";
    }
};

class SqueakQuack : public IQuackBehavior
{
public:
    void Quack() override
    {
        std::cout << "Squeak Quack !!! \n";
    }
};

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* Family of Fly Behaviors */
class IFlyBehavior
{
public:
    virtual ~IFlyBehavior() = default;
    virtual void Fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
public:
    void Fly() override
    {
        std::cout << "Fly with Wings !!! \n";
    }
};

class FlyNoWay : public IFlyBehavior
{
public:
    void Fly() override
    {
        std::cout << "Fly No Way !!! \n";
    }
};

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
class IDuck
{
public:
    virtual ~IDuck() = default;

    virtual void Display() = 0;
    virtual void PerformQuack()
    {
        m_QuackBehavior->Quack();
    }
    virtual void PerformFly()
    {
        m_FlyBehavior->Fly();
    }
    virtual void Swim()
    {
        std::cout << "All ducks float, even decoys !!! \n";
    }
    virtual void SetFlyBehavior(std::unique_ptr<IFlyBehavior> flyBehavior)
    {
        m_FlyBehavior = std::move(flyBehavior);
    }
    virtual void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior)
    {
        m_QuackBehavior = std::move(quackBehavior);
    }

protected:
    std::unique_ptr<IFlyBehavior> m_FlyBehavior;
    std::unique_ptr<IQuackBehavior> m_QuackBehavior;
};

class MallardDuck : public IDuck
{
public:
    MallardDuck()
    {
        m_FlyBehavior = std::make_unique<FlyNoWay>();
        m_QuackBehavior = std::make_unique<SimpleQuack>();
    }

    void Display() override
    {
        std::cout << "I'm Mallard Duck !!! \n";
    }
};

class ModelDuck : public IDuck
{
public:
    ModelDuck()
    {
        m_FlyBehavior = std::make_unique<FlyWithWings>();
        m_QuackBehavior = std::make_unique<MuteQuack>();
    }

    void Display() override
    {
        std::cout << "I'm Model Duck !! \n";
    }
};

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int main()
{
    std::unique_ptr<IDuck> mallard = std::make_unique<MallardDuck>();
    mallard->Display();
    mallard->PerformFly();
    mallard->PerformQuack();
    std::cout << "\n";

    std::unique_ptr<IDuck> model = std::make_unique<ModelDuck>();
    model->Display();
    model->PerformFly();
    model->PerformQuack();
    std::cout << "\n";

    model->Display();
    model->SetFlyBehavior(std::make_unique<FlyNoWay>());
    model->SetQuackBehavior(std::make_unique<SqueakQuack>());
    model->PerformFly();
    model->PerformQuack();
    std::cout << "\n";

    return 0;
}