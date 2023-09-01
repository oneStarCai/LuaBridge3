#include <iostream>
#include <memory>

#include <lua.hpp>
//#include <LuaBridge/LuaBridge.h>
#include "../LuaBridge/LuaBridge.h"

class Test
{
public:
    Test(){
        data = 0
        std::cout << "this is Test:Test()" << std::endl;
    }
    void Print(){
        std::cout << "this is Test:Print()" << std::endl;
    }
    void PrintData() {
        std::cout << "this is PrintData:" << data << std::endl;
    }


    void SetData(int val){
        std::cout << "this is SetData(int)" << std::endl;
        data = val;
    }
    
    
    void SetData(int val, int v2){
        std::cout << "this is SetData(int, int)" << std::endl;
        data = val;
    }
    

    int GetData(){
        std::cout << "this is GetData" << std::endl;
        return data;
    }

private:
    void printTest(){
        std::cout << "this is printTest()" << std::endl;
    }

public:
    int data;
};

void runLua(lua_State* L, const std::string& script)
{
    if (luaL_loadstring(L, script.c_str()) != 0)
    {
        throw std::runtime_error(lua_tostring(L, -1));
    }

    if (lua_pcall(L, 0, 0, -2) != 0)
    {
        throw std::runtime_error(lua_tostring(L, -1));
    }
}

void runFile(lua_State* L, const std::string& file)
{
    if (luaL_loadfile(L, file.c_str()) != 0)
    {
        throw std::runtime_error(lua_tostring(L, -1));
    }

    if (lua_pcall(L, 0, 0, -2) != 0)
    {
        throw std::runtime_error(lua_tostring(L, -1));
    }
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luabridge::getGlobalNamespace(L)
        .beginClass<Test>("Test")
            .addConstructor<void (*)()>()
            .addFunction("Print", &Test::Print)
            .addFunction("PrintData", &Test::PrintData)
            .addFunction("SetData", luabridge::overload<int>(&Test::SetData), luabridge::overload<int, int>(&Test::SetData))
            .addFunction("GetData", &Test::GetData)
            .addProperty("data", &Test::data)
        .endClass();

    std::cout << "this is main." << std::endl;

    //Test t;
    //luabridge::setGlobal(L, &t, "t");
    //runLua(L, "t = Test(); t:Print()");

    auto t = std::make_shared<Test>();
    //auto t = new Test;
    std::cout << "make shared Test" << std::endl;

    luabridge::setGlobal(L, /*t.get()*/t, "t");
    std::cout << "set global t" << std::endl;

    runLua(L, "t:Print()");

    std::cout << "now run file test.lua" << std::endl;

    Test t2;
    Test& tt = t2;
    luabridge::setGlobal(L, tt, "tt");

    runFile(L, "test.lua");

    std::cout << "after:" << t->data << std::endl;

    return 0;
}