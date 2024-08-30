#include <cstdlib>  // 包含 rand() 和 srand()
#include <ctime>    // 包含 time()
#include <SFML/Graphics.hpp>
#define width 800
#define height 600
class dot_dot
{
    private:
        float now_x;
        float now_y;
        sf::CircleShape ball;
    public:
        dot_dot(float x, float y,float size)
        //給出生點座標，生成一顆球
        {
            ball.setRadius(size);
            ball.setFillColor(sf::Color::Magenta);
            ball.setPosition(x, y); // 設定小球初始位置，使其在視窗中心附近
            updatePosit(x, y);
            moveRandomly();
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
            // 生成一個新的隨機位置
            float new_x = static_cast<float>(rand() % width);
            float new_y = static_cast<float>(rand() % height);

            // 更新小球位置
            ball.setPosition(new_x, new_y);
        }
};
int main()
{
    // 創建一個 800x600 的視窗
    sf::RenderWindow window(sf::VideoMode(width,height), "NGGYU");
    srand(time(NULL));
    
    dot_dot script1(375.f, 275.f,20);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // 關閉視窗的事件處理
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Yellow); // 設定背景顏色為黑色
        script1.display(window);
        window.display();

    }

    return 0;
}
