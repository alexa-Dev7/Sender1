
#include <iostream>
#include <uwebsockets/App.h>

using namespace std;

int main() {
    uWS::App().ws("/*", {
        .open = [](auto *ws) { cout << "User connected." << endl; },
        .message = [](auto *ws, string_view message, uWS::OpCode opCode) { ws->send(message, opCode); },
        .close = [](auto *ws, int code, string_view message) { cout << "User disconnected." << endl; }
    }).listen(9002, [](auto *token) { if (token) cout << "Server running on port 9002." << endl; });

    uWS::Loop::get()->run();
}
