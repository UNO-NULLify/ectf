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
from Crypto.Cipher import AES
import traceback
import binascii
import os


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
        response = jsonify({'ERROR': 'Could not validate transaction'})
        response.status_code = 403
        try:
            # Check if all required arugment present
            if not request.json or not 'atm_id' in request.json or 'pin' not in request.json or 'card_id' not in request.json or 'num_bills' not in request.json or 'encrypted_response' not in request.json:
                time.sleep(2)
                return response

            # get account
            account = db.get_account(request.json['card_id'])
            if account is None:
                time.sleep(2)
                return response

            # if the account exists, make sure it has been provisioned.
            if account['AES_KEY'] is None or account['time'] is None:
                time.sleep(2)
                return response

            print account['chall']
            print request.json['encrypted_response']
            print account['AES_KEY']
            key = str(bytearray.fromhex(account['AES_KEY']))
            cipher = AES.new(key, AES.MODE_ECB, '')
            decrypted_response = cipher.decrypt(str(bytearray.fromhex(request.json['encrypted_response'])))
            print decrypted_response
            # authenticate the card
            if not db.verify_challenge(account['chall'], request.json['encrypted_response'], account['AES_KEY'], account['time']):
                time.sleep(2)
                return response

            # get atm
            atm = db.get_atm(request.json['atm_id'])
            if atm is None:
                time.sleep(2)
                return response

            # make sure hsm is in a good state
            if atm['num_bills'] == 0 or atm['AES_KEY'] is None:
                time.sleep(2)
                return response

            # make sure atm has enough bills
            if int(atm['num_bills']) < int(request.json['num_bills']):
                time.sleep(2)
                return response

            # make sure account has high enough balance
            if int(account['balance']) < int(request.json['num_bills']):
                time.sleep(2)
                return response

            # authenticate user
            if not db.verify_pin(request.json['pin'], request.json['card_id'], account):
                time.sleep(2)
                return response


            # OK To Dispense
            message  = ''

            # some math
            db.set_balance(request.json['card_id'], str(int(account['balance']) - int(request.json['num_bills'])))
            db.set_atm_num_bills(request.json['atm_id'], str(int(atm['num_bills']) - int(request.json['num_bills'])))
            dispensed_bills_old = int(atm['num_dispensed_bills'])
            dispensed_bills_now = int(request.json['num_bills']) + dispensed_bills_old
            db.set_atm_num_dispensed_bills(str(request.json['atm_id']),str(dispensed_bills_now))
            key =  str(bytearray.fromhex(atm['AES_KEY']))

            # Create a message that is "{bills_dispensed},{last_bill_to_dispense}\x00" + random bytes.
            # Do this four times since attackers could potentially bruteforce and only have to have HSM match first 4-8 bytes.
            # HSM checks to make sure each encrypted block is different, but has same first n bytes
            cipher = AES.new(key, AES.MODE_ECB, '')
            bill_message = '{0},{1}'.format(dispensed_bills_old,dispensed_bills_now) + '\x00'
            needed_bytes = 16 - len(bill_message)
            for i in range(0,4):
                message += bill_message
                message += os.urandom(needed_bytes)

            encrypted_message = cipher.encrypt(message)
            return jsonify({'OK': binascii.hexlify(encrypted_message)})

        except Exception as e:
            traceback.print_exc()

        return response

    @server.route('/balance', methods = ['POST'])
    def check_balance():
        response = jsonify({'ERROR': 'Could not validate transaction'})
        response.status_code = 403

        # make sure we have correct params
        if not request.json or not 'card_id' in request.json or not 'pin' in request.json or not 'encrypted_response' in request.json:
            time.sleep(2)
            return response

        # get account
        account = db.get_account(request.json['card_id'])
        if account is None:
            time.sleep(2)
            return response

        # authenticate card
        if not db.verify_challenge(account['chall'], request.json['encrypted_response'], account['AES_KEY'],account['time']):
            time.sleep(2)
            return jsonify({'ERROR': 'Could not validate transaction'})

        # authenticate user, return result
        if db.verify_pin(request.json['pin'], request.json['card_id'], account):
            return jsonify({'OK': str(account['balance'])})
        else:
            time.sleep(2)
            return response

    @server.route('/change_pin', methods = ['POST'])
    def change_pin():
        response = jsonify({'ERROR': 'Could not validate transaction'})
        response.status_code = 403

        # make sure we have valid params
        if not request.json or not 'card_id' in request.json or not 'pin' in request.json or not 'new_pin' in request.json or not 'encrypted_response' in request.json:
            time.sleep(2)
            return response

        # get account
        account = db.get_account(request.json['card_id'])
        if account is None:
            time.sleep(2)
            return response

        # authenticate card
        if not db.verify_challenge(account['chall'], request.json['encrypted_response'], account['AES_KEY'],account['time']):
            time.sleep(2)
            return jsonify({'ERROR': 'Could not validate transaction'})

        # authenticate user, return result
        if db.verify_pin(request.json['pin'],request.json['card_id'], account):
            db.set_pin(request.json['card_id'], request.json['new_pin'])
            return jsonify({'OKAY': 'Pin has been changed.'})
        else:
            time.sleep(2)
            return response

    @server.route('/initalize_card', methods = ['POST'])
    def new_card():
        response = jsonify({'ERROR': 'Could not validate transaction'})
        response.status_code = 403

        # make sure we have valid params
        if not request.json or not 'card_id' in request.json or not 'new_pin' in request.json or not 'key' in request.json:
            time.sleep(2)
            return response

        # make sure account exists
        account = db.get_account(request.json['card_id'])
        if account is None:
            time.sleep(2)
            return response

        # make sure account has not been initalizied already
        if account['pin'] == None and account['AES_KEY'] == None:
            success = db.initialize_card(request.json['card_id'], request.json['key'], request.json['new_pin'])
            if success:
                return jsonify({'OK': 'Card has been provisioned!'})
            else:
                time.sleep(2)
                return response
        else:
            time.sleep(2)
            return response

    @server.route('/initalize_atm', methods = ['POST'])
    def new_atm():
        response = jsonify({'ERROR': 'Could not validate transaction'})
        response.status_code = 403

        # make sure we have valid params
        if not request.json or not 'atm_id' in request.json or not 'key' in request.json or not 'num_bills' in request.json:
            time.sleep(2)
            return response

        # make sure atm exists
        atm = db.get_atm(request.json['atm_id'])
        if atm is None:
            time.sleep(2)
            return response

        # make sure atm has not been initalized altready.
        if atm['AES_KEY'] == None and atm['num_bills'] == 0 and atm['num_dispensed_bills'] == 0:
            success = db.initialize_atm(request.json['key'], request.json['num_bills'], request.json['atm_id'])
            if success:
                return jsonify({'OKAY': 'HSM has been provisioned!'})
            else:
                time.sleep(2)
                return response
        else:
            time.sleep(2)
            return response

    @server.route('/get_challenge', methods = ['POST'])
    def get_chall():
        # You would probably want to check pin in real world implementation of this, but its faster not to.

        response = jsonify({'ERROR': 'Could not validate transaction'})
        response.status_code = 403

        if not 'card_id' in request.json:
            time.sleep(2)
            return response

        # update challenge for users document, return it
        challenge = db.get_challenge(request.json['card_id'])

        if challenge != False:
            return jsonify({'OK': challenge})
        else:
            time.sleep(2)
            return jsonify({'ERROR': 'Could not validate transaction3'})

