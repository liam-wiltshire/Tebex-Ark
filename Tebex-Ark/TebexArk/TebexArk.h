#pragma once

#ifdef TEBEX_ARK
#include <API/ARK/Ark.h>
#else
#include <API/Atlas/Atlas.h>
#endif

#include <set>

#include "json.hpp"

#include "WebstoreInfo.h"
#include "Config.h"

using json = nlohmann::json;
using Config = tebexConfig::Config;

class TebexPushCommands;

struct PendingCommand {
	int pluginPlayerId;
	uint64 playerId;
};

inline TArray<PendingCommand> pendingCommands;

// Store executed commands id, used to solve multiple executions problem
inline std::set<int> executedCommandsId;

class TebexArk {
public:
	TebexArk();

	void logWarning(const FString& message) const;
	void logError(const FString& message) const;
	void setWebstore(const json& json);
	WebstoreInfo getWebstore() const;
	Config getConfig() const;
	json getJson() const;
	FString GetText(const std::string& str, const std::string& default_message = "No message") const;
	void setConfig(const std::string& key, const std::string& value);
	void readConfig(const std::string& address);
	std::string getSecret(const json& config, const std::string& address) const;
	void setNextCheck(int newValue);
	bool doCheck();
	bool loadServer();
	bool parsePushCommands(const std::string& body);
	std::string getConfigPath() const;
	std::string getGameType() const;
	time_t getLastCalled() const;
	int getNextCheck() const;

	static FString buildCommand(std::string command, std::string playerName, std::string playerId, std::string UE4ID);
	static int GetTotalInventoryItems(AShooterPlayerController* player);
	bool ConsoleCommand(APlayerController* player, FString command, bool checkInventory);

private:
	static void ReplaceStringInPlace(std::string& subject, const std::string& search, const std::string& replace);
	void saveConfig();

	std::shared_ptr<spdlog::logger> logger_;
	WebstoreInfo webstoreInfo_;
	Config config_;
	json json_config_;
	int nextCheck_ = 15 * 60;
	time_t lastCalled_ = time(nullptr);
	bool serverLoaded_ = false;

	std::unique_ptr<TebexPushCommands> pushCommands_;
};
