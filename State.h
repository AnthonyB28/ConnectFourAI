#define EMPTY 0
#define BLACK 1
#define RED 2
#define COLUMN_SIZE 6
#define ROW_SIZE 7
#include <algorithm>

// Terminal state has a utility value
// Non terminal state uses an eval function

struct State
{
	Board m_Board;
	bool m_Terminal = false;
};

struct Board
{
	Board()
		:m_Board()
	{
		std::fill_n(m_Board, COLUMN_SIZE * ROW_SIZE, 0);
	}
	unsigned int m_Board[COLUMN_SIZE * ROW_SIZE];

	void SetElement(int row, int col, unsigned int value)
	{
		m_Board[ROW_SIZE * row + col] = value;
	}

	unsigned int GetPos(int row, int col)
	{
		return m_Board[ROW_SIZE * row + col];
	}

	unsigned int maxValue(State& state)
	{

	}

	unsigned int minValue(State& state)
	{

	}

	// return an action 0 - 6
	unsigned int minimaxDecision(State& state, unsigned int limit)
	{
		for (int i = 0; i < 7; ++i)
		{

		}
	}
};