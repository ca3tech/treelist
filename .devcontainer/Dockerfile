ARG VARIANT="11"
FROM debian:${VARIANT}

WORKDIR /root

RUN ln -fs /usr/share/zoneinfo/America/Chicago /etc/localtime \
 && apt update \
 && DEBIAN_FRONTEND=noninteractive apt install -y software-properties-common \
 && apt update \
 && apt install -y build-essential cmake gdb git \
 && apt-get autoremove -y \
 && apt-get clean -y \
 && rm -rf /var/lib/apt/lists/*
