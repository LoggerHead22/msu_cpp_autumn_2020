#include "bigint.h"
#include <cassert>

void constructorTest(){
	BigInt b1 = BigInt("1250519");
	BigInt b2 = b1;
	
	assert(b2 == 1250519);
	assert(b1 == 1250519);
	
	BigInt b3 = move(b1);
	
	assert(b3 == 1250519);
	assert(b1 != 1250519);
	
	BigInt b4 = 10;
	b4 += (b2 + 481)*(b3 - 519);    //1251000*1250000 + 10
	assert(b4 == BigInt("1563750000010"));
}

void LessEqTest(){
	
	assert(BigInt("123456789012") <  BigInt("1234567891013"));
	assert(BigInt("123456789012") <= BigInt("1234567891012"));
	assert(BigInt("100") < BigInt("1234567891012"));
	assert(BigInt("100") <= BigInt("1234567891012"));
	
	assert(BigInt("-123456789012") <  BigInt("1234567890123"));
	assert(BigInt("-123456789012") <= BigInt("1234567890123"));
	assert(BigInt("-1234567890123") <= BigInt("-1234567890123"));
	assert(BigInt("-1234567890124") <  BigInt("-1234567890123"));
	
	assert(BigInt("-123456") < -123455);
	assert(BigInt("123456") <= 123456);
	assert(BigInt("123456") < 1234567);
	assert(BigInt("0") <= 0);
}


void GreatherEqTest(){
	
	assert(BigInt("123456789013") >  BigInt("123456789012"));
	assert(BigInt("123456789012") >= BigInt("123456789012"));
	assert(BigInt("1234567891012") > BigInt("100"));
	assert(BigInt("1234567891012") >= BigInt("100"));
	
	assert(BigInt("123456789011") >  BigInt("-123456789012"));
	assert(BigInt("123456789012") >= BigInt("-123456789012"));
	assert(BigInt("-1234567890123") >= BigInt("-1234567890123"));
	assert(BigInt("-1234567890123") >  BigInt("-1234567890124"));
	
	assert(BigInt("-123455") > -123456);
	assert(BigInt("123456") >= 123456);
	assert(BigInt("1234567") > 1234566);
	assert(BigInt("0") >= 0);
}


void EqualTest(){
	
	assert(BigInt("123456789013") == BigInt("123456789013"));
	assert(BigInt("-123456789013") == BigInt("-123456789013"));
	assert(BigInt("123456789013") != BigInt("-123456789013"));
		
	assert(BigInt("1234567891012") != BigInt("100"));
	assert(BigInt("-1234567891012") != BigInt("100"));
	
	assert(BigInt("987654") != BigInt("123456"));
	
	assert(BigInt("-123455") == -123455);
	assert(BigInt("123456") != -123456);
	assert(BigInt("-123457") != 123457);
	assert(BigInt("0") == 0);
}

void AddTest(){
	
	BigInt t1 = 1234;
	BigInt t2 = -234;	
	
	assert(t1 + t2 == 1000);
	
	t1 = BigInt("125000519");
	t2 = BigInt("-125000716");
	
	assert(t1 + t2 == BigInt("-197"));
	
	t1 = BigInt("123000789000456000");
	t2 = BigInt("456000123000789");
	
	assert(t1 + t2 == BigInt("123456789123456789"));
	
	t1 = BigInt("123456000123456");
	t2 = BigInt("-123456000123456");
	
	assert(t1 + t2 == 0);
	
	t1 = BigInt("111111111111111");
	t2 = BigInt("1234321234321");

	assert(t1 + t2 == BigInt("112345432345432"));	
}

void SubTest(){
	
	BigInt t1 = 1234;
	BigInt t2 = 234;	
	
	assert(t1 - t2 == 1000);
	
	t1 = BigInt("125000519");
	t2 = BigInt("125000716");
	
	assert(t1 - t2 == BigInt("-197"));
	
	t1 = BigInt("123000789000456000");
	t2 = BigInt("-456000123000789");
	
	assert(t1 - t2 == BigInt("123456789123456789"));
	
	t1 = BigInt("123456000123456");
	t2 = BigInt("123456000123456");
	
	assert(t1 - t2 == 0);
	
	t1 = BigInt("-111111111111111");
	t2 = BigInt("1234321234321");

	assert(t1 - t2 == BigInt("-112345432345432"));	
}

void MultiplyTest(){
	
	BigInt t1 = 56398;
	BigInt t2 = 27119;	
	
	assert(t1 * t2 == 1529457362);
	
	t1 = BigInt("125000519");
	assert((t1 * 2) == 250001038);
	
	t1 = BigInt("123000789000456000");
	t2 = BigInt("-456000123000789");
	
	assert(t1 * t2 == BigInt("-56088374913402030678609359784000"));
	
	t1 = BigInt("123456000123456");
	t2 = BigInt("-123456000123456");
	
	assert(t1 * -1 == t2);
	
	t1 = BigInt("123456000123456");
	t2 = BigInt("0");
	
	assert(t1 * t2 == 0);
	
	t1 = BigInt("-10101010101010101010");
	t2 = BigInt("10101010101010101010");

	assert(t1 * t2 == BigInt("-102030405060708091009080706050403020100"));	
}


void uMinusTest(){
	BigInt b1 = BigInt("1250519");
	assert(-b1 == BigInt("-1250519"));
	
	BigInt b2 = BigInt("-1250255");
	assert(-b2 == BigInt("1250255"));
	
	BigInt b3 = BigInt("0");
	assert(-b3 == BigInt("0"));
}

void streamTest(){
	cout<<"StreamTest: "<<endl;
	BigInt b1 = BigInt("1250519");
	cout<<b1;
	BigInt b2 = BigInt("-1250255");
	cout<<b2;
	BigInt b3 = BigInt("-98765432123");
	cout<<b3;
}




int main(){
	EqualTest();
	LessEqTest();
	GreatherEqTest();
	AddTest();
	SubTest();
	streamTest();
	uMinusTest();
	MultiplyTest();
	constructorTest();
	
    cout<<"Success!"<<endl;
    return 0;
}
