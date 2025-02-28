#include "storage.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <bcrypt.h>

using json = nlohmann::json;

json loadJSON(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) return json::array();
    
    json data;
    file >> data;
    return data;
}

void saveJSON(const string &filename, const json &data) {
    ofstream file(filename);
    file << data.dump(4);
}

bool registerUser(const string &username, const string &password) {
    json users = loadJSON("users.json");
    
    for (const auto &user : users) {
        if (user["username"] == username) return false;
    }

    string hashed = bcrypt::generateHash(password);
    users.push_back({{"username", username}, {"password", hashed}});
    saveJSON("users.json", users);
    return true;
}

bool authenticateUser(const string &username, const string &password) {
    json users = loadJSON("users.json");

    for (const auto &user : users) {
        if (user["username"] == username && bcrypt::validatePassword(password, user["password"])) {
            return true;
        }
    }
    return false;
}

void saveMessage(const string &sender, const string &receiver, const string &message) {
    json messages = loadJSON("messages.json");
    messages.push_back({{"sender", sender}, {"receiver", receiver}, {"message", message}});
    saveJSON("messages.json", messages);
}
