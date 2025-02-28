# Use an official Debian-based image  
FROM debian:latest  

# Install required dependencies  
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    libssl-dev \
    libcrypto++-dev \
    libuv1-dev \
    libwebsockets-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*  

# Set working directory  
WORKDIR /app  

# Copy project files into container  
COPY . .  

# Compile the C++ project  
RUN g++ -std=c++17 -c storage.cpp -o storage.o  
RUN g++ -std=c++17 -c encryption.cpp -o encryption.o  
RUN g++ -std=c++17 main.cpp storage.o encryption.o -o chat_server -luWS -lssl -lcrypto  

# Expose port  
EXPOSE 8080  

# Run the server  
CMD ["./chat_server"]  
