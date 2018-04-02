
docker run -it --rm  \
           -e TOKEN=$1 -e SCRIPT=/var/TelegramBot/main.py \
           -v `pwd`:/var/TelegramBot \
           telegram_bot /bin/bash
