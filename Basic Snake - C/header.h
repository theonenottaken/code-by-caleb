/**********************************
 * Caleb Shere
 * Student ID: 2-49327691-9
 * Tirgul Group: 89-110-03
 * Exercise 4
 *********************************/


#ifndef targ4_header_h
#define targ4_header_h

int Get_4_Numbers (char str[], int* a, int* b, int* c, int* d);
int Check_Input (int a, int b, int c, int d);
void Start_Loc (int** matr, int w, int h, int sn, int st);
void Print_Board (int** matr, int w, int h, int sn, int* t);
int Move (int** matr, int w, int h, int sn, char m);
void End_Game (int** matr, int w, int h, int sn);

#endif
