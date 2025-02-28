#include <bits/stdc++.h>
#include <uwebsockets/App.h>
#include "storage.h"
#include "encryption.h"

using namespace std;

unordered_map<string, uWS::WebSocket<false, true>*> activeUsers;

void onMessage(uWS::WebSocket<false, true> *ws, string_view message, uWS::OpCode opCode) {
    json msgData = json::parse(message);
    string type = msgData["type"];

    if (type == "register") {
        string username = msgData["username"];
        string password = msgData["password"];
        if (registerUser(username, password)) {
            ws->send(R"({"status": "success", "message": "Registered successfully"})", opCode);
        } else {
            ws->send(R"({"status": "error", "message": "User already exists"})", opCode);
        }
    } 
    else if (type == "login") {
        string username = msgData["username"];
        string password = msgData["password"];
        if (authenticateUser(username, password)) {
            activeUsers[username] = ws;
            ws->send(R"({"status": "success", "message": "Login successful"})", opCode);
        } else {
            ws->send(R"({"status": "error", "message": "Invalid credentials"})", opCode);
        }
    } 
    else if (type == "message") {
        string sender = msgData["sender"];
        string receiver = msgData["receiver"];
        string messageText = encryptMessage(msgData["message"]);

        saveMessage(sender, receiver, messageText);

        if (activeUsers.find(receiver) != activeUsers.end()) {
            json response = {{"type", "message"}, {"sender", sender}, {"message", messageText}};
            activeUsers[receiver]->send(response.dump(), opCode);
        }
    }
}

int main() {
    uWS::App().ws<false>("/*", {
        .message = onMessage
    }).listen(9001, [](auto *listen_socket) {
        if (listen_socket) {
            cout << "Server running on port 9001" << endl;
        }
    }).run();

    return 0;
}
