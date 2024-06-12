#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

struct Ingredient
{
    vector<vector<int>> shape;
    int points;
    int color;
};

struct AllRotatedIngredients
{
    vector<Ingredient> ingredients;
};

struct Cauldron
{
    vector<vector<tuple<int, int>>> matrix;
    vector<int> efficacy;
};

Cauldron initializeCauldron()
{
    Cauldron cauldron;
    cauldron.matrix = vector<vector<tuple<int, int>>>(7, vector<tuple<int, int>>(7, make_tuple(0, 0)));
    cauldron.efficacy = vector<int>(5, 0);

    return cauldron;
}

vector<AllRotatedIngredients> initializeRotatedIngredients()
{
    vector<AllRotatedIngredients> rotatedIngredients;

    // Tetromino I
    AllRotatedIngredients tetrominoI;
    tetrominoI.ingredients.push_back({{{1, 1, 1, 1}}, 4, 1});       // Original
    tetrominoI.ingredients.push_back({{{1}, {1}, {1}, {1}}, 4, 1}); // 90 degrees
    rotatedIngredients.push_back(tetrominoI);

    // Tetromino O
    AllRotatedIngredients tetrominoO;
    tetrominoO.ingredients.push_back({{{1, 1}, {1, 1}}, 4, 2}); // Only one rotation
    rotatedIngredients.push_back(tetrominoO);

    // Tetromino S
    AllRotatedIngredients tetrominoS;
    tetrominoS.ingredients.push_back({{{0, 1, 1}, {1, 1, 0}}, 4, 3});   // Original
    tetrominoS.ingredients.push_back({{{1, 0}, {1, 1}, {0, 1}}, 4, 3}); // 90 degrees
    rotatedIngredients.push_back(tetrominoS);

    // Tetromino Z
    AllRotatedIngredients tetrominoZ;
    tetrominoZ.ingredients.push_back({{{1, 1, 0}, {0, 1, 1}}, 4, 4});   // Original
    tetrominoZ.ingredients.push_back({{{0, 1}, {1, 1}, {1, 0}}, 4, 4}); // 90 degrees
    rotatedIngredients.push_back(tetrominoZ);

    // Tetromino L
    AllRotatedIngredients tetrominoL;
    tetrominoL.ingredients.push_back({{{1, 0, 0}, {1, 1, 1}}, 4, 5});   // Original
    tetrominoL.ingredients.push_back({{{1, 1}, {1, 0}, {1, 0}}, 4, 5}); // 90 degrees
    tetrominoL.ingredients.push_back({{{1, 1, 1}, {0, 0, 1}}, 4, 5});   // 180 degrees
    tetrominoL.ingredients.push_back({{{0, 1}, {0, 1}, {1, 1}}, 4, 5}); // 270 degrees
    rotatedIngredients.push_back(tetrominoL);

    // Tetromino J
    AllRotatedIngredients tetrominoJ;
    tetrominoJ.ingredients.push_back({{{0, 0, 1}, {1, 1, 1}}, 4, 6});   // Original
    tetrominoJ.ingredients.push_back({{{1, 0}, {1, 0}, {1, 1}}, 4, 6}); // 90 degrees
    tetrominoJ.ingredients.push_back({{{1, 1, 1}, {1, 0, 0}}, 4, 6});   // 180 degrees
    tetrominoJ.ingredients.push_back({{{1, 1}, {0, 1}, {0, 1}}, 4, 6}); // 270 degrees
    rotatedIngredients.push_back(tetrominoJ);

    // Tetromino T
    AllRotatedIngredients tetrominoT;
    tetrominoT.ingredients.push_back({{{0, 1, 0}, {1, 1, 1}}, 4, 7});   // Original
    tetrominoT.ingredients.push_back({{{1, 0}, {1, 1}, {1, 0}}, 4, 7}); // 90 degrees
    tetrominoT.ingredients.push_back({{{1, 1, 1}, {0, 1, 0}}, 4, 7});   // 180 degrees
    tetrominoT.ingredients.push_back({{{0, 1}, {1, 1}, {0, 1}}, 4, 7}); // 270 degrees
    rotatedIngredients.push_back(tetrominoT);

    // Custom 3x1
    AllRotatedIngredients custom3x1;
    custom3x1.ingredients.push_back({{{1, 1, 1}}, 3, 8});     // Horizontal
    custom3x1.ingredients.push_back({{{1}, {1}, {1}}, 3, 8}); // Vertical
    rotatedIngredients.push_back(custom3x1);

    // Custom 1x2
    AllRotatedIngredients custom1x2;
    custom1x2.ingredients.push_back({{{1}, {1}}, 2, 9}); // Vertical
    custom1x2.ingredients.push_back({{{1, 1}}, 2, 9});   // Horizontal
    rotatedIngredients.push_back(custom1x2);

    return rotatedIngredients;
}

bool placeIngredient(vector<vector<tuple<int, int>>> &board, const vector<vector<int>> &shape, int row, int col, int type, int color)
{
    // Try to see whether the ingredients fit in the current position
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= board.size() || newCol >= board[0].size() || get<0>(board[newRow][newCol]) != 0)
                {
                    return false;
                }
            }
        }
    }

    // If it fits then place it
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                board[row + i][col + j] = make_tuple(type, color);
            }
        }
    }
    return true;
}

void removeIngredient(vector<vector<tuple<int, int>>> &board, const vector<vector<int>> &shape, int row, int col)
{
    for (int i = 0; i < shape.size(); ++i)
    {
        for (int j = 0; j < shape[i].size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                board[row + i][col + j] = make_tuple(0, 0);
            }
        }
    }
}

void printBoard(const vector<vector<tuple<int, int>>> &board)
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            int type = get<0>(cell);
            int color = get<1>(cell);
            if (type == 0)
            {
                cout << ". ";
            }
            else if (type == -1)
            {
                cout << "X ";
            }
            else
            {
                switch (color)
                {
                case 1: // Red
                    cout << "\033[31m" << type << "\033[0m ";
                    break;
                case 2: // Orange
                    cout << "\033[38;5;208m" << type << "\033[0m ";
                    break;
                case 3: // Yellow
                    cout << "\033[33m" << type << "\033[0m ";
                    break;
                case 4: // Green
                    cout << "\033[32m" << type << "\033[0m ";
                    break;
                case 5: // Blue
                    cout << "\033[34m" << type << "\033[0m ";
                    break;
                case 6: // Purple
                    cout << "\033[35m" << type << "\033[0m ";
                    break;
                case 7: // Cyan
                    cout << "\033[36m" << type << "\033[0m ";
                    break;
                case 8: // Light Gray
                    cout << "\033[37m" << type << "\033[0m ";
                    break;
                case 9: // White
                    cout << "\033[38;5;255m" << type << "\033[0m ";
                    break;
                default:
                    cout << "\033[0m" << type << " ";
                    break;
                }
            }
        }
        cout << endl;
    }
}

bool solve(Cauldron &cauldron, const vector<AllRotatedIngredients> &allRotatedIngredients, int currentIngredientIndex, int efficacy, int potentness, int &solutionCount, int maxSol)
{
    if (solutionCount >= maxSol)
    {
        return true;
    }

    int emptySlots = 0;
    for (const auto &row : cauldron.matrix)
    {
        for (const auto &cell : row)
        {
            if (get<0>(cell) == 0)
            {
                emptySlots++;
            }
        }
    }

    // Heuristic to prune if the potentness is unreachable at this state
    if (cauldron.efficacy[efficacy - 1] + emptySlots < potentness)
    {
        return false;
    }

    // Print the solution
    if (cauldron.efficacy[efficacy - 1] >= potentness)
    {
        printBoard(cauldron.matrix);
        cout << "Solution found!\n\n";
        solutionCount++;
        return false;
    }

    // Check whether all ingredients including its rotation has been tried yet
    if (currentIngredientIndex == allRotatedIngredients.size())
    {
        return false;
    }

    const auto &rotatedIngredients = allRotatedIngredients[currentIngredientIndex];

    // Iterate the matrix and try to place the ingredients
    bool found = false;
    for (const auto &ingredient : rotatedIngredients.ingredients)
    {
        for (int row = 0; row < cauldron.matrix.size(); row++)
        {
            for (int col = 0; col < cauldron.matrix[row].size(); col++)
            {
                if (placeIngredient(cauldron.matrix, ingredient.shape, row, col, efficacy, ingredient.color))
                {
                    cauldron.efficacy[efficacy - 1] += ingredient.points;

                    if (solve(cauldron, allRotatedIngredients, currentIngredientIndex + 1, efficacy, potentness, solutionCount, maxSol))
                    {
                        found = true;
                    }

                    cauldron.efficacy[efficacy - 1] -= ingredient.points;
                    removeIngredient(cauldron.matrix, ingredient.shape, row, col);
                }
            }
        }
    }
    return found;
}

int main()
{
    Cauldron cauldron = initializeCauldron();
    int numObstacles;

    cout << "Enter the number of obstacles: ";
    cin >> numObstacles;
    cout << "Enter the coordinates of each obstacle (index starts from 0):\n";
    for (int i = 0; i < numObstacles; i++)
    {
        int row, col;
        cout << "Obstacle " << i + 1 << ": ";
        cin >> row >> col;
        if (row < cauldron.matrix.size() && col < cauldron.matrix[row].size())
        {
            cauldron.matrix[row][col] = make_tuple(-1, 10);
        }
    }

    int type;
    cout << "Enter the type of efficacy" << endl;
    cout << "1. Wisdom" << endl;
    cout << "2. Dexterity" << endl;
    cout << "3. Strength" << endl;
    cout << "4. Constitution" << endl;
    cout << "5. Charisma" << endl;
    cout << ">> ";
    cin >> type;

    int level;
    cout << "Enter the level of efficacy" << endl;
    cout << "1. Beginner" << endl;
    cout << "2. Intermediate" << endl;
    cout << "3. Advanced" << endl;
    cout << ">> ";
    cin >> level;

    if (level == 1)
    {
        level = 1;
    }
    else if (level == 2)
    {
        level = 10;
    }
    else
    {
        level = 20;
    }

    int numOfSol;
    cout << "Enter the number of solution: ";
    cin >> numOfSol;

    vector<AllRotatedIngredients> allRotatedIngredients = initializeRotatedIngredients();
    int solutionCount = 0;

    if (solve(cauldron, allRotatedIngredients, 0, type, level, solutionCount, numOfSol))
    {
    }
    else
    {
        cout << "No possible solution.\n";
    }

    return 0;
}
