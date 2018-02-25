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
    global db = DB()

    def __init__(self, config):
        super(Bank, self).__init__()
        self.bank_host = config['bank']['host']
        self.bank_port = int(config['bank']['port'])
        self.server.run(host='0.0.0.0', port=1337,ssl_context=('/data/certs/cert.pem','/data/certs/key.pem'))
        self.server.run(debug=True)

    @server.route('/withdraw')
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

    @server.route('/balance')
    def check_balance():
        if not request.json or not 'card_id' in request.json or not 'pin' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})
        try:
            uuid.UUID(str(request.json['card_id']))
        except ValueError:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})
        balance = db.get_balance(request.json['card_id'])
        if balance is None:
            time.sleep(5)
            return jsonify({'ERROR': 'Could not validate transaction'})
        if db.verify_pin(request.json['pin'],request.json['card_id']):
            return jsonify({'OKAY': str(balance)})
        else:
            return jsonify({'ERROR': 'Could not validate transaction'})


    @server.route('/change_pin')
    def change_pin():
        if not request.json or not 'card_id' in request.json or not 'pin' in request.json or not 'new_pin' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})
        if db.verify_pin(request.json['pin'],request.json['card_id']):
            db.set_pin(request.json['card_id'], request.json['new_pin'])
            return jsonify({'OKAY': 'Pin has been changed.'})

    @server.route('/initalize_card')
    def new_card():
        if not request.json or not 'card_id' in request.json or not 'new_pin' in request.json or not 'key' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})
        if db.get_account(request.json['card_id']) is None or not db.empty_pin(request.json['card_id']):
            return jsonify({'ERROR': 'Could not validate transaction'})
        else:
            db.set_pin(request.json['card_id'], request.json['pin'])
            db.set_key(request.json['card_id'], request.json['key'])
            return jsonify({'OKAY': 'Pin has been changed.'})

    @server.route('/get_challenge')
    def get_chall():
        if not request.json or not 'card_id' in request.json:
            return jsonify({'ERROR': 'Could not validate transaction'})
        if db.get_account(request.json['card_id']) is None:
            return jsonify({'ERROR': 'Could not validate transaction'})
        else:
            db.set_key(request.json['card_id'], request.json['key'])
            return db.get_challenge(request.json['card_id'])


    @server.route('/test')
    def test():
        return "Flask is working."

