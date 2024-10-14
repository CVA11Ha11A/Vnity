#include "pch.h"
#include "Test001.h"

#include "VTimeManager.h"
#include "VResourceManager.h"

Test001::Test001()
{
}

Test001::~Test001()
{
}


void Test001::Awake()
{	
	void (Test001::*_func)(void) = &Test001::CoroutineTest;
	StartCoroutine(_func);
}

void Test001::Start()
{

}

void Test001::Update()
{

}

void Test001::Render()
{
}

void Test001::CoroutineTest()
{
	int a = 0;
}


