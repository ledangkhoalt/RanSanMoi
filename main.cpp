#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int N = 30, M = 20; //Số ô ngang , dọc
int size = 16; // kích thước pixel mỗi ô
int w = size * N; //ngang
int h = size * M; // dọc

int dir, num = 4; // hướng, num= độ dài con rắn
struct Snake
{
    int x,y;
} s[100];
struct Fruct
{
    int x,y;
} f;
void Tick()
{
    for(int i=num; i > 0; --i) //nhấc dồn đuôi rắn tiến tới 1 ô
    {
        s[i].x =s[i-1].x;
        s[i].y= s[i-1].y;
    }
    //điều chỉnh đầu rắn
    if(dir == 0) s[0].y += 1; //đầu hướng lên
    if(dir == 1) s[0].x -= 1; // đầu hướng trái
    if(dir == 2) s[0].x += 1; // đầu hướng phải
    if(dir == 3) s[0].y -= 1; // cắm đầu xuống

    //vị trí đầu rắn trùng với cục thức ăn thì rắn dài thêm 1, đổi vị trí ngẫu nhiên cục mồi sang chổ khác
    if((s[0].x==f.x) && s[0].y==f.y)
    {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
        printf("Diem hien tai la: %d\n",num);
    }
    //cho đi xuyên lề
    if(s[0].x >= N)
        s[0].x = 0;

    if(s[0].x < 0)
        s[0].x = N;

    if(s[0].y >= M)
        s[0].y = 0;

    if(s[0].y < 0)
        s[0].y = M;

    //kiem tra rắn tự cắt đuôi mình
    for(int i=1; i<num; i++)
    {
        if((s[0].x == s[i].x) && (s[0].y == s[i].y))
        {
             num = i;
             printf("Can trung duoi. Diem hien tai la: %d\n",num);
        }
    }




}
int main()
{
    srand(time(0));
	RenderWindow window(VideoMode(w, h), "Ran san moi");
	Texture t1, t2;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);

	Clock clock;
	float timer=0, delay=0.1;

    f.x = 11;
    f.y = 12;
	while (window.isOpen())
	{
	    float time = clock.getElapsedTime().asSeconds();
	    clock.restart();
	    timer+=time;

        delay = 0.1 - 0.001 * num;
        if (delay < 0.01) delay = 0.01;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
        // kiểm tra nhấn phím
		if(Keyboard::isKeyPressed(Keyboard::Left)) if(dir != 2)  dir = 1;
        if(Keyboard::isKeyPressed(Keyboard::Right))if(dir != 1) dir = 2;
 		if(Keyboard::isKeyPressed(Keyboard::Up))   if(dir != 0) dir = 3;
        if(Keyboard::isKeyPressed(Keyboard::Down)) if(dir != 3) dir = 0;
		if(timer > delay)
        {
            timer=0;
            Tick(); //update vị trí mới cho con rắn

        }


		window.clear();

        // vẽ các ô trống ngang dọc
		for( int i=0; i< N; i++)
			for (int j = 0; j < M; j++)
			{
				sprite1.setPosition(i * size, j * size);
				window.draw(sprite1);
			}
		//vẽ con rắn
        for(int i=0; i<num;i++)
        {
            sprite2.setPosition(s[i].x*size,s[i].y*size);
            window.draw(sprite2);
        }


        sprite2.setPosition(f.x*size,f.y*size);
        window.draw(sprite2);

		window.display();
	}

	return 0;
}
