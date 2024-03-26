#include "TheGameOfPong.hpp"

int main()
{
    std::shared_ptr<Player> player1{ new Player() };
    std::shared_ptr<Player> player2{ new Player() };
    TheGameOfPong pong(player1, player2);

    return 0;
}