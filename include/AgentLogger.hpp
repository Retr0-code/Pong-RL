#pragma once
#include <thread>
#include <memory>
#include <fstream>
#include <functional>

#include "IAgent.hpp"
#include "TheGameOfPong/IPlayer.hpp"

template <typename T, typename ActionEnum>
class AgentLoggerCSV;

/**
 * @brief Inteface for logger classes
 * 
 * @tparam T agents calculations type
 * @tparam ActionEnum enumeration of available agent's actions
 */
template <typename T, typename ActionEnum>
class IAgentLogger
{
public:
    /**
     * @brief alias for IAgent<T, ActionEnum>*
     */
    using IAgentPtr = IAgent<T, ActionEnum>*;

    /**
     * @brief enumeration of logging export types
     */
    typedef enum
    {
        CSV,
        XML
    } ExportType;

    /**
     * @brief Construct a new IAgentLogger object
     * 
     * @param agent pointer to RL agent object
     * @param fileMark string that will be included in file name to recognize logs
     */
    IAgentLogger(IAgentPtr agent, const std::string& fileMark = "rl_agent");

    virtual ~IAgentLogger();

    /**
     * @brief Operator to start logging procedure
     * 
     * @param episodes total amount of episodes to be logged
     * @param step step with rewards will be logged
     */
    virtual void operator()(size_t episodes = 1000, size_t step = 10) = 0;

    /**
     * @brief Factory function for creating basic sub-classes loggers
     * 
     * @param type export type from enum
     * @param agent pointer to RL agent
     * @param fileMark string that will be included in file name to recognize logs
     * @return IAgentLogger<T, ActionEnum>* newly created object of logger on a heap
     */
    static IAgentLogger<T, ActionEnum>* LoggerFactory(
        ExportType type,
        IAgentPtr agent,
        const std::string& fileMark = "rl_agent"
    );

    /**
     * @brief Setter for the file mark
     * 
     * @param fileMark string that will be included in file name to recognize logs
     */
    void SetFileMark(const std::string& fileMark);

    /**
     * @brief Fuction that stops logger thread
     */
    void Stop(void);

    /**
     * @brief Function returns state of logger
     * 
     * @return true still running logging
     * @return false stoped logging
     */
    bool Running(void) const;

protected:
    /**
     * @brief Function opening file-handle
     * 
     * @param extension file extension of log
     */
    void OpenHandle(const std::string& extension);

protected:
    std::atomic_bool _run; // Variable of logger state
    IAgentPtr _agent; // Pointer to RL agent object
    std::string _fileMark; // String that will be included in file name to recognize logs
    std::jthread _logger; // Join-thread C++20 - thread for a logger
    std::ofstream _outHandle; // Output file-handle
    std::string _extension; // Output file extension
};

/**
 * @brief Agent logger class for CSV output
 * 
 * @tparam T agents calculations type
 * @tparam ActionEnum enumeration of available agent's actions
 */
template <typename T, typename ActionEnum>
class AgentLoggerCSV
    : public IAgentLogger<T, ActionEnum>
{
public:
    /**
     * @brief alias for IAgent<T, ActionEnum>*
     */
    using IAgentPtr = IAgent<T, ActionEnum>*;

    /**
     * @brief Construct a new Agent Logger CSV object
     * 
     * @param agent pointer to RL agent object
     * @param fileMark string that will be included in file name to recognize logs
     */
    AgentLoggerCSV(IAgentPtr agent, const std::string& fileMark = "rl_agent");

    virtual ~AgentLoggerCSV() = default;

    /**
     * @brief Operator to start logging procedure
     * 
     * @param episodes total amount of episodes to be logged
     * @param step step with rewards will be logged
     */
    virtual void operator()(size_t episodes = 1000, size_t step = 10) override;

private:
    void LogCSV(size_t episodes, size_t step);
};
