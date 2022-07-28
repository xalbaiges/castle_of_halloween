/*
 * Compilation :
 *               gcc -lm -lgdi32  main.c -o main
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <windows.h>

#define WINDOW_WIDTH 500
#define TILE_SIZE 50
#define MAP_SIZE 10



int map[10][10] = {
                 {1,1,1,1,1,1,1,1,1,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,1,0,0,0,1},
                 {1,0,0,0,0,1,0,0,0,1},
                 {1,0,0,1,1,1,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,0,0,1},
                 {1,1,1,1,1,1,1,1,1,1}
                };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int game();/*
void my_delay(int delay_time_in_milis);
long long get_current_time_in_ms();
void draw_player_orientation(SDL_Renderer *renderer, int ox, int oy, int giro);
void draw_map(SDL_Renderer *renderer);
void move_player(int speed, SDL_Rect *rect, int giro,int avance );
int is_wall(int posX, int posY);
void raycasting(SDL_Renderer *renderer,int ox, int oy, int giro);

double rinc = ((2*M_PI)/360); // 1 deg === ((2*M_PI)/360) rad */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow) {
    
    MSG  msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Rectangle";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Rectangle",
          WS_OVERLAPPEDWINDOW | WS_VISIBLE,
          100, 100, 250, 200, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}/*WinMain*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    HDC hdc;
    PAINTSTRUCT ps;

    switch(msg) {
    
        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);
            Rectangle(hdc, 50, 50, 200, 100);
            EndPaint(hwnd, &ps);
            break;

        case WM_DESTROY:
 
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}/*WndProc*/    


/*
int main( int argc, char **argv )
{



  game();  

 return 0;
}/*eo_main*/

int game() {/*
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init( SDL_INIT_VIDEO );
    SDL_CreateWindowAndRenderer( WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer );
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );

    SDL_Rect rect;
    rect.x = 230;
    rect.y = 200;
    rect.w = 4;
    rect.h = 4;
    int giro = 0; // angulo de giro del jugador
    int v_giro = 1; // velocidad de giro
    int avance = 0; // indica si avanza(1), retrocede(-1) o parado(0)
    int speed = 3;   // velocidad de avance

    int quit = 0;
    /* game loop *//*
    while( !quit ) 
    {
      long long init_msec = get_current_time_in_ms();
      const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
      SDL_PollEvent( &event);
      if(  event.type == SDL_QUIT) {
        quit = 1;
      }
      if(  event.type == SDL_KEYDOWN && keyboard_state_array[SDL_SCANCODE_LEFT] ) {
        giro -= v_giro;
        giro = giro % 360;
      }
      if(  event.type == SDL_KEYDOWN && keyboard_state_array[SDL_SCANCODE_RIGHT] ) {
        giro += v_giro;
        giro = giro % 360;
      }
      if(  event.type == SDL_KEYDOWN && keyboard_state_array[SDL_SCANCODE_UP] ) {
        avance = 1;
      } 
      if(  event.type == SDL_KEYDOWN && keyboard_state_array[SDL_SCANCODE_DOWN] ){
        avance = -1;
      }
      if( event.type == SDL_KEYUP && 
          !keyboard_state_array[SDL_SCANCODE_LEFT] && 
          !keyboard_state_array[SDL_SCANCODE_RIGHT] ) {
        avance = 0;
      }
      // Actualizamos posicion
      move_player(speed, &rect, giro, avance );
      

      SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
      SDL_RenderClear( renderer );
      draw_map(renderer);
      raycasting(renderer,rect.x+2, rect.y+2, giro);
      SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
      SDL_RenderFillRect( renderer, &rect );
      draw_player_orientation(renderer, rect.x+2, rect.y+2, giro);
      SDL_RenderPresent( renderer ); 

      // keep the frame rate 30 frames / 1 sec => 0,033sec o 33 ms
      while(1) {
       long long msec = get_current_time_in_ms();
       if(msec-init_msec > 33) break;
      }/*eo_while*/ 
    /*}/*eo_while*/


    /*SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();  */

 return 0;
}/*eo_game*/

/*
void draw_map(SDL_Renderer *renderer) 
{
  SDL_Rect tile;
  tile.x = 0;
  tile.y = 0;
  tile.w = TILE_SIZE;
  tile.h = TILE_SIZE;


  for(int i=0; i<MAP_SIZE; ++i) {
    tile.x = 0;
    for(int j=0; j<MAP_SIZE; ++j) {
      switch(map[i][j]) {
        case 1: /*wall*//*
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                break;
        case 0: /*floor*/
                /*SDL_SetRenderDrawColor( renderer, 125, 125, 125, 255 );
                break;
      } /*eo_switch*/
     /* SDL_RenderFillRect( renderer, &tile );
      tile.x += TILE_SIZE; // idea optimitzacio si TILE SIZE es multiple de 2 es pot multiplicar utilitzant operador << 
    }/*eo_for*/
   /* tile.y += TILE_SIZE;  
  }/*eo_for*/

/*}/*draw_map*/

/*
void raycasting(SDL_Renderer *renderer,int ox, int oy, int giro) 
{
  //int rx = 0; // coordinadas del punto final
  //int ry = 0; // del punto final de la linea
  //int L = 910; // Longitud de la linea
 
  /*int indx = 0;*/
  /*double rinc = ((2*M_PI)/360); // 1 deg === ((2*M_PI)/360) rad
  double rad = giro * rinc; // pasamos de grados a radianes    
  /*  
  rx = round((L*(cos(rad))+ox)); // calculo de las coordinadas del punto final
  ry = round((L*(sin(rad))+oy)); // de la linea
  */

  // Calculo de la colision con tiles Horizontales
  /*int ty = oy / TILE_SIZE;
  int y2 = ty * TILE_SIZE;
  int x2 = ((y2-oy)/tan(rad))+ox;
  int dx = x2 - ox;

  while(ty>0) {
   // if( is_wall(x2,y2-1)) {
   //   break;
   // }/*eo_if*/

    //x2 = x2 + dx; 
   /* --ty;
  }/*eo_while*/

 /* SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
  SDL_RenderDrawLine( renderer, ox,oy, x2, y2 );
}/*eo_ray_casting*/

/*void draw_player_orientation(SDL_Renderer *renderer, int ox, int oy, int giro)
{
  int rx = 0; // coordinadas del punto final
  int ry = 0; // del punto final de la linea
  int L = 90; // Longitud de la linea
 
  int indx = 0;
  double rinc = ((2*M_PI)/360); // 1 deg === ((2*M_PI)/360) rad
  double rad = giro * rinc; // pasamos de grados a radianes    
    
  rx = round((L*(cos(rad))+ox)); // calculo de las coordinadas del punto final
  ry = round((L*(sin(rad))+oy)); // de la linea

  SDL_RenderDrawLine( renderer, ox,oy, rx,ry );
}/*turn_arround*/    

/*
  return 1 if wall
  return 0 if floor
*/
/*int is_wall(int posX, int posY) 
{
 posX +=2;
 posY +=2; 
 int j = posX / TILE_SIZE ;
 int i = posY / TILE_SIZE ;

 if(map[i][j] == 1) {
  return 1;
 }
 return 0;

}/* is_wall */

/*void move_player(int speed, SDL_Rect *rect, int giro,int avance  )
{ 
  if(avance == 0) return ;

  double rad = giro * rinc; // pasamos de grados a radianes

  int IncrY = speed * sin(rad);
  int IncrX = speed * cos(rad);
  int posY = rect->y + (IncrY * avance);
  int posX = rect->x + (IncrX * avance);
  
  if(!is_wall(posX,posY)) {
    rect->y = posY;
    rect->x = posX;
  }/*eo_if*/
/*}/*move_player*/

/*void my_delay(int delay_time_in_milis)
{
  int c,d;
  
  int f = delay_time_in_milis * 9;
  for(c=1;c<f;c++){
    for(d=1;d<32767;d++){}
  }

}/* my_delay */

/*long long get_current_time_in_ms()
{
  struct timeval te;
  gettimeofday(&te, NULL);
  long long milliseconds = te.tv_sec * 1000LL + te.tv_usec/1000;

  return milliseconds;
}/* get_current_time_in_ms */