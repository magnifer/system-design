/*
The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
Strategy lets the algorithm vary independently from clients that use it.
*/

#include <iostream>

namespace Component
{
    class Beverages
    {
    public:
        virtual ~Beverages() = default;
        virtual std::string GetDescription() = 0;
        virtual double Cost() = 0;

    private:
        std::string m_vDescription;
    };
}

namespace ConcreteComponents
{
    class HouseBlend : public Component::Beverages
    {
    public:
        std::string GetDescription() override
        {
            return "House Blend ";
        }
        double Cost() override
        {
            return 1.22f;
        }
    };

    class DarkRoast : public Component::Beverages
    {
    public:
        std::string GetDescription() override
        {
            return "Dark Roast ";
        }
        double Cost() override
        {
            return 1.5f;
        }
    };

    class Espresso : public Component::Beverages
    {
    public:
        std::string GetDescription() override
        {
            return "Espresso ";
        }
        double Cost() override
        {
            return 1.5f;
        }
    };

    class Decaf : public Component::Beverages
    {
    public:
        std::string GetDescription() override
        {
            return "Decaf ";
        }
        double Cost() override
        {
            return 1.4f;
        }
    };
}

namespace Decorator
{
    class CondimentsDecorator : public Component::Beverages
    {
    public:
        virtual std::string GetDescription() = 0;
    };
}

namespace ConcreteDecorators
{
    class Milk : public Decorator::CondimentsDecorator
    {
    public:
        Milk(std::unique_ptr<Component::Beverages> beverage) : m_vBeverage(std::move(beverage)) {}
        std::string GetDescription() override
        {
            return m_vBeverage->GetDescription() + "Milk ";
        }
        double Cost() override
        {
            return m_vBeverage->Cost() + .6f;
        }

    private:
        std::unique_ptr<Component::Beverages> m_vBeverage;
    };

    class Mocha : public Decorator::CondimentsDecorator
    {
    public:
        Mocha(std::unique_ptr<Component::Beverages> beverage) : m_vBeverage(std::move(beverage)) {}
        std::string GetDescription() override
        {
            return m_vBeverage->GetDescription() + " Mocha ";
        }
        double Cost() override
        {
            return 0.5f + m_vBeverage->Cost();
        }

    private:
        std::unique_ptr<Component::Beverages> m_vBeverage;
    };

    class Soy : public Decorator::CondimentsDecorator
    {
    public:
        Soy(std::unique_ptr<Component::Beverages> beverage) : m_vBeverage(std::move(beverage)) {}
        std::string GetDescription() override
        {
            return m_vBeverage->GetDescription() + "Soy ";
        }
        double Cost() override
        {
            return m_vBeverage->Cost() + .4f;
        }

    private:
        std::unique_ptr<Component::Beverages> m_vBeverage;
    };

    class Whip : public Decorator::CondimentsDecorator
    {
    public:
        Whip(std::unique_ptr<Component::Beverages> beverage) : m_vBeverage(std::move(beverage)) {}
        std::string GetDescription() override
        {
            return m_vBeverage->GetDescription() + "Whip ";
        }
        double Cost() override
        {
            return m_vBeverage->Cost() + .5f;
        }

    private:
        std::unique_ptr<Component::Beverages> m_vBeverage;
    };
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int main()
{
    auto beverage = std::make_unique<ConcreteComponents::Espresso>();
    std::cout << beverage->GetDescription() << "$" << beverage->Cost() << "\n";

    std::unique_ptr<Component::Beverages> beverage1 = std::make_unique<ConcreteComponents::DarkRoast>();
    beverage1 = std::make_unique<ConcreteDecorators::Mocha>(std::move(beverage1));
    beverage1 = std::make_unique<ConcreteDecorators::Milk>(std::move(beverage1));
    std::cout << beverage1->GetDescription() << "$" << beverage1->Cost() << "\n";

    std::unique_ptr<Component::Beverages> beverage2 = std::make_unique<ConcreteComponents::HouseBlend>();
    beverage2 = std::make_unique<ConcreteDecorators::Mocha>(std::move(beverage2));
    beverage2 = std::make_unique<ConcreteDecorators::Milk>(std::move(beverage2));
    beverage2 = std::make_unique<ConcreteDecorators::Whip>(std::move(beverage2));
    std::cout << beverage2->GetDescription() << "$" << beverage2->Cost() << "\n";

    return 0;
}