#include "Renderer.h"
#include "Objects.h"
#include "GlobalValues.h"
#include "Graphics.h"
#include <random>

static unsigned int font5x3[] = { 32319,17393,24253,32437,31879,30391,29343,31905,32447,31911 };


Renderer::Renderer()
{
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



void Renderer::RenderGame(GameInfo game, unsigned int * pixelBuffer, unsigned int zoom)
{
	Graphics g = Graphics();
	_renderTick++;

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

	char display[CAVE_WIDTH][(INFO_HEIGHT + CAVE_HEIGHT)];
	memset(display, 0, (INFO_HEIGHT + CAVE_HEIGHT) * CAVE_WIDTH);

	//cave part:

	for (int y = 0; y < CAVE_HEIGHT; y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			int field = game.cavemap[x][y];

			if (game.Tick < START_DELAY)
				if (field == BD_INBOX)
					if (game.Tick % 20 < 10)
						field = BD_STEELWALL;


			if (game.Tick < UNCOVER_LOOP)
			{
				if (game.covered[x][y])
				{
					field = BD_STEELWALL;
				}
			}

			display[x][y] = field;
		}
	}

	//info part:

	for (int y = CAVE_HEIGHT; y < (CAVE_HEIGHT + INFO_HEIGHT); y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			display[x][y] = BD_STEELWALL;
		}
	}

	if ((game.DiamondsRequired - game.DiamondsCollected) > 0)
		RenderNum(game.DiamondsRequired - game.DiamondsCollected, 1, 22, 3, 0, BD_COLOR_PURPLE, BD_BOULDER, display);

	if ((game.CaveTime - (game.Tick / 8)) > 0)
		RenderNum(game.CaveTime - (game.Tick / 8), 28, 22, 3, 0, BD_MAGICWALL, BD_BOULDER, display);



	// render to pixelbuffer
	for (int y = 0; y < (INFO_HEIGHT + CAVE_HEIGHT); y++)
	{
		for (int x = 0; x < CAVE_WIDTH; x++)
		{
			int colors[3];
			g.GetColors(display[x][y], _renderTick, colors);

			unsigned int col = (colors[0] << 16) + (colors[1] << 8) + colors[2];

			unsigned int start = y*zoom*CAVE_WIDTH*zoom + x*zoom;
			unsigned int end = start + zoom*zoom*CAVE_WIDTH;

			for (unsigned int a = start; a < end; a += CAVE_WIDTH*zoom)
			{
				for (unsigned int b = a; b < a + zoom; b++)
				{
					pixelBuffer[b] = col;
				}
			}
		}
	}
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




