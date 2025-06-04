/**
 * The Singleton Pattern ensures a class has only one instance, and provides a global point of access to it.
 */

#include <iostream>

namespace SingletonPattern
{
    class Singleton
    {
    public:
        /**
         * Delete copy & move constructors to prevent creating a copy of an instance
         * by any means
         */
        Singleton(const Singleton &) = delete;
        Singleton &operator=(const Singleton &) = delete;
        Singleton(const Singleton &&) = delete;
        Singleton &operator=(const Singleton &&) = delete;
        ~Singleton()
        {
            created = false;
        }
        /**
         * Override new operator; this stops heap allocation completely.
         * But this also prevents static Singleton instance;
         * from compiling if it's on the heap, so use carefully
         */
        void *operator new(std::size_t) = delete;
        void operator delete(void *) = delete;

        static Singleton &GetInstance()
        {
            static Singleton uniqueInstance;
            return uniqueInstance;
        }

        void DoSomething()
        {
            std::cout << "accessing this using a singleton isntance!!! \n";
        }

#ifdef UNIT_TEST_SINGLETON
        // to make unit test for Singleton
        void ResetStateForTesting()
        {
            // Reset internal testable state here
            counter = 0;
        }
        int counter = 0;
#endif

    private:
        Singleton()
        {
            /**
             * what if someone create an object by creating a FRIEND CLASS of Singleton?
             * class SingletonFactory {
             * public:
             *   Singleton* Create() {
             *        return new Singleton();  // legal due to friendship
             *   }
             * };
             *
             * By throwing error in private constructor we can ensure that it's not called again.
             */
            if (created)
            {
                throw std::runtime_error("Instance already created!");
            }
            else
            {
                std::cout << "Singleton is Initialized! \n";
                created = true;
            }
        }

        static inline bool created = false;
    };
}

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
int main()
{
    auto &SingletonInstance = SingletonPattern::Singleton::GetInstance();
    SingletonInstance.DoSomething();

#ifdef UNIT_TEST_SINGLETON
    SingletonInstance.counter++;

    /**
     * DO some unit test logic
     */

    SingletonInstance.ResetStateForTesting();
#endif

    return 0;
}