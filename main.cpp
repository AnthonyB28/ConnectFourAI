#include <stdio.h>
#include "Board.h"

int main(int argc, const char* argv[])
{
	Board connectFourBoard;
	int player = 1;
	for (int i = 0; i < 14; ++i) // 14 turns
	{
		int movePos = connectFourBoard.minimaxDecision(connectFourBoard, 3, player);
		connectFourBoard.SetPos(movePos, player);
		player = (player % 2) + 1;
	}
}