#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DifferentEpsilonExperiment 

#include <vector>
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
    
    EnvironmentPong5I enviroment;
    player2->CreateAgent(enviroment);

    // Epsilon = 0.1

    std::vector<std::pair<float, const char*>> testCases{
        {0.1, "ucb_eps_01"},
        {0.5, "ucb_eps_05"},
        {0.8, "ucb_eps_08"}
    };

    AgentLoggerCSV<float, IPlayer::PlayerAction> logPlayer(player2->Agent().get());
    for (auto [epsilon, fileMark] : testCases)
    {
        logPlayer.SetFileMark(fileMark);
        player2->SetEpsilon(epsilon);
        
        logPlayer(100, 1);
        pong.Run();

        while (logPlayer.Running());
        BOOST_TEST(!logPlayer.Running());
        pong.Stop();
        pong.Reset();
    }
}
