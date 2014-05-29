#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

void go_up( Tank tank )
{
    int up = tank.x - 1;
    int x = tank.x, y = tank.y;
    if ( ( map[ up ][ y ] == EMPTY ) && ( map[ up ][ y + 1 ] == EMPTY ) && ( map[ up ][ y + 2 ] == EMPTY ) )
        if ( tank.dir == UP )
        {
            erase_tank( tank.x, tank.y );
            tank.x = up;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = UP;
            print_tank( tank.dir, tank.x, tank.y );
            tank.x = up;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void go_down( Tank tank )
{
    int down = tank.x + 3;
    int x = tank.x, y = tank.y;
    if ( ( map[ down ][ y ] == EMPTY ) && ( map[ down ][ y + 1 ] == EMPTY ) && ( map[ down ][ y + 2 ] == EMPTY ) )
        if ( tank.dir == DOWN )
        {
            erase_tank( tank.x, tank.y );
            tank.x = down;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = DOWN;
            print_tank( tank.dir, tank.x, tank.y );
            tank.x = down;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void go_left( Tank tank )
{
    int left = tank.y - 1;
    int x = tank.x, y = tank.y;
    if ( ( map[ x ][ left ] == EMPTY ) && ( map[ x + 1 ][ left ] == EMPTY ) && ( map[ x + 2 ][ left ] == EMPTY ) )
        if ( tank.dir == LEFT )
        {
            erase_tank( tank.x, tank.y );
            tank.y = left;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = LEFT;
            print_tank( tank.dir, tank.x, tank.y );
            tank.y = left;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void go_right( Tank tank )
{
    int right = tank.y + 3;
    int x = tank.x, y = tank.y;
    if ( ( map[ x ][ right ] == EMPTY ) && ( map[ x + 1 ][ right ] == EMPTY ) && ( map[ x + 2 ][ right ] == EMPTY ) )
        if ( tank.dir == RIGHT )
        {
            erase_tank( tank.x, tank.y );
            tank.y = right;
            print_tank( tank.dir, tank.x, tank.y );
        }
        else
        {
            tank.dir = RIGHT;
            print_tank( tank.dir, tank.x, tank.y );
            tank.y = right;
            print_tank( tank.dir, tank.x, tank.y );
        }
}
void shoot( Tank tank )
{
    int i;
    for ( i = 0; i < 20; i++)
        if ( !bullets[ i ] )
        {
            bullets[ i ] = malloc( sizeof( Bullet ) );
            bullets[ i ]->x = tank.x;
            bullets[ i ]->y = tank.y;
            bullets[ i ]->dir = tank.dir;
            break;
        }
}
void update_game()
{
    for ( i = 0; i < 20; i++ )
    if ( !bullets[ i ] )
        {
            bullets[ i ].state++;
            if ( bullets[ i ] == BULLET_SPEED )
            {
                bullets[ i ]->state = 0;
                erase_bullet( bullets[ i ]->x, bullets[ i ]->y );
                switch ( bullets[ i ]->dir )
                {
                    case UP: { bullets[ i ]->x--; break; }
                    case DOWN: { bullets[ i ]->x++; break; }
                    case LEFT: { bullets[ i ]->y--; break; }
                    case RIGHT: { bullets[ i ]->y++; break; }
                }
            }
            switch ( map[ bullets[ i ]->x ][ bullets[ i ]->y ] )
            {
                case 'T':
                    p = grid[ bullets[ i ]->x ][ bullets[ i ]->y ];
                    erase_tank( p->x, p->y );
                    free( p );
                    p = NULL;
                    erase_bullet( p->x, p->y );
                    free( bullets[ i ] );
                    bullets[ i ] = NULL;
                    break;
                case 'B':
                    p = grid[ bullets[ i ]->x ][ bullets[ i ]->y ];
                    print_empty( p->x, p->y );
                    free( p );
                    p = NULL;
                    free( bullets[ i ] );
                    bullets[ i ] = NULL;
                    break;
                case 'S':
                    p = grid[ bullets[ i ]->x ][ bullets[ i ]->y ];




        }

#endif // ENGINE_H_INCLUDED
