#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DifferentEnvironmentsExperiment 

#include <boost/test/unit_test.hpp>

#include "TheGameOfPong/PlayerHuman.hpp"
#include "TheGameOfPong/PlayerFollower.hpp"
#include "TheGameOfPong/TheGameOfPong.hpp"

#include "PlayerUCB.hpp"
#include "AgentLogger.hpp"

#define PADDLE_SIZE {10, 40}

BOOST_AUTO_TEST_CASE(experiment_DifferentEpsilon)
{
    std::shared_ptr<IPlayer> player1{ new PlayerFollower(IPlayer::Left, PADDLE_SIZE) };
    std::shared_ptr<PlayerUCB> player2{ new PlayerUCB(IPlayer::Right, PADDLE_SIZE) };
    TheGameOfPong pong(player1, player2);
    EnvironmentPong enviroment;
    TheGameOfPong::SetSpeedMultiplier(4);
    player2->CreateAgent(enviroment);
    player2->SetEpsilon(0.8);
    AgentLoggerCSV<float, IPlayer::PlayerAction> logPlayer(player2->Agent().get(), "ucb_env6");
    logPlayer(10000, 10);
    pong.Run();

    while (logPlayer.Running());
    BOOST_TEST(!logPlayer.Running());
}
