FROM debian:latest

RUN apt update && apt install -y build-essential cmake libssl-dev wget

RUN wget https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.25.0.tar.gz \
    && tar -xvzf v20.25.0.tar.gz && cd uWebSockets-20.25.0 \
    && make && make install

WORKDIR /app

COPY . .

RUN g++ main.cpp storage.cpp encryption.cpp -o chat_server -luWS -lssl -lcrypto -std=c++17

CMD ["./chat_server"]
