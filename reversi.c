/*******************************************************************
 *                                                                 *
 *  Author: rodolfoams                                             *
 *  Contact: rodolfo ( at ) grupomarinho ( dot ) com ( dot ) br    *
 *  (C) 2018 All rights reserved                                   *
 *                                                                 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE    0
#define BLACK    1
#define EMPTY    2
#define PLAYABLE 3

#define FALSE 0
#define TRUE  1

const char *row_names = "01234567";
const char *col_names = "01234567";

char board[8][8];
int current_player;
int game_ended = 0;
int skipped_turn = 0;
int wrong_move = 0;
int has_valid_move = 0;

void init_game( )
{
    memset( board, EMPTY, sizeof( board ) );
    board[3][3] = BLACK;
    board[4][4] = BLACK;
    board[3][4] = WHITE;
    board[4][3] = WHITE;
    current_player = WHITE;
}

int is_valid_position( int i, int j )
{
    if ( i < 0 || i >= 8 || j < 0 || j >= 8 ) return FALSE;
    return TRUE;
}

int distance( int i1, int j1, int i2, int j2 )
{
    int di = abs( i1 - i2 ), dj = abs( j1 - j2 );
    if ( di > 0 ) return di;
    return dj;
}

int is_playable( int i, int j )
{
    if ( !is_valid_position( i, j ) ) return FALSE;
    if ( board[i][j] != EMPTY ) return FALSE;

    int opposing_player = ( current_player + 1 ) % 2;
    
    // Test UL diagonal
    int i_it = i-1, j_it = j-1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it -= 1;
        j_it -= 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    // Test UP path
    i_it = i-1, j_it = j;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        i_it -= 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;
    
    // Test UR diagonal
    i_it = i-1, j_it = j+1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it -= 1;
        j_it += 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    // Test LEFT path
    i_it = i, j_it = j-1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        j_it -= 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    // Test RIGHT path
    i_it = i, j_it = j+1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        j_it += 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    // Test DL diagonal
    i_it = i+1, j_it = j-1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it += 1;
        j_it -= 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    // Test DOWN path
    i_it = i+1, j_it = j;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
        i_it += 1;

    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    // Test DR diagonal
    i_it = i+1, j_it = j+1;
    while ( is_valid_position( i_it, j_it ) && board[i_it][j_it] == opposing_player )
    {
        i_it += 1;
        j_it += 1;
    }
    if ( is_valid_position( i_it, j_it ) && distance( i, j, i_it, j_it ) > 1 && board[i_it][j_it] == current_player )
        return 1;

    return FALSE;
}

void mark_playable_positions( )
{
    for ( int i=0; i<7; ++i )
    {
        for ( int j=0; j<7; ++j )
        {
            if ( is_playable( i, j ) )
            {
                board[i][j] = PLAYABLE;
                has_valid_move = 1;
            }
        }
    }
}

void draw_board( )
{
    printf( "     %c     %c     %c     %c     %c     %c     %c     %c\n", col_names[0], col_names[1], col_names[2], col_names[3], col_names[4], col_names[5], col_names[6], col_names[7] );
    printf( "   _____ _____ _____ _____ _____ _____ _____ _____\n" );
    for ( int i=0; i<8; ++i )
    {
        printf( "  |     |     |     |     |     |     |     |     |\n" );
        printf( "%c |", row_names[i] );
        for ( int j=0; j<8; ++j )
        {
            if ( board[i][j] == WHITE )
            {
                printf( "  O  " );
            } else if ( board[i][j] == BLACK )
            {
                printf( "  X  " );
            } else if ( board[i][j] == PLAYABLE )
            {
                printf( "  *  " );
            } else
            {
                printf( "     " );
            }
            printf("|");
        }
        printf( "\n" );
        printf( "  |_____|_____|_____|_____|_____|_____|_____|_____|\n" );
    }
}

int main( )
{
    init_game();
    while ( !game_ended ){
        if ( !wrong_move ) mark_playable_positions();
        draw_board();
        if ( wrong_move )
        {
            printf( "You entered an invalid move!\n" );
            wrong_move = 0;
        }

        game_ended = 1;
    }
}