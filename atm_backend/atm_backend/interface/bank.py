"""Backend of ATM interface for xmlrpc"""

import logging
import sys
import socket
import requests
import json


class Bank:
    """Interface for communicating with the bank

    Args:
        address (str): IP address of bank
        port (int): Port to connect to
    """

    def __init__(self, address='https://127.0.0.1/', port=1337):
        self.ip_address = address + ':' + port

    def check_balance(self, card_id, signed_message, pin):
        """Requests the balance of the account associated with the card_id

        Args:
            card_id (str): UUID of the ATM card to look up

        Returns:
            str: Balance of account on success
            bool: False on failure
        """
        logging.info('check_balance: Sending request to Bank')
        print card_id
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id,
                        'signed_message': signed_message,
                        'pin':pin
                       }

        response = requests.post(self.ip_address + 'balance', headers=headers, data=json.dumps(data_to_send))

        if response.status_code == 403:
            return 'Transaction could not be verified.'
        else:
            return response.json()['balance']
        return False

    def withdraw(self, card_id, signed_message, pin, amount):
        logging.info('withdraw: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id,
                        'signed_message': signed_message,
                        'pin':pin,
                        'amount': amount
                       }

        response = requests.post(self.ip_address + 'withdraw', headers=headers, data=json.dumps(data_to_send))

        if response.status_code == 403:
            return 'Transaction could not be verified.'
        else:
            return response.json()['bill_otps']
        return False