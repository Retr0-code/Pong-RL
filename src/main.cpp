#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

int main(void)
{
    std::shared_ptr<IPlayer> player1{ new PlayerHuman()};
    std::shared_ptr<IPlayer> player2{ new PlayerHuman };
    TheGameOfPong pong(player1, player2);

    return 0;
}