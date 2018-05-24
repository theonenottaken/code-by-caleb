/*
 * Name: Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-231-06
 * Targil 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <errno.h>
#include <sys/sem.h>
#define SHM_SIZE 5
#define TRUE 1
#define FALSE 0
#define MAX_RETRIES 10
#define ROWS 8
#define COLS 8

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

int isTheSame(char* first, char* sec);
int initsem(key_t key, int nsems);
void initializeBoard(char bd[][COLS]);
void updateBoard(char bd[][COLS], struct move m);
int isGameOver(char bd[][COLS], char nextPl);
int isValidMove(char bd[][COLS], int row, int col, char pl);
int shouldFlipLeft(char bd[][COLS], struct move m);
int shouldFlipRight(char bd[][COLS], struct move m);
int shouldFlipUp(char bd[][COLS], struct move m);
int shouldFlipDown(char bd[][COLS], struct move m);
int shouldFlipUpRight(char bd[][COLS], struct move m);
int shouldFlipUpLeft(char bd[][COLS], struct move m);
int shouldFlipDownRight(char bd[][COLS], struct move m);
int shouldFlipDownLeft(char bd[][COLS], struct move m);
char determineWinner(char bd[][COLS]);

int gameOverFlag;
/*
 * main function
 */
int main() {
	int file, fd_read;
	pid_t pid1, pid2;

	/*
	 * Make fifo
	 */
	file = mkfifo("fifo_clientTOserver",0666);
	if(file<0) {
		printf("Unable to create a fifo");
		exit(-1);
	}
	/*
	 * Read from fifo twice
	 */
	fd_read = open("fifo_clientTOserver", O_RDWR);
	if (fd_read < 0) {
		perror("Failed to open fifo");
		exit(-1);
	}
	// read from first client
	read(fd_read,&pid1,sizeof(pid_t));
	// read from second client
	read(fd_read, &pid2, sizeof(pid_t));

	// Close and delete fifo
	close(fd_read);
	unlink("fifo_clientTOserver");

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
	 * Make shared memory key
	 */
	if ((mKey = ftok("ex31.c", 'k')) == -1) {
		perror("ftok failed to make key");
		exit(-1);
	}
	/*
	 * Make shared memory
	 */
	if ((shmid = shmget(mKey, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
	    perror("shmget - Error creaing shared memory segment");
	    exit(-1);
	}
	/*
	 * Make semaphore key
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

	// Store contents to see if they change
	char prevData[5];
	strcpy(prevData, data);

	char board[ROWS][COLS];
	initializeBoard(board);
	gameOverFlag = FALSE;

	// Signal first client
	kill (pid1, SIGUSR1);

	// Wait for first client to write to shared memory
	while (TRUE) {
		sleep(1);
		// Lock semaphore to access shared memory
		sb.sem_op = -1;
		semop(semid, &sb, 1);
		int same = isTheSame(prevData, data);
		// Unlock semaphore
		sb.sem_op = 1;
		semop(semid, &sb, 1);
		if (same == FALSE)
			break;
	}

	struct move mov;
	sb.sem_op = -1;
	semop(semid, &sb, 1);
	mov.player = data[0];
	// Subtract one because in computers we start counting at 0
	mov.col = data[1] - '0' - 1;
	mov.row = data[2] - '0' - 1;
	strcpy(prevData, data);
	sb.sem_op = 1;
	semop(semid, &sb, 1);
	updateBoard(board, mov); // no need to access the memory while updating the board

	// Signal second client
	kill (pid2, SIGUSR1);

	while (gameOverFlag == 0) {
		sleep(1);
		sb.sem_op = -1;
		semop(semid, &sb, 1);
		int same = isTheSame(prevData, data);
		if (same == FALSE) {
			mov.player = data[0];
			mov.col = data[1] - '0' - 1;
			mov.row = data[2] - '0' - 1;
			strcpy(prevData, data);
			updateBoard(board, mov);
		}
		sb.sem_op = 1;
		semop(semid, &sb, 1);
	}
	char winner = determineWinner(board);
	printf("GAME OVER\n");
	if (winner == 'b')
		printf("Winning player: Black\n");
	else if (winner == 'w')
		printf("Winning player: White\n");
	else
		printf("No winning player\n");

	sb.sem_op = -1;
	semop(semid, &sb, 1);

	// Detach from memory
	if (shmdt(data) == -1) {
		perror("shmdt failed to detach from memory");
		exit(-1);
	}
	// Delete memory
	shmctl(shmid, IPC_RMID, NULL);
	// Delete the semaphore
	semctl(semid, 0, IPC_RMID);
	return EXIT_SUCCESS;
}

/*
 * Checks to see if the contents of the shared memory has changed
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
			else
				break;
		}
	}
	// Check if the game is over now
	if (isGameOver(board, otherPl))
		gameOverFlag = TRUE;
}

/*
 * Checks if the game is over
 */
int isGameOver(char board[][COLS], char nextPl) {
	int i, j;
	// Assume the game is over until something tells us that it isn't
	int full = TRUE;
	int foundWhite = FALSE;
	int foundBlack = FALSE;
	int noMove = TRUE;
	int notOver = FALSE;
	for (i = 0; i < ROWS; i++) {
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
		if (notOver == TRUE)
			break;
	}
	if (notOver == TRUE)
		return FALSE;
	else
		return TRUE;
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
	else					// Equal number of blacks and whites
		return 'd';
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
