#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

#define PADDLE_SIZE {5, 30}

int main(void)
{
    std::shared_ptr<IPlayer> player1{ new PlayerHuman(IPlayer::Left, PADDLE_SIZE) };
    std::shared_ptr<IPlayer> player2{ new PlayerHuman(IPlayer::Left, PADDLE_SIZE) };
    TheGameOfPong pong(player1, player2);

    return 0;
}