#include <algorithm>
#include <vector>
#include <queue>

#define EMPTY 0
#define BLACK 1
#define RED 2
#define COLUMN_SIZE 6
#define ROW_SIZE 7


class Board
{
public:
	Board();
	void SetPos(int position, unsigned int player);
	unsigned int GetPos(int row, int col);
	std::queue<unsigned int> GetPossibleMoves();
	unsigned int GetStreakTotalFromPos(unsigned int position, unsigned int player);
	std::vector<unsigned int> GetWinningMoves(std::queue<unsigned int> possibleMoves, unsigned int player);
	unsigned int GetUtility(Board& state, unsigned int player);
	unsigned int maxValue(Board& state, int limit, unsigned int player);
	unsigned int minValue(Board& state, int limit, unsigned int player);
	unsigned int minimaxDecision(Board& state, unsigned int limit, unsigned int player);

private:
	unsigned int m_Board[ROW_SIZE*COLUMN_SIZE];
};