# Sudoku
Test Repo to write code for Sudoku puzzle solving

Sudoku puzzle solver is used here to demonstrate incremental development of solution across multiple iteration

Planned iterations
1. Display 9x9 matrix/Grid on screen based on input value(at this point all values are hard coded) 
2. For every row, Ensure Unique digits are filled in each cell for that row. A bitflag to be used for all probable values for each row
3. For every column, Ensure Unique digits are filled in each cell for that column. A bitflag to be used for all probable values for each column
4. Divide 9x9 matrix/Grid into 9 sub-grids each of 3x3. Given any cell with row and column, correct sub-grid should be identified.
5. For each sub Grid,ensure Unique digits are filled in each cell. A bitflag to be used for all probable values
6. Likely a final iteration, put together everything to Solve Sudoku puzzle
