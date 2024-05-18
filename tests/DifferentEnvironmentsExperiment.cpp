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
    TheGameOfPong::SetSpeedMultiplier(4);

    EnvironmentPong6I enviroment6I;
    player2->CreateAgent(enviroment6I);
    player2->SetEpsilon(0.8);
    AgentLoggerCSV<float, IPlayer::PlayerAction> logPlayer(player2->Agent().get(), "ucb_env6");
    logPlayer(10000, 10);
    pong.Run();

    while (logPlayer.Running());
    BOOST_TEST(!logPlayer.Running());

    pong.Stop();
    pong.Reset();

    EnvironmentPong3I enviroment3I;
    player2->CreateAgent(enviroment3I);
    player2->SetEpsilon(0.8);
    logPlayer.SetFileMark("ucb_env3");
    logPlayer(10000, 10);
    pong.Run();
    
    while (logPlayer.Running());
    BOOST_TEST(!logPlayer.Running());
    
    pong.Stop();
}
