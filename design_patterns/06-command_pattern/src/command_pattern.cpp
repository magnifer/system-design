/**
 * The Command Pattern encapsulates a request as an object,
 * thereby letting you parameterize other objects with different requests,
 * queue or log requests, and support undoable operations.
 */

#include <iostream>
#include <vector>

namespace Receiver
{
    class Light
    {
    public:
        Light()
        {
            std::cout << "Default Constructor : Receiver::Light \n";
        };
        Light(const std::string &szLight) : m_szLight(szLight)
        {
            std::cout << "Light created for: " << m_szLight << std::endl;
            std::cout << "Parameterized Constructor : " << m_szLight << " \n";
        };
        void On()
        {
            std::cout << m_szLight << " is ON.\n";
        }
        void Off()
        {
            std::cout << m_szLight << " is OFF.\n";
        }
        std::string GetName()
        {
            return m_szLight;
        }

    private:
        std::string m_szLight;
    };
}

namespace Commands
{
    class ICommand
    {
    public:
        virtual ~ICommand() {};
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };

    class NoCommand : public ICommand
    {
    public:
        void Execute() override
        {
            std::cout << "No command assigned to this button.\n";
        }
        void Undo() override
        {
            std::cout << "No command assigned Undo does nothing .\n";
        }
    };
    class LightOnCommand : public ICommand
    {
    public:
        LightOnCommand(Receiver::Light &light) : m_light(light)
        {
            std::cout << "Parameterized Constructor : " << m_light.GetName() << "LightOnCommand \n";
        }
        void Execute() override
        {
            m_light.On();
        }
        void Undo() override
        {
            m_light.Off();
        }

    private:
        Receiver::Light &m_light;
    };

    class LightOffCommand : public ICommand
    {

    public:
        LightOffCommand(Receiver::Light &light) : m_light(light)
        {
            std::cout << "Parameterized Constructor : " << m_light.GetName() << "LightOffCommand \n";
        };

        void Execute() override
        {
            m_light.Off();
        }
        void Undo() override
        {
            m_light.On();
        }

    private:
        Receiver::Light &m_light;
    };
}

namespace Invoker
{
    class RemoteControl
    {
    public:
        RemoteControl()
        {
            std::cout << "Default Constructor : RemoteControl \n";
            std::shared_ptr<Commands::ICommand> noCommand = std::make_shared<Commands::NoCommand>();
            m_vOnCommands.resize(slotCount, noCommand);
            m_vOffCommands.resize(slotCount, noCommand);
            undoCommand = noCommand;
            std::cout << "Default Constructor : RemoteControl initialized with NoCommand.\n";
        }

        void SetCommand(int slot, std::shared_ptr<Commands::ICommand> onCommand,
                        std::shared_ptr<Commands::ICommand> offCommand)
        {
            if (slot >= m_vOnCommands.size())
            {
                m_vOnCommands.resize(slot + 1, std::make_shared<Commands::NoCommand>());
                m_vOffCommands.resize(slot + 1, std::make_shared<Commands::NoCommand>());
            }
            m_vOnCommands[slot] = onCommand;
            m_vOffCommands[slot] = offCommand;
        }

        void OnButtonPressed(int slot)
        {
            if (slot >= 0 && slot < m_vOnCommands.size())
            {
                m_vOnCommands[slot]->Execute();
                undoCommand = m_vOnCommands[slot];
            }
            else
            {
                std::cerr << "Invalid slot: " << slot << "\n";
            }
        }

        void OffButtonPressed(int slot)
        {
            if (slot >= 0 && slot < m_vOffCommands.size())
            {
                m_vOffCommands[slot]->Execute();
                undoCommand = m_vOffCommands[slot];
            }
            else
            {
                std::cerr << "Invalid slot: " << slot << "\n";
            }
        }
        void UndoButtonWasPushed()
        {
            std::cout << "Undoing last command:\n";
            undoCommand->Undo();
        }

    private:
        static constexpr int slotCount = 5;
        std::vector<std::shared_ptr<Commands::ICommand>> m_vOnCommands;
        std::vector<std::shared_ptr<Commands::ICommand>> m_vOffCommands;
        std::shared_ptr<Commands::ICommand> undoCommand;
    };
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int main()
{
    Receiver::Light KitchenLight("Kitchen light! ");
    Receiver::Light livingRoomLight("Living Room light! ");

    auto KitchenOn = std::make_shared<Commands::LightOnCommand>(KitchenLight);
    auto KitchenOff = std::make_shared<Commands::LightOffCommand>(KitchenLight);

    auto livingRoomOn = std::make_shared<Commands::LightOnCommand>(livingRoomLight);
    auto livingRoomOff = std::make_shared<Commands::LightOffCommand>(livingRoomLight);

    Invoker::RemoteControl remote;
    remote.SetCommand(0, KitchenOn, KitchenOff);
    remote.SetCommand(1, livingRoomOn, livingRoomOff);

    remote.OnButtonPressed(0);
    remote.OffButtonPressed(0);
    remote.UndoButtonWasPushed();

    remote.OnButtonPressed(1);
    remote.UndoButtonWasPushed();
    remote.OffButtonPressed(1);

    return 0;
}