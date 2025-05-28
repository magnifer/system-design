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
    class Button
    {
    public:
        virtual void RenderButton() = 0;
    };
    class Checkbox
    {
    public:
        virtual void RenderCheckbox() = 0;
    };
}

namespace ConcreteProduct
{
    class WinButton : public Product::Button
    {
    public:
        void RenderButton() override
        {
            std::cout << "render button in windows style. \n ";
        }
    };
    class WinCheckbox : public Product::Checkbox
    {
    public:
        void RenderCheckbox() override
        {
            std::cout << "render checkbox in windows style. \n ";
        }
    };
    class MacButton : public Product::Button
    {
    public:
        void RenderButton() override
        {
            std::cout << "render button in mac style. \n";
        }
    };
    class MacCheckbox : public Product::Checkbox
    {
    public:
        void RenderCheckbox() override
        {
            std::cout << "render checkbox in mac style. \n";
        }
    };
}

namespace Creator
{
    class GUIFactory
    {
    public:
        virtual std::unique_ptr<Product::Button> CreateButton() = 0;
        virtual std::unique_ptr<Product::Checkbox> CreateCheckbox() = 0;
    };
}

namespace ConcreteCreator
{
    class WinFactory : public Creator::GUIFactory
    {
    public:
        std::unique_ptr<Product::Button> CreateButton() override
        {
            return std::make_unique<ConcreteProduct::WinButton>();
        }
        std::unique_ptr<Product::Checkbox> CreateCheckbox() override
        {
            return std::make_unique<ConcreteProduct::WinCheckbox>();
        }
    };
    class MacFactory : public Creator::GUIFactory
    {
    public:
        std::unique_ptr<Product::Button> CreateButton() override
        {
            return std::make_unique<ConcreteProduct::MacButton>();
        }
        std::unique_ptr<Product::Checkbox> CreateCheckbox() override
        {
            return std::make_unique<ConcreteProduct::MacCheckbox>();
        }
    };
}

class Application
{
public:
    Application(std::unique_ptr<Creator::GUIFactory> factory)
    {
        button = factory->CreateButton();
        checkbox = factory->CreateCheckbox();
    }
    void Render()
    {
        button->RenderButton();
        checkbox->RenderCheckbox();
    }

private:
    std::unique_ptr<Product::Button> button;
    std::unique_ptr<Product::Checkbox> checkbox;
};

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int main()
{
    std::string osType;
    std::cout << "Enter OS type (mac/windows): ";
    std::cin >> osType;

    std::unique_ptr<Creator::GUIFactory> factory;

    if (osType == "mac")
    {
        factory = std::make_unique<ConcreteCreator::MacFactory>();
    }
    else if (osType == "windows")
    {
        factory = std::make_unique<ConcreteCreator::MacFactory>();
    }
    else
    {
        std::cerr << "Unsupported OS type.\n";
        return 1;
    }
    Application app(std::move(factory));
    app.Render();
    std::cout << " ------------------------------------------- \n";

    // std::cout << "Client: Testing client code with the mac factory type:\n";
    // std::unique_ptr<ConcreteCreator::MacFactory> macFactory = std::make_unique<ConcreteCreator::MacFactory>();
    // Application app(std::move(macFactory));
    // app.Render();
    // std::cout << " ------------------------------------------- \n";

    // std::cout << "Client: Testing client code with the windows factory type:\n";
    // std::unique_ptr<ConcreteCreator::WinFactory> winFactory = std::make_unique<ConcreteCreator::WinFactory>();
    // Application app1(std::move(winFactory));
    // app1.Render();
    // std::cout << " ------------------------------------------- \n";

    return 0;
}