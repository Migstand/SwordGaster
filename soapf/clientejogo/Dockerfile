# --- ESTÁGIO 1: Ambiente de Compilação (C++17 + SFML 3 + cURL + pugixml) ---
FROM gcc:13 AS builder

# Instala ferramentas de build, dependências do projeto e dependências gráficas da SFML
RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    git \
    libcurl4-openssl-dev \
    libpugixml-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Monta o endereço sem cortes
ENV REPO_HOST="github.com"
ENV REPO_PATH="SFML/SFML/archive/refs/tags/3.0.0.tar.gz"

# Baixa, compila e instala a SFML 3.0.0
RUN curl -L "https://${REPO_HOST}/${REPO_PATH}" -o /tmp/sfml.tar.gz \
    && tar -xzf /tmp/sfml.tar.gz -C /tmp \
    && cmake -S /tmp/SFML-3.0.0 -B /tmp/SFML-3.0.0/build -G Ninja \
       -DBUILD_SHARED_LIBS=OFF \
       -DSFML_BUILD_AUDIO=OFF \
       -DSFML_BUILD_NETWORK=OFF \
    && cmake --build /tmp/SFML-3.0.0/build --target install \
    && rm -rf /tmp/sfml.tar.gz /tmp/SFML-3.0.0



WORKDIR /app

# Copia os arquivos do seu projeto
COPY CMakeLists.txt .
COPY include/ ./include/
COPY src/ ./src/
COPY assets/ ./assets/

# Compila o ClienteCoordenadas em C++17
# RUN cmake -B build -G Ninja \
#     && cmake --build build

# --- ESTÁGIO 2: Ambiente Final de Execução ---
FROM debian:bookworm-slim

# Instala apenas as bibliotecas de execução necessárias (X11, OpenGL, cURL, pugixml)
RUN apt-get update && apt-get install -y \
    libcurl4 \
    libpugixml1v5 \
    libxrandr2 \
    libxcursor1 \
    libxi6 \
    libudev1 \
    libfreetype6 \
    libgl1 \
    libegl1 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copia o executável gerado e a pasta de imagens (assets)
# COPY --from=builder /app/build/ClienteCoordenadas ./ClienteCoordenadas
# COPY --from=builder /app/assets ./assets

CMD ["./ClienteCoordenadas"]
