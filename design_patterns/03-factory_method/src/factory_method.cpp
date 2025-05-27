/*
 * The Factory Method Pattern defi nes an interface for creating an object, but lets subclasses decide which
 * class to instantiate. Factory Method lets a class defer instantiation to subclasses.
 * All factory patterns encapsulate object creation. The Factory Method Pattern encapsulates
 * object creation by letting subclasses decide what objects to create.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>

namespace Product
{
    class Pizza
    {
    public:
        virtual void Prepare()
        {
            std::cout << "Preparing " << m_szName << "\n";
            std::cout << "Tossing Dough \n";
            std::cout << "Adding Sauce \n";
            std::cout << "Adding Toppings: \n";
            for (auto topping : m_vToppings)
            {
                std::cout << "* " << topping << "\n";
            }
        }
        virtual void Bake()
        {
            std::cout << "Bake for 25 min at 175 degree \n";
        }
        virtual void Cut()
        {
            std::cout << "Cut in Diagonal slices \n";
        }
        virtual void Box()
        {
            std::cout << "Place pizza in official PizzaStore box \n";
        }
        virtual std::string GetName() { return m_szName; };

    protected:
        std::string m_szName;
        std::string m_szDough;
        std::string m_szSauce;
        std::vector<std::string> m_vToppings;
    };
}

namespace ConcreteProduct
{
    class NYStyleCheesePizza : public Product::Pizza
    {
    public:
        NYStyleCheesePizza()
        {
            m_szName = "Ny Style Cheese Pizza";
            m_szDough = "Thin Crust Dough";
            m_szSauce = "Marinara Sauce";

            m_vToppings.emplace_back("Grated Reggiano Cheese");
            m_vToppings.emplace_back("Shredded Mozzarella Cheese");
        }
    };

    class NYStyleClamPizza : public Product::Pizza
    {
    public:
        NYStyleClamPizza()
        {
            m_szName = "Ny Style Clam, Pizza";
            m_szDough = "Thin Crust Dough";
            m_szSauce = "Marinara Sauce";

            m_vToppings.emplace_back("Grated Reggiano Cheese");
            m_vToppings.emplace_back("Shredded Mozzarella Cheese");
        }
    };
    class NYStyleVeggiePizza : public Product::Pizza
    {
    public:
        NYStyleVeggiePizza()
        {
            m_szName = "Ny Style Veggie, Pizza";
            m_szDough = "Thin Crust Dough";
            m_szSauce = "Marinara Sauce";

            m_vToppings.emplace_back("Basil, Olive Oil");
            m_vToppings.emplace_back("Mushroom & Jalapeno");
            m_vToppings.emplace_back("Shredded Mozzarella Cheese");
        }
    };

    class ChicagoStyleVeggiePizza : public Product::Pizza
    {
    public:
        ChicagoStyleVeggiePizza()
        {
            m_szName = "Ny Style Veggie, Pizza";
            m_szDough = "Thin Crust Dough";
            m_szSauce = "Marinara Sauce";

            m_vToppings.emplace_back("Basil, Olive Oil");
            m_vToppings.emplace_back("Shredded Mozzarella Cheese");
        }
    };
}

namespace Creator
{
    class PizzaStore
    {
    public:
        virtual std::unique_ptr<Product::Pizza> CreatePizza(std::string item) = 0;
        virtual std::unique_ptr<Product::Pizza> OrderPizza(std::string type)
        {
            auto pizza = CreatePizza(type);
            if (pizza == nullptr)
            {
                std::cout << "Sorry, we don't make that type of pizza.\n";
                return nullptr;
            }
            pizza->Prepare();
            pizza->Bake();
            pizza->Cut();
            pizza->Box();

            return pizza;
        }
    };
}

namespace ConcreteCreator
{
    class NYPizzaStore : public Creator::PizzaStore
    {
    protected:
        std::unique_ptr<Product::Pizza> CreatePizza(std::string item) override
        {
            if (item.compare("cheese") == 0)
            {
                return std::make_unique<ConcreteProduct::NYStyleCheesePizza>();
            }
            else if (item.compare("clam") == 0)
            {
                return std::make_unique<ConcreteProduct::NYStyleClamPizza>();
            }
            else if (item.compare("veggie") == 0)
            {
                return std::make_unique<ConcreteProduct::NYStyleVeggiePizza>();
            }
            else
                return nullptr;
        }
    };
    class ChicagoPizzaStore : public Creator::PizzaStore
    {
    protected:
        std::unique_ptr<Product::Pizza> CreatePizza(std::string item) override
        {
            if (item.compare("veggie") == 0)
            {
                return std::make_unique<ConcreteProduct::ChicagoStyleVeggiePizza>();
            }
            else
                return nullptr;
        }
    };
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int main()
{
    std::unique_ptr<Creator::PizzaStore> nyPizzaStore = std::make_unique<ConcreteCreator::NYPizzaStore>();
    std::unique_ptr<Creator::PizzaStore> chicagoPizzaStore = std::make_unique<ConcreteCreator::ChicagoPizzaStore>();

    std::unique_ptr<Product::Pizza> pizza = nyPizzaStore->OrderPizza("cheese");
    std::cout << "Ethan's order " << pizza->GetName() << "is ready \n";
    std::cout << " ------------------------------------------- \n";

    std::unique_ptr<Product::Pizza> pizza1 = chicagoPizzaStore->OrderPizza("veggie");
    std::cout << "John's order " << pizza1->GetName() << "is ready \n";
    std::cout << " ------------------------------------------- \n";

    std::unique_ptr<Product::Pizza> pizza2 = chicagoPizzaStore->OrderPizza("cheese");
    if (pizza2 != nullptr)
        std::cout << "Ethan's order " << pizza2->GetName() << "is ready \n";
    else
        std::cout << "We don't have this pizza type!!! \n";
    std::cout << " ------------------------------------------- \n";

    return 0;
}