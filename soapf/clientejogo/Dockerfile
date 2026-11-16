
FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-13 \
    g++-13 \
    cmake \
    ninja-build \
    git \
    curl \
    tar \
    libcurl4-openssl-dev \
    libpugixml-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libharfbuzz-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gcc-13
ENV CXX=g++-13

WORKDIR /app

# Baixa o código-fonte da SFML 3.1.0
RUN curl -L https://github.com/SFML/SFML/archive/refs/tags/3.1.0.tar.gz \
    -o /tmp/sfml.tar.gz \
    && tar -xzf /tmp/sfml.tar.gz -C /tmp

# Configura a compilação da SFML
RUN cmake -S /tmp/SFML-3.1.0 -B /tmp/SFML-3.1.0/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr/local \
    -DBUILD_SHARED_LIBS=OFF \
    -DSFML_BUILD_AUDIO=OFF \
    -DSFML_BUILD_NETWORK=OFF

# Compila e instala a SFML
RUN cmake --build /tmp/SFML-3.1.0/build --target install --parallel 2 \
    && rm -rf /tmp/sfml.tar.gz /tmp/SFML-3.1.0


# Define o diretório de trabalho
WORKDIR /app

# Copia os arquivos necessários para a compilação
COPY CMakeLists.txt .
COPY include/ ./include/
COPY src/ ./src/
COPY assets/ ./assets/

# Configura o projeto com CMake e Ninja
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DSFML_STATIC_LIBRARIES=ON

# Compila o cliente
RUN cmake --build build --parallel 2

# Verifica se o executável foi gerado
RUN test -x /app/build/ClienteCoordenadas

# ==========================================
# Etapa Runtime
# ==========================================

FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

# Instala as bibliotecas necessárias para executar o jogo
RUN apt-get update && apt-get install -y \
    libcurl4 \
    libpugixml1v5 \
    libxrandr2 \
    libxcursor1 \
    libxi6 \
    libx11-6 \
    libudev1 \
    libstdc++6 \
    libgcc-s1 \
    libgl1 \
    libegl1 \
    xvfb \
    x11vnc \
    novnc \
    websockify \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copia o executável da etapa de compilação
COPY --from=builder /app/build/ClienteCoordenadas .

# Copia o script de inicialização
COPY entrypoint.sh /app/entrypoint.sh

# Dá permissão de execução ao script
RUN chmod +x /app/entrypoint.sh

# Copia os recursos do jogo
COPY --from=builder /app/assets ./assets

ENTRYPOINT ["/app/entrypoint.sh"]

# Porta utilizada para acessar a interface pelo navegador
EXPOSE 6080