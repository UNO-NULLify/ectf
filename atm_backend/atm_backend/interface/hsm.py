from psoc import Psoc
import struct
from serial_emulator import HSMEmulator
import logging
import time
import binascii
import traceback



class HSM(Psoc):
    """Interface for communicating with the HSM

    Args:
        port (str, optional): Serial port connected to HSM
        verbose (bool, optional): Whether to print debug messages

    Note:
        Calls to get_uuid and withdraw must be alternated to remain in sync
        with the HSM
    """

    def __init__(self, port=None, verbose=False, dummy=False):
        super(HSM, self).__init__('HSM', port, verbose)
        self._vp('Please connect HSM to continue.')
        while not self.connected and not dummy:
            time.sleep(2)
        self._vp('Initialized')
        self.GET_UUID = 1
        self.WITHDRAW = 2


    def _send_op(self, op):
        """Sends requested operation to ATM card

        Args:
            op (int): Operation to send from [self.CHECK_BAL, self.WITHDRAW,
                self.CHANGE_PIN]
        """
        self._vp('Sending op %d' % op)
        self._push_msg(str(op))

        while self._pull_msg() != 'K':
            self._vp('Card hasn\'t received op', logging.error)
        self._vp('Card received op')

    def get_uuid(self):
        """Requests for a pin to be changed

        Args:
            old_pin (str): Challenge PIN
            new_pin (str): New PIN to change to

        Returns:
            bool: True if PIN was changed, False otherwise
        """
        self._sync(False)
        self._send_op(self.GET_UUID)
        self._vp('Getting Pin')
        uuid = self._pull_msg()
        self._vp('Card sent response %s' % uuid)
        return uuid

    def withdraw(self, message):
        """Attempts to withdraw bills from the HSM

        Args:
            uuid (str): Challenge UUID of HSM
            amount (int): Number of bills to withdraw from HSM

        Returns:
            list of str: List of dispensed bills on success
            str: 'Insufficient funds' if the UUID was incorrect
                 'Not enough bills in ATM' if HSM doesn't have enough bills
                    to complete request
        """
        self._sync(False)
        self._send_op(self.WITHDRAW)
        try:
            self._push_msg(message)

            while self._pull_msg() != 'K':
                self._vp('Card hasn\'t accepted uuid', logging.error)

            self._vp('a')
            bills = []
            bill = self._pull_msg()
            self._vp('b')
            while bill != 'K':
                self._vp('c')
                bills.append(bill)
                self._vp('1 - Received bill ' + bill)
                bill = self._pull_msg()
                self._vp('2- Received bill ' + bill)

        except:
            self._vp(traceback.print_exc())

        return bills

    def provision(self, uuid, bills):
        """Attempts to provision HSM

        Args:
            uuid (str): UUID for HSM
            bills (list of str): List of bills to store in HSM

        Returns:
            bool: True if HSM provisioned, False otherwise
        """
        self._sync(True)

        msg = self._pull_msg()
        if msg != 'P':
            self._vp('HSM already provisioned!', logging.error)
            return False
        self._vp('HSM sent provisioning message')

        self._push_msg('%s\00' % uuid)
        while self._pull_msg() != 'K':
            self._vp('Card hasn\'t accepted uuid', logging.error)

        self._push_msg(struct.pack('B', len(bills)))
        while self._pull_msg() != 'K':
            self._vp('HSM hasn\'t accepted number of bills', logging.error)
        self._vp('HSM accepted number of bills')

        key = ''
        while len(key) != 32:
            key = self._pull_msg()
            self._vp('Card hasn\'t sent', logging.error)

        for bill in bills:
            msg = bill.strip()
            self._vp('Sending bill \'%s\'' % msg.encode('hex'))
            self._push_msg(msg)

            while self._pull_msg() != 'K':
                self._vp('HSM hasn\'t accepted bill', logging.error)
            self._vp('HSM accepted bill')

        self._vp('All bills sent!')



        self._vp('Provisioning complete')

        return binascii.hexlify(key)
