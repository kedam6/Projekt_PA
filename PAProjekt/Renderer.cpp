#include "Renderer.h"
#include "GameObjects.h"
#include "GlobalValues.h"
#include "Graphics.h"
#include <random>

//font dla liczb 1 2 3 4 5 6 7 8 9 0
static unsigned int font5x3[] = { 32319,17393,24253,32437,31879,30391,29343,31905,32447,31911 };


Renderer::Renderer()
{
}

Renderer::Renderer(ColorRepository repo)
{
	this->colorRepo = repo;
}


Renderer::~Renderer()
{
}


void RenderDigit(int x, int y, int digit, int typea, int typeb, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)])
{
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<5; j++)
		{
			if (digit == -1)
				display[x + i][y + j] = typeb;
			else
			{
				if (font5x3[digit] & (1 << (i * 5 + j)))
				{
					display[x + i][y + j] = typea;
				}
				else
				{
					display[x + i][y + j] = typeb;
				}

			}
		}
	}
}

void RenderDigits(int x, int y, const char *text, int typea, int typeb, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)])
{
	while (*text)
	{
		RenderDigit(x, y, (*text) - 48, typea, typeb, display);
		x += 4;
		text++;
	}

}

void Renderer::HandleUncover(GameInfo& game)
{
	if (game.Tick < UNCOVER_LOOP)
	{
		for (int line = 0; line < CAVE_HEIGHT; line++)
		{
			int pos = rand() % CAVE_WIDTH;
			game.covered[pos][line] = 0;
			pos = rand() % CAVE_WIDTH;
			game.covered[pos][line] = 0;
			pos = rand() % CAVE_WIDTH;
			game.covered[pos][line] = 0;
			pos = rand() % CAVE_WIDTH;
			game.covered[pos][line] = 0;
		}
	}
}

void Renderer::WriteCavePart(GameInfo& game, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)])
{
	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			int field = game.cavemap[x][y];

			if (game.Tick < START_DELAY)
				if (field == DATA_INBOX)
					if (game.Tick % 20 < 10)
						field = DATA_STEELWALL;


			if (game.Tick < UNCOVER_LOOP)
			{
				if (game.covered[x][y])
				{
					field = DATA_STEELWALL;
				}
			}

			display[x][y] = field;
		}
	}
}

void Renderer::CreateDisplay(char ret[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)])
{
	memset(ret, 0, (INFO_HEIGHT + CAVE_HEIGHT) * CAVE_WIDTH);
}

void Renderer::WriteInfoPart(GameInfo& game, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)])
{
	for (int y = CAVE_HEIGHT; y < (CAVE_HEIGHT + INFO_HEIGHT); y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			display[x][y] = DATA_STEELWALL;
		}
	}

	if ((game.DiamondsRequired - game.DiamondsCollected) > 0)
		RenderNum(game.DiamondsRequired - game.DiamondsCollected, 1, 22, 3, 0, DATA_COLOR_PURPLE, DATA_BOULDER, display);

	if ((game.CaveTime - (game.Tick / 8)) > 0)
		RenderNum(game.CaveTime - (game.Tick / 8), 28, 22, 3, 0, DATA_MAGICWALL, DATA_BOULDER, display);
}

void Renderer::WriteToPixelBuffer(char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)], unsigned int zoom, unsigned int* pixelBuffer)
{
	for (int y = 0; y < (INFO_HEIGHT + CAVE_HEIGHT); y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			int colors[3];

			colorRepo.GetColors(display[x][y], _renderTick, colors);

			//kodowanie koloru
			unsigned int col = (colors[0] << 16) + (colors[1] << 8) + colors[2];
			//kwadrat ktory malujemy
			unsigned int start = y * zoom * CAVE_WIDTH * zoom + x * zoom;
			unsigned int end = start + zoom * zoom * CAVE_WIDTH;

			for (unsigned int a = start; a < end; a += CAVE_WIDTH * zoom)
			{
				for (unsigned int b = a; b < a + zoom; b++)
				{
					pixelBuffer[b] = col;
				}
			}
		}
	}
}

void Renderer::RenderGame(GameInfo& game, PixelBuffer& pixelBuffer, unsigned int zoom)
{
	_renderTick++;

	//w zasadzie to tylko wymazuje z danych to co nie ma byc widoczne (efekt szumu)
	HandleUncover(game);

	//tablica calego ekranu, jako ze nie ma tekstur tutaj zapisuje id przedmiotow ktore sie znajda na ekranie
	char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)];
	CreateDisplay(display);

	//cave:
	WriteCavePart(game, display);
	//info:
	WriteInfoPart(game, display);

	WriteToPixelBuffer(display, zoom, pixelBuffer.GetBuffer());
}

void Renderer::RenderNum(int number, int x, int y, int length, int pad, int typea, int typeb, char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)])
{
	char s[10];
	snprintf(s, 10, "%i", (int)number);

	int len = strlen(s);

	if (length < len) {
		int i;
		for (i = 0; i < length; i++) {
			RenderDigit(x, y, -1, typea, typeb, display);
			x += 4;
		}
		return;
	}
	int i;
	for (i = 0; i < length - len; i++) {
		RenderDigit(x, y, pad, typea, typeb, display);
		x += 4;
	}

	RenderDigits(x, y, (char*)s, typea, typeb, display);
}




