#include <stdio.h>
#include <graphics.h> 
#include <time.h>

IMAGE bk;
IMAGE plane1;
IMAGE plane2;
IMAGE image_bull[2];
IMAGE image_enermy[2][2];

enum My
{
    WIDTH = 480,
    HEIGHT = 850,
    BULLET_NUM = 15,
    ENERMY_NUM=10,
    BIG,
    SMALL
};
struct Plane {
    int x;
    int y;
    bool live;
    int width;
    int height;
    int hp;
    int type;
} 
player,bull[BULLET_NUM],enermy[ENERMY_NUM];


void loadImg() {
    loadimage(&bk, "C:/Users/10343/Desktop/dog code/images/background.jpg");
    loadimage(&plane1, "C:\\Users\\10343\\Desktop\\dog code\\plane match\\fuckkk\\images\\me1.jpg");
    loadimage(&plane2, "C:\\Users\\10343\\Desktop\\dog code\\plane match\\fuckkk\\images\\me2.jpg");
    loadimage(&image_bull[0], "C:\\Users\\10343\\Desktop\\dog code\\images\\bullet1.jpg");
    loadimage(&image_bull[1], "C:\\Users\\10343\\Desktop\\dog code\\images\\bullet1.jpg");
    loadimage(&image_enermy[0][0], "C:\\Users\\10343\\Desktop\\dog code\\plane match\\fuckkk\\images\\enemy1.jpg");
    loadimage(&image_enermy[0][1], "C:\\Users\\10343\\Desktop\\dog code\\plane match\\fuckkk\\images\\enemy2.jpg");
    loadimage(&image_enermy[1][0], "C:\\Users\\10343\\Desktop\\dog code\\plane match\\fuckkk\\images\\enemy3.jpg");
    loadimage(&image_enermy[1][1], "C:\\Users\\10343\\Desktop\\dog code\\plane match\\fuckkk\\images\\enemy3_n1.jpg");
    
}


void enermyHP(int i) {

    if (rand() % 8)
    {
        enermy[i].type = BIG;
        enermy[i].hp = 3;
        enermy[i].width = 104;
        enermy[i].height = 148;
    }
    else {
        enermy[i].type = SMALL;
        enermy[i].hp = 1;
        enermy[i].width = 52;
        enermy[i].height = 39;
    }
}
void gameInit() {
    player.x = WIDTH / 2;
    player.y = HEIGHT / 2;
    player.live = true;

    for (int i = 0; i < BULLET_NUM; i++)
    {
        bull[i].x = 0;
        bull[i].y = 0;
        bull[i].live = false;
    }

    for (int i = 0; i < ENERMY_NUM; i++) {
        enermy[i].live = false;
        enermyHP(i);
    }
    //enermy[0].live = false;
    //enermy[0].y = 10;
    //enermy[0].x = 10;
    
}



    void gamedriving()
    {
        loadImg();
        putimage(0, 0, &bk);
        putimage(player.x, player.y, &plane1, NOTSRCERASE);
        putimage(player.x, player.y, &plane2, SRCINVERT);


        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bull[i].live)
                putimage(bull[i].x, bull[i].y, &image_bull[0], NOTSRCERASE);
                putimage(bull[i].x, bull[i].y, &image_bull[1], SRCINVERT);
        }

        for (int i = 0; i < ENERMY_NUM; i++)
        {
            if (enermy[i].live)
            {
                if (enermy[i].type == BIG) {
                    putimage(enermy[i].x, enermy[i].y, &image_enermy[1][0], NOTSRCERASE);
                    putimage(enermy[i].x, enermy[i].y, &image_enermy[1][1], SRCINVERT);
                }
                else {
                    putimage(enermy[i].x, enermy[i].y, &image_enermy[0][0], NOTSRCERASE);
                    putimage(enermy[i].x, enermy[i].y, &image_enermy[0][1], SRCINVERT);
                }
                }
            }
        }
    

   

    
    

    void createBullet()
    {
        for (int i = 0; i < BULLET_NUM; i++) {
            if (!bull[i].live)
            {
                bull[i].x = player.x + 60;
                bull[i].y = player.y;
                bull[i].live = true;

                break;
            }
        }
    }

    void BulletMove() {

        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (bull[i].live)
            { 
                bull[i].y -= 1;
                if (bull[i].y < 0)
                {
                    bull[i].live = false;
                }
            }

        }
  

}
   
    void createEnermy() {
        for (int i = 0; i < ENERMY_NUM; i++) {
            if (!enermy[i].live) {
                enermy[i].live = true;
                enermy[i].x = rand() % (WIDTH - 60);
                enermy[i].y = 0;
                break;
            }
          }
    }

    void enermyMove(int speed) {
        for (int i = 0; i < BULLET_NUM; i++)
        {
            if (enermy[i].live) {
                enermy[i].y += speed;
                if (enermy[i].y > HEIGHT) {
                    enermy[i].live = false;
                }
            }
        }

    }
    void playerMove(int speed)
    {
        if (GetAsyncKeyState(VK_UP)|| GetAsyncKeyState('W'))
        {
            if (player.y > 0) {

                player.y -= speed;
            }

        }
    
    if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
    {
        if(player.y*2<HEIGHT){
            player.y += speed;
        }
        
    }
    if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
    {
        if (player.x +60> 0){

            player.x -= speed;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
    {
        if (player.x + 60 < WIDTH) {

            player.x += speed;
        }

    }
        static DWORD t1 = 0, t2 = 0;
        if (GetAsyncKeyState(VK_SPACE) && t2 - t1 > 50) 
        {
            createBullet();
            t1 = t2;
         }
        t2 = GetTickCount();
        
    }
    int i;
    void playPlance() {
        for (int i = 0; i < ENERMY_NUM; i++) {
            if (!enermy[i].live) {
                continue;
            }
            for (int k = 0; k < ENERMY_NUM; k++) {
                if (bull[k].x > enermy[i].x && bull[k].x < enermy[i].x + enermy[i].width 
                    && bull[k].y > enermy[i].y 
                    && bull[k].y <enermy[i].y + enermy[i].height) {
                    bull[i].live = false;
                    enermy[i].hp--;


                }
            }

            if (enermy[i].hp <= 0) {
                enermy[i].live = false;
            }
        }


     }
    bool Time(int ms, int id) {

        static DWORD t[10];
        if (clock()-t[id]>ms)
        {
            t[id] = clock();
            return true;
        }

        return false;

    }

    
int main()
{
    initgraph(WIDTH, 850, 1);
    gameInit();

    BeginBatchDraw();
    while (1)
    {
        gamedriving();
        FlushBatchDraw();
        playerMove(3);
        BulletMove();

        if (Time(500, 0))
        {
            createEnermy();
        }
        


        enermyMove(1);
        playPlance();
    }
     
    return 0;
}