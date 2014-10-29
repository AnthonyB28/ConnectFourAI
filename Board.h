#include <algorithm>
#include <vector>
#include <queue>

#define EMPTY 0
#define BLACK 1
#define RED 2
#define COLUMN_SIZE 6
#define ROW_SIZE 7


struct Board
{
	Board()
		:m_Board()
	{
		std::fill_n(m_Board, COLUMN_SIZE * ROW_SIZE, 0);
	}
	unsigned int m_Board[COLUMN_SIZE * ROW_SIZE];

	void SetElement(int position, unsigned int value)
	{
		m_Board[position] = value;
	}

	unsigned int GetPos(int row, int col)
	{
		return m_Board[ROW_SIZE * row + col];
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
				else if (i < (COLUMN_SIZE * ROW_SIZE) && i >= COLUMN_SIZE * ROW_SIZE - 8)
				{
					if (m_Board[i] == 0 || m_Board[i] == 0)
					{
						validEmptyPos.push(i);
					}
				}
				if (validEmptyPos.size() == 7)
				{
					break;
				}
				
			}
		}
		return validEmptyPos;
	}

	unsigned int GetStreakTotalFromPos(unsigned int position, unsigned int player)
	{
		std::vector<unsigned int> streaks;
		int streakLeft = 0;
		for (int i = position; i % 7 != 0; --i)
		{
			if (m_Board[i] == player)
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
			if (m_Board[i] == player)
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
			if (m_Board[i] == player)
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
			if (m_Board[i] == player)
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
			if (m_Board[i] == player)
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
			if (m_Board[i] == player)
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
			if (m_Board[i] == player)
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

	std::vector<unsigned int> GetWinningMoves(std::queue<unsigned int> possibleMoves, unsigned int player)
	{
		std::vector<unsigned int> winningMoves;
		while (!possibleMoves.empty())
		{
			unsigned int position = possibleMoves.front();
			possibleMoves.pop();
			int streakLeft = 0;
			for (int i = position; i % 7 != 0; --i)
			{
				if (m_Board[i] == player)
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
				if (m_Board[i] == player)
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
				if (m_Board[i] == player)
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
				if (m_Board[i] == player)
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
				if (m_Board[i] == player)
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
				if (m_Board[i] == player)
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
				if (m_Board[i] == player)
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

	unsigned int GetUtility(Board& state, unsigned int player)
	{
		std::queue<unsigned int> posMoves = state.GetPossibleMoves();
		unsigned int utility = 0;
		while (!posMoves.empty())
		{
			unsigned int move = posMoves.front();
			posMoves.pop();
			utility += state.GetStreakTotalFromPos(move, player);

		}
		return utility;
	}

	unsigned int maxValue(Board& state, int limit, unsigned int player)
	{
		std::vector<unsigned int> winningMoves = state.GetWinningMoves(state.GetPossibleMoves(), player);
		if (limit == 0 || winningMoves.size() > 0)
		{
			return GetUtility(state, player);
		}
		int v = -1;
		std::queue<unsigned int> posMoves = state.GetPossibleMoves();
		std::vector<unsigned int> results;
		while (!posMoves.empty())
		{
			unsigned int move = posMoves.front();
			posMoves.pop();
			Board newState;
			newState = state;
			newState.SetElement(move, player);
			unsigned int val = minValue(state, limit - 1, player);
			if (v < val)
			{
				v = val;
			}
		}
		return v;
	}

	unsigned int minValue(Board& state, int limit, unsigned int player)
	{
		std::vector<unsigned int> winningMoves = state.GetWinningMoves(state.GetPossibleMoves(), player);
		if (limit == 0 || winningMoves.size() > 0)
		{
			return GetUtility(state, player);
		}
		int v = 1765;
		std::queue<unsigned int> posMoves = state.GetPossibleMoves();
		std::vector<unsigned int> results;
		while (!posMoves.empty())
		{
			unsigned int move = posMoves.front();
			posMoves.pop();
			Board newState = state;
			newState.SetElement(move, player);
			unsigned int val = maxValue(state, limit - 1, player);
			if (v > val)
			{
				v = val;
			}
		}
		return v;
	}

	// return an action 0 - 6
	unsigned int minimaxDecision(Board& state, unsigned int limit, unsigned int player)
	{
		std::queue<unsigned int> posMoves = state.GetPossibleMoves();
		std::vector<unsigned int> posMoves2;
		unsigned int highestStreak = 0;
		unsigned int moveToMake = 0;
		std::vector<unsigned int> possibleActions;
		while (!posMoves.empty())
		{
			unsigned int move = posMoves.front();
			posMoves.pop();
			posMoves2.push_back(move);
			Board newState = state;
			newState.SetElement(move, player);
			possibleActions.push_back(minValue(state, limit - 1, player));
		}

		std::vector<unsigned int>::iterator it = std::max_element(possibleActions.begin(), possibleActions.end());
		int action = it - possibleActions.begin();
		return posMoves2[action];
	}

	// 	std::queue<unsigned int> posMoves = state.GetPossibleMoves();
	// 	unsigned int highestStreak = 0;
	// 	unsigned int moveToMake = 0;
	// 	while (!posMoves.empty())
	// 	{
	// 		unsigned int move = posMoves.front();
	// 		posMoves.pop();
	// 		unsigned int streaks = state.GetStreakTotalFromPos(move);
	// 		if (streaks > highestStreak)
	// 		{
	// 			highestStreak = streaks;
	// 			moveToMake = move;
	// 		}
	// 	}
};