const COMPUTER = 1;
        const HUMAN = 2;
        const SIDE = 3;
        const COMPUTERMOVE = 'O';
        const HUMANMOVE = 'X';

        let gboard = Array(SIDE).fill().map(() => Array(SIDE).fill('*'));
        let maxIn = 0;
        let whoseTurn = HUMAN;

        function initialize(gboard) {
            for (let i = 0; i < SIDE; i++) {
                for (let j = 0; j < SIDE; j++) {
                    gboard[i][j] = '*';
                    document.getElementsByClassName('button-option')[i * SIDE + j].innerText = '';
                }
            }
            maxIn = 0;
        }

        function showBoard(gboard) {
            for (let i = 0; i < SIDE; i++) {
                for (let j = 0; j < SIDE; j++) {
                    document.getElementsByClassName('button-option')[i * SIDE + j].innerText = gboard[i][j] === '*' ? '' : gboard[i][j];
                }
            }
        }

        function columnCross(gboard) {
            for (let i = 0; i < SIDE; i++) {
                if (gboard[0][i] === gboard[1][i] && gboard[1][i] === gboard[2][i] && gboard[0][i] !== '*') {
                    return true;
                }
            }
            return false;
        }

        function rowCrossed(gboard) {
            for (let i = 0; i < SIDE; i++) {
                if (gboard[i][0] === gboard[i][1] && gboard[i][1] === gboard[i][2] && gboard[i][0] !== '*') {
                    return true;
                }
            }
            return false;
        }

        function diagonalCross(gboard) {
            if ((gboard[0][0] === gboard[1][1] && gboard[1][1] === gboard[2][2] && gboard[0][0] !== '*') ||
                (gboard[0][2] === gboard[1][1] && gboard[1][1] === gboard[2][0] && gboard[0][2] !== '*')) {
                return true;
            }
            return false;
        }

        function gameOver(gboard) {
            return rowCrossed(gboard) || columnCross(gboard) || diagonalCross(gboard);
        }

        function minimax(gboard, depth, isPlay) {
            if (gameOver(gboard)) {
                return isPlay ? -10 + depth : 10 - depth;
            }
            if (depth === SIDE * SIDE) {
                return 0;
            }
        
            let bestScore = isPlay ? -1000 : 1000;
            for (let i = 0; i < SIDE; i++) {
                for (let j = 0; j < SIDE; j++) {
                    if (gboard[i][j] === '*') {
                        gboard[i][j] = isPlay ? COMPUTERMOVE : HUMANMOVE;
                        let currentScore = minimax(gboard, depth + 1, !isPlay);
                        gboard[i][j] = '*';
                        if (isPlay) {
                            bestScore = Math.max(bestScore, currentScore);
                        } else {
                            bestScore = Math.min(bestScore, currentScore);
                        }
                    }
                }
            }
            return bestScore;
        }

        function bestWay(gboard) {
            let bestScore = -1000;
            let move = { x: -1, y: -1 };

            for (let i = 0; i < SIDE; i++) {
                for (let j = 0; j < SIDE; j++) {
                    if (gboard[i][j] === '*') {
                        gboard[i][j] = COMPUTERMOVE;
                        let score = minimax(gboard, 0, false);
                        gboard[i][j] = '*';
                        if (score > bestScore) {
                            bestScore = score;
                            move = { x: i, y: j };
                        }
                    }
                }
            }
            return move.x * SIDE + move.y;
        }

        function declareWinner(whoseTurn) {
            let message = '';
            if (whoseTurn === COMPUTER) {
                message = "COMPUTER has won!";
            } else if (whoseTurn === HUMAN) {
                message = "YOU won!";
            } else {
                message = "It's a draw!";
            }
            document.getElementById('message').innerText = message;
            document.getElementById('popup').classList.remove('hide');
        }
        

        function playTurn(row, col) {
            if (gboard[row][col] !== '*' || gameOver(gboard)) return;
        
            gboard[row][col] = HUMANMOVE;
            showBoard(gboard);
            maxIn++;
            if (gameOver(gboard)) {
                declareWinner(HUMAN);
                return;
            }
            if (maxIn === SIDE * SIDE) {
                document.getElementById('message').innerText = "It's a draw!";
                document.getElementById('popup').classList.remove('hide');
                return;
            }
        
            // Human's move is done, simulate delay for computer's turn
            setTimeout(function () {
                let n = bestWay(gboard);
                let x = Math.floor(n / SIDE);
                let y = n % SIDE;
                gboard[x][y] = COMPUTERMOVE;
                showBoard(gboard);
                maxIn++;
                if (gameOver(gboard)) {
                    declareWinner(COMPUTER);
                    return;
                }
                if (maxIn === SIDE * SIDE) {
                    document.getElementById('message').innerText = "It's a draw!";
                    document.getElementById('popup').classList.remove('hide');
                    return;
                }
            }, 1000); // Adjust the delay time as needed (in milliseconds)
        }

        function resetGame() {
            initialize(gboard);
            whoseTurn = HUMAN;
            document.getElementById('popup').classList.add('hide');
            document.getElementById('message').innerText = '';
        }

        initialize(gboard);