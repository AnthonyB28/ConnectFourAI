#define EMPTY 0
#define BLACK 1
#define RED 2
#define COLUMN_SIZE 6
#define ROW_SIZE 7
#include <algorithm>
#include <vector>
#include <queue>

// Terminal state has a utility value
// Non terminal state uses an eval function

struct State
{
	Board m_Board;
	unsigned int m_Priority = 0;
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

	unsigned int minValue(State& state, int target)
	{

	}

	std::queue<unsigned int> GetPossibleMoves()
	{
		std::queue<unsigned int> validEmptyPos;
		for (int i = 0; i < COLUMN_SIZE * ROW_SIZE; ++i)
		{
			if (m_Board[i] == 0) // empty
			{
				// Valid move
				if (m_Board[i + 7] == 1 || m_Board[i + 7] == 1)
				{
					validEmptyPos.push(i);
				}
				if (validEmptyPos.size() == 7)
				{
					break;
				}
			}
		}
		return validEmptyPos;
	}

	unsigned int GetStreakTotalFromPos(unsigned int position)
	{
		std::vector<unsigned int> streaks;
		int streakLeft = 0;
		for (int i = position; i % 7 != 0; --i)
		{
			if (m_Board[i] == 1)
			{
				++streakLeft;
			}
			else
			{
				break;
			}
		}
		int streakRight = 0;
		for (int i = position; i % 7 != 0; ++i)
		{
			if (m_Board[i] == 1)
			{
				++streakRight;
			}
			else
			{
				break;
			}
		}
		int streakDown = 0;
		for (int i = position; i < COLUMN_SIZE * ROW_SIZE; i += 7)
		{
			if (m_Board[i] == 1)
			{
				++streakDown;
			}
			else
			{
				break;
			}
		}
		int streakLDiagonal = 0;
		for (int i = position; i < COLUMN_SIZE * ROW_SIZE; i += 6)
		{
			if (m_Board[i] == 1)
			{
				++streakLDiagonal;
			}
			else
			{
				break;
			}
		}
		for (int i = position; i >= 0; i -= 6)
		{
			if (m_Board[i] == 1)
			{
				++streakLDiagonal;
			}
			else
			{
				break;
			}
		}
		int streakRDiagonal = 0;
		for (int i = position; i < COLUMN_SIZE * ROW_SIZE; i += 8)
		{
			if (m_Board[i] == 1)
			{
				++streakRDiagonal;
			}
			else
			{
				break;
			}
		}
		for (int i = position; i >= 0; i -= 8)
		{
			if (m_Board[i] == 1)
			{
				++streakRDiagonal;
			}
			else
			{
				break;
			}
		}
// 		streaks.push_back(streakLeft);
// 		streaks.push_back(streakRight);
// 		streaks.push_back(streakDown);
// 		streaks.push_back(streakLDiagonal);
// 		streaks.push_back(streakRDiagonal);
		int totalStreaks = streakLeft + streakRight + streakDown + streakLDiagonal + streakRDiagonal;
		return totalStreaks;
	}

	std::vector<unsigned int> GetWinningMoves(std::queue<unsigned int> possibleMoves)
	{
		std::vector<unsigned int> winningMoves;
		while (!possibleMoves.empty())
		{
			unsigned int position = possibleMoves.front();
			possibleMoves.pop();
			int streakLeft = 0;
			for (int i = position; i % 7 != 0; --i)
			{
				if (m_Board[i] == 1)
				{
					++streakLeft;
				}
				else
				{
					break;
				}
			}
			int streakRight = 0;
			for (int i = position; i % 7 != 0; ++i)
			{
				if (m_Board[i] == 1)
				{
					++streakRight;
				}
				else
				{
					break;
				}
			}
			int streakDown = 0;
			for (int i = position; i < COLUMN_SIZE * ROW_SIZE; i += 7)
			{
				if (m_Board[i] == 1)
				{
					++streakDown;
				}
				else
				{
					break;
				}
			}
			int streakLDiagonal = 0;
			for (int i = position; i < COLUMN_SIZE * ROW_SIZE; i += 6)
			{
				if (m_Board[i] == 1)
				{
					++streakLDiagonal;
				}
				else
				{
					break;
				}
			}
			for (int i = position; i >= 0; i -= 6)
			{
				if (m_Board[i] == 1)
				{
					++streakLDiagonal;
				}
				else
				{
					break;
				}
			}
			int streakRDiagonal = 0;
			for (int i = position; i < COLUMN_SIZE * ROW_SIZE; i += 8)
			{
				if (m_Board[i] == 1)
				{
					++streakRDiagonal;
				}
				else
				{
					break;
				}
			}
			for (int i = position; i >= 0; i -= 8)
			{
				if (m_Board[i] == 1)
				{
					++streakRDiagonal;
				}
				else
				{
					break;
				}
			}
			if (streakLeft == 3 || streakRight == 3 || streakDown == 3
				|| streakLDiagonal == 3 || streakRDiagonal == 3)
			{
				winningMoves.push_back(position);
			}
		}
		return winningMoves;
	}

	// return an action 0 - 6
	unsigned int minimaxDecision(State& state, unsigned int limit)
	{
		std::queue<unsigned int> posMoves = state.m_Board.GetPossibleMoves();
		unsigned int highestStreak = 0;
		unsigned int moveToMake = 0;
		while (!posMoves.empty())
		{
			unsigned int move = posMoves.front();
			posMoves.pop();
			unsigned int streaks = state.m_Board.GetStreakTotalFromPos(move);
			if (streaks > highestStreak)
			{
				highestStreak = streaks;
				moveToMake = move;
			}
		}
		

		unsigned int maxP = *std::max_element(priority.begin(), priority.end());

	}
};