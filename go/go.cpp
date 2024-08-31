#include <cstdlib>  // 包含 rand() 和 srand()
#include <ctime>    // 包含 time()
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#define width 800
#define height 600
class dot_dot
{
    private:
        float speed = 1.0f; // 固定速度
        float now_x;
        float now_y;
        float target_x = static_cast<float>(rand() % 800);
        float target_y = static_cast<float>(rand() % 600);
        sf::Vector2f direction; // 移動方向向量
        sf::CircleShape ball;
    public:
        dot_dot(float size,float x= rand() % width, float y= rand() % height)
        //給出生點座標，生成一顆球
        {
            
            ball.setRadius(size);
            ball.setFillColor(sf::Color::Magenta);
            ball.setPosition(x, y); // 設定小球初始位置，使其在視窗中心附近
            updatePosit(x, y);
            moveRandomly();
            direction = sf::Vector2f(static_cast<float>(rand() % 10), static_cast<float>(rand() % 10)); // 初始方向，可以設置為任意值
        }
        void display(sf::RenderWindow& window)
        {
            window.draw(ball);
        }
        void updatePosit(float x, float y)
        {
            now_x = x;
            now_y = y;
        }
        void moveRandomly()
        {
            // 如果到達目標，則生成一個新目標
            if ((int)target_x == (int)now_x && (int)target_y == (int)now_y)
            {
                target_x = static_cast<float>(rand() % 800);
                target_y = static_cast<float>(rand() % 600);
            }

            // 計算從當前位置到目標位置的向量
            float dx = target_x - now_x;
            float dy = target_y - now_y;

            // 計算距離
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance != 0) // 防止除以零
            {
                dx = (dx / distance) * speed;
                dy = (dy / distance) * speed;
            }

            // 更新當前位置
            if (std::abs(dx) >= std::abs(target_x - now_x)) now_x = target_x; else now_x += dx;
            if (std::abs(dy) >= std::abs(target_y - now_y)) now_y = target_y; else now_y += dy;

            // 設置小球的新位置
            ball.setPosition(now_x, now_y);

            std::cout << now_x << "," << now_y << "\n";
        }
        void move() { move(speed); }
        void move(float step)//移動 step 步，碰到邊緣就反彈
        {
            // 更新位置
            now_x += direction.x * step;
            now_y += direction.y * step;

            // 檢查是否碰到邊緣，若碰到則反彈
            if (now_x <= 0 || now_x >= width - ball.getRadius() * 2)
            {
                direction.x = -direction.x;//變號，方向相反
                direction.x += (static_cast<float>(rand() % 20 - 10) / 100.0f);
                moveRandomly();
            }

            if (now_y <= 0 || now_y >= height - ball.getRadius() * 2)
            {
                direction.y = -direction.y;//變號，方向相反
                direction.y += (static_cast<float>(rand() % 20 - 10) / 100.0f);
                moveRandomly();

            }
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            direction.x = (direction.x / length) ;
            direction.y = (direction.y / length);
            // 更新小球位置
            ball.setPosition(now_x, now_y);
        }
};
int main()
{

    srand(static_cast<unsigned>(time(NULL)));
    // 創建一個 800x600 的視窗
    sf::RenderWindow window(sf::VideoMode(width,height), "NGGYU");
    
    std::vector<dot_dot> ball_group1;
    for (int i = 0; i < 30; ++i)
    {
        ball_group1.emplace_back(10.f); // 每顆球的半徑為 10
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // 關閉視窗的事件處理
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear(sf::Color::Yellow); // 設定背景顏色為黑色
        //window.display();
        // 移動每顆球
        for (auto& ball : ball_group1)
        {
            ball.move(0.1); // 每顆球移動
        }

        window.clear(sf::Color::Yellow);
        for (auto& ball : ball_group1)
        {
            ball.display(window);
        }
        window.display();
    }

    return 0;
}
