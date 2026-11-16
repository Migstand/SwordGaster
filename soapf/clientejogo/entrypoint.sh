#!/bin/bash

set -e
# Remove arquivos temporários de sessões gráficas anteriores
rm -f /tmp/.X0-lock
rm -f /tmp/.X11-unix/X0

# Inicia o servidor gráfico virtual
Xvfb :0 -screen 0 1280x720x24 &

# Aguarda a inicialização do servidor gráfico
sleep 2

# Define o display gráfico utilizado pelo jogo
export DISPLAY=:0

# Compartilha a tela virtual pela porta 5900
x11vnc -display :0 -forever -shared -nopw -rfbport 5900 &

# Disponibiliza o VNC através de WebSocket
websockify --web=/usr/share/novnc 6080 localhost:5900 &

# Executa o jogo
exec ./ClienteCoordenadas