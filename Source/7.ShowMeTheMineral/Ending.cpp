#include "DXUT.h"
#include "SDKmisc.h"
#include "Ending.h"
#include "ObjectManager.h"

Ending::Ending()
{
	Create();
}


Ending::~Ending()
{
}

void Ending::Create()
{
	pEnding = new Object(OBJMANAGER()->GetTexture(GaBase::TextureID::ENDING), 1024, 768, 0, 0);
	nCharCount = 0;
}

void Ending::Update()
{
	KeyProc();
}

void Ending::Render()
{
	pEnding->Render(OBJMANAGER()->GetSprite());

	CDXUTTextHelper txtTimer(OBJMANAGER()->GetFontTime(), OBJMANAGER()->GetSprite(), 75);
	txtTimer.Begin();
	txtTimer.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.8f));
	txtTimer.SetInsertionPos(450, 227);
	txtTimer.DrawFormattedTextLine(L"%d", OBJMANAGER()->GetScore());
	txtTimer.SetForegroundColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
	txtTimer.SetInsertionPos(180, 360);
	txtTimer.DrawTextLine(L"NAME : ");
	for (int i = 0; i < nCharCount; i++)
	{
		txtTimer.SetInsertionPos(400 + i*50, 360);
		txtTimer.DrawFormattedTextLine(L"%c", OBJMANAGER()->CurrentPlayer[i]);
	}
	txtTimer.End();
}

void Ending::KeyProc()
{
	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i) & 0x0001)
		{
			OBJMANAGER()->CurrentPlayer[nCharCount] = i;
			nCharCount++;
		}
	}
	if (nCharCount > 3)
	{
		nCharCount = 0;
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		OBJMANAGER()->SetScene(ObjectManager::SceneState::MENU);
		if (OBJMANAGER()->GetScore() >= OBJMANAGER()->FirstScore)
		{
			OBJMANAGER()->ThirdScore = OBJMANAGER()->SecondScore;
			for (int i = 0; i < 3; i++)
			{
				OBJMANAGER()->ThirdPlayer[i] = OBJMANAGER()->SecondPlayer[i];
			}
			
			OBJMANAGER()->SecondScore = OBJMANAGER()->FirstScore;
			for (int i = 0; i < 3; i++)
			{
				OBJMANAGER()->SecondPlayer[i] = OBJMANAGER()->FirstPlayer[i];
			}
			
			OBJMANAGER()->FirstScore = OBJMANAGER()->GetScore();
			for (int i = 0; i < 3; i++)
			{
				OBJMANAGER()->FirstPlayer[i] = OBJMANAGER()->CurrentPlayer[i];
			}
		}
		else if (OBJMANAGER()->GetScore() >= OBJMANAGER()->SecondScore)
		{
			OBJMANAGER()->ThirdScore = OBJMANAGER()->SecondScore;
			for (int i = 0; i < 3; i++)
			{
				OBJMANAGER()->ThirdPlayer[i] = OBJMANAGER()->SecondPlayer[i];
			}

			OBJMANAGER()->SecondScore = OBJMANAGER()->GetScore();
			for (int i = 0; i < 3; i++)
			{
				OBJMANAGER()->SecondPlayer[i] = OBJMANAGER()->CurrentPlayer[i];
			}
		}
		else if (OBJMANAGER()->GetScore() >= OBJMANAGER()->ThirdScore)
		{
			OBJMANAGER()->ThirdScore = OBJMANAGER()->GetScore();
			for (int i = 0; i < 3; i++)
			{
				OBJMANAGER()->ThirdPlayer[i] = OBJMANAGER()->CurrentPlayer[i];
			}
		}
	}
}