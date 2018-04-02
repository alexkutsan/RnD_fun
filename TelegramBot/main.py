import argparse
from telegram.ext import Updater
from telegram.ext import CommandHandler

import logging

import sys
parser = argparse.ArgumentParser(description='Start Hello World bot')
parser.add_argument('token', type=str,
                    help='token of hello world bot')
logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO)

args = parser.parse_args()

def user_signal_handelr(signum, frame):
    print(signum, frame)
    


updater = Updater(token=args.token, user_sig_handler=user_signal_handelr)
print(updater.bot.get_me())
dispatcher = updater.dispatcher


def start(bot, update):
    bot.send_message(chat_id=update.message.chat_id, text="Echo : " + update.message.text)

def stop(bot, update):
    bot.send_message(chat_id=update.message.chat_id, text="Bye bye")
    print ("exit")
    updater.stop()    
    print ("stopped")
    assert(false)

dispatcher.add_handler(CommandHandler('start', start))
dispatcher.add_handler(CommandHandler('stop', stop))
updater.start_polling()