void King::randomMove(Piece*** board, int boardSizeOnX, int boardSizeOnY, bool duplicate) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 7);
    
    // Fisher Yates Shuffle Algorithm https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
    // This shuffles the directions array elements
    for (int i = 7; i > 0; i--) {
        int j = dis(gen) % (i + 1);
        std::swap(directions[i][0], directions[j][0]);
        std::swap(directions[i][1], directions[j][1]);
    }

    // Check every direction (in random order since we shuffled them)
    for (int i = 0; i < 8; i++) {
        // Pick a random x and y from the possible directions
        int targetX = directions[i][0] + x;
        int targetY = directions[i][1] + y;

        // Checks if target position isn't out of bounds
        if (isValidPos(targetX, targetY, boardSizeOnX, boardSizeOnY)) {
            // Checks if target position is empty
            if (board[targetX][targetY] == nullptr) {
                movePiece(targetX, targetY, board, boardSizeOnX, boardSizeOnY, duplicate);
                return; // Because if not, it would continue moving the piece if available
            }
        }
    }
}
