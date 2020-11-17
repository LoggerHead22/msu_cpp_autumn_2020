#include "format.h"

class TestClass{
public:
	friend ostream& operator<<(ostream& stream, const TestClass&);
};

ostream& operator<<(ostream& stream, const TestClass&){
	stream<<"I'm test class";
	
	return stream;
} 


void TestCase1(){
	//Тест с базовыми типами 
	string s1 = format("{1}+{1} = {0}", 2, "one");
	assert(s1 == "one+one = 2");
	
	string s2 = format("{0}+{1}+{2} = {3}", "one", "two", "three", 6);
	assert(s2 == "one+two+three = 6");
	
	string s3 = format("{002}+{1}+{0} = {3} or {4}", 0.5, "two", 2.5, 6, "six");
	assert(s3 == "2.5+two+0.5 = 6 or six");
}


void TestCase2(){
	//Тест с произвольным объектом
	string s1 = format("{0} - not {1} or {2}", TestClass(), 2, "three");
	assert(s1 == "I'm test class - not 2 or three");
}

void TestCase3(){
	//Тест с некоректным расположением скобок
	bool catch_error = false;
	
    try{
        string s1 = format("{1}+{1}} =} {{0}", 2, "one");
    }catch(const BadStringFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;
	
	try{
        string s2 = format("{0}+{{1}}+{{2}} = {3}", "one", "two", "three", 6);
    }catch(const BadStringFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;
	
	try{
		string s3 = format("{{{{{2}+{1}+{0} = {3} or {4}}}}}", 0.5, "two", 2.5, 6, "six");
	}catch(const BadStringFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;	
}


void TestCase4(){
	//Тест с некоректным значением внутри скобок
	bool catch_error = false;
	
    try{
        string s1 = format("{-1}+{-1} = {0}", 2, "one");
    }catch(const BadValueFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;
	
	try{
        string s2 = format("{0}+{1}+{abc} = {def}", "one", "two", "three", 6);
    }catch(const BadValueFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;
	
	try{
		string s3 = format("{21}+{1}+{7} = {3} or {4}", 0.5, "two", 2.5, 6, "six");
	}catch(const BadValueFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;	
	
	try{
		string s4 = format("{}+{1}+{0.5} = {3} or {4}", 0.5, "two", 2.5, 6, "six");
	}catch(const BadValueFormat&){
        catch_error = true;
    }
    //проверим словилось ли исключение
    assert(catch_error);
	catch_error = false;	
}

int main()
{
	
	TestCase1();
	TestCase2();
	TestCase3();
	TestCase4();
	
	
    std::cout << "Success!\n";

    return 0;
}
