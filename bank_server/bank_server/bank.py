""" Bank Server
This module implements a bank server interface

The module exposes the following functions through a socket listening on
host 127.0.0.1 and port 1337

------------------------------------------------------------------------
function:
    withdraw

args:
    param1 (string - max length 1024): card_id of account to withdraw from
    param2 (string - max length ): amount to withdraw

returns:
    string: 'OKAY' on Success, 'ERROR' otherwise.
------------------------------------------------------------------------
function:
    check_balance

args:
    param1 (string - max length 1024): card_id of account to check balance

returns:
    String: Account balance on Success, empty string otherwise.
------------------------------------------------------------------------
"""

import uuid
import time
from flask import Flask, jsonify, request
from bank_server import DB


class Bank(object):
    """
    request is OPCODE followed by fields separated by spaces, terminated with a
    newline

    response is either OKAY or ERROR followed by newline. OKAY may have one or
    more fields separated by spaces. ERROR may have any amount of text between
    the space and the newline.

    "withdraw <acct> <amount>\n"
    "OKAY\n"
    "balance <acct>\n"
    "OKAY <amount>\n"
    "ERROR\n"
    """
    server = Flask(__name__)
    global db
    db = DB()

    def __init__(self, config,ready_event):
        super(Bank, self).__init__()
        self.bank_host = config['bank']['host']
        self.bank_port = int(config['bank']['port'])
        ready_event.set()
        self.server.run(host='0.0.0.0', port=1337,ssl_context=('/data/certs/cert.pem','/data/certs/key.pem'))
        self.server.run(debug=True)

    @server.route('/withdraw', methods = ['POST'])
    def withdraw():
        try:
            amount = int(request.json['amount'])
        except ValueError:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})

        atm = db.get_atm(int(request.json['atm_id']))
        if atm is None:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})

        num_bills = db.get_atm_num_bills(int(request.json['atm_id']))
        if num_bills is None:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})

        if num_bills < amount:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})

        balance = db.get_balance(request.json['card_id'])
        if balance is None:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})

        final_amount = balance - amount
        if final_amount >= 0 and db.verify_pin(request.json['pin'],request.json['card_id']):
            db.set_balance(request.json['card_id'], final_amount)
            db.set_atm_num_bills(int(request.json['atm_id']), num_bills - amount)
            return jsonify({'OKAY': str(request.json['atm_id'])})
        else:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})

    @server.route('/balance', methods = ['POST'])
    def check_balance():
        if not request.json or not 'card_id' in request.json or not 'pin' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})

        account = db.get_account(request.json['card_id'])
        if account is None:
            return jsonify({'ERROR': 'Could not validate transaction'})

        if db.verify_pin(request.json['pin'], request.json['card_id'], account):
            return jsonify({'OK': str(account['balance'])})
        else:
            return jsonify({'ERROR': 'Could not validate transaction'})


    @server.route('/change_pin', methods = ['POST'])
    def change_pin():
        if not request.json or not 'card_id' in request.json or not 'pin' in request.json or not 'new_pin' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})

        account = db.get_account(request.json['card_id'])
        if account is None:
            return jsonify({'ERROR': 'Could not validate transaction'})

        if db.verify_pin(request.json['pin'],request.json['card_id'], account):
            db.set_pin(request.json['card_id'], request.json['new_pin'])
            return jsonify({'OKAY': 'Pin has been changed.'})
        else:
            return jsonify({'ERROR': 'Could not validate transaction'})

    @server.route('/initalize_card', methods = ['POST'])
    def new_card():
        if not request.json or not 'card_id' in request.json or not 'new_pin' in request.json or not 'key' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})

        account = db.get_account(request.json['card_id'])
        if account is None:
            return jsonify({'ERROR': 'Could not validate transaction'})

        if account['pin'] == None and account['key'] == None:
            success = db.initialize_card(request.json['card_id'], request.json['key'], request.json['new_pin'])
            if success:
                return jsonify({'OKAY': 'Card has been provisioned!'})
            else:
                return jsonify({'ERROR': 'Could not validate transaction'})
        return jsonify({'ERROR': 'Could not validate transaction'})

    @server.route('/get_challenge', methods = ['POST'])
    def get_chall():
        if not request.json:
            return jsonify({'ERROR': 'Could not validate transaction1'})
        if not 'card_id' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction2'})
        challenge = db.get_challenge(request.json['card_id'])
        if challenge != False:
            return jsonify({'OK': challenge})
        else:
            return jsonify({'ERROR': 'Could not validate transaction3'})


    @server.route('/test')
    def test():
        return "Flask is working."

