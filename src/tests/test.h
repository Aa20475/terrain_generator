#pragma once

#include<vector>
#include<functional>
#include<string>
#include<iostream>

namespace test
{
    class Test{
    public:
        Test(){}
        virtual ~Test(){}

        virtual void onUpdate(float deltaTime){}
        virtual void onRender(){}
        virtual void onImGuiRender(){}
    };

    class TestMenu : public Test {
    public:
        TestMenu(Test*& currentTestPointer);

        void onImGuiRender() override;

        template<typename T>
        void registerTest(const std::string& name ){
            std::cout<<"Registering " + name<<std::endl;
            m_tests.push_back(std::make_pair(name, [](){return new T();}));
        }
    private:
        Test*& m_currentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
    };
} // namespace test
