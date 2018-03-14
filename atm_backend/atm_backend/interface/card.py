from psoc import Psoc
from serial_emulator import CardEmulator
import logging
import binascii


class Card(Psoc):
    """Interface for communicating with the ATM card

    Args:
        port (str, optional): Serial port connected to an ATM card
            Default is dynamic card acquisition
        verbose (bool, optional): Whether to print debug messages
    """
    def __init__(self, port=None, verbose=False):
        super(Card, self).__init__('CARD', port, verbose)
        self.GET_UUID = 1
        self.SIGNED_RESPONSE = 2
        self.GET_PUBLIC_KEY = 3

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

    def get_encrypted_response(self, challenge):
        """Requests for a pin to be changed

        Args:
            old_pin (str): Challenge PIN
            new_pin (str): New PIN to change to

        Returns:
            bool: True if PIN was changed, False otherwise
        """
        self._sync(False)

        self._send_op(self.SIGNED_RESPONSE)
        self._vp('Getting Signed Response')

        self._push_msg(challenge)
        signed_response = self._pull_msg()

        self._vp('Card sent response %s' % signed_response)
        return signed_response

    def provision(self, uuid):
        """Attempts to provision a new ATM card

        Args:
            uuid (str): New UUID for ATM card
            pin (str): Initial PIN for ATM card

        Returns:
            bool: True if provisioning succeeded, False otherwise
        """
        self._sync(True)
        msg = self._pull_msg()
        if msg != 'P':
            self._vp('Card alredy provisioned!', logging.error)
            return False
        self._vp('Card sent provisioning message')

        self._push_msg('%s\00' % uuid)
        while self._pull_msg() != 'K':
            self._vp('Card hasn\'t accepted uuid', logging.error)
        self._vp('Card accepted uuid')

        self._push_msg(str(self.GET_PUBLIC_KEY))
        key = ''
        while len(key) != 32:
            key = self._pull_msg()
            self._vp('Card hasn\'t sent', logging.error)

        self._vp('Provisioning complete')

        return binascii.hexlify(key)

