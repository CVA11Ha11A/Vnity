#include "pch.h"
#include "Test001.h"

#include "VTimeManager.h"
#include "VResourceManager.h"

Test001::Test001()
{
	SetPos(Vector2(500.f, 500.f));
	SetScale(Vector2(100.f, 100.f));
}

Test001::~Test001()
{
}


void Test001::Awake()
{	
	StartCoroutine<Test001>(&Test001::CoroutineTest, this);
}

void Test001::Start()
{

}

void Test001::Update()
{

}

void Test001::Render(HDC _dc)
{
	VObject::Render(_dc);
}

void Test001::CoroutineTest()
{
	static int routineBrance = 1;

	static int CallCount = 0;
	switch (routineBrance)
	{
	case 1:
	{
		Vector2 pos = Vector2(GetPos().x + (1000 * DeltaTime), GetPos().y);
		SetPos(pos);
		CallCount += 1;
		new VWaitForSecond(0.1f);
		if (CallCount > 15) { routineBrance += 1; }

	}
	break;
	case 2:
	{
		int a = 0;
	}
	break;
	default:
	{
		int i = 0;
	}
		break;
	} // switch

}		// CoroutineTest()


