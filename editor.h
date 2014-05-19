#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

void print_editor()
{
    int i,j,tank_x=-1,tank_y=-1,base_x=-1,base_y=-1;
     for (i=0;i<MAP_SIZE;i++)
        for(j=0;j<MAP_SIZE;j++)
            switch(editor[i][j])
            {
            case BASE: if(base_x==-1)base_x=i,base_y=j; break;
            case TANK: if(tank_x==-1)tank_x=i,tank_y=j; break;
            default: draw_field(i,j);break;
            }
    print_tank(UP,MAP_OFFSET_X+tank_x,MAP_OFFSET_Y+tank_y);
    print_base(MAP_OFFSET_X+base_x,MAP_OFFSET_Y+base_y);
}
void save_editor()
{
   int i,j;
   FILE * output_file = fopen(level_name, "w");
    for(i=0;i<MAP_SIZE;i++)
    {
        for(j=0;j<MAP_SIZE;j++) fprintf(output_file,"%c",editor[i][j]);
        fprintf(output_file,"\n");
    }
    fclose(output_file);
}

void change_cursor()
{
    editor_cursor_id++;
    editor_cursor_id%=4;
}

void create_base(int x, int y)
{
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            editor[i+1+x][j+1+y]=BASE;
    for(j=0;j<5;j++)
        editor[x][j+y]=BRICK;
    for(i=0;i<4;i++)
        editor[i+x][y]=editor[i+x][y+4]=BRICK;
}

void create_tank(int x, int y)
{
    int i,j;
    for (i=0;i<3;i++)
        for (j=0;j<3;j++)
            editor[i+x][j+y]=TANK;
}

void create_cursor(int x, int y)
{
    int i,j;
    for (i=0;i<=editor_cursor_size;i++)
        for(j=0;j<=editor_cursor_size;j++)
            editor[x+i][y+j]=character_map[editor_cursor_id];
    create_base(35,16);
    create_tank(36,13);
}

void move_right()
{
    if (editor_cursor_y+editor_cursor_size<MAP_SIZE-1)
    editor_cursor_y++;
}

void move_left()
{
    if (editor_cursor_y>0) editor_cursor_y--;
}

void move_up()
{
    if (editor_cursor_x>0) editor_cursor_x--;
}

void move_down()
{
    if (editor_cursor_x+editor_cursor_size<MAP_SIZE-1) editor_cursor_x++;
}

void load_editor()
{
    int i,j,c,get_me_out_of_here=0,iter;
    clock_t prev,curr;
    for (i=0;i<MAP_SIZE;i++)
        for(j=0;j<MAP_SIZE;j++) editor[i][j]=EMPTY;
    editor_cursor_x=0;
    editor_cursor_y=0;
    editor_cursor_id=0;
    create_base(35,16);
    create_tank(36,13);
    print_editor();
    attron(COLOR_PAIR(3));
    print_empty(MAP_OFFSET_X+editor_cursor_x,MAP_OFFSET_Y+editor_cursor_y);
    attroff(COLOR_PAIR(3));
    while(1)
    {
      c=getch();
      switch(c)
      {
          get_me_out_of_here=0;
          case KEY_RIGHT: move_right(); break;
          case KEY_LEFT: move_left(); break;
          case KEY_UP: move_up(); break;
          case KEY_DOWN: move_down(); break;
          case 'Q':
          case 'q': change_cursor(); break;
          case 'W':
          case 'w': change_size(); break;
          case 'E':
          case 'e': create_cursor(editor_cursor_x,editor_cursor_y); break;
          case KEY_F(2): get_me_out_of_here=1; break;
          case KEY_F(12): get_me_out_of_here=2; break;
      }
      if(get_me_out_of_here==1)
      {
          save_editor();
          break;
      }
      else if(get_me_out_of_here==2) break;
      print_editor();
      draw_cursor();
      refresh();
      prev=clock();
      iter=0;
      while(!kbhit())
      {
          curr=clock();
          if((double)(curr-prev)/CLOCKS_PER_SEC<0.1)continue;
          prev=curr;
          print_editor();
          if(iter)attron(A_BLINK);
          draw_cursor();
          if(iter)attroff(A_BLINK);
          iter=(iter+1)%2;
          refresh();
      }
    }
}

void draw_cursor()
{
    int i,j;
    for (i=0;i<=editor_cursor_size;i++)
        for(j=0;j<=editor_cursor_size;j++)
    switch(editor_cursor_id)
    {
    case 0 :
            attron(COLOR_PAIR(3));
            print_empty(MAP_OFFSET_X+editor_cursor_x+i,MAP_OFFSET_Y+editor_cursor_y+j);
            attroff(COLOR_PAIR(3));
            break;
    case 1 : print_brick(MAP_OFFSET_X+editor_cursor_x+i,MAP_OFFSET_Y+editor_cursor_y+j); break;
    case 2 : print_steel(MAP_OFFSET_X+editor_cursor_x+i,MAP_OFFSET_Y+editor_cursor_y+j); break;
    case 3 : print_water(MAP_OFFSET_X+editor_cursor_x+i,MAP_OFFSET_Y+editor_cursor_y+j); break;
    }
}



void draw_field(int x, int y)
{
    switch(editor[x][y])
    {
    case EMPTY : print_empty(MAP_OFFSET_X+x,MAP_OFFSET_Y+y); break;
    case BRICK : print_brick(MAP_OFFSET_X+x,MAP_OFFSET_Y+y); break;
    case STEEL : print_steel(MAP_OFFSET_X+x,MAP_OFFSET_Y+y); break;
    case WATER : print_water(MAP_OFFSET_X+x,MAP_OFFSET_Y+y); break;
    }
}

void change_size()
{
    editor_cursor_size++;
    editor_cursor_size%=3;
    if(editor_cursor_x+editor_cursor_size>=MAP_SIZE) editor_cursor_size=0;
    if(editor_cursor_y+editor_cursor_size>=MAP_SIZE) editor_cursor_size=0;
}

#endif // EDITOR_H_INCLUDED
