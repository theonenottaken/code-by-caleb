/*
 * Name: Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-231-06
 * Targil 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <signal.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#define SHM_SIZE 5
#define MAX_RETRIES 10
#define ROWS 8
#define COLS 8
#define TRUE 1
#define FALSE 0

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};

struct move {
	char player;
	char otherPl;
	int col;
	int row;
};

void sigHandler(int signum, siginfo_t* info, void* ptr);
int initsem(key_t key, int nsems);
void initializeBoard(char bd[][COLS]);
int isValidMove(char bd[][COLS], int r, int c, char p);
int shouldFlipLeft(char bd[][COLS], struct move m);
int shouldFlipRight(char bd[][COLS], struct move m);
int shouldFlipUp(char bd[][COLS], struct move m);
int shouldFlipDown(char bd[][COLS], struct move m);
int shouldFlipUpRight(char bd[][COLS], struct move m);
int shouldFlipUpLeft(char bd[][COLS], struct move m);
int shouldFlipDownRight(char bd[][COLS], struct move m);
int shouldFlipDownLeft(char bd[][COLS], struct move m);
void updateBoard(char bd[][COLS], struct move m);
int isGameOver(char bd[][COLS], char nextPl);
char determineWinner(char bd[][COLS]);
void printBoard(char bd[][COLS]);
int isTheSame(char* first, char* sec);
void gameOver(char bd[][COLS]);
int sigFlag;
int gameOverFlag;
/*
 * main function
 */
int main(void) {
	int fd_write;
	pid_t pid = getpid();
	sigFlag = 0;
	struct sigaction start_action;
	sigfillset(&start_action.sa_mask);
	start_action.sa_flags = SA_SIGINFO;
	start_action.sa_sigaction = sigHandler;
	fd_write = open("fifo_clientTOserver",O_WRONLY);
	if (fd_write < 0) {
		perror("Failed to open fifo");
		exit(-1);
	}
	// Write this pid to the fifo
	write(fd_write, &pid, sizeof(pid_t));
	close(fd_write);

	// Wait for signal from server
	sigaction(SIGUSR1, &start_action, NULL);
	while (sigFlag == 0) {
		sleep(1);
	}

	key_t mKey;
	int shmid;
	char* data;
	key_t sKey;
	int semid;
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1;  /* set to allocate resource */
	sb.sem_flg = 0;
	/*
	 * Get memory key
	 */
	if ((mKey = ftok("ex31.c", 'k')) == -1) {
		perror("ftok");
		exit(-1);
	}
	/*
	 * Get shared memory id
	 */
	if ((shmid = shmget(mKey, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
		perror("shmget - Error creaing shared memory segment");
		exit(-1);
	}
	/*
	 * Get the semaphore key
	 */
	if ((sKey = ftok("ex31.c", 'j')) == -1) {
		perror("ftok");
		exit(-1);
	}
	/*
	 * Get the semaphore set (just one semaphore)
	 */
	if ((semid = initsem(sKey, 1)) == -1) {
		perror("initsem");
		exit(1);
	}
	/*
	 * Attach to memory
	 */
	data = shmat(shmid, (void*) 0, 0);
	if (data == (char*) -1) {
		perror("shmat");
		exit(-1);
	}
	gameOverFlag = FALSE;
	char color;
	char board[ROWS][COLS];
	struct move mov;
	initializeBoard(board);
	semop(semid, &sb, 1);
	// Determine if you are the first or the second player
	if (data[0] == 'b')
		color = 'w';
	else
		color = 'b';
	// Second player
	if (color == 'w') {
		mov.col = data[1] - '0' - 1;
		mov.row = data[2] - '0' - 1;
		mov.player = 'b';
		updateBoard(board, mov);
	}
	sb.sem_op = 1;
	semop(semid, &sb, 1);

	char userIn[6];
	char col;
	char row;
	char prevData[5];
	printBoard(board);
	while (TRUE) {
		printf("Please choose a square\n");
		// Input string of the for [x,y]
		scanf("%s", userIn);
		col = userIn[1];
		row = userIn[3];
		mov.col = col - '0' - 1;
		mov.row = row - '0' - 1;
		mov.player = color;
		if ((mov.row > ROWS - 1) || (mov.col > COLS - 1) || (mov.row < 0) || (mov.col < 0)) {
			printf("No such square\n");
			continue;
		}
		if (isValidMove(board, mov.row, mov.col, mov.player) == FALSE) {
			printf("This square is invalid\n");
			continue;
		}
		updateBoard(board, mov);
		printBoard(board);
		sb.sem_op = -1;
		semop(semid, &sb, 1);
		data[0] = color;
		data[1] = col;
		data[2] = row;
		strcpy(prevData, data);
		sb.sem_op = 1;
		semop(semid, &sb, 1);
		if (gameOverFlag == TRUE) {
			gameOver(board);
			break;
		} else {
			printf("‫‪Waiting‬‬ ‫‪for‬‬ ‫‪the‬‬ ‫‪other‬‬ ‫‪player‬‬ ‫‪to‬‬ ‫‪make‬‬ ‫‪a‬‬ ‫‪move‬‬\n");
			int same;
			while (TRUE) {
				sleep(1);
				sb.sem_op = -1;
				semop(semid, &sb, 1);
				same = isTheSame(prevData, data);
				if (same == FALSE) {
					mov.player = data[0];
					mov.col = data[1] - '0' - 1;
					mov.row = data[2] - '0' - 1;
					strcpy(prevData, data);
					sb.sem_op = 1;
					semop(semid, &sb, 1);
					updateBoard(board, mov);
					printBoard(board);
					break;
				}
				sb.sem_op = 1;
				semop(semid, &sb, 1);
			}
			if (gameOverFlag == TRUE) {
				gameOver(board);
				break;
			}
		}
	}

	if (shmdt(data) == -1) {
		perror("shmdt failed to detach from memory");
		exit(-1);
	}
	return EXIT_SUCCESS;
}
/*
 * Signal handler for handling the SIGUSR1 received from the server
 */
void sigHandler(int signum, siginfo_t* info, void* ptr) {
	sigFlag = 1;
}

/*
 * Initializes the board with the four pieces in the center
 */
void initializeBoard(char board[][COLS]) {
	int i, j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if ((i == 3 && j == 3) || (i == 4 && j == 4))
				board[i][j] = 'w';
			else if ((i == 3 && j == 4) || (i == 4 && j == 3))
				board[i][j] = 'b';
			else
				board[i][j] = 'o';
		}
	}
}

/*
 * Checks to see if it is valid for player pl to play a move at [col, row]
 */
int isValidMove(char board[][COLS], int row, int col, char pl) {
	char otherPl;
	if (pl == 'w')
		otherPl = 'b';
	else
		otherPl = 'w';
	struct move mov;
	mov.col = col;
	mov.row = row;
	mov.player = pl;
	mov.otherPl = otherPl;
	if (shouldFlipLeft(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipRight(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipDown(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipUp(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipDownLeft(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipDownRight(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipUpLeft(board, mov) == TRUE)
		return TRUE;
	if (shouldFlipUpRight(board, mov) == TRUE)
		return TRUE;
	return FALSE;
}

/*
 * Checks if there are pieces to flip in the left direction
 */
int shouldFlipLeft(char board[][COLS], struct move m) {
	int j;
	if (board[m.row][m.col - 1] == m.otherPl) {
		for (j = m.col - 2; j >= 0; j--) {
			if (board[m.row][j] == 'o')
				break;
			else if (board[m.row][j] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the right direction
 */
int shouldFlipRight(char board[][COLS], struct move m) {
	int j;
	if (board[m.row][m.col + 1] == m.otherPl) {
		for (j = m.col + 2; j < COLS; j++) {
			if (board[m.row][j] == 'o')
				break;
			else if (board[m.row][j] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the down direction
 */
int shouldFlipDown(char board[][COLS], struct move m) {
	int i;
	if (board[m.row + 1][m.col] == m.otherPl) {
		for (i = m.row + 2; i < ROWS; i++) {
			if (board[i][m.col] == 'o')
				break;
			else if (board[i][m.col] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the up direction
 */
int shouldFlipUp(char board[][COLS], struct move m) {
	int i;
	if (board[m.row - 1][m.col] == m.otherPl) {
		for (i = m.row - 2; i >= 0; i--) {
			if (board[i][m.col] == 'o')
				break;
			else if (board[i][m.col] == m.player) {
				return TRUE;
			}
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the down-left direction
 */
int shouldFlipDownLeft(char board[][COLS], struct move m) {
	int i, j;
	if (board[m.row + 1][m.col - 1] == m.otherPl) {
		for (i = m.row + 2, j = m.col - 2; i < ROWS && j >= 0; i++, j--) {
			if (board[i][j] == 'o')
				break;
			else if (board[i][j] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the down-right direction
 */
int shouldFlipDownRight(char board[][COLS], struct move m) {
	int i, j;
	if (board[m.row + 1][m.col + 1] == m.otherPl) {
		for (i = m.row + 2, j = m.col + 2; i < ROWS && j < COLS; i++, j++) {
			if (board[i][j] == 'o')
				break;
			else if (board[i][j] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the up-right direction
 */
int shouldFlipUpRight(char board[][COLS], struct move m) {
	int i, j;
	if (board[m.row - 1][m.col + 1] == m.otherPl) {
		for (i = m.row - 2, j = m.col + 2; i >= 0 && j < COLS; i--, j++) {
			if (board[i][j] == 'o')
				break;
			else if (board[i][j] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}
/*
 * Checks if there are pieces to flip in the up-left direction
 */
int shouldFlipUpLeft(char board[][COLS], struct move m) {
	int i, j;
	if (board[m.row - 1][m.col - 1] == m.otherPl) {
		for (i = m.row - 2, j = m.col - 2; i >= 0 && j >= 0; i--, j--) {
			if (board[i][j] == 'o')
				break;
			else if (board[i][j] == m.player)
				return TRUE;
		}
	}
	return FALSE;
}

/*
 * Updates the board after a move has been made
 */
void updateBoard(char board[][COLS], struct move mov) {
	char pl = mov.player;
	char otherPl = 0;
	if (pl == 'w')
		otherPl = 'b';
	else if (pl == 'b')
		otherPl = 'w';
	board[mov.row][mov.col] = pl;
	mov.otherPl = otherPl;
	int i, j;
	char place;
	// Down
	if (shouldFlipDown(board, mov)) {
		for (i = mov.row + 1; i < ROWS; i++) {
			place = board[i][mov.col];
			if (place == otherPl)
				board[i][mov.col] = pl;
			else
				break;
		}
	}
	// Up
	if (shouldFlipUp(board, mov)) {
		for (i = mov.row - 1; i >= 0; i--) {
			place = board[i][mov.col];
			if (place == otherPl)
				board[i][mov.col] = pl;
			else
				break;
		}
	}
	// Left
	if (shouldFlipLeft(board, mov)) {
		for (j = mov.col - 1; j >= 0; j--) {
			place = board[mov.row][j];
			if (place == otherPl)
				board[mov.row][j] = pl;
			else
				break;
		}
	}
	// Right
	if (shouldFlipRight(board, mov)) {
		for (j = mov.col + 1; j < COLS; j++) {
			place = board[mov.row][j];
			if (place == otherPl)
				board[mov.row][j] = pl;
			else
				break;
		}
	}
	//Up-Right
	if (shouldFlipUpRight(board, mov)) {
		for (i = mov.row - 1, j = mov.col + 1; i >= 0 && j < COLS; i--, j++) {
			place = board[i][j];
			if (place == otherPl)
				board[i][j] = pl;
			else
				break;
		}
	}
	//Up-Left
	if (shouldFlipUpLeft(board, mov)) {
		for (i = mov.row - 1, j = mov.col - 1; i >= 0 && j >= 0; i--, j--) {
			place = board[i][j];
			if (place == otherPl)
				board[i][j] = pl;
			else
				break;
		}
	}
	//Down-Right
	if (shouldFlipDownRight(board, mov)) {
		for (i = mov.row + 1, j = mov.col + 1; i < ROWS && j < COLS; i++, j++) {
			place = board[i][j];
			if (place == otherPl)
				board[i][j] = pl;
			else
				break;
		}
	}
	//Down-Left
	if (shouldFlipDownLeft(board, mov)) {
		for (i = mov.row + 1, j = mov.col - 1; i < ROWS && j >= 0; i++, j--) {
			place = board[i][j];
			if (place == otherPl)
				board[i][j] = pl;
			else if (place == 'o')
				break;
		}
	}
	if (isGameOver(board, otherPl))
		gameOverFlag = TRUE;
}

/*
 * Checks if the game is over
 */
int isGameOver(char board[][COLS], char nextPl) {
	int i, j;
	// Assume the game is over until something tells us it isn't
	int full = TRUE;
	int foundWhite = FALSE;
	int foundBlack = FALSE;
	int noMove = TRUE;
	int notOver = FALSE;
	for (i = 0; i < ROWS; i++) {
		if (notOver == TRUE)
			break;
		for (j = 0; j < COLS; j++) {
			if (board[i][j] == 'b')
				foundBlack = TRUE;
			else if (board[i][j] == 'w')
				foundWhite = TRUE;
			else {
				full = FALSE; // Found an empty spot
				if (isValidMove(board, i, j, nextPl))
					noMove = FALSE;
			}
			if (full == FALSE && foundWhite == TRUE && foundBlack == TRUE && noMove == FALSE) {
				notOver = TRUE;
				break;
			}
		}
	}
	if (notOver == TRUE)
		return FALSE;
	else
		return TRUE;
}

/*
 * Returns 'b' if black won. 'w' if white won. And 'd' if draw
 */
char determineWinner(char board[][COLS]) {
	int blacks = 0;
	int whites = 0;
	int i, j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (board[i][j] == 'b')
				blacks++;
			else if (board[i][j] == 'w')
				whites++;
		}
	}
	if (blacks > whites)
		return 'b';
	else if (whites > blacks)
		return 'w';
	// Equal number of blacks and whites
	else
		return 'd';
}

/*
 * Prints the board to screen
 */
void printBoard(char board[][COLS]) {
	int i, j;
	char toPrint;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (board[i][j] == 'o')
				toPrint = ' ';
			else
				toPrint = board[i][j];
			printf("|%c", toPrint);
		}
		printf("|");
		printf("\n");
	}
}

/*
 * Checks to see if the contents of the shared memory have changed
 */
int isTheSame(char* first, char* sec) {
	int len = strlen(first);
	if (len != strlen(sec))
		return FALSE;
	int i;
	for (i = 0; i < len; i++) {
		if (first[i] != sec[i])
			return FALSE;
	}
	return TRUE;
}

/*
 * Determines the outcome of the game and prints the appropriate message
 */
void gameOver(char board[][COLS]) {
	char winner = determineWinner(board);
	printf("GAME OVER\n");
	if (winner == 'b')
		printf("Winning player: Black\n");
	else if (winner == 'w')
		printf("Winning player: White\n");
	else
		printf("No winning player\n");
}

/*
 * A function for safely initializing the semaphores.
 * This is taken from the examples that Chen posted online
 */
int initsem(key_t key, int nsems) {
	int i;
	union semun arg;
	struct semid_ds buf;
	struct sembuf sb;
	int semid;

	semid = semget(key, nsems, IPC_CREAT | IPC_EXCL | 0666);

	if (semid >= 0) { /* we got it first */
		sb.sem_op = 1;
		sb.sem_flg = 0;

		for(sb.sem_num = 0; sb.sem_num < nsems; sb.sem_num++) {
			/* do a semop() to "free" the semaphores. */
			/* this sets the sem_otime field, as needed below. */
			if (semop(semid, &sb, 1) == -1) {
				int e = errno;
				semctl(semid, 0, IPC_RMID,NULL); /* clean up */
				errno = e;
				return -1; /* error, check errno */
			}
		}

	} else if (errno == EEXIST) { /* someone else created it first */
		int ready = 0;
		semid = semget(key, nsems, 0); /* get the id */
		if (semid < 0)
			return semid; /* error, check errno */

		/* wait for other process to initialize the semaphore: */
		arg.buf = &buf;

		for(i = 0; i < MAX_RETRIES && !ready; i++) {
			semctl(semid, nsems-1, IPC_STAT, arg);
			if (arg.buf->sem_otime != 0) {
				ready = 1;
			} else {
				sleep(1);
			}
		}
		if (!ready) {
			errno = ETIME;
			return -1;
		}

	} else {
		return semid; /* error, check errno */
	}

	return semid;
}
